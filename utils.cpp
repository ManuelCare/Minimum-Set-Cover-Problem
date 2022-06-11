#include "utils.h"

void printSet(set<string> S){
    if(S.empty())
        cout << "conjunto vacio";
    else{
        set<string>::iterator it = S.begin();
        cout << *it;
        ++it;
        for (;it!=S.end(); ++it)
            cout << " " << *it; 
    }
    cout << endl;
}

void printSet(set<set<string>> S){
    if(S.empty())
        cout << "conjunto vacio";
    else
        cout << endl;
        for (set<set<string>>::iterator it=S.begin(); it!=S.end(); ++it){
            cout << "  "; printSet(*it);
            }
    cout << endl;
}

set<string> maxS(set<set<string>> F, set<string> U){
    set<string> S,t;
    int max=0;
    for (set<set<string>>::iterator it=F.begin(); it!=F.end(); ++it){
        t=setIntersection(U,*it);
        if(t.size()>=max){
            S=*it;
            max=t.size();
        }
    }
    return S;
}

set<string> setUnion(set<string> A, set<string> B){
    set<string> C;
    set_union(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()));
    return C;
}
set<string> setIntersection(set<string> A, set<string> B){
    set<string> C;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()));
    return C;
}
set<string> setDifference(set<string> A, set<string> B){    
    set<string> C;
    set_difference(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()));
    return C;
}

set<set<string>> removeFrom(set<set<string>> A, set<string> B){
    set<set<string>> C (A); // Clona todo lo de A en C 
    C.erase(B); // Borramos a B de C
    return C;
}

set<set<string>> insertionTo(set<set<string>> A,set<string> B){
    set<set<string>> C (A); // Clona todo lo de A en C
    C.insert(B); // Insertamos a B en C
    return C;
}

set<set<string>> returnClone(set<set<string>> A){
    set<set<string>> C (A); // Clona todo lo de A en C
    return C;
}
