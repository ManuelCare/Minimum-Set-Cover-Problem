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
set<string> returnClone(set<string> A){
    set<string> C (A); // Clona todo lo de A en C
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
set<string> setDifference(set<string> A, set<set<string>> B){    
    for (set<set<string>>::iterator it=B.begin(); it!=B.end(); ++it){
        A = setDifference(A,*it);
    }
    return A;
}
set<set<string>> removeFrom(set<set<string>> A, set<string> B){
    set<set<string>> C (A); // Clona todo lo de A en C 
    C.erase(B); // Borramos a B de C
    return C;
}
set<set<string>> setDifference(set<set<string>> A, set<set<string>> B){    
    set<set<string>> C;
    set_difference(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()));
    return C;
}
set<set<string>> setUnion(set<set<string>> A, set<set<string>> B){
    set<set<string>> C;
    set_union(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()));
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
set<set<string>> maxSMod(set<set<string>> &F, set<string> U, int k){
    set<set<string>> solution;
    if(F.size()<k){                 // caso especial donde no hay suficientes elementos, solo puede suceder al final
        solution = returnClone(F);
        F.clear();
        return solution;
    }


    int i,j,maxSolution,c,currentSize;

    set<string> kSetsUnions, tempShare , instantShare, currentIntersection;
    set<set<string>>::iterator it= F.begin();
    set<set<string>> currentSolution;
    solution.insert(*it);
    currentSolution.insert(*it);
    Node* node = new Node;
    node->S=*it;
    node->unique = *it;
    Node* p,*q,*r;
    Node* front = node;
    Node* rear = node;
    it++;
    for(i=1;i<k;i++){
        solution.insert(*it);
        currentSolution.insert(*it);
        instantShare.clear();
        tempShare.clear();
        p = front;
        while(p!=NULL){
            instantShare = setIntersection(p->unique,*it);
            tempShare = setUnion(tempShare,instantShare);
            p->unique = setDifference(p->unique,instantShare);
            p->shared = setUnion(p->shared,instantShare);
            p=p->next;
        }
        instantShare = setIntersection(kSetsUnions,*it);
        tempShare = setUnion(instantShare,tempShare);
        node = new Node;
        node->S = *it;
        node->unique = setDifference(*it,tempShare);
        node->shared = tempShare;
        rear->next = node;
        rear = rear->next;
        kSetsUnions=setUnion(kSetsUnions,*it); //debe ir al final 
        ++it;
    }
    maxSolution = setIntersection(kSetsUnions,U).size();
    ++it;
    set<string>::iterator symIt;
    while(it!=F.end()){
        
        p = front;                                              //cambios al eliminar el elemento inicial
        front = front->next;                                    //el front avanza
        kSetsUnions = setDifference(kSetsUnions,p->unique);       //los elementos unicos del inicial son quitados
        currentSolution.erase(p->S);                             //la solucion actual pierde el conjunto inicial
        symIt = p->shared.begin();                               
        while(symIt!=p->shared.end()){                          //se iteran por los elementos compartidos del conjunto inicial
            q = front;                                          //por todos los demas conjuntos
            c = 0;                                              
            while(q!=NULL && c<2){                              //se iteran mientras hayan conjuntos o hayan 2+ conjuntos con el elemento
                if(setContains(q->shared,*symIt)){              //si un conjunto lo comparte, apuntalo y aumenta el contador
                    r=q;
                    c++;
                }
                q = q->next;                                   //avanza
            }
            if(c==1){                                          // si solo habia 1 que lo compartia
                r->shared.erase(*symIt);    // ahora este elemento es unico para este conjunto
                r->unique.insert(*symIt);
            }
            ++symIt;
        }
        delete p;                                             //fin de los cambios al eliminar elemneto inicial (delete)
        //Inicio de pasos para añadir el nuevo elemento al final del conjunto
        currentSolution.insert(*it);
        instantShare.clear();
        tempShare.clear();
        p = front;
        while(p!=NULL){
            instantShare = setIntersection(p->unique,*it);
            tempShare = setUnion(tempShare,instantShare);
            p->unique = setDifference(p->unique,instantShare);
            p->shared = setUnion(p->shared,instantShare);
            p=p->next;
        }
        instantShare = setIntersection(kSetsUnions,*it);
        tempShare = setUnion(instantShare,tempShare);
        node = new Node;
        node->S = *it;
        node->unique = setDifference(*it,tempShare);
        node->shared = tempShare;
        rear->next = node;
        rear = rear->next;
        kSetsUnions=setUnion(kSetsUnions,*it); //debe ir al final 
        currentIntersection = setIntersection(kSetsUnions,U);
        currentSize = currentIntersection.size();
        if(currentSize>maxSolution){
            maxSolution=currentSize;
            solution = currentSolution;
        }
        ++it;
    }
    F = setDifference(F,solution);
    return solution;
}
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P){   //Entran X con todas las key y F con todos los conjuntos y devuelve los conjuntos donde solo se repite una vez un elemento solo los que se repiten una vez
    int cont;
    string letra;
    set<string> Temp;
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
void loadExample(set<set<string>> &F, set<string> &U){
    //INFO145 2021 I Clase 15 Pagina 14 ejemplo 2
    U = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    set<string> s1 = {"a","b","d","e","f"};
    set<string> s2 = {"e","f","h","i"};
    set<string> s3 = {"a","d","g","j"};
    set<string> s4 = {"b","e","g","h","k"};
    set<string> s5 = {"c","f","i","l"};
    // Aportan elementos unicos 
    set<string> s6 = {"m","n","o",};
    set<string> s7 = {"p","q","r"};
    set<string> s8 = {"s","t","u","v"};
    set<string> s9 = {"w","x","y","z"};
    // Estos no aportan elementos unicos 
    set<string> s10 = {"w","z"};
    set<string> s11 = {"y","z"};
    set<string> s12 = {"x","y"};
    F = {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12};
}
void printTime(double time){
    double S;
    int H, M;
    S=time/CLOCKS_PER_SEC;
    M=S/60;
    S=fmod(S,60);
    H=M/60;
    M=M%60;
    cout << "TIEMPO: ";
    if(H>0) cout << H << "[H] ";
    if(M>0) cout << M << "[m] ";
    cout << S << "[s]" << endl;
}
set<set<string>> UniqueSets(set<set<string>> &F, set<string> &U){
    set<string> Ucopy (U), temp;
    set<set<string>> C;
    int c;
    for(set<string>::iterator simb=Ucopy.begin(); simb!=Ucopy.end(); ++simb){
        c=0;
        set<set<string>>::iterator conj=F.begin();
        while(conj!=F.end() && c<2){
            if(setContains(*conj,*simb)){
                temp = *conj;
                c++;
            }
            ++conj;
        }
        if(c==1){
            F.erase(temp);
            U=setDifference(U,temp);
            C.insert(temp);
        }
    }
    return C;
}