#include "env.h"
#include "read.h"
#include "eval.h"
#include "write.h"
#include "primitive_proc.h"

// *******************LOOP*******************

int main() {
    Expression *expr = nullptr;

    std::cout << "=== Scheme Interpreter === ^C to quit\n";

    Reader r = Reader(); // allow repl to read from stdin
    Writer w = Writer(); // allow repl to print to stdout
    
    while (true) {
        std::cout << "> ";
        r.fillBuff();
        expr = r.readIn();
        if (expr == nullptr) break;
        // w.write(expr); *w.out << '\n'; // Uncomment to see input from file
        w.write(eval(expr, theEnv::global_env()));
        *w.out << '\n';
        r.emptyBuff();
    }
    
    std::cout << "Goodbye\n";
    return 0;
}
