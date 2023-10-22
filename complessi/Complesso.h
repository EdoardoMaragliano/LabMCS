//
//  complesso.hpp
//  
//
//  Created by Edoardo Maragliano on 13/10/20.
//

#ifndef complesso_hpp
#define complesso_hpp

#include <iostream>
#include "TVector2.h"


/*
 Affrontate, a scelta, uno dei seguenti problemi
 
 Create un classe di numeri complessi derivandola da TVector2 (classe di ROOT per vettori 2D). La classe deve avere almeno un metodo Print() (o la ridefinizione di <<) che stampi opportunamente il numero complesso, un metodo per il complesso coniugato, gli operatori +,-,* (per alcuni di questi, ma non per tutti, vanno bene quelli default derivati da TVector2). Create un breve programma di test

 */

class Complesso : public TVector2{
public:
    using TVector2::TVector2;		//eredita i costruttori da TVector2
    Complesso(TVector2);			//costruttore da oggetto TVector2
    double Re() const; //è ridondante ma mi piaceva avere Re e Im
    double Im() const; //in alternativa a .X() e .Y()
    void Re(double);
    void Im(double);
    Complesso Conj();
    Complesso operator*(const Complesso&) const;
    
private:
    //i membri privati di TVector2 si chiamano fX e fY
};

std::ostream& operator<<(std::ostream &stream, Complesso z);

#endif /* complessi_hpp */
