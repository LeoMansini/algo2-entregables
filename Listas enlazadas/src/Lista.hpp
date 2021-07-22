#include "Lista.h"

Lista::Lista() : length(0), first(nullptr), last(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    // Completar

    while(length!=0){
        this->eliminar(0);
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    for(int i = this->longitud() - 1; i >= 0; i--){
        this->eliminar(i);
    }
    for(int i = aCopiar.longitud() - 1; i >= 0; i--){
        this->agregarAdelante(aCopiar.iesimo(i));
    }
    length = aCopiar.longitud();
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nodo = new Nodo();
    nodo->data = elem;
    nodo->next = first;
    if(length == 0){
        last = nodo;
    }
    else{
        first->prev = nodo;
    }
    first = nodo;
    length++;
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    Nodo* nodo = new Nodo();
    nodo->data = elem;
    nodo->prev = last;
    if(length == 0){
        first = nodo;
    } else{
        last->next = nodo;
    }
    last = nodo;
    length++;
}

void Lista::eliminar(Nat i) {
    // Completar    
    if(i == 0){
        if(length > 1){
            first = first->next;
            delete first->prev;
        }else{
            delete first;
        }
    }
    else if(i == (length-1)){
        last = last->prev;
        delete last->next;
    }
    else{
        Nodo* nodo = first;
        while(nodo->data != this->iesimo(i)){
            nodo = nodo->next;
        }
        nodo->prev->next = nodo->next;
        nodo->next->prev = nodo->prev;
        delete nodo;
    }
    length--;
}

int Lista::longitud() const {
    // Completar
    return this->length;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* nodo = first;
    Nat j = 0;
    while(j != i){
        nodo = nodo->next;
        j++;
    }
    return nodo->data;
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* nodo = first;
    Nat j = 0;
    while(j != i){
        nodo = nodo->next;
        j++;
    }
    return nodo->data;
}

void Lista::mostrar(ostream& o) {
    // Completar
    Nodo* nodo = this->first;
    o << "{";
    while(nodo != NULL){
        o << nodo->data << ", ";
        nodo = nodo->next;
    }
    o << "}";
}