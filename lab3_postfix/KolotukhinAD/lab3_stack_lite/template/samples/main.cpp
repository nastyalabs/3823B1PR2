#include "algexp.h"
#include "iostream"
int main() {
    algexp expr("(1+2*3)*(8/1-3)");
    // algexp expr("");
    int result = expr.solveIt();
    string a = expr.getExpr();
    cout << a << "    " << result;
}
