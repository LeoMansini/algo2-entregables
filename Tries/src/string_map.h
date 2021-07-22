#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

    void mostrarDefs(){
        cout << "[";
        vector<pair<string, T>> s = definiciones(raiz);
        for(int i = 0; i < s.size() - 1; i++){
            cout << s[i].first << "->" << s[i].second << ", ";
        }
        cout << s[s.size() - 1].first << "->" << s[s.size() - 1].second << "]";
    }

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        string* clave;
        Nodo();
        Nodo(T* def);
        int hijos;
    };

    Nodo* raiz;
    int _size;
    void borrarNodos(Nodo* r);
    vector<pair<string, T>> definiciones(Nodo* n);
    void insertarTodo(Nodo* n);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_