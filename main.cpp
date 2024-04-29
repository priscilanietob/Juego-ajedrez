/*
AJEDREZ
changed var types to enum
*/

#include <iostream>

using namespace std;

//caracteristicas generales de todas las piezas
class Pieza{
protected:


public:
    enum Color{Blanca, Negra};
    enum Tipo{Peon, Caballo, Alfil, Torre, Dama, Rey};

    Color color;
    Tipo tipo;

    //constructor y destructor
    Pieza(Color _color, Tipo _tipo) :
        color(_color), tipo(_tipo){}
    ~Pieza(){}

    //gets
    char getColor()const { return color; }
    char getTipo()const { return tipo; }

    //movimientos invalidos para cualquier pieza
    bool dentroTablero(int col_inicial, int ren_inicial, int col_final, int ren_final){
        if(col_final > 0 && col_final <= 8 && ren_final > 0 && ren_final <= 8){
            return true;
        } else {
            cout << "Jugada invalida. Fuera del tablero." << endl;
            return false;
        }
    }

    bool isCheck(){
        //revisar si esta en jaque
        return false;
    }

    bool isCheckmate(){
        //revisar si esta en jaque mate
        return false;
    }

    void actualizarPosicion(int col_inicial, int ren_inicial, int col_final, int ren_final){
        col_inicial = col_final;
        ren_inicial = ren_final;
    }

};


/* COLUMNA = col
   RENGLON = ren */

class Peon : public Pieza{
public:
    //constructor y destructor
    Peon(Color _color) :
        Pieza(_color, Tipo::Peon){}
    ~Peon(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){

        //revisar que no este en jaque/mate y q se mueva dentro del tablero
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate())){

            //q se mueva solo uno hacia en frente
            if (col_final == col_inicial && ren_final == ren_inicial + 1 && color == Color::Blanca) {
                cout << "El peon blanco se movio una casilla hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo
            } else if (col_final == col_inicial && ren_final == ren_inicial - 1 && color == Color::Negra) {
                cout << "El peon negro se movio una casilla hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo

            //q avance dos casillas cuando esta en posicion inicial
            } else if (ren_inicial == 2 && ren_final == 4 && col_inicial == col_final && color == Color::Blanca) {
                cout << "El peon blanco se movio dos casillas hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo

            } else if (ren_inicial == 7 && ren_final == 5 && col_inicial == col_final && color == Color::Negra) {
                cout << "El peon negro se movio dos casillas hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

class Caballo : public Pieza{
public:
    //constructor y destructor
    Caballo(Color _color) :
        Pieza(_color, Tipo::Caballo){}
    ~Caballo(){}

    void mover(){
        //reglas de movimiento especificas del caballo
    }
};

class Alfil : public Pieza{
public:
    //constructor y destructor
    Alfil(Color _color) :
        Pieza(_color, Tipo::Alfil){}
    ~Alfil(){}

    void mover(){
        //reglas de movimiento especificas del alfil
    }
};

class Torre : public Pieza{
public:
    //constructor y destructor
    Torre(Color _color) :
        Pieza(_color, Tipo::Torre){}
    ~Torre(){}

    void mover(){
        //reglas de movimiento especificas de la tore
    }
};

class Dama : public Pieza{
public:
    //constructor y destructor
    Dama(Color _color) :
        Pieza(_color, Tipo::Dama){}
    ~Dama(){}

    void mover(){
        //reglas de movimiento especificas de la dama
    }
};

class Rey : public Pieza{
public:
    //constructor y destructor
    Rey(Color _color) :
        Pieza(_color, Tipo::Rey){}
    ~Rey(){}

    void mover(){
        //reglas de movimiento especificas del rey
    }
};



int main()
{
    Peon peonBlancoPrueba(Pieza::Blanca);
    Peon peonNegroPrueba(Pieza::Negra);

    //se mueve una casilla
    peonBlancoPrueba.mover(1,5,1,6);
    //se mueve dos casillas desde posicion inicial
    peonNegroPrueba.mover(3,7,3,5);

    //se intenta mover dos casillas despues de posicion inicial
    peonBlancoPrueba.mover(1,6,1,8);
    //se mueve fuera del tablero
    peonBlancoPrueba.mover(1,8,1,9);


    return 0;
}

