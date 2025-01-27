#ifndef __STACK_QUEUE_H__
#define __STACK_QUEUE_H__

#pragma once
#include <iostream>
#include <stack>
using namespace std;
template <typename T>
class TStackQueue
{
	stack<T> ls;
    stack<T> rs;
    size_t sz;
public:
    TStackQueue() : sz(0) { }
    size_t size() const { return sz; }
    bool isEmpty() const { return sz == 0; }

    void Push(const T& val) {
        ls.push(val);
        sz++;
    }

    T top() {
        if (isEmpty()) {
            throw ("Queue is empty");
        }
        if (rs.empty()) {
            while (!ls.empty()) {
                rs.push(ls.top());
                ls.pop();
            }
        }
        return rs.top();
    }

    T pop() {
        if (isEmpty()) {
            throw ("Queue is empty");
        }
        if (rs.empty()) {
            while (!ls.empty()) {
                rs.push(ls.top());
                ls.pop();
            }
        }
        T val = rs.top();
        rs.pop();
        sz--;
        return val;
    }

    T getMin() const {
        if (isEmpty()) {
            throw ("Queue is empty");
        }
        stack<T> temp = ls;
        stack<T> temp2 = rs;
        T minVal;
        if (temp2.empty()) {
            minVal = temp.top();
        } else {
            minVal = temp2.top();
        }
        while (!temp.empty()) {
            if (temp.top() < minVal) {
                minVal = temp.top();
            }
            temp.pop();
        }
        while (!temp2.empty()) {
            if (temp2.top() < minVal) {
                minVal = temp2.top();
            }
            temp2.pop();
        }
        return minVal;
    }

    T getMax() const {
        if (isEmpty()) {
            throw ("Queue is empty");
        }
        stack<T> temp = ls;
        stack<T> temp2 = rs;
        T maxVal;
        if (temp2.empty()) {
            maxVal = temp.top();
        } else {
            maxVal = temp2.top();
        }
        while (!temp.empty()) {
            if (temp.top() > maxVal) {
                maxVal = temp.top();
            }
            temp.pop();
        }
        while (!temp2.empty()) {
            if (temp2.top() > maxVal) {
                maxVal = temp2.top();
            }
            temp2.pop();
        }
        return maxVal;
    }
};
#endif