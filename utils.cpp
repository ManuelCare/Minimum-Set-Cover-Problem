#include "utils.h"

void printSet(set<string> S)
{
    if (S.empty())
        cout << "conjunto vacio";
    else
    {
        set<string>::iterator it = S.begin();
        cout << *it;
        ++it;
        for (; it != S.end(); ++it)
            cout << " " << *it;
    }
    cout << endl;
}
void printSet(set<set<string>> S)
{
    if (S.empty())
        cout << "conjunto vacio";
    else
        cout << endl;
    for (set<set<string>>::iterator it = S.begin(); it != S.end(); ++it)
    {
        cout << "  ";
        printSet(*it);
    }
    cout << endl;
}
set<string> maxS(set<set<string>> F, set<string> U)
{
    set<string> S, t;
    int max = 0;
    for (set<set<string>>::iterator it = F.begin(); it != F.end(); ++it)
    {
        t = setIntersection(U, *it);
        if (t.size() >= max)
        {
            S = *it;
            max = t.size();
        }
    }
    return S;
}
set<string> setUnion(set<string> A, set<string> B)
{
    set<string> C;
    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
    return C;
}
set<string> returnClone(set<string> A)
{
    set<string> C(A); // Clona todo lo de A en C
    return C;
}
set<string> setIntersection(set<string> A, set<string> B)
{
    set<string> C;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
    return C;
}
set<string> setDifference(set<string> A, set<string> B)
{
    set<string> C;
    set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
    return C;
}
set<string> setDifference(set<string> A, set<set<string>> B)
{
    for (set<set<string>>::iterator it = B.begin(); it != B.end(); ++it)
    {
        A = setDifference(A, *it);
    }
    return A;
}
set<set<string>> removeFrom(set<set<string>> A, set<string> B)
{
    set<set<string>> C(A); // Clona todo lo de A en C
    C.erase(B);            // Borramos a B de C
    return C;
}
set<set<string>> setDifference(set<set<string>> A, set<set<string>> B)
{
    set<set<string>> C;
    set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
    return C;
}
set<set<string>> setUnion(set<set<string>> A, set<set<string>> B)
{
    set<set<string>> C;
    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
    return C;
}
set<set<string>> insertionTo(set<set<string>> A, set<string> B)
{
    set<set<string>> C(A); // Clona todo lo de A en C
    C.insert(B);           // Insertamos a B en C
    return C;
}
set<set<string>> returnClone(set<set<string>> A)
{
    set<set<string>> C(A); // Clona todo lo de A en C
    return C;
}
set<set<string>> maxSMod(set<set<string>> &F, set<string> U, int k)
{
    set<set<string>> solution;
    if (F.size() <= k)
    {
        solution = returnClone(F);
        F.clear();
        return solution;
    }
    return solution;
}
set<set<string>> returnAloneES(set<set<string>> &F, set<string> &X, set<set<string>> C, set<string> &P)
{ // Entran X con todas las key y F con todos los conjuntos y devuelve los conjuntos donde solo se repite una vez un elemento solo los que se repiten una vez
    int cont;
    string letra;
    set<string> Temp;
    set<set<string>> G(F);
    for (set<string>::iterator it = X.begin(); it != X.end(); ++it)
    {
        cont = 0;
        for (set<set<string>>::iterator it2 = F.begin(); it2 != F.end(); ++it2)
        {
            if (setContains(*it2, *it))
            {                // si el subconjunto contiene a la letra
                cont++;      // sumar al contador
                Temp = *it2; // temp sera el conjunto
                letra = *it; // letra sera el simbolo
            }
        }
        if (cont == 1)
        {
            P = setUnion(P, Temp);
            C.insert(Temp);
            G.erase(Temp);
        }
    }
    F = G;
    return C;
}
set<set<string>> returnAlone(set<set<string>> &F, set<string> &X)
{ // Entran X con todas las key y F con todos los conjuntos y devuelve los conjuntos donde solo se repite una vez un elemento solo los que se repiten una vez
    set<set<string>> C;
    set<string> Temp;
    int cont;
    string letra;
    for (set<string>::iterator it = X.begin(); it != X.end(); ++it)
    { //*it
        cont = 0;
        for (set<set<string>>::iterator it2 = F.begin(); it2 != F.end(); ++it2)
        {
            if (setContains(*it2, *it))
            {
                cont++;
                Temp = *it2;
                letra = *it;
            }
        }
        if (cont <= 1)
        {
            C.insert(Temp);
            X.erase(letra);
            F.erase(Temp);
        }
    }
    return C;
}
set<set<string>> genUniverse(int A, int seed)
{
    srand(seed);
    set<set<string>> C;
    set<string> TM; // T de Temporal y M de motomami
    int num = 0;
    int setSize = 0;
    for (int i = 0; i < A; i++)
    {                          // Cantidad de elementos del universo a crear
        setSize = rand() % 27; // Numero random entre 1 y 26
        for (int j = 0; j < setSize; j++)
        {
            num = 97 + rand() % (123 - 97); // numero random entre el 97 al 122
            string s(1, char(num));
            TM.insert(s);
        }
        C.insert(TM);
        TM = {};
    }
    return C;
}
bool setContains(set<string> A, string b)
{ // Verifica si un string esta almacenado en un set
    set<string>::iterator it = A.find(b);
    if (it != A.end())
    {
        return true;
    }
    return false;
}
void loadProblem(set<set<string>> &F, set<string> &U, int k)
{
    ifstream file("data/rail4284.txt");
    set<string> tempSet;

    if (!file.is_open())
        return; // en caso de que no exista tal archivo, aborta

    int n, m, i = 0, j, t; // t es una variable basurero.
    string elem;
    file >> m >> n;

    if (k > n)
        k = n; // si pides más sets de los que existen, utiliza el maximo posible.

    while (i < k)
    {
        tempSet.clear();
        file >> t >> m;
        for (j = 0; j < m; j++)
        {
            file >> elem;
            tempSet.insert(elem);
            U.insert(elem);
        }
        F.insert(returnClone(tempSet));
        i++;
    }
}
void loadExample(set<set<string>> &F, set<string> &U)
{
    // INFO145 2021 I Clase 15 Pagina 14 ejemplo 2
    U = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    set<string> s1 = {"a", "b", "d", "e", "f"};
    set<string> s2 = {"e", "f", "h", "i"};
    set<string> s3 = {"a", "d", "g", "j"};
    set<string> s4 = {"b", "e", "g", "h", "k"};
    set<string> s5 = {"c", "f", "i", "l"};
    // Aportan elementos unicos
    set<string> s6 = {
        "m",
        "n",
        "o",
    };
    set<string> s7 = {"p", "q", "r"};
    set<string> s8 = {"s", "t", "u", "v"};
    set<string> s9 = {"w", "x", "y", "z"};
    // Estos no aportan elementos unicos
    set<string> s10 = {"w", "z"};
    set<string> s11 = {"y", "z"};
    set<string> s12 = {"x", "y"};
    F = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12};
}
void printTime(double time)
{
    double S;
    int H, M;
    S = time / CLOCKS_PER_SEC;
    M = S / 60;
    S = fmod(S, 60);
    H = M / 60;
    M = M % 60;
    cout << "time: ";
    if (H > 0)
        cout << H << "[H] ";
    if (M > 0)
        cout << M << "[m] ";
    cout << S << "[s]";
    cout << " | time[s]: " << time / CLOCKS_PER_SEC << endl;
}
set<set<string>> UniqueSets(set<set<string>> &F, set<string> &U)
{
    set<string> Ucopy(U), temp;
    set<set<string>> C;
    int c;
    for (set<string>::iterator simb = Ucopy.begin(); simb != Ucopy.end(); ++simb)
    {
        c = 0;
        set<set<string>>::iterator conj = F.begin();
        while (conj != F.end() && c < 2)
        {
            if (setContains(*conj, *simb))
            {
                temp = *conj;
                c++;
            }
            ++conj;
        }
        if (c == 1)
        {
            F.erase(temp);
            U = setDifference(U, temp);
            C.insert(temp);
        }
    }
    return C;
}
void addNode(Node *front, Node *rear, set<string> originalSet, set<string> uniqueSet, set<string> sharedSet)
{
    Node *n = new Node;
    n->S = originalSet;
    n->unique = uniqueSet;
    n->shared = sharedSet;
    if (rear != NULL)
        rear->next = n;
    else
        front = n;
    rear = n;
}
void validateSolution(set<set<string>> sol, set<string> universe)
{
    set<string> solUniverse;
    for (set<set<string>>::iterator it = sol.begin(); it != sol.end(); ++it)
        for (set<string>::iterator elem = (*it).begin(); elem != (*it).end(); ++elem)
            solUniverse.insert(*elem);
    int solUniSize = solUniverse.size();
    int probUniSize = universe.size();
    cout << "Solution Universe Size: " << solUniSize << " | Problem Universe Size: " << probUniSize << " | ";
    if (solUniSize == probUniSize)
        cout << "VALID SOLUTION" << endl;
    else
        cout << "INVALID SOLUTION" << endl;
}
void refreshOnDataExit(Node *data, Node **front, set<set<string>> &currentSolution, set<string> &kSetUnion)
{
    if (data == NULL)
    {
        return;
    }
    cout << "aui XD?" << endl;
    currentSolution.erase(data->S);
    cout << "aqui?" << endl;
    kSetUnion = setDifference(kSetUnion, data->unique); // Eliminamos de la union de la solucion actual los elementos unicos del set en salida
    int count;
    Node *p, *q;
    cout << "aqui?" << endl;
    for (set<string>::iterator it = data->shared.begin(); it != data->shared.end(); ++it)
    { // ver con cuantos conjuntos compartia elementos
        p = *front;
        count = 0;
        cout << "aca xd?" << endl;
        while (p != NULL && count < 2)
        {
            cout << "inicio:" << count << endl;
            printSet(p->shared);
            cout << "intermedio" << endl;
            if (p->shared.find(*it) != p->shared.end())
            {
                q = p;
                count++;
            }
            cout << "intermedio" << endl;
            p++;
            cout << "fin:" << count << endl;
        }
        cout << "aco xd?" << endl;
        if (count == 1)
        { // si solo compartia con 1 conjunto, entonces el elemento es unico para este ahora
            p->shared.erase(*it);
            p->unique.insert(*it);
        }
    }
}
void refreshOnDataEntry(set<string> s, Node **front, Node **rear, set<set<string>> &currentSolution, set<string> &kSetUnion)
{
    printSet(s);
    cout << "control 1 " << endl;
    set<string> currentShare;
    set<string>::iterator it;
    Node *p = *front;
    Node *data = new Node;
    data->S = s;
    data->unique = s;
    while (p != NULL)
    {
        currentShare = setIntersection(p->unique, data->unique);
        for (set<string>::iterator i = currentShare.begin(); i != currentShare.end(); ++i)
        {
            data->unique.erase(*i);
            data->shared.insert(*i);
            data->shared.insert(*i);
        }

        p = p->next;
    }
    currentShare = setIntersection(kSetUnion, data->unique);
    for (set<string>::iterator i = currentShare.begin(); i != currentShare.end(); ++i)
    {
        data->unique.erase(*i);
        data->shared.insert(*i);
    }
    cout << "control 2 " << endl;

    currentSolution.insert(s);
    kSetUnion.insert(data->S.begin(), data->S.end());
    cout << "control 1 " << endl;
    if (*rear != NULL)
        (*rear)->next = data;
    else
        *front = data;
    *rear = data;
}
set<set<string>> maxSModV2(set<set<string>> &F, set<string> U, int k)
{
    set<set<string>> solution;
    set<string> tempSolUni;
    if (F.size() < k)
    { // caso especial donde no hay suficientes elementos, solo puede suceder al final
        solution = returnClone(F);
        F.clear();
        return solution;
    }
    set<set<string>> currentSolution;
    set<string> currentUniverse, currentShare;
    set<set<string>>::iterator setIt;
    set<string>::iterator strIt;
    int i, maxSize, currentSize, count;
    Node *front = nullptr, *rear = nullptr, *entryData, *exitData, *p, *q;

    setIt = F.begin();
    for (i = 0; i < k; i++)
    {
        // refresca la informacion vieja y suma una nueva
        entryData = new Node;
        entryData->S = *setIt;
        entryData->unique = *setIt;
        entryData->shared = {};
        p = front;
        while (p != nullptr)
        {
            currentShare = setIntersection(p->unique, entryData->unique);
            for (strIt = currentShare.begin(); strIt != currentShare.end(); ++strIt)
            {
                entryData->unique.erase(*strIt);
                entryData->shared.insert(*strIt);
                p->unique.erase(*strIt);
                p->shared.insert(*strIt);
            }
            p = p->next;
        }
        currentShare = setIntersection(entryData->unique, currentUniverse);
        for (strIt = currentShare.begin(); strIt != currentShare.end(); ++strIt)
        {
            entryData->unique.erase(*strIt);
            entryData->shared.insert(*strIt);
        }
        currentSolution.insert(entryData->S);
        for (strIt = entryData->unique.begin(); strIt != entryData->unique.end(); ++strIt)
            currentUniverse.insert(*strIt);
        if (rear != nullptr)
            rear->next = entryData;
        else
            front = entryData;
        rear = entryData;
        // fin del segmento
        ++setIt;
    }
    solution = currentSolution;
    maxSize = setIntersection(currentUniverse,U).size();
    if (front == nullptr)
    {
        cout << "ALGO SALIO EXTREMADAMENTE MAL | abortando" << endl;
        return solution;
    }
    while (setIt != F.end())
    {
        // REFRESCA la informacion al eliminar un conjunto de la posible solucion
        exitData = front;
        front = front->next;
        for (strIt = exitData->shared.begin(); strIt != exitData->shared.end(); ++strIt)
        {
            count = 0;
            p = front;
            while (p != nullptr && count < 2)
            {
                if (p->shared.find(*strIt) != p->shared.end())
                {
                    q = p;
                    count++;
                }
                p = p->next;
            }
            if (count == 1)
            {
                q->shared.erase(*strIt);
                q->unique.insert(*strIt);
            }
        }
        for (strIt = exitData->unique.begin(); strIt != exitData->unique.end(); ++strIt)
        {
            currentUniverse.erase(*strIt);
        }
        currentSolution.erase(exitData->S);
        delete exitData;
        // FIN DEL SEGMENTO
        // refresca la informacion vieja y suma una nueva
        entryData = new Node;
        entryData->S = *setIt;
        entryData->unique = *setIt;
        entryData->shared = {};
        p = front;
        while (p != nullptr)
        {
            currentShare = setIntersection(p->unique, entryData->unique);
            for (strIt = currentShare.begin(); strIt != currentShare.end(); ++strIt)
            {
                entryData->unique.erase(*strIt);
                entryData->shared.insert(*strIt);
                p->unique.erase(*strIt);
                p->shared.insert(*strIt);
            }
            p = p->next;
        }
        currentShare = setIntersection(entryData->unique, currentUniverse);
        for (strIt = currentShare.begin(); strIt != currentShare.end(); ++strIt)
        {
            entryData->unique.erase(*strIt);
            entryData->shared.insert(*strIt);
        }
        currentSolution.insert(entryData->S);
        for (strIt = entryData->unique.begin(); strIt != entryData->unique.end(); ++strIt)
            currentUniverse.insert(*strIt);
        if (front != nullptr){
            rear->next = entryData;}
        else{
            front = entryData;}
        if(front==nullptr){
        }
        if(entryData==nullptr){
        }
        rear = entryData;
        // fin del segmento
        currentSize = setIntersection(U,currentUniverse).size();
        if(maxSize<currentSize){
            maxSize = currentSize;
            solution = currentSolution;
        }
        ++setIt;
    }
    F = setDifference(F, solution);
    return solution;
}