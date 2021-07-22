template <typename T>
string_map<T>::Nodo::Nodo() : siguientes(256, NULL), definicion(NULL), hijos(0) { }

template <typename T>
string_map<T>::Nodo::Nodo(T* def) : siguientes(256, NULL), definicion(def), hijos(0) { }

template <typename T>
string_map<T>::string_map(){
    // COMPLETAR
    _size = 0;
    raiz = NULL;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } 
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
    vector<pair<string, T>> vec1 = definiciones(raiz);
    
    for(int i = 0; i < vec1.size(); i++){
        erase(vec1[i].first);
    }


    vector<pair<string, T>> vec2 = definiciones(d.raiz);
    
    for(int i = 0; i < vec2.size(); i++){
        insert(vec2[i]);
    }


    return *this;
}

template <typename T>
vector<pair<string, T>> string_map<T>::definiciones(Nodo* n){
    vector<pair<string, T>> s;
    vector<pair<string, T>> v;
    if(n != NULL){
        
        for(int i = 0; i < 256; i++){
            if(n->siguientes[i] != NULL){
                s = definiciones(n->siguientes[i]);
                for(int i = 0; i < s.size(); i++){
                    v.push_back(s[i]);
                }
            }
        }
        if(n->definicion != NULL){
            v.push_back(make_pair(*(n->clave), *(n->definicion)));
        }
    }
    return v;
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
    if(raiz == NULL){
        delete raiz;
    }
    else if(_size == 1 && raiz->definicion != NULL){
        T* aBorrarDef = raiz->definicion;
        string* aBorrarCl = raiz->clave;
        raiz->clave = NULL;
        raiz->definicion = NULL;
        delete aBorrarDef;
        delete aBorrarCl;
    }

    else{
        borrarNodos(raiz);
    }
    
    _size = 0;
}

template <typename T>
void string_map<T>::borrarNodos(Nodo* r){
    // COMPLETAR
    for(int i = 0; i < 256; i++){
        if(r->siguientes[i] != NULL){
            Nodo* aBorrar = r->siguientes[i];
            r->siguientes[i] = NULL;
            borrarNodos(aBorrar);
        }
    }
    if(r->definicion != NULL){
        T* aBorrarDef = r->definicion;
        string* aBorrarCl = r->clave;
        r->clave = NULL;
        r->definicion = NULL;
        delete aBorrarDef;
        delete aBorrarCl;
    }
    Nodo* final = r;
    r = NULL;
    delete final;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p){
    
    
    if(raiz == NULL){
        raiz = new Nodo();
    }
    Nodo* n = raiz;
    n->hijos++;
    int i = 0;

    while(i != p.first.length()){
        char letra = p.first[i];
        

        if(n->siguientes[int(letra) - 1] == NULL){
            n->siguientes[int(letra) - 1] = new Nodo();
        }
        n = n->siguientes[int(letra) - 1];
        n->hijos++;
        i++;
    }
    T* def = new T(p.second);

    if(n->definicion == NULL){
        _size++;
        n->definicion = def;
        string* key = new string(p.first);
        n->clave = key;
    }
    else{
        T* aBorrar = n->definicion;
        string* aBorrarCl = n->clave;
        n->clave = NULL;
        n->definicion = NULL;
        delete aBorrarCl;
        delete aBorrar;
        n->definicion = def;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
    if(count(clave) == 0){
        insert(make_pair(clave, T()));
        return at(clave);
    }
    
    else{
        Nodo* n = raiz;    
        int i = 0;

        while(i != clave.length()){
            char letra = clave[i];
            n = n->siguientes[int(letra) - 1];
            i++;
        }
        return *(n->definicion);
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    // COMPLETAR
    Nodo* n = raiz;
    if(raiz != NULL){
        int i = 0;

        while(i != clave.length()){
            char letra = clave[i];
            if(n->siguientes[int(letra) - 1] == NULL){
                return 0;
            }
            n = n->siguientes[int(letra) - 1];
            i++;
        }
        return (n->definicion != NULL) ? 1 : 0;
    }
    else{
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
    Nodo* n = raiz;  
    int i = 0;

    while(i != clave.length()){
        char letra = clave[i];
        n = n->siguientes[int(letra) - 1];
        i++;
    }
    return *(n->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
    Nodo* n = raiz;    
    int i = 0;

    while(i != clave.length()){
        char letra = clave[i];
        n = n->siguientes[int(letra) - 1];
        i++;
    }
    return *(n->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
    Nodo* n = raiz;    
    int i = 0;
    bool borreNodos = false;

    if(clave == ""){
        if(raiz->definicion != NULL){
            T* aBorrar = n->definicion;
            string* aBorrarCl = n->clave;
            n->clave = NULL;
            n->definicion = NULL;
            delete aBorrar;
            delete aBorrarCl;
        }
    }

    while(i != clave.length() - 1){
        char letra = clave[i];
        if(n->siguientes[int(letra) - 1]->hijos == 1){
            Nodo* b = n->siguientes[int(letra) - 1];
            n->siguientes[int(letra) - 1] = NULL;
            borrarNodos(b);
            borreNodos = true;
            break;
        }
        else{
            n->hijos--;
            n = n->siguientes[int(letra) - 1];
            i++;
        }
    }
    if(borreNodos == false){
        n = n->siguientes[int(clave[i]) - 1];
        T* aBorrar = n->definicion;
        string* aBorrarCl = n->clave;
        n->clave = NULL;
        n->definicion = NULL;
        delete aBorrar;
        delete aBorrarCl;
    }
    _size--;


}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
    return (_size == 0);
}