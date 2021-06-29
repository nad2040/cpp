#include "env.h"
#include "read.h"
#include "eval.h"
#include "write.h"
#include "primitive_proc.h"

using namespace std;

// *******************LOOP*******************

ifstream _ifs;
ofstream _ofs;
ifstream _ifs_2; // for scheme input filestream
ofstream _ofs_2; // for scheme output filestream

int main() {
    Expression *expr = nullptr;

    cout << "=== Scheme in C++ === ^C to quit\n";

    //ifstream ifs("scm_files/testing_input.scm");
    //ofstream ofs("a.txt");
    //Reader r = Reader("scm_files/b.scm"); // allow repl to read from a file
    Reader r = Reader(); // allow repl to read from stdin
    Writer w = Writer(); // allow repl to print to stdout
    
    while (true) {
        cout << "> ";
        r.fillBuff();
        expr = r.readIn();
        if (expr == nullptr) break;
        w.write(expr); *w.out << '\n'; // Uncomment to see input from file
        w.write(eval(expr, theEnv::global_env()));
        *w.out << '\n';
        //r.emptyBuff();
    }
    
    cout << "Goodbye\n";
    return 0;
}
