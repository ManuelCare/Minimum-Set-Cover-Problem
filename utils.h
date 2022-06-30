#ifndef UTILS_H
#define UTILS_H

#include <set>
#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node{
    set<string> S = {};
    set<string> unique = {};
    set<string> shared = {};
    Node* next = nullptr;
};
struct Node2 {
    set<string> S;
    Node2* next = NULL;
};

void printSet(set<string> S);
void printSet(set<set<string>> S);
set<string> maxS(set<set<string>> F, set<string> U);
set<string> setUnion(set<string> A, set<string> B);
set<string> setIntersection(set<string> A, set<string> B);
set<string> setDifference(set<string> A, set<string> B);
set<string> setDifference(set<string> A, set<set<string>> B);
set<string> returnClone(set<string> A);
set<set<string>> setDifference(set<set<string>> A, set<set<string>> B);
set<set<string>> insertionTo(set<set<string>> A,set<string> B);
set<set<string>> removeFrom(set<set<string>> A, set<string> B);
set<set<string>> returnClone(set<set<string>> A);
set<set<string>> maxSMod(set<set<string>> &F, set<string> U, int k);
set<set<string>> setUnion(set<set<string>> A, set<set<string>> B);
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P);
set<set<string>> returnAlone(set<set<string>> &F,set<string> &X);
set<set<string>> genUniverse(int A, int seed);
bool setContains(set<string> A, string b);
void loadProblem(set<set<string>> &F, set<string> &U, int k);
void loadExample(set<set<string>> &F, set<string> &U);
void printTime(double time);
set<set<string>> UniqueSets(set<set<string>> &F, set<string> &U);
void addNode(Node* front,Node* rear,set<string> originalSet ,set<string> uniqueSet, set<string> sharedSet);
void validateSolution(set<set<string>> sol, set<string> universe);
set<set<string>> maxSModV2(set<set<string>> &F, set<string> U, int k);
void refreshOnDataExit(Node *data, Node **front, set<set<string>> &currentSolution, set<string> &kSetUnion);
void refreshOnDataEntry(set<string> s, Node **front, Node **rear, set<set<string>> &currentSolution, set<string> &kSetUnion);
#endif