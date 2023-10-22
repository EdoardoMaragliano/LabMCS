#include <iostream>
#include <TVector3.h>
#include "Particella.h"
#include "Elettrone.h"

Elettrone::Elettrone():Particella(9.1093826e-31,-1.60217653e-19){}
void Elettrone::Print() const{
  std::cout << "Elettrone, massa=" << m_massa << " carica=" << m_carica << std::endl;
}
