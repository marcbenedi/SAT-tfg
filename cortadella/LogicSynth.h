#ifndef __LOGICSYNTH__
#define __LOGICSYNTH__


#include <bitset>
#include <map>
#include <string>
#include <vector>
#include "cuddObj.hh"

extern "C" {
    namespace Espresso
    {
#include "espresso.h"
#undef bool
    }

}

/// String that stores the abc command.
/// The function Init_Abc() must be invoked before any logic synthesis activity.
/// If initialzed and the string is empty, it means that abc cannot be found.
extern std::string Abc_cmd;
extern bool Abc_initialized;

typedef int varID;                      /// Type to represent indices of variables (from 0 to ...)
const int MAX_LOGIC_VARS = 64;          /// Maximum number of variables for logic synthesis
const varID invalidVar = -1;            /// Invalid variable ID

/// Type to represent sets of variables
typedef std::bitset<MAX_LOGIC_VARS>  varSet;

/// Type to represent sets of literals
typedef struct {
    varSet positive; // Positive literals
    varSet negative; // Negative literals
} literalSet;

/// Type to represent an incompletely specified function (ON/DC set)
typedef struct {
    BDD on; // On set
    BDD dc; // Don't care set
} ISF;

typedef enum {
    MIN_EXACT,         // exact minimization (QM)
    MIN_ESPRESSO,      // espresso algorithm
    MIN_FAST_ESPRESSO, // espresso with single expand
    MIN_ISOP           // BDD-based ISOP
} minMethod;

/**
 * @brief Reduces DC set to minimize the support of the function.
 * @param mgr The BDD manager.
 * @param isf The ISF to be minimized.
 * @param var Try to avoid this variable in the support (if not essential).
 * @param reductions A string that representes the sequence of reductions that must
 * be applied. Each char of the string represents a reduction and can have the
 * following values: 'v' indicates that variable var must be eliminated, 'V' indicates
 * that all variables must be reduced, 'p' indicates that positive literals must be reduced,
 * 'n' indicates that negative literals must be reduced.
 * @return True if changes have been produced, and false otherwise.
 */
bool reduceSupport(Cudd& mgr, ISF& isf, BDD var, const std::string& reductions = "vVpn");

/**
 * @brief Boolean minimization with espresso.
 * @param mgr The BDD manager.
 * @param on The on-set.
 * @param dc The dc-set.
 * @param method The method for boolean minimization.
 * @param is_complement If asserted, the obtained cover corresponds to
 * the complemented function.
 * @return The cover.
 */
Espresso::set_family_t *call_espresso(Cudd& mgr, const BDD& on, const BDD& dc, minMethod method, bool& is_complement);

/**
 * @brief Transforms a BDD into a cover.
 * @param mgr The BDD manager.
 * @param f The function to be transformed.
 * @return A cover representing f.
 */
Espresso::set_family_t* bdd2cover(Cudd& mgr, const BDD& f);

/**
 * @brief Transforms a cover into a BDD.
 * @param mgr The BDD manager.
 * @param C The cover.
 * @return The BDD representing cover C.
 */
BDD cover2bdd(Cudd& mgr, const Espresso::set_family_t* C);

/**
 * @brief Generic function for Boolean minimization of ISFs.
 * @param mgr BDD manager.
 * @param on The On set of the ISF.
 * @param dc The DC set of the ISF.
 * @param method Minimization method.
 * @return The BDD of the simplified function.
 */
BDD bddSimplify(Cudd& mgr, const BDD& on, const BDD& dc, minMethod method);

/**
 * @brief Reports information about essential literals of an ISF.
 * @param mgr The BDD manager.
 * @param f The On set of the ISF.
 * @param dc The DC set of the ISF.
 * @return The set of essential literals (positive and negative)
 */
literalSet essentialLiterals(Cudd& mgr, const BDD& f, const BDD& dc);

/**
 * @brief Initializes espresso to minimize functions.
 * @param nvars Number of variables of the cubes.
 */
void init_espresso(int nvars);

/**
 * @brief Frees the resources used by espresso.
 */
void close_espresso();

/**
 * @brief Initializes Abc (checks whether the binary is available).
 * @return True if found, and false otherwise.
 */
bool Init_Abc();

/**
 * @class FactoredForm
 * @author Jordi Cortadella
 * @date 06/04/17
 * @file LogicSynth_Utils.h
 * @brief A class to represent factored forms obtained from parsing Verilog expressions.
 */
class FactoredForm
{
public:

    typedef std::map<std::string, varID> name2id;   // Map from strings to identifiers
    typedef std::vector<std::string> id2name;       // Vector to get names from identifiers

    // Node type of the factored form
    enum ffType {
        CONSTANT, LEAF, AND, OR, XOR, MUX, UNKNOWN
    };

    /**
     * @brief Default constructor (usually representing an error)
     */
    FactoredForm() {
        init();
    }

    /**
     * @brief Main constructor from a Verilog expression.
     * @param mgr The BDD manager.
     * @param expr A Boolean expression (Verilog syntax).
     * @param var2id A map from names to variable identifiers.
     * @param error A string to return an error message (empty if no error).
     */
    FactoredForm(Cudd* mgr, const std::string& expr, const name2id& var2id,
                 std::string& error);

    /**
     * @brief Creates a factored form from a BDD. The variable id's correspond
     * to the variable indices in the BDD.
     * @note The constructior calls abc.
     */
    FactoredForm(Cudd* mgr, const BDD& f);

    /**
     * @brief Default constructor (zero function).
     * @brief mgr The BDD manager.
     * @param value Initial value of the form (false -> 0, true -> 1).
     */
    FactoredForm(Cudd* mgr, bool value) :
        mgr(mgr), f(value ? (*mgr).bddOne() : (*mgr).bddZero()), type(CONSTANT), complement(not value), id(invalidVar), nlits(0), nxor(0), nmux(0) {}

    /**
     * @brief Constructs the factored form for a leaf (variable).
     * @param mgr The BDD manager.
     * @param id The id of the variable.
     * @param positive Indicates whether the variable should be negated.
     */
    FactoredForm(Cudd* mgr, varID id, bool positive) :
        mgr(mgr), f((*mgr).bddVar(id)), type(LEAF), complement(not positive), id(id), nlits(1), nxor(0), nmux(0) {}

    /**
     * @brief Constructs a FF as a conjuntion or disjunction of FFs.
     * @param binop Type of operator (must be AND, OR or XOR).
     * @param left The left operand.
     * @param right The right operand.
     */
    FactoredForm(ffType binop, const FactoredForm& left, const FactoredForm& right);

    /**
     * @brief Constructs a FF from a ternary operator (cond ? cond_true : cond_false)
     * @param cond The condition.
     * @param cond_true The function when cond is true.
     * @param cond_false The function with cons is false.
     */
    FactoredForm(const FactoredForm& cond, const FactoredForm& cond_true, const FactoredForm& cond_false);

    /**
     * @return The BDD associated to the factored form.
     */
    BDD getBDD() const {
        return f;
    }

    /**
     * @return The number of literals of the factored form
     */
    int numLiterals() const {
        return nlits;
    }

    /**
     * @return The number of XOR nodes of the factored form
     */
    int numXor() const {
        return nxor;
    }

    /**
     * @return The number of muxes of the factored form
     */
    int numMuxes() const {
        return nmux;
    }

    /**
     * @brief Generates a string with the factored form.
     * @param varnames The vector to obtain variable names from identifiers.
     * @param level specifies the level of the tree. It should be called with level=0 externally.
     * @return The string.
     */
    std::string write(const id2name& varnames, int level = 0);

    /**
     * @brief Complements the factored form.
     */
    void Complement();

private:
    Cudd* mgr;                      // BDD manager
    BDD f;                          // Global boolean function of the factored form
    ffType type;                    // Node type of the ff
    std::vector<FactoredForm> kids; // List of kids (empty if leaf)
    bool complement;                // is it complemented? (true for 0, false for 1)
    varID id;                       // Variable identifier (if leaf)
    int nlits;                      // Total number of literals
    int nxor;                       // Number of XOR nodes
    int nmux;                       // Number of MUX nodes

    /**
     * @brief Initializes a factored form
     */
    void init();

    /**
     * @brief Copies the contents of another ff.
     * @param ff The other factored form.
     */
    void init(const FactoredForm& ff);

    /**
     * @brief Normalizes the factored form (removal of constants,
     * compaction of nodes of the same type, pushing complements to the leaves).
     * @param positive The sign of the root node. The goal is to push all the
     * inverters to the leaves.
     */
    void Normalize(bool positive = true);

    /**
     * @brief Prints the structure of the factored form.
     * @param varnames The vector to obtain variable names from identifiers.
     * @param level The level of indentation.
     */
    void print(const id2name& varnames, int level = 0) const;
};

/**
 * @class EssentialLits
 * @author Jordi Cortadella
 * @brief Class to store information about essential literals and variables of a node
 */
class EssentialLits
{
public:
    /**
     * @brief Default constructor.
     */
    EssentialLits() {}

    /**
     * @brief Calculates the essential literals of f with dc as don't care set.
     * @param mgr BDD manager.
     * @param f The function.
     * @param dc The DC set.
     */
    EssentialLits(Cudd& mgr, const BDD& f, const BDD& dc);

    /**
     * @brief Returns the number of essential positive literals.
     */
    int numPositive() const {
        return nPos;
    }

    /**
     * @brief Returns the number of essential negative literals.
     */
    int numNegative() const {
        return nNeg;
    }

    /**
     * @brief Returns the number of essential variables.
     */
    int numEssentialVars() const {
        return nEssential;
    }

    /**
     * @brief Returns the number of essential literals.
     */
    int numEssentialLits() const {
        return nPos + nNeg;
    }

private:
    literalSet literals;
    varSet allVars;
    int nPos;
    int nNeg;
    int nEssential;
};

#endif // __LOGICSYNTH__
