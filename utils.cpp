#include "utils.h"

void printSet(set<string> S){
    set<string>::iterator it = S.begin();
    cout << *it;
    for (;it!=S.end(); ++it)
        cout << " " << *it; 
    cout << endl;
}

void printSet(set<set<string>> S){
    for (set<set<string>>::iterator it=S.begin(); it!=S.end(); ++it)
        printSet(*it);
    cout << endl;
}

void setSubstract(set<string> &A, set<string> B){ // Itera por los n elementos de B para eliminarlos de A. O(n)
    for (set<string>::iterator it=B.begin(); it!=B.end(); ++it){
        A.erase(*it);
    }
}