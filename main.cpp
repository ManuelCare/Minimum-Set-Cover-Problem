
#include <set>
#include <ostream>
#include <iostream>
#include <string>
#include "utils.h"
using namespace std;

set<string> MSCClassicGreedy(set<string> X,set<set<string>> F);

int main(){
    set<string> s2 = {"mo","to","ma","mi","mas"};
    set<string> s3={"mo","to","mi"}; 
    cout << s1.count(0) << endl;
    cout << s1.count(20) << endl;
    printSet(s2);
    printSet(s2);
    exit(EXIT_SUCCESS);
}

set<string> MSCClassicGreedy(set<string> X,set<set<string>> F){
    set<string> U (X); // Sea U un conjunto copia de X, el universo.
    set<set<string>> C; //sea C un conjunto vacio. C almacenara otros conjuntos
    while(!U.empty()){
        set<string> S;
        setSubstract(U,S); //setSubstract: U = U-S

        
    }
    return U;
}