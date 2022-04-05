// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <stack>
#include "tstack.h"
int prior(char w) {
  switch (w) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 3;
  }
  return 0;
}
bool search(std::string c, char w) {
  for (int i = 0; i < c.length(); ++i) {
    if (c[i] == w) {
      return true;
    }
  }
  return false;
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::stack<char> Stack;
  std::string number = "0123456789";
  std::string operation = "()+-*/";
  std::string res = "";
  for (int i = 0; i < inf.length(); ++i) {
    if (search(number, inf[i])) {
      res += inf[i];
      res += ' ';
    } else if (search(operation, inf[i])) {
      if (prior(inf[i]) == 0) {
        Stack.push(inf[i]);
      } else if (Stack.empty()) {
        Stack.push(inf[i]);
      } else if (prior(inf[i]) > prior(Stack.top())) {
        Stack.push(inf[i]);
      } else if (inf[i] == ')') {
        while (Stack.top() != '(') {
          res += Stack.top();
          res += ' ';
          Stack.pop();
        }
        if (Stack.top() == '(') {
          Stack.pop();
        }
      } else {
        for (int j = 0; j<= Stack.size(); ++j) {
          if (prior(Stack.top()) >= prior(inf[i])) {
            res += Stack.top();
            res += ' ';
            Stack.pop();
          }
        }
        Stack.push(inf[i]);
      }
    }
  }
  if (!Stack.empty()) {
    for (int j = 0; j <= Stack.size(); ++j) {
      res += Stack.top();
      res += ' ';
      Stack.pop();
    }
  }
  if (res[res.length() - 1] == ' ') {
    res.erase(res.length() - 1);
  }
  return res;
}
int eval(std::string pref) {
  int summ = 0;
  std::stack<int> Stack;
  TStack<int, 100> stack;
  std::string number = "0123456789";
  std::string operation = "()+-*/";
  for (int i = 0; i < pref.length(); ++i) {
    if (search(number, pref[i])) {
      Stack.push(pref[i] - '0');
    } else if (search(operation, pref[i])) {
      int a = 0, b = 0;
      a = Stack.top();
      Stack.pop();
      b = Stack.top();
      Stack.pop();
      if (pref[i] == '+') {
        Stack.push(b + a);
      }
      if (pref[i] == '-') {
        Stack.push(b - a);
      }
      if (pref[i] == '*') {
        Stack.push(b * a);
      }
      if (pref[i] == '/') {
        Stack.push(b / a);
      }
    }
  }
  summ = Stack.top();
  return summ;
}
