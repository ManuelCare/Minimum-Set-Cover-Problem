#ifndef UTILS_H
#define UTIlS_H

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

#endif