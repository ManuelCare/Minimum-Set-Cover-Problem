#ifndef UTILS_H
#define UTILS_H

#include <set>
#include <string>
#include <ostream>
#include <iostream>
#include <algorithm>
using namespace std;

void printSet(set<string> S);
void printSet(set<set<string>> S);
set<string> maxS(set<set<string>> F, set<string> U);
set<string> setUnion(set<string> A, set<string> B);
set<string> setIntersection(set<string> A, set<string> B);
set<string> setDifference(set<string> A, set<string> B);
set<set<string>> insertionTo(set<set<string>> A,set<string> B);
set<set<string>> removeFrom(set<set<string>> A, set<string> B);
set<set<string>> returnClone(set<set<string>> A);
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P);
set<set<string>> returnAlone(set<string> &X, set<set<string>> &F);
bool setContains(set<string> A, string b);


#endif
