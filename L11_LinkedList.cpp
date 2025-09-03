#include <iostream>

using namespace std;

class Nodo {
    private:
    string nombre;
    int prioridad;
    Nodo * next = nullptr;

    public:
    Nodo(string n, int p) : nombre(n), prioridad(p) { }

    string GetNombre() { return nombre; }
    int GetPrioridad() { return prioridad; }
    Nodo * GetNext() { return next; }
    void SetNext(Nodo * n) { next = n; }
};

class SingleLinkedList {
    private:
    Nodo * head = nullptr;

    public:
    void Add(string nombre, int prioridad);
    string Pop();
};

void SingleLinkedList::Add(string nombre, int prioridad) {
    Nodo * nuevoNodo = new Nodo(nombre, prioridad);
    
    if (head == nullptr) {
        head = nuevoNodo;
        return;
    }
    
    if (prioridad > head->GetPrioridad()) {
        nuevoNodo->SetNext(head);
        head = nuevoNodo;
        return;
    }
    
    Nodo * nodoActual = head;
    while (nodoActual->GetNext() != nullptr && nodoActual->GetNext()->GetPrioridad() >= prioridad) {
        nodoActual = nodoActual->GetNext();
    }

    nuevoNodo->SetNext(nodoActual->GetNext());
    nodoActual->SetNext(nuevoNodo);
}

string SingleLinkedList::Pop() {
    if (head == nullptr) {
        return "";
    }

    Nodo * popped = head;
    head = popped->GetNext();
    string nombre = popped->GetNombre();
    delete popped;
    return nombre;
}

int main() {
    SingleLinkedList SLL;

    string nombre;
    int prioridad;
    while (cin >> nombre) {
        if (nombre == "V") {
            cout << SLL.Pop() << "\n";
        }
        else {
            cin >> prioridad;
            SLL.Add(nombre, prioridad);
        }
    }
}