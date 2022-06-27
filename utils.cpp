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
set<string> getUniverse(set<string> &X){
    set<string> temp;
    ifstream file("setcover.csv");
    string line, Passport;
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,Passport,',');
        X.insert(Passport);
    }
    file.close();
    return X;
}
set<set<string>> getSets(set<string> X, set<set<string>> &F){
    set<string> temp;
    ifstream file("setcover.csv");
    string line, Passport, Destination, Requirement,po;
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,Passport,',');
        getline(ss,Destination,',');
        getline(ss,Requirement,',');
        string pais = Passport;
        temp.clear();
        po = pais;
        while(!file.eof() && pais == po){
            if(Requirement == "visa free" ||Requirement =="-1")
                temp.insert(Destination);
            getline(file,line);
            stringstream ss(line);
            getline(ss,pais,',');
            getline(ss,Destination,',');
            getline(ss,Requirement,',');

        }
        F.insert(returnClone(temp));
    }
    file.close();
    return F;   
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
set<string> returnClone(set<string> A){
    set<string> C (A); // Clona todo lo de A en C
    return C;
} 
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P){   //Entran X con todas las key y F con todos los conjuntos y devuelve los conjuntos donde solo se repite una vez un elemento solo los que se repiten una vez
    set<string> Temp;
    int cont;
    string letra;
    set<set<string>> G (F);
    for(set<string>::iterator it=X.begin(); it!=X.end(); ++it){
        cont = 0;
        for(set<set<string>>::iterator it2=F.begin(); it2!=F.end(); ++it2){
            if(setContains(*it2,*it)){ // si el subconjunto contiene a la letra
                cont++; // sumar al contador
                Temp = *it2; // temp sera el conjunto
                letra = *it; // letra sera el simbolo 
            }
        }
        if(cont == 1){
            P = setUnion(P,Temp);
            C.insert(Temp);
            G.erase(Temp);
        }
    }
    F = G;
    return C;
}
set<set<string>> returnAlone(set<set<string>> &F,set<string> &X){   //Entran X con todas las key y F con todos los conjuntos y devuelve los conjuntos donde solo se repite una vez un elemento solo los que se repiten una vez
    set<set<string>> C;
    set<string> Temp;
    int cont;
    string letra;
    for(set<string>::iterator it=X.begin(); it!=X.end(); ++it){     //*it
        cont = 0;
        for(set<set<string>>::iterator it2=F.begin(); it2!=F.end(); ++it2){
            if(setContains(*it2,*it)){
                cont++;
                Temp = *it2;
                letra = *it;
            }
        }
        if(cont <= 1){
            C.insert(Temp);
            X.erase(letra);
            F.erase(Temp);
        } 
    }
    return C;
}
set<set<string>> genUniverse(int A, int seed){
    srand(seed);
    set<set<string>> C; 
    set<string> TM; //T de Temporal y M de motomami
    int num = 0;
    int setSize = 0;
    for(int i=0; i<A; i++){   //Cantidad de elementos del universo a crear
        setSize=rand()%27;   //Numero random entre 1 y 26
        for(int j = 0; j<setSize; j++){
            num = 97 + rand()%(123-97);   //numero random entre el 97 al 122
            string s(1,char(num));
            TM.insert(s);
        }
        C.insert(TM);
        TM = {};
    }
    return C;
}
bool setContains(set<string> A, string b){   //Verifica si un string esta almacenado en un set
    set<string>::iterator it = A.find(b);
    if (it != A.end()){
        return true;
    }
    return false;
}

void loadProblem(set<set<string>> &F, set<string> &U,int k){
    ifstream file("data/rail4284.txt");
    set<string> tempSet;

    if(!file.is_open()) return; //en caso de que no exista tal archivo, aborta

    int n, m, i=0, j, t; // t es una variable basurero. 
    string elem;
    file >> m >> n;

    if(k>n) k=n; // si pides más sets de los que existen, utiliza el maximo posible.

    while(i<k){
        tempSet.clear();
        file >> t >> m;
        for(j=0; j<m; j++){
            file >> elem;
            tempSet.insert(elem);
            U.insert(elem);
        }
        F.insert(returnClone(tempSet));
        i++;
    }
}