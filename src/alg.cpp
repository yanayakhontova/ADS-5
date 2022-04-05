// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
std::string infx2pstfx(std::string inf) {
    std::string c = "";
    TStack<char, 100> a;
    std::map<char, int> b;
    b['('] = 0;
    b[')'] = 0;
    b['+'] = 1;
    b['-'] = 1;
    b['*'] = 2;
    b['/'] = 2;
    for (int i = 0; i < inf.size(); i++) {
        if (b.find(inf[i]) == b.end()) {
            c += inf[i];
            c += ' ';
        } else {
        if (inf[i] == ')') {
            while (a.Get() != '(') {
                c += a.Get();
                c += ' ';
                a.pop();
            }
            a.pop();
        } else {
        if (inf[i] == '(' || a.Empty()) {
            a.push(inf[i]);
        } else {
            if (b[inf[i]] > b[a.Get()]) {
            a.push(inf[i]);
            } else {
                        while (b[inf[i]] <= b[a.Get()]) {
                            if (!a.Empty()) {
                            c += a.Get();
                            c += ' ';
                            a.pop();
                            }
                        }
                        a.push(inf[i]);
                    }
                }
            }
        }
    }
    while (!a.Empty()) {
        c += a.Get();
        c += ' ';
        a.pop();
    }
    c.pop_back();
    return c;
}
int eval(std::string br) {
    TStack<int, 100> a;
    int x1, x2, r, i = 0;
    while (i < br.size()) {
        if (br[i] >= '0') {
            a.push(br[i] - '0'); 
        } else {
            if (br[i] != ' ') {
                x2 = a.Get();
                a.pop();
                x1 = a.Get();
                a.pop();
                switch (br[i]) {
                    case '+':
                        r = x1 + x2;
                        break;
                    case '-':
                        r = x1 - x2;
                        break;
                    case '*':
                        r = x1 * x2;
                        break;
                    case '/':
                        r = x1 / x2;
                        break;
                    }
                a.push(r);
            }
        }
        i++;
    }
    return a.Get();
}
