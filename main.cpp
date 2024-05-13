/*
AJEDREZ
se agrego movimiento del rey
*/

#include <iostream>

using namespace std;

class Tablero {
    int columna;
    int renglon;
public:
    Tablero(){}
    ~Tablero(){}

    //funcion de registro de jugadas


    //funcion de cambio de turno
};

//caracteristicas generales de todas las piezas
class Pieza{
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

    bool esJaque(){
        //revisar si esta en jaque
        return false;
    }

    bool esJaquemate(){
        //revisar si esta en jaque mate
        return false;
    }

    bool casillaOcupada(){
        //checar si la casilla esta ocupada
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

        //revisar que no este en jaque/mate y q se mueva dentro del tablero Y q no este ocupada la casilla
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){

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

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){
            if ((col_final == col_inicial-1 || col_inicial+1) && (ren_final == ren_inicial + 2 || ren_final == ren_inicial - 2)) {
                cout << "El caballo se movio hacia el norte o el sur." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else if ((ren_final == ren_inicial-1 || ren_inicial+1) && (col_final == col_inicial + 2 || col_final == col_inicial - 2)) {
                cout << "El caballo se movio al este u oeste." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

class Alfil : public Pieza{
public:
    //constructor y destructor
    Alfil(Color _color) :
        Pieza(_color, Tipo::Alfil){}
    ~Alfil(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        //reglas de movimiento especificas del alfil
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;


        //obetner valor absoluto para que los signos no afecten la igualdad
        if(renglonDiff<0){
            renglonDiff = renglonDiff*(-1);
        }

        if(columnaDiff<0){
            columnaDiff = columnaDiff*(-1);
        }

        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){
            if (columnaDiff == renglonDiff) {
                cout << "El alfil se movio." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

class Torre : public Pieza{
public:
    //constructor y destructor
    Torre(Color _color) :
        Pieza(_color, Tipo::Torre){}
    ~Torre(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        //reglas de movimiento especificas de la tore
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){
            if (col_inicial == col_final || ren_inicial == ren_final) {
                cout << "La torre se movio." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

class Dama : public Pieza{
public:
    //constructor y destructor
    Dama(Color _color) :
        Pieza(_color, Tipo::Dama){}
    ~Dama(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if(renglonDiff<0){
            renglonDiff = renglonDiff*(-1);
        }
        if(columnaDiff<0){
            columnaDiff = columnaDiff*(-1);
        }

        //reglas de movimiento especificas de la dama
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){
            if (columnaDiff == renglonDiff) {
                cout << "La dama se movio en diagonal." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else if (col_inicial == col_final || ren_inicial == ren_final){
                cout << "La dama se movio en horizontal o vertical." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

class Rey : public Pieza{
public:
    //constructor y destructor
    Rey(Color _color) :
        Pieza(_color, Tipo::Rey){}
    ~Rey(){}

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if(renglonDiff<0){
            renglonDiff = renglonDiff*(-1);
        }
        if(columnaDiff<0){
            columnaDiff = columnaDiff*(-1);
        }

        //reglas de movimiento especificas de la dama
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && (!casillaOcupada())){
            if(columnaDiff <=1 && renglonDiff<=1){ //se asegura que solo se mueva una casilla
                if (columnaDiff == renglonDiff) {
                    cout << "El rey se movio en alguna diagonal." << endl;
                    Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                    //cambio turno
                } else if (col_inicial == col_final || ren_inicial == ren_final){
                    cout << "El rey se movio en horizontal o vertical." << endl;
                    Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                    //cambio turno
                }
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }
};

int main()
{
    Rey reyPrueba(Pieza::Blanca);

    //invalidas
    reyPrueba.mover(1,1,3,2);

    //diagonal
    reyPrueba.mover(1,1,2,2);
    reyPrueba.mover(8,8,7,7);

    //invalida
    reyPrueba.mover(8,8,7,6);

    //horizontal y vertical
    reyPrueba.mover(1,1,1,2);
    reyPrueba.mover(5,3,6,3);

    return 0;
}
