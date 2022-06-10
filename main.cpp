#include <set>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>
#include "utils.h"


using namespace std;
set<set<string>> MSCClassicGreedy(set<string> X,set<set<string>> F);

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
    //creo que esta bien -manu
    cout << "Calculando el MSCP con el algoritmo greedy clasico ... ";
    set<set<string>> C = MSCClassicGreedy(X,F);
    cout << "TERMINADO!" << endl;
    cout << "C: ";printSet(C);

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