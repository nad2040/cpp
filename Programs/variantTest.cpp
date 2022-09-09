#include <fstream>
#include <iostream>
#include <string>
#include <variant>

bool isInitial(char c);
bool isSym(std::string &str);

struct Boolean {
  bool b;
};

class Expression;
enum AtomType {
  UNK,
  BOOL,
  CHAR,
  NUM,
  STR,
  SYMBOL,
  PRIM_PROC,
  COMP_PROC,
  INPUT,
  OUTPUT,
  EOF_OBJECT
};
class Atom {
public:
  typedef Expression *(*fn)(Expression *);
  struct Compound {
    Expression *params;
    Expression *body;
    Expression *env;
    Compound() : params(nullptr), body(nullptr), env(nullptr) {}
    Compound(Expression *p, Expression *b, Expression *e)
        : params(p), body(b), env(e) {}
  };

  AtomType atomType_;
  std::variant<bool, long, char, std::string, fn, Compound, std::ifstream *,
               std::ofstream *, Expression *>
      value_;

  Atom() : atomType_(UNK), value_((std::string) "") {}

  Atom(bool b) : atomType_(BOOL) { value_ = b; }
  Atom(char c) : atomType_(CHAR), value_(c) {}
  Atom(long num) : atomType_(NUM), value_(num) {}
  Atom(std::string str) {
    if (str[0] == '"') {
      atomType_ = STR;
      str.erase(0, 1);
      value_ = str;
    } else if (isSym(str)) {
      atomType_ = SYMBOL;
      value_ = str;
    } else {
      atomType_ = UNK;
      value_ = str;
    } // for debugging purposes
  }
  Atom(Expression *(*fnptr)(Expression *args))
      : atomType_(PRIM_PROC), value_(fnptr) {}
  Atom(Expression *params, Expression *body, Expression *env)
      : atomType_(COMP_PROC), value_(Compound(params, body, env)) {}
  Atom(std::ifstream &in) : atomType_(INPUT), value_(&in) {}
  Atom(std::ofstream &out) : atomType_(OUTPUT), value_(&out) {}

  void write() {
    switch (atomType_) {
    case BOOL:
      std::cout << (std::get<bool>(value_) == false ? "#f" : "#t");
      return; // special case deal with later
    case CHAR:
      std::cout << "#\\" << std::get<char>(value_);
      return;
    case NUM:
      std::cout << std::get<long>(value_);
      return;
    // case STR: std::cout << (std::get<bool>(value_) == false) ? "#f" : "#t";
    // // special case deal with later
    case SYMBOL:
      std::cout << std::get<std::string>(value_);
      return;
    case PRIM_PROC:
      std::cout << "#<primitive-procedure>";
      return;
    case COMP_PROC:
      std::cout << "#<compound-procedure>";
      return;
    case UNK:
      std::cout << "unknown type";
      return;
    default:
      std::cout << "unsupported type";
      return;
    }
  }
};

enum ExpressionType { ATOM, LIST };
class Expression {
public:
  struct List {
    Expression *car;
    Expression *cdr;
  };

  Atom atom;
  List *list;
  ExpressionType exprType_;

  Expression() : atom(), list(), exprType_(LIST) {}
  Expression(Atom atom_) : atom(atom_), list(nullptr), exprType_(ATOM) {}
  Expression(List *list_) : atom(), list(list_), exprType_(LIST) {}
};

int main() {
  Expression *expr = new Expression(Atom(false));
  expr->atom.write();
}
