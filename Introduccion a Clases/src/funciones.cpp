// Leo Mansini. LU: 318/19
#include <vector>
#include "algobot.h"
#include <set>
#include <map>

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    vector<int> res;
    bool repe = false;

    for(int i = 0; i < s.size(); i++){
        for(int j = i+1; j < s.size(); j++){
            if(s[i] == s[j]){
                repe = true;
            }
        }
        if(!repe){
            res.push_back(s[i]);
        }
        repe = false;
    }
    
    return res;

}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> conj(s.begin(), s.end());

    vector<int> v(conj.begin(), conj.end());

    return v;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    bool mismos = true;

    vector<int> v1;
    vector<int> v2;

    for(int i = 0; i < a.size(); i++){
        bool esta = false;
        for(int j = 0; j < b.size(); j++){
            if(a[i] == b[j]){
                esta = true;
                break;
            }
        }
        if(!esta){
            mismos = false;
            break;
        }
    }
    
    if(mismos == true){
        
        for(int k = 0; k < b.size(); k++){
            bool esta = false;
            for(int n = 0; n < a.size(); n++){
                if(a[n] == b[k]){
                    esta = true;
                    break;
                }
            }
            if(!esta){
                mismos = false;
                break;
            }
        }
    }
    
    return mismos;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    a = quitar_repetidos_v2(a);
    b = quitar_repetidos_v2(b);

    return a == b;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> m;

    vector<int> v = quitar_repetidos_v2(s);
    
    for(int i = 0; i < v.size(); i++){
        int a = v[i];
        int n = 0;

        for(int j = 0; j < s.size(); j++){
            if(s[j] == a){
                n++;
            }
        }
        
        m.insert({a, n});
    }
    
    
    return m;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int, int> m = contar_apariciones(s);

    vector<int> v;

    for(int i = 0; i < s.size(); i ++){
        if(m[s[i]] == 1){
            v.push_back(s[i]);
        }
    }
    
    return v;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    
    vector<int> v1(a.begin(), a.end());
    vector<int> v2(b.begin(), b.end());
    set<int> inter;

    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v2.size(); j++){
            if(v1[i] == v2[j]){
                inter.insert(v1[i]);
            }
        } 
    }

    return inter;
}

// Ejercicio 8

void swap(vector<int> &s, int a, int b){
    int c = s[a];
    s[a] = s[b];
    s[b] = c;
}

void ordenar(vector<int> &s){
    for(int j = 0; j < s.size(); j++){
        for(int i = s.size()-1; i > j; i--){
            if((s[i] % 10) < (s[i-1] % 10)){
                swap(s, i, i-1);
            }
        }
    }
}

map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> m;

    ordenar(s);
    
    int i = 1;

    set<int> a;

    if(s.size() != 0){
        a.insert(s[0]);
    }

    while(i < s.size()){
        int mod = (s[i] % 10);
        int modAnt = (s[i-1] % 10);
        if(mod != modAnt){
            m.insert({modAnt, a});
            a.clear();
        }
        a.insert(s[i]);
        i++;
    }

    if(s.size() != 0){
        int modFinal = (s[i-1] % 10);
        m.insert({modFinal, a});
    }

    return m;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    map<char, char> m;
    vector<char> res;
    
    for(int i = 0; i < tr.size(); i++){
        m.insert({tr[i].first, tr[i].second});
    }

    for(int j = 0; j < str.size(); j++){
        if(m.find(str[j]) != m.end()){
            res.push_back(m[str[j]]);
        }
        else{
            res.push_back(str[j]);
        }
    }
    return res;
}

// Ejercicio 10

set<LU> interseccionLU(set<LU> a, set<LU> b) {
    
    vector<LU> v1(a.begin(), a.end());
    vector<LU> v2(b.begin(), b.end());
    set<LU> inter;

    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v2.size(); j++){
            if(v1[i] == v2[j]){
                inter.insert(v1[i]);
            }
        } 
    }

    return inter;
}


bool integrantes_repetidos(vector<Mail> s) {
    bool rep = false;
    
    vector<set<LU>> grupos;

    for(int i = 0; i < s.size(); i++){
        grupos.push_back(s[i].libretas());
    }

    for(int j = 0; j < grupos.size() && !rep; j++){
        for(int k = j+1; k < grupos.size() && !rep; k++){
            set<LU> inter = interseccionLU(grupos[j], grupos[k]);
            if(inter.size() != 0 && grupos[j] != grupos[k]){
                rep = true;
            }
        }
    }
    return rep;
}

// Ejercicio 11

map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> mapa;


    for(int i = 0; i < s.size(); i++){
        Mail m = s[i];
        if(m.adjunto()){
            if(mapa.find(m.libretas()) == mapa.end()){
                mapa.insert({m.libretas(), m});
            }
            else{
                if(m.fecha() > mapa[m.libretas()].fecha()){
                    mapa[m.libretas()] = m;
                }
            }
        }
    }
    return mapa;
}
