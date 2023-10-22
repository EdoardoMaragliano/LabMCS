//
//  Particella.h
//  
//
//  Created by Edoardo Maragliano on 28/09/20.
//

#ifndef Particella_h
#define Particella_h

#include <string>

using namespace std;

class Particella{
public:
    Particella(double massa=0, double carica=0):m_massa(massa),m_carica(carica){}
    //il costruttore setta massa e carica
    //setters
    void Massa(double);
    void Carica(double);
    void Name(string);
    //getters
    double Massa() const; 
    double Carica() const;
    string Name() const;
    
private:
    double m_massa, m_carica;
    string m_name;
    
};


class Elettrone : public Particella{
    public: Elettrone();
};

class Protone : public Particella{
    public: Protone();
};

#endif /* particella_h */


