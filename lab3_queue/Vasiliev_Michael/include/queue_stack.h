#ifndef __QUEUE_STACK_H
#define __QUEUE_STACK_H__

#include <string>
#include "string.h"
#include <map>
#include <cmath>
#include <stack>

using namespace std;
template <typename T>

class TStackQueue
{
private:
    size_t sz;
    stack<T> leftStack;
    stack<T> rightStack;
    stack<T> MinLeftStack;
    stack<T> MinRightStack;
    stack<T> MaxLeftStack;
    stack<T> MaxRightStack;
public:
    TStackQueue() : sz(0) {};

    size_t Size() const {
        return sz;
    }

    bool isEmpty() const {
        return sz == 0;
    }

    void Push(const T& val) {
        leftStack.push(val);
        if (MinLeftStack.empty() || val <= MinLeftStack.top()) {
            MinLeftStack.push(val);
        } else {
            MinLeftStack.push(MinLeftStack.top());
        }

        if (MaxLeftStack.empty() || val >= MaxLeftStack.top()) {
            MaxLeftStack.push(val);
        } else {
            MaxLeftStack.push(MaxLeftStack.top());
        }
        sz++;
    }

    T top() {
        if (rightStack.empty()) {
            while (!leftStack.empty()) {
                T val = leftStack.top();
                leftStack.pop();
                MinLeftStack.pop();
                MaxLeftStack.pop();
                rightStack.push(val);

                if (MinRightStack.empty() || val <= MinRightStack.top()) {
                    MinRightStack.push(val);
                } else {
                    MinRightStack.push(MinRightStack.top());
                }

                if (MaxRightStack.empty() || val >= MaxRightStack.top()) {
                    MaxRightStack.push(val);
                } else {
                    MaxRightStack.push(MaxRightStack.top());
                }
            }
        }
        if (rightStack.empty()) {
            throw ("Queue is empty.");
        }
        return rightStack.top();
    }

    T pop() {
        if (rightStack.empty()) {
            while (!leftStack.empty()) {
                T val = leftStack.top();
                leftStack.pop();
                MinLeftStack.pop();
                MaxLeftStack.pop();
                rightStack.push(val);

                if (MinRightStack.empty() || val <= MinRightStack.top()) {
                    MinRightStack.push(val);
                } else {
                    MinRightStack.push(MinRightStack.top());
                }

                if (MaxRightStack.empty() || val >= MaxRightStack.top()) {
                    MaxRightStack.push(val);
                } else {
                    MaxRightStack.push(MaxRightStack.top());
                }
            }
        }
        if (rightStack.empty()) {
            throw ("Queue is empty.");
        }
        T val = rightStack.top();
        rightStack.pop();
        MinRightStack.pop();
        MaxRightStack.pop();
        sz--;
        return val;
    }
    
    T getMin() const {
        if (isEmpty()) {
            throw ("Queue is empty.");
        }

        if (MinLeftStack.empty()) {
            return MinRightStack.top();
        } else if (MinRightStack.empty()) {
            return MinLeftStack.top();
        } else {
            return min(MinLeftStack.top(), MinRightStack.top());
        }
    }

    T getMax() const {
        if (isEmpty()) {
            throw ("Queue is empty");
        }

        if (MaxLeftStack.empty()) {
            return MaxRightStack.top();
        } else if (MaxRightStack.empty()) {
            return MaxLeftStack.top();
        } else {
            return max(MaxLeftStack.top(), MaxRightStack.top());
        }        
    }
};

#endif
