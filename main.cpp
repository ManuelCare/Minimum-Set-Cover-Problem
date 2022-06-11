#include <set>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>
#include "utils.h"


using namespace std;
set<set<string>> MSCClassicGreedy(set<string> X,set<set<string>> F);
set<set<string>> MSCExhaustiveSearch(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n);

int main(){ 
    cout << endl;
    cout << "=================================================================" << endl;
    cout << "=================== MINIMUM SET COVER PROBLEM ===================" << endl;
    cout << "=================================================================" << endl;
    cout << endl;
    //INFO145 2021 I Clase 15 Pagina 14 ejemplo 2
    set<string> X = {"a","b","c","d","e","f","g","h","i","j","k","l"};
    set<string> s1 = {"a","b","c","d","e","f"};
    set<string> s2 = {"e","f","h","i"};
    set<string> s3 = {"a","d","g","j"};
    set<string> s4 = {"b","e","g","h","k"};
    set<string> s5 = {"c","f","i","l"};
    set<string> s6 = {"j","k"};
    set<set<string>> F = {s1,s2,s3,s4,s5,s6};

    cout << "Calculando el MSCP con el algoritmo busqueda exhaustiva ... ";
    set<set<string>> C1;
    set<string> P;
    C1 = MSCExhaustiveSearch(F, X, C1, P, F.size());
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C1);

    cout << "Calculando el MSCP con el algoritmo greedy clasico ... ";
    set<set<string>> C3 = MSCClassicGreedy(X,F);
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C3);
}

set<set<string>> MSCExhaustiveSearch(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n){
    if (X == P){
        return C;
    }
    set<set<string>> temp;
    set<set<string>> minSets;
    int min = n; // largo de F, cualquier (subconjunto de F <= min)
    for(set<set<string>>::const_iterator it = F.begin(); it != F.end(); ++it){
        temp = MSCExhaustiveSearch(removeFrom(F,(*it)), X, insertionTo(C,(*it)), setUnion(P,(*it)),n);
        if (temp.size() <= min){ 
            min = temp.size();
            minSets = temp;
        }
    }
    return minSets;
}

set<set<string>> MSCClassicGreedy(set<string> X,set<set<string>> F){
    set<string> U (X); // Sea U un conjunto copia de X, el universo.
    set<set<string>> C; //sea C un conjunto vacio. C almacenara otros conjuntos
    set<string> S;
    while(!U.empty()){
        S=maxS(F,U);
        U=setDifference(U,S); //setSubstract: U = U-S
        C.insert(S);
    }
    return C;
}