#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Moneda {
    private:
    int probabilidad;

    public:
    Moneda(int prob) {
        probabilidad = prob;
        srand(time(NULL));
    }

    int Tirar() {
        return !(rand() & probabilidad);
    }
};

class Nodo {
    private:
    string nombre;
    int prioridad;
    Nodo * down = nullptr;
    Nodo * next = nullptr;

    public:
    Nodo() : nombre(""), prioridad(-1) { }
    Nodo(string n, int p) : nombre(n), prioridad(p) { }

    string GetNombre() { return nombre; }
    int GetPrioridad() { return prioridad; }
    Nodo * GetDown() { return down; }
    void SetDown(Nodo * d) { down = d; }
    Nodo * GetNext() { return next; }
    void SetNext(Nodo * n) { next = n; }
};

class SkipList {
    private:
    Nodo * head = nullptr;
    Nodo * AddAux(Nodo * nodoActual, string nombre, int prioridad);
    Nodo * PopAux(Nodo * nodoActual);
    Moneda moneda;

    public:
    SkipList(int probabilidad) : head(new Nodo()), moneda(probabilidad) { }
    void Add(string nombre, int prioridad);
    string Pop();
};

void SkipList::Add(string nombre, int prioridad) {
    Nodo * ascendido = AddAux(head, nombre, prioridad);

    // overflow de ascendencia
    if (ascendido != nullptr) {
        Nodo * nuevoNodo = new Nodo(nombre, prioridad);
        nuevoNodo->SetDown(ascendido);
    
        Nodo * nuevaHead = new Nodo();
        nuevaHead->SetDown(head);
        nuevaHead->SetNext(nuevoNodo);
    
        head = nuevaHead;
    }
}

Nodo * SkipList::AddAux(Nodo * nodoActual, string nombre, int prioridad) {
    // Moverse lo más a la derecha posible
    while (nodoActual->GetNext() != nullptr && nodoActual->GetNext()->GetPrioridad() >= prioridad) {
        nodoActual = nodoActual->GetNext();
    }

    // Caso: estamos en el último nivel
    if (nodoActual->GetDown() == nullptr) {
        Nodo * nuevoNodo = new Nodo(nombre, prioridad);
        nuevoNodo->SetNext(nodoActual->GetNext());
        nodoActual->SetNext(nuevoNodo);

        return moneda.Tirar() ? nuevoNodo : nullptr;
    }

    Nodo * ascendido = AddAux(nodoActual->GetDown(), nombre, prioridad);

    // Caso: el nodo no ascendió más
    if (ascendido == nullptr) {
        return nullptr;
    }

    Nodo * nuevoNodo = new Nodo(nombre, prioridad);
    nuevoNodo->SetDown(ascendido);
    nuevoNodo->SetNext(nodoActual->GetNext());
    nodoActual->SetNext(nuevoNodo);

    return moneda.Tirar() ? nuevoNodo : nullptr;
}

string SkipList::Pop() {
    if (head->GetNext() == nullptr) {
        return "";
    }

    Nodo * popped = PopAux(head);
    string nombre = popped->GetNombre();
    delete popped;

    // Limpiar niveles vacíos
    while (head->GetNext() == nullptr && head->GetDown() != nullptr) {
        Nodo * borrarHead = head;
        head = head->GetDown();
        delete borrarHead;
    }

    return nombre;
}

Nodo * SkipList::PopAux(Nodo * headActual) {
    if (headActual->GetDown() == nullptr) {
        Nodo * popped = headActual->GetNext();
        headActual->SetNext(popped->GetNext());
        return popped;
    }

    Nodo * popped = PopAux(headActual->GetDown());
    Nodo * nextPopped = headActual->GetNext();

    if (nextPopped != nullptr && nextPopped->GetNombre() == popped->GetNombre() && nextPopped->GetPrioridad() == popped->GetPrioridad()) {
        headActual->SetNext(nextPopped->GetNext());
        delete nextPopped;
    }

    return popped;
}

int main() {
    SkipList SKL(2);

    string nombre;
    int prioridad;
    while (cin >> nombre) {
        if (nombre == "V") {
            cout << SKL.Pop() << endl;
        }
        else {
            cin >> prioridad;
            SKL.Add(nombre, prioridad);
        }
    }
}