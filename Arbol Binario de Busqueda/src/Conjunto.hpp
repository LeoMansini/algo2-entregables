// Leo Mansini. LU: 318/19

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v) : valor(v), izq(NULL), der(NULL), padre(NULL) {}


template <class T>
Conjunto<T>::Conjunto() {
    // Completar
    _raiz = NULL;
    _card = 0;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    borrarNodos(_raiz);
    _card = 0;
}

template <class T>
void Conjunto<T>::borrarNodos(Nodo* r) { 
    // Completar
    if(r != NULL){
        borrarNodos(r->der);
        borrarNodos(r->izq);
        delete r;
    }
    
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* node = _raiz;
    while(node != NULL){
        if(node->valor == clave){
            break;
        }
        else if(node->valor < clave){
            node = node->der;
        }
        else{
            node = node->izq;
        }
    }
    return(node != NULL);
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if(_raiz == NULL){
        _raiz = new Nodo(clave);
        _card++;
    }
    
    else{
        Nodo* n = _raiz;

        while(n->valor != clave){

            if((n->valor) < clave){
                if((n->der) == NULL){
                    n->der = new Nodo(clave);
                    n->der->padre = n;
                    _card++;
                }
                n = n->der;
            }

            else{
                if((n->izq) == NULL){
                    n->izq = new Nodo(clave);
                    n->izq->padre = n;
                    _card++;
                }
                n = n->izq;
            }
        }
    }
    
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(pertenece(clave)){
        _raiz = reemplazoNodo(_raiz, clave);
        _card--;
    }
        
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::reemplazoNodo(Nodo* n, const T& clave){
    if(n == NULL){
        return n;
    }
    else if(n->valor < clave){
        n->der = reemplazoNodo(n->der, clave);
    }
    else if(n->valor > clave){
        n->izq = reemplazoNodo(n->izq, clave);
    }
    else{

        if(n->izq == NULL){
            Nodo* t = n->der;
            delete n;
            return t;
        }
        else if(n->der == NULL){
            Nodo* t = n->izq;
            delete n;
            return t;
        }
        else{
            Nodo* t = buscarNodo(siguiente(clave));
            n->valor = t->valor;
            n->der = reemplazoNodo(n->der, n->valor);
        }
    }
    return n;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* n = buscarNodo(clave);
    
             
    if(n->der != NULL){
        return minimoDesde(n->der);
    }
    else{
        Nodo* p = n->padre;
        while(p != NULL && n == (p->der)){
            n = p;
            p = p->padre;
        }
        return p->valor;
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return minimoDesde(_raiz);
}

template <class T>
const T& Conjunto<T>::minimoDesde(Nodo* n) const {
    Nodo* node = n;
    while(node->izq != NULL){
        node = node->izq;
    }
    return node->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return maximoDesde(_raiz);    
}

template <class T>
const T& Conjunto<T>::maximoDesde(Nodo* n) const {
    Nodo* node = n;
    while(node->der != NULL){
        node = node->der;
    }
    return node->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _card;
}


template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscarNodo(const T& clave){
    Nodo* node = _raiz;
    while(node->valor != clave && node != NULL){

        if(node->valor < clave){
            node = node->der;            
        }

        else{
            node = node->izq;
        }
    }
    return node;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    o << "[";
    vector<T> v = vectorDeConjunto(_raiz);
    for(int i = 0; i < v.size() - 1; i++){
        o << v[i] << ", ";
    }
    o << v[v.size() - 1] << "]";
}

template <class T>
vector<T> Conjunto<T>::vectorDeConjunto(Nodo* n){
    vector<T> v;
    T min = minimo();
    T max = maximo();
    v.push_back(min);

    T next = siguiente(min);
    
    while(next != max){
        v.push_back(next);
        next = siguiente(next);        
    }
    v.push_back(max);
}

