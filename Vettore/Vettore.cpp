#include "Vettore.h"

//accesso alle variabili
double Vettore::X() const{
  return m_v[0];
}

double Vettore::Y() const{
  return m_v[1];
}

double Vettore::Z() const{
  return m_v[2];
}
//set delle variabili
void Vettore::X(double x){
  m_v[0] = x;
}

void Vettore::Y(double y){
  m_v[1] = y;
}

void Vettore::Z(double z){
  m_v[2] = z;
}
//metodi vari

double Vettore::getModulus() const {        //modulo
    return sqrt(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2]);
}

//funzioni esterne
double dot(const Vettore& a, const Vettore& b){ //prod scalare
    return a.X()*b.X()+a.Y()*b.Y()+a.Z()*b.Z();
}
Vettore cross(const Vettore& a, const Vettore& b){  //prod vettore
    Vettore prod;
    prod.X(a.Y()*b.Z()-a.Z()*b.X());
    prod.Y(a.Z()*b.X()-a.X()*b.Z());
    prod.Z(a.X()*b.Y()-a.Y()*b.X());
    return prod;
}



//operatori
Vettore Vettore::operator-() const{     //meno unario
  Vettore res;              //creo un oggetto vettore
  for (int i=0;i<3;i++){
    res.m_v[i] = -m_v[i];   //inverto i segni delle sue variabili
  }
  return res;               //restituisco l'oggetto vettore
}

Vettore Vettore::operator+(const Vettore& b) const{ //somma
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] + b.m_v[i];
  }
  return res;
}


Vettore Vettore::operator-(const Vettore& b) const{ //differenza
  Vettore res = (*this)+(-b);
  return res;
}

Vettore Vettore::operator*(double b) const{     //prodotto per scalare come metodo
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = b*m_v[i];
  }
  return res;
}

double Vettore::operator*(const Vettore& b){        //prodotto scalare
    return this->X()*b.X()+this->Y()*b.Y()+this->Z()*b.Z();
}
//this si riferisce all'oggetto che precede l'operatore

Vettore Vettore::operator^(const Vettore& b) const{//prodotto vettore
    Vettore prod;
    prod.X(m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1]);
    prod.Y(m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2]);
    prod.Z(m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0]);
    return prod;    
}

Vettore operator*(double b, const Vettore& a){     //prodotto per scalare (funzione)
  return a*b;
}

//stream
std::ostream& operator<<(std::ostream &stream, Vettore v){
  stream << "(" << v.X() << "," << v.Y() << "," << v.Z() << ")";
  return stream;
}

std::istream& operator>>(std::istream &stream, Vettore &v){
  double x,y,z;
  stream >> x >> y >> z;
  v.X(x); v.Y(y); v.Z(z);
  return stream;
}

