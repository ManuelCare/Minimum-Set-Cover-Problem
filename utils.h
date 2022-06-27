#ifndef UTILS_H
#define UTILS_H

#include <set>
#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

void printSet(set<string> S);
void printSet(set<set<string>> S);
set<string> maxS(set<set<string>> F, set<string> U);
set<string> setUnion(set<string> A, set<string> B);
set<string> setIntersection(set<string> A, set<string> B);
set<string> setDifference(set<string> A, set<string> B);
set<string> getUniverse(set<string> &X);
set<set<string>> getSets(set<string> X, set<set<string>> &F);
set<set<string>> insertionTo(set<set<string>> A,set<string> B);
set<set<string>> removeFrom(set<set<string>> A, set<string> B);
set<set<string>> returnClone(set<set<string>> A);
set<string> returnClone(set<string> A);
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P);
set<set<string>> returnAlone(set<set<string>> &F,set<string> &X);
set<set<string>> genUniverse(int A, int seed);
bool setContains(set<string> A, string b);
void loadProblem(set<set<string>> &F, set<string> &U, int k);
#endif