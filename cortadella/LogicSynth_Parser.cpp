#include <cassert>
#include <iostream>
#include <string>
#include "LogicSynth.h"

using namespace std;

/// String that stores the abc command.
/// The function Init_Abc() must be invoked before any logic synthesis activity.
/// If initialzed and the string is empty, it means that abc cannot be found.
std::string Abc_cmd = "";
bool Abc_initialized = false;

bool Init_Abc()
{
    if (Abc_initialized) {
        if (Abc_cmd.empty()) {
            cerr << "Abc cannot be found." << endl;
            return false;
        }
        return true;
    }

    Abc_initialized = true;

    int ret = system("abc -q quit");
    if (ret == 0) {
        Abc_cmd = "abc";
        return true;
    }

    ret = system("berkeley-abc -q quit");
    if (ret == 0) {
        Abc_cmd = "berkeley-abc";
        return true;
    }

    Abc_cmd = "";
    return false;
}

// This file implements a recursive descent parser for Verilog expressions.
// The main function receives a string, a BDD manager and a map from identifiers
// to variable indices. The function returns a BDD and (possibly) and error.
//
// The expressions accept Verilog identifiers (start with '_' or alphabetic char,
// followed by alphanumeric, '_' or '$' chars.
//
// Bitwise and logical operators are accepted (!, ~, &, &&, |, ||, ^, ^~, ~^).
//
// The only constants accepted are: 0, 1, 1'b0 and 1'b1.

// Tokens generated for lexical analysis.
enum token_type {TOK_ERR, TOK_ID, TOK_CONST, TOK_NOT,
                 TOK_AND, TOK_OR, TOK_XOR, TOK_XNOR,
                 TOK_LPAR, TOK_RPAR, TOK_COND, TOK_COLON,
                 TOK_EOF
                };

// Structure to represent tokens and their values. When TOK_ERR is delivered,
// the error message is stored in the value.
struct token {
    token_type type;
    string value;
    token(token_type t, const string& v = "") : type(t), value(v) {}
    token(int k) : type(TOK_CONST), value(to_string(k)) {}
};

// Structure to propagate global information across the parser.
struct bddExprInfo {
    const string& expr; // Original expression
    int p;              // Pointer to the next token
    int prev;           // Pointer to the previous token
    Cudd* mgr;          // BDD manager
    const FactoredForm::name2id& vars; // Map of identifiers to variable indices
    int lastIndex;      // Last used index for the variables.
    string& error;

    bddExprInfo(Cudd* mgr, const string& e, const FactoredForm::name2id& vars, string& error) :
        expr(e), p(0), prev(0), mgr(mgr), vars(vars), error(error) {
        lastIndex = -1;
        for (auto it: vars) lastIndex = max(lastIndex, it.second);
        error = "";
    }
};

static bool eof(const bddExprInfo& I)
{
    return I.p >= I.expr.size();
}

static char current(const bddExprInfo& I)
{
    return not eof(I) ? I.expr[I.p] : 0;
}

static bool hasError(const bddExprInfo& I)
{
    return not I.error.empty();
}

static bool isIdentifierFirstChar(char c)
{
    return isalpha(c) or c == '_';
}

static bool isIdentifierChar(char c)
{
    return isalnum(c) or c == '_' or c == '$';
}

static token getIdentifier(bddExprInfo& I)
{
    while (isIdentifierChar(current(I))) ++(I.p);
    token t(TOK_ID, I.expr.substr(I.prev, I.p-I.prev));
    return t;
}

static token getConstant(bddExprInfo& I)
{
    // Case 0
    if (I.expr[I.p] == '0') {
        ++(I.p);
        return token(0);
    }

    if (I.expr[I.p] != '1') {
        return token(TOK_ERR, "Incorrect constant at location " + to_string(I.p));
    }

    // We may expect 1'b0 or 1'b1
    ++I.p;
    if (I.p >= I.expr.size() or I.expr[I.p] != '\'') return token(1);
    ++I.p;
    if (I.p >= I.expr.size() or I.expr[I.p] != 'b') return token(TOK_ERR, "Incorrect constant at location " + to_string(I.p-2));
    ++I.p;
    if (I.p >= I.expr.size() or (I.expr[I.p] != '0' and I.expr[I.p] != '1')) return token(TOK_ERR, "Incorrect constant at location " + to_string(I.p-3));
    ++I.p;
    return token(I.expr[I.p - 1] - '0');
}

static token nextToken(bddExprInfo& I)
{

    while (isspace(current(I))) ++(I.p);
    I.prev = I.p;
    if (eof(I)) return token(TOK_EOF);
    char c = current(I);
    if (isIdentifierFirstChar(c)) return getIdentifier(I);
    if (isdigit(c)) return getConstant(I);

    switch (c) {
    case '(':
        ++(I.p);
        return token(TOK_LPAR);
    case ')':
        ++(I.p);
        return token(TOK_RPAR);
    case '|':
        ++(I.p);
        if (current(I) == '|') ++(I.p);
        return token(TOK_OR);
    case '&':
        ++(I.p);
        if (current(I) == '&') ++(I.p);
        return token(TOK_AND);
    case '!':
        ++(I.p);
        return token(TOK_NOT);
    case '~':
        ++(I.p);
        if (current(I) != '^') return token(TOK_NOT);
        ++(I.p);
        return token(TOK_XNOR);
    case '^':
        ++(I.p);
        if (current(I) != '~') return token(TOK_XOR);
        ++(I.p);
        return token(TOK_XNOR);
    case '?':
        ++(I.p);
        return token(TOK_COND);
    case ':':
        ++(I.p);
        return token(TOK_COLON);
    default:
        return token(TOK_ERR, "Unexpected character at location " + to_string(I.p));
    }
}

static void unreadToken(bddExprInfo& I)
{
    I.p = I.prev;
}

static FactoredForm evalVerilogExpression(bddExprInfo& I);

static FactoredForm evalAtom(bddExprInfo& I)
{
    token t = nextToken(I);
    if (t.type == TOK_CONST) {
        return FactoredForm(I.mgr, t.value[0] == '1');
    }

    if (t.type == TOK_LPAR) {
        FactoredForm f = evalVerilogExpression(I);
        if (hasError(I)) return FactoredForm();
        if (nextToken(I).type != TOK_RPAR) {
            I.error = "Missing ) in expression";
            return FactoredForm();
        }
        return f;
    }

    // Identifier
    if (t.type != TOK_ID) {
        I.error = "Incorrect atom in expression";
        return FactoredForm();
    }

    auto it = I.vars.find(t.value);
    if (it != I.vars.end()) return FactoredForm(I.mgr, it->second, true);

    I.error = "Identifier " + t.value + " not found";
    return FactoredForm();
}

static FactoredForm evalFactor(bddExprInfo& I)
{
    token_type t = nextToken(I).type;
    if (t == TOK_ERR) return FactoredForm();
    if (t == TOK_NOT) {
        FactoredForm ff = evalFactor(I);
        ff.Complement();
        return ff;
    }
    unreadToken(I);
    return evalAtom(I);
}

static FactoredForm evalXterm(bddExprInfo& I)
{
    FactoredForm f = evalFactor(I);
    if (hasError(I)) return FactoredForm();

    while (nextToken(I).type == TOK_AND) {
        FactoredForm g = evalFactor(I);
        if (hasError(I)) break;
        f = FactoredForm(FactoredForm::AND, f, g);
    }

    if (hasError(I)) return FactoredForm();
    unreadToken(I);
    return f;
}

static FactoredForm evalTerm(bddExprInfo& I)
{
    FactoredForm f = evalXterm(I);
    if (hasError(I)) return FactoredForm();

    token_type t = nextToken(I).type;
    while (t == TOK_XOR or t == TOK_XNOR) {
        FactoredForm g = evalXterm(I);
        if (hasError(I)) break;
        f = FactoredForm(FactoredForm::XOR, f, g);
        if (t == TOK_XNOR) f.Complement();
        t = nextToken(I).type;
    }

    if (hasError(I)) return FactoredForm();
    unreadToken(I);
    return f;
}

static FactoredForm evalExpression(bddExprInfo& I)
{
    FactoredForm f = evalTerm(I);
    if (hasError(I)) return FactoredForm();

    while (nextToken(I).type == TOK_OR) {
        FactoredForm g = evalTerm(I);
        if (hasError(I)) break;
        f = FactoredForm(FactoredForm::OR, f, g);
    }

    if (hasError(I)) return FactoredForm();
    unreadToken(I);
    return f;
}

static FactoredForm evalVerilogExpression(bddExprInfo& I)
{
    FactoredForm cond = evalExpression(I);
    if (hasError(I)) return FactoredForm();

    token t = nextToken(I);
    if (t.type != TOK_COND) {
        unreadToken(I);
        return cond;
    }

    // We have a ternary expression
    FactoredForm c_true = evalExpression(I);
    if (hasError(I)) return FactoredForm();

    t = nextToken(I);
    if (t.type != TOK_COLON) {
        I.error = "':' not found for ternary expression";
        return FactoredForm();
    }

    FactoredForm c_false = evalExpression(I);
    if (hasError(I)) return FactoredForm();

    return FactoredForm(cond, c_true, c_false);
}

FactoredForm::FactoredForm(Cudd* mgr, const string& expr, const name2id& name2id,
                           string& error) : mgr(mgr)
{
    bddExprInfo I(mgr, expr, name2id, error);
    init(evalVerilogExpression(I));

    token t = nextToken(I);
    if (t.type != TOK_EOF) {
        error = "Unexpected token at the end of the expression (" + t.value + ")";
        init();
    }

    Normalize();
}
