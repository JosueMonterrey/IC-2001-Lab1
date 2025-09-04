#include <iostream>

using namespace std;

constexpr int MAX_INT = 2147483647;

class Nodo{
    public:
    int dato;
    Nodo * prev;
    Nodo * next;

    Nodo(const int val){
        dato = val;
        prev = next = nullptr;
    }
};

class Vector{
private:
    int vecSize;
    int vecMaxSize;
    Nodo * head;
    Nodo * tail;

public:
    Vector(){
        vecMaxSize = MAX_INT;
        vecSize = 0;
        head = tail = nullptr;
    }
    Vector(const int size){
        vecMaxSize = size;
        vecSize = 0;
        head = tail = nullptr;
    }

    int size(){
        return vecSize;
    }

    int max_size(){
        return vecMaxSize;
    }

    void resize(const int newSize){
        if(vecSize <= newSize)
            vecMaxSize = newSize;
    }

    void push_back(const int val){
        if(vecSize >= vecMaxSize)
            return;
            
        Nodo * nuevo = new Nodo(val);
        
        if(vecSize == 0){
            head = tail = nuevo;;
        }
        else{
            nuevo->prev = tail;
            tail->next = nuevo;
            tail = nuevo;
        }
        vecSize++;
    }

    int pop_back(){
        const int val = tail->dato;
        Nodo * del = tail;

        if(head == tail){
            head = tail = nullptr;
        }
        else{
            tail->prev->next = nullptr;
            tail = tail->prev;
        }

        delete del;
        vecSize--;
        return val;
    }

    void insert(int pos, const int val){
        if(pos > vecSize - 1)
            return push_back(val);
        
        Nodo * nuevo = new Nodo(val);
        Nodo * actual = head;

        while(pos--){
            actual = actual->next;
        }

        nuevo->prev = actual->prev;
        nuevo->next = actual;
        if(actual == head)
            head = nuevo;
        else
            actual->prev->next = nuevo;
        actual->prev = nuevo;

        vecSize++;
    }

    void erase(int pos){
        if(vecSize <= 0)
            return;

        if(pos >= vecSize - 1){
            pop_back();
            return;
        }

        Nodo * actual = head;

        while(pos--){
            actual = actual->next;
        }

        if(actual == head){
            actual->next->prev = nullptr;
            head = actual->next;
        }
        else{
            actual->prev->next = actual->next;
            actual->next->prev = actual->prev;
        }

        delete actual;
        vecSize--;
    }

    void swap(int pos1, int pos2){
        if(vecSize <= 0)
            return;

        if (pos2 < pos1) {
            pos1 ^= pos2;
            pos2 ^= pos1;
            pos1 ^= pos2;
        }

        Nodo * nodo1 = head;
        while (pos1) {
            nodo1 = nodo1->next;
            pos1--;
        }

        Nodo * nodo2 = nodo1;
        while (pos2) {
            nodo2 = nodo2->next;
            pos2--;
        }

        nodo1->dato ^= nodo2->dato;
        nodo2->dato ^= nodo1->dato;
        nodo1->dato ^= nodo2->dato;
    }

    int& at(int pos){
        Nodo * actual = head;

        while(pos--){
            actual = actual->next;
        }

        return actual->dato;
    }

    int& operator [](int i){
        return at(i);
    }

    int front(){
        return head->dato;
    }

    int back(){
        return tail->dato;
    }

    void print(){
        Nodo * actual = head;

        while(actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->next;
        }
        cout << "\n";
    }
};

void inicializarVectores (const int n, Vector vectores[]) {
    for(int i = 0; i < n; i++){
        int vecSize;
        cin >> vecSize;
        if(vecSize == -1)
            vectores[i] = Vector();
        else
            vectores[i] = Vector(vecSize);
    }
}

void print(const int& N, Vector * vectores){
    for(int vecRef = 0; vecRef < N; vecRef++){
        vectores[vecRef].print();
    }
}

int readParam(){
    int param;
    cin >> param;
    return param;
}

void procesarComando(Vector * vectores, const int& vecRef, const string& comando){
    if (comando == "sz")
        cout << vectores[vecRef].size() << "\n";

    else if (comando == "msz")
        cout << vectores[vecRef].max_size() << "\n";

    else if (comando == "rsz")
        vectores[vecRef].resize(readParam());

    else if (comando == "at")
        cout << vectores[vecRef][readParam()] << "\n";

    else if (comando == "ft")
        cout << vectores[vecRef].front() << "\n";

    else if (comando == "bk") // que rico un whopper
        cout << vectores[vecRef].back() << "\n";

    else if (comando == "pb")
        vectores[vecRef].push_back(readParam());

    else if (comando == "pbk")
        cout << vectores[vecRef].pop_back() << "\n";

    else if (comando == "in")
        vectores[vecRef].insert(readParam(), readParam());

    else if (comando == "es")
        vectores[vecRef].erase(readParam());

    else if (comando == "swp")
        vectores[vecRef].swap(readParam(), readParam());
}


void procesarLinea(const int& N, Vector * vectores){
    int vecRef;
    cin >> vecRef;

    /*
    > Si cin falla es porque el valor ingresado no era int. Entonces era string, osea que era el comando 'print'.

    > Si ese es el caso se hace clear al estado de error de cin.

    > Además, el texto ingresado que dio error sigue en el buffer. Entonces se hace un while, sacando uno por uno cada
    caracter hasta encontrar el salto de linea ('\n').

    > Caso contrario, simplemente se procesa el resto de la linea.
    */

    if(cin.fail()){
        cin.clear();
        while(cin.get() != '\n');
        print(N, vectores);
    }
    else{
        string comando;
        cin >> comando;
        procesarComando(vectores, vecRef, comando);
    }
}


int main(){
    int N, Q;
    cin >> N >> Q;

    Vector vectores[N];
    inicializarVectores(N, vectores);
    
    while(Q--){
        procesarLinea(N, vectores);
    }
}
