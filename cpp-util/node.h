#pragma once

struct node {
    int a;
    int b;
    int c;
public:
    node(int _a, int _b) :a(_a), b(_b) {
        c = _a - _b;
    }

};
