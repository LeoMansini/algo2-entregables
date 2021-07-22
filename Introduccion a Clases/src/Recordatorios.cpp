// Leo Mansini. LU 318/19
#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    // Completar declaraciones funciones
    Fecha(uint m, uint d);
    uint mes();
    uint dia();
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif
    void incrementar_dia();
    bool operator<(Fecha o);

  private:
    //Completar miembros internos
    int dia_;
    int mes_;
};

Fecha::Fecha(uint m, uint d) :  mes_(m), dia_(d) {};

uint Fecha::dia(){
  return dia_;
}

uint Fecha::mes(){
  return mes_;
}

void Fecha::incrementar_dia(){
  uint maxdia = dias_en_mes(this->mes());
  if(this->dia() + 1 > maxdia){
    dia_ = 1;
    mes_++;
  }
  else{
    dia_++;
  }
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    // Completar iguadad (ej 9)
    bool igual_mes = this->mes() == o.mes();
    return igual_dia and igual_mes;
}
#endif

bool Fecha::operator<(Fecha o){
  bool diaAnterior = false;
  bool mesAnterior = false;
  if(this->mes() < o.mes()){
    mesAnterior = true;
  }
  if(this->mes() == o.mes() && this->dia() < o.dia()){
    diaAnterior = true;
  }

  return mesAnterior || diaAnterior;
}

// Ejercicio 11, 12

// Clase Horario

class Horario{
  public:
    Horario(uint h, uint m);
    uint hora();
    uint min();
    bool operator==(Horario ho);
    bool operator<(Horario ho);

  private:
    int h_;
    int m_;

};

Horario::Horario(uint h, uint m) : h_(h), m_(m) {};

uint Horario::hora(){
  return h_;
}

uint Horario::min(){
  return m_;
}

bool Horario::operator==(Horario ho){
  bool mismaHora = this->hora() == ho.hora();
  bool mismomin = this->min() == ho.min();

  return mismaHora and mismomin;
}

bool Horario::operator<(Horario ho){
  bool horaAnterior = false;
  bool minAnterior = false;
  if(this->hora() < ho.hora()){
    horaAnterior = true;
  }
  if(this->hora() == ho.hora() && this->min() < ho.min()){
    minAnterior = true;
  }

  return horaAnterior || minAnterior;
}

ostream& operator<<(ostream& os, Horario ho) {
    os << ho.hora() << ":" << ho.min();
    return os;
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio{
  public:
    Recordatorio(Fecha f, Horario h, string nota);
    Fecha f();
    Horario h();
    string nota();
    bool operator<(Recordatorio r);
  
  private:
    Fecha f_;
    Horario h_;
    string nota_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string nota) : f_(f), h_(h), nota_(nota) {};

Fecha Recordatorio::f(){
  return f_;
}

Horario Recordatorio::h(){
  return h_;
}

string Recordatorio::nota(){
  return nota_;
}

bool Recordatorio::operator<(Recordatorio r){
  bool fechaAnterior = this->f() < r.f();
  bool fechaIgual = this->f() == r.f();
  bool horarioAnterior = this->h() < r.h();

  return fechaAnterior || (fechaIgual && horarioAnterior);
  
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.nota() << " @ " << r.f() << " " << r.h();
    return os;
}

// Ejercicio 14

// Clase Agenda

class Agenda {
  public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
  
  private:
    Fecha hoy_;
    list<Recordatorio> recordatorios_;
};

Agenda::Agenda(Fecha fecha_inicial) : hoy_(fecha_inicial), recordatorios_() {};

Fecha Agenda::hoy(){
  return hoy_;
}

void Agenda::agregar_recordatorio(Recordatorio rec){
  recordatorios_.push_back(rec);
}

void Agenda::incrementar_dia(){
  hoy_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy(){
  list<Recordatorio> recs;
  for(Recordatorio i : recordatorios_){
    if(i.f().dia() == hoy().dia()){
      recs.push_back(i);
    }
  }
  return recs;
}

ostream& operator<<(ostream& os, Agenda a) {
    list<Recordatorio> recs = a.recordatorios_de_hoy();
    recs.sort();
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(Recordatorio i : recs){
      os << i << endl;
    } 
    return os;
}