/*
AJEDREZ
layout inicial clases piezas
Arleth Berumen 37228
16/4/24*/

#include <iostream>

using namespace std;

//caracteristicas generales de todas las piezas
class Pieza{
protected:
    char color; //B o N
    char tipo; //por iniciales
public:
    //constructor y destructor
    Pieza(char _color, char _tipo) :
        color(_color), tipo(_tipo){}
    ~Pieza(){}

    //gets
    char getColor()const { return color; }
    char getTipo()const { return tipo; }

    //movimientos invalidos para cualquier pieza
    bool dentroTablero(int col_inicial, int ren_inicial, int col_final, int ren_final) const{
        if((0 < col_final < 8) && (0 < ren_final < 8)){
            return true;
        }
    }


};


/* COLUMNA = col
   RENGLON = ren */

class Peon : public Pieza{
public:
    //constructor y destrutor
    Peon(char _color) :
        Pieza(color, 'P'){}
    ~Peon(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){

        if(!dentroTablero(col_inicial, ren_inicial, col_final, ren_final)){
            cout << "Jugada invalida." << endl; //implementacion preliminar de jugada invalida
        }

        //jugadas posibles de un peon

        //q se mueva solo uno hacia en frente
        if (col_final == col_inicial && ren_final == ren_inicial + 1 && color == 'B') {
            //aqui se actualizaria su posicion en el tablero

        } else if (col_final == col_inicial && ren_final == ren_inicial - 1 && color == 'N') {
            //posicion se actualiza

        //q avance dos casillas cuando esta en posicion inicial
        } else if (ren_inicial == 2 && ren_final == 4 && col_inicial == col_final && color == 'B') {
            // posicion se actualiza

        } else if (ren_inicial == 7 && ren_final == 5 && col_inicial == col_final && color == 'N') {
            //actualizar posicion
        }
    }
};

class Caballo : public Pieza{
public:
    //constructor y destructor
    Caballo(char _color) :
        Pieza(color, 'C'){}
    ~Caballo(){}

    void mover(){
        //reglas de movimiento especificas del caballo
    }
};

class Alfil : public Pieza{
public:
    //constructor y destructor
    Alfil(char _color) :
        Pieza(color, 'A'){}
    ~Alfil(){}

    void mover(){
        //reglas de movimiento especificas del alfil
    }
};

class Torre : public Pieza{
public:
    //constructor y destructor
    Torre(char _color) :
        Pieza(color, 'T'){}
    ~Torre(){}

    void mover(){
        //reglas de movimiento especificas de la tore
    }
};

class Dama : public Pieza{
public:
    //constructor y destructor
    Dama(char _color) :
        Pieza(color, 'D'){}
    ~Dama(){}

    void mover(){
        //reglas de movimiento especificas de la dama
    }
};

class Rey : public Pieza{
public:
    //constructor y destructor
    Rey(char _color) :
        Pieza(color, 'R'){}
    ~Rey(){}

    void mover(){
        //reglas de movimiento especificas del rey
    }
};



int main()
{

    return 0;
}
