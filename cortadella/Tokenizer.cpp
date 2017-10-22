#include "Tokenizer.h"
#include <cassert>
#include <sstream>

Tokenizer::Tokenizer(const string& filename) : input(filename.empty() ? cin :f)
{
    pref_comment = '#';
    linenumber = 0;
    from_cin = filename.empty();
    error = false;
    validLastLine = false;

    if (not from_cin) {
        f.open(filename);
        if (not f.is_open()) {
            setErrorMessage("Error: Could not open file " + filename);
            error = true;
        }
    }
}

Tokenizer::~Tokenizer()
{
    if (not from_cin and f.is_open()) {
        f.close();
    }
}

/**
 * @brief Adds spaces around a char in a string
 * @param s The string.
 * @param c The char that must be isolated.
 */
static void isolateChar(std::string& s, char c)
{
    size_t pos = 0;
    string replace( {' ', c, ' '});
    while((pos = s.find(c, pos)) != std::string::npos) {
        s.replace(pos, 1, replace);
        pos += 3;
    }
}

/**
 * Returns a vector of tokens (strings)
 * @param str is a string representing the contents of a line.
 * @param charTokens String representing a set of chars that must be isolated as tokens.
 * @return a vector of strings.
 */
static vecTokens tokenize(string &str, const string& charTokens)
{
    for (char c: charTokens) isolateChar(str, c);
    stringstream s(str);
    string token;
    vecTokens tokens;
    while (s >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

vecTokens Tokenizer::Getline(const string& charTokens)
{

    // Read lines until there is one with some token
    while (not Eof() or validLastLine) {
        string line;
        if (validLastLine) {
            line = lastLine;
            validLastLine = false;
        } else {
            getline(input, line);
            if (input.fail()) {
                error = true;
                return vecTokens ();
            }
            linenumber++;
            lastLine = line;
        }

        vecTokens tokens = tokenize(line, charTokens);

        // Remove comments
        for (uint i = 0; i < tokens.size(); i++) {
            int n = tokens[i].find(pref_comment);
            if (n == 0) {
                tokens.erase(tokens.begin() + i, tokens.end());
            } else if (n > 0) {
                tokens[i].resize(n);
                tokens.erase(tokens.begin() + i + 1, tokens.end());
            }
        }

        if (tokens.size() > 0) {
            return tokens;
        }
    }

    // No tokens: returns an empty vector
    return vecTokens ();
}

void Tokenizer::Ungetline()
{
    assert(not validLastLine);
    validLastLine = true;
}

bool Tokenizer::Eof() const
{
    if (from_cin) {
        return cin.eof();
    } else {
        return f.eof();
    }
}

void Tokenizer::Close()
{
    if (not from_cin) {
        f.close();
    }
}

bool Tokenizer::Error() const
{
    return error;
}

/**
 * Indicates whether the string is an identifier.
 * @param s string.
 * @return true if it is an identifier.
 */
bool Tokenizer::IsIdentifier(const string &s)
{
    if (s.length() == 0) {
        return false;
    }
    if (not isalpha(s[0]) and s[0] != '_') {
        return false;
    }
    for (uint i = 1; i < s.length(); ++i)
        if (not isalnum(s[i]) and s[i] != '_') {
            return false;
        }
    return true;
}


unsigned int Tokenizer::GetNumber(const string &s)
{
    if (s.length() == 0 or s.find_first_not_of("0123456789") != string::npos) {
        return -1;
    }
    return atoi(s.c_str());
}
