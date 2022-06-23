#include <set>
#include <ostream>
#include <iostream>
#include <string>
#include "utils.h"

using namespace std;
set<set<string>> MSCClassicGreedy(set<string> X,set<set<string>> F);
set<set<string>> MSCExhaustiveSearch(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n);
set<set<string>> MSCExhaustiveSearchOp1(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n);
set<set<string>> TopDownMSCExhaustiveSearchOp2(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n, int *R);


int main(){ 
    cout << endl;
    cout << "=================================================================" << endl;
    cout << "=================== MINIMUM SET COVER PROBLEM ===================" << endl;
    cout << "=================================================================" << endl;
    cout << endl;
    //INFO145 2021 I Clase 15 Pagina 14 ejemplo 2
    
    set<string> X = {"a","b","c","d","e","f","g","h","i","j","k","l"};
    
    set<string> s1 = {"a","b","e","f","i","j"};
    set<string> s2 = {"f","g","j","k"};
    set<string> s3 = {"a","b","c","d"};
    set<string> s4 = {"c","e","f","g","h"};
    set<string> s5 = {"i","j","k","l"};
    set<string> s6 = {"d","h"};
    // Aportan elementos unicos 
    
    set<set<string>> F = {s1,s2,s3,s4,s5,s6};
    set<set<string>> C1, C2, C3;
    set<string> P1, P2;

    cout << "Calculando el MSCP con el algoritmo greedy clasico ... ";
    C3 = MSCClassicGreedy(X,F);
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C3);
    
    cout << "Calculando el MSCP con el algoritmo de busqueda exhaustiva optimizada ... ";
    C2 = MSCExhaustiveSearchOp1(F, X, C2, P2, F.size());
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C2);

    cout << "Calculando el MSCP con el algoritmo de busqueda exhaustiva ... ";
    C1 = MSCExhaustiveSearch(F, X, C1, P1, F.size());
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C1);
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

set<set<string>> MSCExhaustiveSearchOp1(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n){
    C = returnAloneES(F,X,C,P);
    // Paso 2
    int *R = new int[n];
    for(int i=0;i<n;i++){
        R[i] = -1;
    }
    C = TopDownMSCExhaustiveSearchOp2(F,X,C,P,n,R);
    return C;
}

set<set<string>> TopDownMSCExhaustiveSearchOp2(set<set<string>> F, set<string> X, set<set<string>> C, set<string> P,int n, int *R){
    if (X == P){
        R[C.size()] = 1;
        return C;
    }
    else if (R[C.size()-1] > 0){
        return C;
    }
    set<set<string>> temp;
    set<set<string>> minSets;
    int min = n; // largo de F, cualquier (subconjunto de F <= min)
    for(set<set<string>>::const_iterator it = F.begin(); it != F.end(); ++it){
        temp = MSCExhaustiveSearch(removeFrom(F,(*it)), X, insertionTo(C,(*it)), setUnion(P,(*it)),n);
        printSet(temp);
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