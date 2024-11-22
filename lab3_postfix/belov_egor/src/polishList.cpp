// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// polishList.cpp - Copyright (c) Белов Е.А.
//
// Связный список для хранения польской записи арифметических выражений

#include "polishList.h"

PolishList::~PolishList() {
    while (!isPrevNull()) {
        left();
    }
    while (!isNextNull()) {
        PolishCell* temp = pointer->right;
        delete pointer;
        pointer = temp;
    }
    delete pointer;
}

void PolishList::push(const double& val) {
    if (pointer == nullptr) {
        pointer = new PolishCell(val);
        pointer->left = nullptr;
        pointer->right = nullptr;
    }
    else {
        PolishCell* tempRight = pointer->right;
        pointer->right = new PolishCell(val);
        pointer->right->left = pointer;
        pointer = pointer->right;
        if (tempRight != nullptr) {
            pointer->right = tempRight;
            tempRight->left = pointer;
        }
    }
}

void PolishList::push(const OperationChar& val) {
    if (pointer == nullptr) {
        pointer = new PolishCell(val);
        pointer->left = nullptr;
        pointer->right = nullptr;
    }
    else {
        PolishCell* tempRight = pointer->right;
        pointer->right = new PolishCell(val);
        pointer->right->left = pointer;
        pointer = pointer->right;
        if (tempRight != nullptr) {
            pointer->right = tempRight;
            tempRight->left = pointer;
        }
    }
}

void PolishList::pop() {
    PolishCell* tempRight = pointer->right;
    PolishCell* tempLeft = pointer->left;
    
    delete pointer;
    
    pointer = tempLeft;
    if (pointer != nullptr) {
        pointer->right = tempRight;
    }
    if (tempRight != nullptr) {
        tempRight->left = pointer;
    }
}

void PolishList::left() {
    pointer = pointer->left;
}

void PolishList::right() {
    pointer = pointer->right;
}

void PolishList::toCalculate() {
    while (!isPrevNull()) {
        left();
    }
    while (!isNextNull() && getInfo() == num) {
        right();
    }
}

void PolishList::toNextOp() {
    while (!isNextNull() && getInfo() == num) {
        right();
    }
}

