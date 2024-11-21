#include "algexp.h"
#include "iostream"
int main() {
    // algexp expr("( 1 + 2 * 3 ) * ( 8 / 1 - 3 )");
    /*1 2 3 * + 8 1 / 3 - *     result = 35*/

    // algexp expr("( 10 + 11 ) * 2 + 3 / 100");
    /*10 11 + 2 * 3 100 / +     result = 42.03*/

    // algexp expr{"2 + sin ( 15 + 15 ) / cos ( 0 )"};
    /*2 15 15 + sin 0 cos / +    result = 2.5*/

    algexp expr("2 + sin ( 15 + tan ( 34.5 ) ) * cos ( 15 + 15 * sqrt ( 15 * cos ( 10 ) ) )"); 
    /*2 15 34.5 tan + sin 15 15 15 10 cos * sqrt * + cos * +     result = 2.08062*/
    
    // algexp expr("sqrt ( 9 )");
    /*9 sqrt     result = 3*/
    double result = expr.solveIt();
    string a = expr.getExpr();
    cout << a << "    " << result;
}

