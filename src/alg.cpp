// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
std::string infx2pstfx(std::string inf) {
    std::string c = "";
    TStack<char, 100> st;
    std::map<char, int> pr;
    pr['('] = 0;
    pr[')'] = 0;
    pr['+'] = 1;
    pr['-'] = 1;
    pr['*'] = 2;
    pr['/'] = 2;
    for (int i = 0; i < inf.size(); i++) {
        if (pr.find(inf[i]) == pr.end()) {
            c += inf[i];
            c += ' ';
        } else {
        if (inf[i] == ')') {
            while (st.Get() != '(') {
                c += st.Get();
                c += ' ';
                st.pop();
            }
            st.pop();
        } else {
        if (inf[i] == '(' || st.Empty()) {
            st.push(inf[i]);
        } else {
            if (pr[inf[i]] > pr[st.Get()]) {
            st.push(inf[i]);
            } else {
                        while (pr[inf[i]] <= pr[st.Get()]) {
                            if (!st.Empty()) {
                            c += st.Get();
                            c += ' ';
                            st.pop();
                            }
                        }
                        st.push(inf[i]);
                    }
                }
            }
        }
    }
    while (!st.Empty()) {
        c += st.Get();
        c += ' ';
        st.pop();
    }
    c.pop_back();
    return c;
}
int eval(std::string pref) {
    TStack<int, 100> st;
    int b1, b2, r, i = 0;
    while (i < pref.size()) {
        if (pref[i] >= '0') {
            st.push(pref[i] - '0'); 
        } else {
            if (pref[i] != ' ') {
                b2 = st.Get();
                st.pop();
                b1 = st.Get();
                st.pop();
                switch (pref[i]) {
                    case '+':
                        r = b1 + b2;
                        break;
                    case '-':
                        r = b1 - b2;
                        break;
                    case '*':
                        r = b1 * b2;
                        break;
                    case '/':
                        r = b1 / b2;
                        break;
                    }
                st.push(r);
            }
        }
        i++;
    }
    return st.Get();
}
