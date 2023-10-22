
#include "Particella.h"


    //setters
void Particella::Massa(double massa){
    m_massa=massa;
}
void Particella::Carica(double carica){
    m_carica=carica;
}
void Particella::Name(string nome){
    m_name=nome;
}

    //getters
double Particella::Massa() const{
    return m_massa;
}
double Particella::Carica() const{
    return m_carica;
}

string Particella::Name() const{
    return m_name;
}

Elettrone :: Elettrone(): Particella(9.1093826E-31, -1.6021763E-19){}
//uso il costruttore di Particella settando i valori

Protone :: Protone(): Particella(1.67262192369E-27, +1.6021763E-19){}
