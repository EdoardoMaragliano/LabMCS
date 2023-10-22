ereditarietà

una classe base definisce un concetto generale, la classe derivata ne rappresenta una variante specifica

classe derivata --> classe base

la classe derivata eredita i dati e i metodi della classe base: elimino duplicati e riduco gli errori

Posso gerarchizzare le classi: in C++ sono possibili sia la derivazione singola sia la derivazione multipla

Esiste un linguaggio (UML) che traduce la rappresentazione grafica della gerarchia tra classi in sintassi di vari linguaggi di programmazione

Due operazioni possibili. 

--> significa derivazione
-<>- "rombo" significa inclusione

In UML il segno prima del nome indica la modalità di accesso
- private
+ public
# protected
il tipo del dato segue il nome del dato

Implementazione in C++

class myclass{
    public:
    protected://accessibile dalle classi derivate ma non dal resto del programma
    private:
    
};

class Derivata : public Base1, public Base2{
public:
private:
    
}

// i nomi dopo i: indicano da quali classi base eredito
// la keyword prima del nome delle classi base mi dice il tipo di derivazione:
// se faccio derivazione pubblica ciò che è pubblico di base resta pubblico
// se faccio derivazione protected ciò che è pubblico diventa protected
// se faccio derivazione privata diventa tutto privato


// Di default in C++ il costruttore della classe base non viene ereditato. Bisogna specificare

class Derivata : public Base1, public Base2{
public:
    using Base::Base;   //erida il costruttore della classe base
private:
    
}

Esiste anche la costruzione per delega (vedi slides).

COMPOSIZIONE O EREDITARIETÀ

//Ereditarietà (is a)
class B{};
class A : public b{};
//Composizione (has a)

Rispettare il seguente criterio: ogni metodo della classe base deve funzionare sulla derivata senza ulteriori informazioni

esempi:
//creo una classe punto
class punto{ public :
    punto(double x=0, double y=0):m x(x) ,m y(y){} double dist(const punto& b);
    
    double X(){return m x;} 
    double Y(){return m y;}
    
    private :
    double m x,m y;
};
class poligono{ //un poligono ha dei punti=> compongo la classe punto, non eredito
    public :
    poligono(const vector<punto>& punti):m punti(punti){};
    poligono () : poligono (vector<punto>(0)){} 
    double perimetro () ;
    void print () ; 
    protected :
    vector <punto> m punti ; 
    
};

void poligono :: print (){
    for (auto p: m punti)
    cout << p.X() << ” ” << p.Y() << endl;
}

class triangolo : public poligono{
    public :
    using poligono :: poligono ;
    triangolo(double a, double b, double theta):poligono(){
        m punti.push back(punto(0,0)); 
        m punti.push back(punto(a,0));
        m punti.push back(punto(b∗cos(theta),b∗sin(theta)));
        
    }

    int main(){
        triangolo t(1,1,M_PI/2);
        t.print();
        return 0;
    }


    //Supponiamo di voler utilizzare la classe vector della STL dotandola di calcolo vettoriale: eredito da un template e faccio una classe template
    
    template <class T>
    class vectorn: public vector<T>{
    public:
        using vector<T>::vector;
        vector<T> operator+(const vectorn&) const;
        vector<T> operator*(double) const;
    }

Polimorfismo
    1. compile time => overloading e template
    2. run time => ereditarietà e keyword virtual
    
    La keyword virtual:
    i metodi di una classe base possono essere chimati virtual
    
    virtual retType funcName(parType);
    
    Una classe che eredita un metodo virtual lo può ridefinire.
    Rimando al run time la scelta del metodo
    esempio
    
#include <iostream> class Animale{
    public : Animale () {}
    virtual void parla (){ std :: cout << ”???” << std :: endl ;} 
    
};
class Cane: public Animale{ public :
    using Animale :: Animale ;
    void parla(){ std::cout << ”Bau” << std::endl;
        
    }
};
class Gatto : public Animale{
    public :
    using Animale :: Animale ;
    void parla (){ std :: cout << ”Miao” << std :: endl ;}
    
};
class Uomo: public Animale{ public :
    using Animale :: Animale ;
    void parla (){ std :: cout << ”Burp” << std :: endl ;
        
    }
};

int main(){
cout << ”Inserisci il nome dell ’animale” << endl; //decido runtime che animale ho
    string opt ; 
    cin >> opt ;
Animale ∗p ;        // creo un puntatore a un oggetto della classe base
if (opt==”Cane”)
p = new Cane;
else if (opt==”Gatto”)
p = new Gatto;
else if (opt==”Uomo”)
p = new Uomo;      
// da qui in poi il codice e ’ implementato con // il puntatore della classe base
p −> parla ( ) ;
return 0;
}


CLASSI ASTRATTE <=> METODI PURAMENTE VIRTUALI
Dichiarati uguali a 0

class Poligono{
    public : ...
    virtual double area() = 0; 
    virtual double perimetro () ;
    ...
}
Nota che non posso creare un vero e proprio oggetto funzionante, in questo modo creo solo una interfaccia


CASTING IN C++

static_cast 
non posso convertire puntatori di oggetti di un tipo a oggetti di un altro, ma posso convertire puntatori di oggetti derivati a puntatori a oggetti da cui derivano
dynamic_cast
funziona in runtime e converte puntatori di classi collegate


IL COMANDO MAKE

target : dependancies
[tab]    system command

OBIETTIVI DEL PROGETTO

classe particella (carica e massa)
classe punto materiale(posizione e velocità)
implementare un metodo CampoGravitazionale che calcoli il campo prodotto da un corpo massivo
Usare la classe Vettore per la rappresentazione dei vettori 3D

Consigli: pensa di avere una classe particella e fai i diagrammi per la classe puntomateriale

class particella{
public:
    particella(double massa=0, double carica=0):m_massa(massa),m_carica(carica){}
    double Massa(){return m_massa};
    double Carica() {return m_carica};
private:
    double m_massa, m_carica;

};
