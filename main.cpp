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
set<set<string>> MSCClassicGreedyOptimize(set<string> X, set<set<string>> F, int k);
/*int main(){
    set<set<string>> F;
    set<string> U;
    loadProblem(F,U,1000);
    printSet(F);
    return EXIT_SUCCESS;
}*/
int main(){ 
    cout << endl;
    cout << "=================================================================" << endl;
    cout << "=================== MINIMUM SET COVER PROBLEM ===================" << endl;
    cout << "=================================================================" << endl;
    cout << endl;
    
    set<set<string>> C1, C2, C3, C4, C5;
    set<string> P1, P2;
    
    // set<set<string>> nuevoUniverso = genUniverse(8,300);
    // cout<<"Nuevo universo: "<<endl;
    // printSet(nuevoUniverso);
    
    set<set<string>> F;
    set<string> U;
    loadProblem(F,U,10000);

    clock_t begin, end;
    double time_spent;
    begin = clock();
    // cout << "Calculando el MSCP con el algoritmo de busqueda exhaustiva ... ";
    // 
    // C1 = MSCExhaustiveSearch(F2, X2, C1, P1, X2.size());
    // 
    // 
    // cout << "TERMINADO!" << endl;
    // cout << "C: ";printSet(C1);

    // cout << "Calculando el MSCP con el algoritmo greedy clasico ... ";
    // C5 = MSCClassicGreedy(X2,F2);
    // cout << "TERMINADO!" << endl;
    // cout << "C: ";printSet(C4);
    // cout << C4.size();

    cout << "Calculando el MSCP con el algoritmo greedy clasico ... ";
    C3 = MSCClassicGreedy(U,F);
    cout << "TERMINADO!" << endl;
    // cout << "C: ";printSet(C3);

    // cout << "Calculando el MSCP con el algoritmo de busqueda exhaustiva optimizada ... ";
    // C2 = MSCExhaustiveSearchOp1(nuevoUniverso, X, C2, P2, nuevoUniverso.size());
    // cout << "TERMINADO!" << endl;
    // cout << "C: ";printSet(C2);

    // cout<<"Calculando el MSCP con el algoritmo greedy clasico optimizado ...";
    // C4 = MSCClassicGreedyOptimize(X,nuevoUniverso,1);
    // cout<< "TERMINADO!" << endl;
    // cout << "C: ";printSet(C4);
    end = clock();
    printTime((double)(end - begin));
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
        R[C.size()-1] = 1;
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
        if (temp.size() <= min && R[C.size()-1]<1){ 
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

set<set<string>> MSCClassicGreedyOptimize(set<string> X, set<set<string>> F, int k){   //K=2 es la union de dos cosos
    set<string> U (X); // Sea U un conjunto copia de X, el universo.
    set<set<string>> R (F); 
    set<set<string>> C = returnAlone(R,U);  //Encuentra los conjuntos donde hay elemetos que solo estan en el mismo y los agregan a la solución C
    set<string> S;
    set<string> L (X);
    set<set<string>> acum;
    set<string> suma;
    int cont = 0;
    while(!U.empty()){
        for(set<set<string>>::iterator it=R.begin(); it!=R.end(); ++it){
            cont++;
            acum.insert(*it);
            suma = {};
            if(cont%k==0){
                for(set<set<string>>::iterator it1=acum.begin(); it1!=acum.end(); ++it1){
                    suma = setUnion(suma, *it1);
                }
                S=maxS(R,U);
                U=setDifference(U,S);
                C.insert(S);
                acum = {};
            }
        }

       
    }
    return C;
}