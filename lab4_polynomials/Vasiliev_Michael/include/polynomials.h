#ifndef __POLYNOMIALS_H
#define __POLYNOMIALS_H__

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "list.h"

using namespace std;
class Polynomial
{
private:
    TList<int> terms;
public:
    Polynomial() {}

    void add_term(int coef, string expon) {
        if (coef == 0) {
            return;
        }

        for (TList<int>::Iterator i = terms.begin(); i != terms.end(); i++) {
            int index = 0;
            if (i.get_node()->exps == expon) {
                i.get_node()->value += coef;
                if (i.get_node()->value == 0) {
                    terms.Delete(index);
                }
                return;
            }
        }
        terms.insert(0, expon, coef);
    }
    

    Polynomial operator+(const Polynomial& other) {
        Polynomial result;

        for (TList<int>::Iterator i = other.terms.begin(); i != other.terms.end(); i++) {
            result.add_term(i.get_node()->value, i.get_node()->exps);
        }

        for (TList<int>::Iterator i = terms.begin(); i != terms.end(); i++) {
            result.add_term(i.get_node()->value, i.get_node()->exps);
        }
        
        return result;
    }

    Polynomial operator-(const Polynomial& other) {
        Polynomial result;

        for (TList<int>::Iterator i = other.terms.begin(); i != other.terms.end(); i++) {
            result.add_term(-i.get_node()->value, i.get_node()->exps);
        }

        for (TList<int>::Iterator i = terms.begin(); i != terms.end(); i++) {
            result.add_term(i.get_node()->value, i.get_node()->exps);
        }
        
        return result;
    }

    Polynomial operator*(const Polynomial& other) {
        Polynomial result;

        for (TList<int>::Iterator i1 = terms.begin(); i1 != terms.end(); i1++) {
            for (TList<int>::Iterator i2 = other.terms.begin(); i2 != other.terms.end(); i2++) {
                int new_coef = i1.get_node()->value * i2.get_node()->value;
                string ex1 = i1.get_node()->exps;
                int x1_exp = ex1[0] - '0';
                int y1_exp = ex1[1] - '0';
                int z1_exp = ex1[2] - '0';
                string ex2 = i2.get_node()->exps;
                int x2_exp = ex2[0] - '0';
                int y2_exp = ex2[1] - '0';
                int z2_exp = ex2[2] - '0';
                string new_exps = to_string(x1_exp + x2_exp) + to_string(y1_exp + y2_exp) + to_string(z1_exp + z2_exp);
                result.add_term(new_coef, new_exps);
            }
        }

        return result;
    }

    int evaluate(int x, int y, int z) {
        int result = 0;

        for (TList<int>::Iterator i = terms.begin(); i != terms.end(); i++) {
            string expons = i.get_node()->exps;

            int x_exp = expons[0] - '0';
            int y_exp = expons[1] - '0';
            int z_exp = expons[2] - '0';

            result += i.get_node()->value * pow(x, x_exp) * pow(y, y_exp) * pow(z, z_exp);
        }

        return result;
    }

    friend ostream& operator<<(ostream& ostr, const Polynomial& other)
    {
        for (TList<int>::Iterator i = other.terms.begin(); i != other.terms.end(); i++) {
            if (i != other.terms.begin() && i.get_node()->value > 0) {
                ostr << " + ";
            } else if (i != other.terms.begin() && i.get_node()->value < 0) {
                ostr << " ";
            }

            if (i.get_node()->value == -1) {
                ostr << "-";
            } else if (i.get_node()->value != 1) {
                ostr << i.get_node()->value;
            }

            string expons = i.get_node()->exps;
            
            int x_exp = expons[0] - '0';
            int y_exp = expons[1] - '0';
            int z_exp = expons[2] - '0';

            if (x_exp == 1) {
                ostr << "x";
            } else if (x_exp > 0) {
                ostr << "x^" << x_exp;
            }
            if (y_exp == 1) {
                ostr << "y";
            } else if (y_exp > 0) {
                ostr << "y^" << y_exp;
            }
            if (z_exp == 1) {
                ostr << "z";
            } else if (z_exp > 0) {
                ostr << "z^" << z_exp;
            }
        }
        ostr << endl;
        
        return ostr;
    }
};

#endif
