#ifndef UTILS_H
#define UTIlS_H

#include <set>
#include <string>
#include <ostream>
#include <iostream>
using namespace std;

void printSet(set<string> S);
void printSet(set<set<string>> S);
void setSubstract(set<string> &A, set<string> B);

#endif