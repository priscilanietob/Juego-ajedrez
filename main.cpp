/*
AJEDREZ
se agrega funcion bool casillaOcupadaOponente()
esta funcion revisa que la casilla este ocupada y que ademas la pieza que la ocupa sea del color opuesto
*/

#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TableroValores.h"

using namespace std;
using namespace sf;

class Tablero {
    int columna;
    int renglon;
    enum Color {Blanca, Negra};
    Color turnoActual = Color::Blanca;

public:
    Tablero() {}
    ~Tablero() {}

    //funcion de registro de jugadas

    //funcion de cambio de turno
    void cambiarTurno()
    {
        if (turnoActual == Color::Blanca)
        {
            turnoActual = Color::Negra;
        }
        else
        {
            turnoActual = Color::Blanca;
        }
    }
    string getTurnoATexto() const
    {
        return (turnoActual == Blanca) ? "Blanco" : "Negro";
    }

    void displayTurno()
    {
        cout << "Turno de: " << getTurnoATexto() << endl;
        cambiarTurno();
        cout << "Ahora es turno de: " << getTurnoATexto() << endl;
        cambiarTurno();
        cout << "Ahora es turno de: " << getTurnoATexto() << endl;
    }
};
//caracteristicas generales de todas las piezas
class Pieza {
public:
    enum Color { Blanca, Negra };
    enum Tipo { Peon, Caballo, Alfil, Torre, Dama, Rey };

    Color color;
    Tipo tipo;

    //constructor y destructor
    Pieza(Color _color, Tipo _tipo) :
        color(_color), tipo(_tipo) {}
    ~Pieza() {}

    //gets
    char getColor()const { return color; }
    char getTipo()const { return tipo; }

    //movimientos invalidos para cualquier pieza
    bool dentroTablero(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        if (col_final > 0 && col_final <= 8 && ren_final > 0 && ren_final <= 8) {
            return true;
        }
        else {
            cout << "Jugada invalida. Fuera del tablero." << endl;
            return false;
        }
    }

    bool esJaque() {
        //revisar si esta en jaque
        return false;
    }

    bool esJaquemate() {
        //revisar si esta en jaque mate
        return false;
    }

    bool casillaOcupada(Pieza* tablero[8][8], int col, int ren) const {
        return tablero[col - 1][ren - 1] != nullptr; //se le quita uno por lo de los indices
    }

    void actualizarPosicion(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        col_inicial = col_final;
        ren_inicial = ren_final;
    }

};

class Peon : public Pieza {
public:
    //constructor y destructor
    Peon(Color _color) :
        Pieza(_color, Tipo::Peon) {}
    ~Peon() {}

    //para revisar si se puede mover a cierta casilla, independientemente de si esta ocupada o no
    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        //revisar que no este en jaque/mate y q se mueva dentro del tablero
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            //q se mueva solo uno hacia en frente
            if (col_final == col_inicial && ren_final == ren_inicial + 1 && color == Color::Blanca) {
                return true;
            }
            else if (col_final == col_inicial && ren_final == ren_inicial - 1 && color == Color::Negra) {
                return true;
                //q avance dos casillas cuando esta en posicion inicial
            }
            else if (ren_inicial == 2 && ren_final == 4 && col_inicial == col_final && color == Color::Blanca) {
                return true;
            }
            else if (ren_inicial == 7 && ren_final == 5 && col_inicial == col_final && color == Color::Negra) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {

        //revisar que no este en jaque/mate y q se mueva dentro del tablero Y q no este ocupada la casilla
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {

            //q se mueva solo uno hacia en frente
            if (col_final == col_inicial && ren_final == ren_inicial + 1 && color == Color::Blanca) {
                cout << "El peon blanco se movio una casilla hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo
            }
            else if (col_final == col_inicial && ren_final == ren_inicial - 1 && color == Color::Negra) {
                cout << "El peon negro se movio una casilla hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo

            //q avance dos casillas cuando esta en posicion inicial
            }
            else if (ren_inicial == 2 && ren_final == 4 && col_inicial == col_final && color == Color::Blanca) {
                cout << "El peon blanco se movio dos casillas hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo

            }
            else if (ren_inicial == 7 && ren_final == 5 && col_inicial == col_final && color == Color::Negra) {
                cout << "El peon negro se movio dos casillas hacia en frente." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
                    //codigo
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};

class Caballo : public Pieza {
public:
    //constructor y destructor
    Caballo(Color _color) :
        Pieza(_color, Tipo::Caballo) {}
    ~Caballo() {}

    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            if ((col_final == col_inicial - 1 || col_inicial + 1) && (ren_final == ren_inicial + 2 || ren_final == ren_inicial - 2)) {
                return true;
            }
            else if ((ren_final == ren_inicial - 1 || ren_inicial + 1) && (col_final == col_inicial + 2 || col_final == col_inicial - 2)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {
            if ((col_final == col_inicial - 1 || col_inicial + 1) && (ren_final == ren_inicial + 2 || ren_final == ren_inicial - 2)) {
                cout << "El caballo se movio hacia el norte o el sur." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else if ((ren_final == ren_inicial - 1 || ren_inicial + 1) && (col_final == col_inicial + 2 || col_final == col_inicial - 2)) {
                cout << "El caballo se movio al este u oeste." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};

class Alfil : public Pieza {
public:
    //constructor y destructor
    Alfil(Color _color) :
        Pieza(_color, Tipo::Alfil) {}
    ~Alfil() {}

    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        //reglas de movimiento especificas del alfil
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        //obetner valor absoluto para que los signos no afecten la igualdad
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }

        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            if (columnaDiff == renglonDiff) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {
        //reglas de movimiento especificas del alfil
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;


        //obetner valor absoluto para que los signos no afecten la igualdad
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }

        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {
            if (columnaDiff == renglonDiff) {
                cout << "El alfil se movio." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};


class Torre : public Pieza {
public:
    //constructor y destructor
    Torre(Color _color) :
        Pieza(_color, Tipo::Torre) {}
    ~Torre() {}

    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        //reglas de movimiento especificas de la torre
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            if (col_inicial == col_final || ren_inicial == ren_final) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {
        //reglas de movimiento especificas de la tore
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {
            if (col_inicial == col_final || ren_inicial == ren_final) {
                cout << "La torre se movio." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};

class Dama : public Pieza {
public:
    //constructor y destructor
    Dama(Color _color) :
        Pieza(_color, Tipo::Dama) {}
    ~Dama() {}

    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }
        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        //reglas de movimiento especificas de la dama
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            if (columnaDiff == renglonDiff) {
                return true;
            }
            else if (col_inicial == col_final || ren_inicial == ren_final) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }
        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        //reglas de movimiento especificas de la dama
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {
            if (columnaDiff == renglonDiff) {
                cout << "La dama se movio en diagonal." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else if (col_inicial == col_final || ren_inicial == ren_final) {
                cout << "La dama se movio en horizontal o vertical." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};

class Rey : public Pieza {
public:
    //constructor y destructor
    Rey(Color _color) :
        Pieza(_color, Tipo::Rey) {}
    ~Rey() {}

    bool puedeMoverse(int col_inicial, int ren_inicial, int col_final, int ren_final) {
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }
        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        //reglas de movimiento especificas de la dama
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate())) {
            if (columnaDiff <= 1 && renglonDiff <= 1) { //se asegura que solo se mueva una casilla
                if (columnaDiff == renglonDiff) {
                    return true;
                }
                else if (col_inicial == col_final || ren_inicial == ren_final) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void mover(int col_inicial, int ren_inicial, int col_final, int ren_final, Pieza* tablero[8][8]) {
        int columnaDiff = col_final - col_inicial;
        int renglonDiff = ren_final - ren_inicial;
        if (renglonDiff < 0) {
            renglonDiff = renglonDiff * (-1);
        }
        if (columnaDiff < 0) {
            columnaDiff = columnaDiff * (-1);
        }

        //reglas de movimiento especificas de la dama
        if (Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!esJaque()) && (!esJaquemate()) && !(Pieza::casillaOcupada(tablero, col_final, ren_final))) {
            if (columnaDiff <= 1 && renglonDiff <= 1) { //se asegura que solo se mueva una casilla
                if (columnaDiff == renglonDiff) {
                    cout << "El rey se movio en alguna diagonal." << endl;
                    Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                    //cambio turno
                }
                else if (col_inicial == col_final || ren_inicial == ren_final) {
                    cout << "El rey se movio en horizontal o vertical." << endl;
                    Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                    //cambio turno
                }
                else {
                    cout << "Jugada invalida." << endl;
                }
            }
            else {
                cout << "Jugada invalida." << endl;
            }
        }
        else {
            cout << "Jugada invalida." << endl;
        }
    }
};


// Función para cargar texturas desde un archivo
bool cargarTextura(Texture& textura, const string& archivo)
{
    if (!textura.loadFromFile(archivo))
    {
        cerr << "Error al cargar el archivo " << archivo << endl;
        return false;
    }
    return true;
}


int main()
{
    //carga la tipografia arial para las coordenadas
    Font font;
    if (!font.loadFromFile("arial.ttf.ttf")) { //busca el archivo de font y despliega error si no se encuentra.
        cerr << "Error al cargar el archivo de letra." << endl;
        return 0;
    }
    const int numPeones = 8;

    RenderWindow ventanaMenu(VideoMode(600, 330), "Menu Principal"); //Crear ventana para el menu de inicio

    Texture texturaFondo, texturaPlay, texturaSettings, texturaExit; //Crear las texturas de los botones
    cargarTextura(texturaFondo, "fondo.png");
    cargarTextura(texturaPlay, "Play_resized.png");
    cargarTextura(texturaSettings, "Settings_resized.png");
    cargarTextura(texturaExit, "Exit_resized.png");

    Sprite spriteFondo(texturaFondo);//Creo el sprite del fondo
    spriteFondo.setScale((float)ventanaMenu.getSize().x / spriteFondo.getTexture()->getSize().x, (float)ventanaMenu.getSize().y / spriteFondo.getTexture()->getSize().y); //Ajusta el tamaño del sprite del fondo a la ventana

    Sprite play(texturaPlay), Settings(texturaSettings), Exit(texturaExit); //Posicion de las texturas de botones (debe ser la misma que de los botones)
    play.setPosition(100, 50);
    Settings.setPosition(100, 150);
    Exit.setPosition(100, 250);

    // Creacion de botones
    RectangleShape botonPlay(Vector2f(200, 60)); //Tamaño y posicion de los botones
    botonPlay.setPosition(100, 50);

    RectangleShape botonSettings(Vector2f(200, 60));
    botonSettings.setPosition(100, 150);

    RectangleShape botonExit(Vector2f(200, 60));
    botonExit.setPosition(100, 250);

    RectangleShape botonSalirJuego(Vector2f(100, 60));
    botonSalirJuego.setPosition(850, 900);
    botonSalirJuego.setFillColor(Color::Red);

    RenderWindow ventanaJuego(VideoMode(1000, 1000), "Tablero");
    ventanaJuego.setVisible(false);

    vector<Sprite> peonesBlancos(numPeones);
    vector<Sprite> peonesNegros(numPeones);

    // Bucle principal
    while (ventanaMenu.isOpen() || ventanaJuego.isOpen())
    {
        if (ventanaMenu.isOpen())
        {
            Event evento;
            while (ventanaMenu.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                {
                    ventanaMenu.close();
                }
                else if (evento.type == Event::MouseButtonPressed)
                {
                    if (evento.mouseButton.button == Mouse::Left)
                    {
                        Vector2i mousePos = Mouse::getPosition(ventanaMenu);
                        if (botonPlay.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            ventanaMenu.setVisible(false);
                            ventanaJuego.setVisible(true);
                        }
                        else if (botonExit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            ventanaMenu.close();
                        }
                    }
                }
            }
             ventanaMenu.clear();
             ventanaMenu.draw(spriteFondo);
             ventanaMenu.draw(botonPlay);
             ventanaMenu.draw(play);
             ventanaMenu.draw(botonSettings);
             ventanaMenu.draw(Settings);
             ventanaMenu.draw(botonExit);
             ventanaMenu.draw(Exit);
             ventanaMenu.display();
        }
        if (ventanaJuego.isOpen())
        {
            Event evento;
            while (ventanaJuego.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                {
                    ventanaJuego.close();
                }
                else if (evento.type == Event::MouseButtonPressed)
                {
                    if (evento.mouseButton.button == Mouse::Left)
                    {
                        Vector2i mousePos = Mouse::getPosition(ventanaJuego);
                        Vector2i clicPos = Mouse::getPosition(ventanaJuego);
                        int clicColumna = clicPos.x / 100; // Obtener la columna donde se hizo clic
                        int clicFila = clicPos.y / 100; // Obtener la fila donde se hizo clic

/*movimiento::movimiento(int X1, int Y1, int X2, int Y2)
{
    aX=X1;
    aY=Y1;
    X=X2;
    Y=Y2;
}
void tableroAjedrez::PeonBlanco(vector<movimiento> &movimientos, int X, int Y)
{
    if(y>0)
    {
         if(aTablero.arr[x][y-1]==-1)
            {
                movimientos.push_back(movimiento(x, y, x, y-1));
                if(aTablero.arr[x][y-2]==-1 && y==6)
                {
                    movimientos.push_back(movimiento(x, y, x, y-2));
                }
            }
         if (x>0)
            {
                if(aTablero.arr[x-1[y-1]>=6)
                {
                    movimientos.push_back(movimiento(x, y, x-1, y-1));
                }
            }
         if (x<7)
            {
                if(aTablero.arr[x+1[y-1]>=6)
                {
                    movimientos.push_back(movimiento(x, y, x+1, y-1));
                }
            }
    }
}*/

                        for (int i = 0; i < numPeones; ++i)
                        {
                            // Verificar si se hizo clic en una casilla delante de un peón blanco
                            if (peonesBlancos[i].getPosition().y / 100 == clicFila - 1 && peonesBlancos[i].getPosition().x / 100 == clicColumna)
                            {
                                // Si hay un peón blanco en la fila 6 (índice 1) y se hace clic en la casilla delante de él, puede avanzar una casilla
                                peonesBlancos[i].move(0, -100); // Mover el peón blanco hacia adelante
                                break; // Salir del bucle una vez que se ha movido un peón
                            }

                            // Verificar si se hizo clic en una casilla delante de un peón negro
                            if (peonesNegros[i].getPosition().y / 100 == clicFila + 1 && peonesNegros[i].getPosition().x / 100 == clicColumna)
                            {
                                // Si hay un peón negro en la fila 1 (índice 6) y se hace clic en la casilla delante de él, puede avanzar una casilla
                                peonesNegros[i].move(0, 100); // Mover el peón negro hacia adelante
                                break; // Salir del bucle una vez que se ha movido un peón
                            }
                        }
                        cout << "La pieza esta en la posicion: " << mousePos.x << ", " << mousePos.y << endl;
                    }
                }
            }
            ventanaJuego.clear();


             // Crear el cuadro para el tablero
            RectangleShape cuadro(Vector2f(100, 100));//tamanio de cada cuadro
            bool colorBlanco = true;

            // Funciones que imprimen las imagenes de los peones
            Texture texturaPeonBlanco, texturaPeonNegro;//TEXTURAS DE PEONES
            cargarTextura(texturaPeonBlanco, "Peon_blanco.png");
            cargarTextura(texturaPeonNegro, "Peon_negro.png");

            //TEXTURAS DE TORRES
            Texture texturaTorreBlanca, texturaTorreNegra;
            cargarTextura(texturaTorreBlanca, "Torre_Blanca.png");
            cargarTextura(texturaTorreNegra, "Torre_Negra.png");

            //TEXTURAS DE CABALLOS/KNIGHTS
            Texture texturaCaballoBlanco, texturaCaballoNegro;
            cargarTextura(texturaCaballoBlanco, "Caballo_Blanco.png");
            cargarTextura(texturaCaballoNegro, "Caballo_Negro.png");

            //TEXTURAS DE ALFIL/BISHOP
            Texture texturaAlfilBlanco, texturaAlfilNegro;
            cargarTextura(texturaAlfilBlanco, "Alfil_Blanco.png");
            cargarTextura(texturaAlfilNegro, "Alfil_Negro.png");

            //TEXCTURAS DE LA REINA/QUEEN
            Texture texturaReinaBlanca, texturaReinaNegra;
            cargarTextura(texturaReinaBlanca, "Reina_Blanca.png");
            cargarTextura(texturaReinaNegra, "Reina_Negra.png");

            //TEXTURAS DEL REY/KING
            Texture texturaReyBlanco, texturaReyNegro;
            cargarTextura(texturaReyBlanco, "Rey_Blanco.png");
            cargarTextura(texturaReyNegro, "Rey_Negro.png");

            Sprite PeonBlanco, PeonNegro, TorreBlanca, TorreNegra, CaballoBlanco, CaballoNegro, AlfilBlanco, AlfilNegro, ReinaBlanca, ReinaNegra, ReyBlanco, ReyNegro;

            // Posiciones iniciales de los peones
            const int numPeones = 8;
            Sprite peonesBlancos[numPeones], peonesNegros[numPeones];

            for (int i = 0; i < numPeones; i++)
            {
                //for para establecer la posicion de las piezas
                peonesBlancos[i].setTexture(texturaPeonBlanco);
                peonesNegros[i].setTexture(texturaPeonNegro);

                peonesBlancos[i].setPosition(i * 100, 600);
                peonesNegros[i].setPosition(i * 100, 100);
            }
                // Dibujar el tablero
                for (int i = 0; i < 8; ++i)
                {
                    for (int j = 0; j < 8; ++j)
                    {
                        cuadro.setFillColor(colorBlanco ? Color::White : Color::Black);
                        cuadro.setPosition(j * 100, i * 100);
                        ventanaJuego.draw(cuadro);
                        colorBlanco = !colorBlanco;
                    }
                    colorBlanco = !colorBlanco;
                }

                //define el texto, su tamanio y color
                Text text;
                text.setFont(font);
                text.setCharacterSize(30);
                text.setFillColor(sf::Color::White);

                // posiciones iniciales para letras y numeros
                int letrasss = 30;
                int numeros = 40;

                // Dibujar las letras (A-H)
                for (int i = 0; i < 8; ++i) {
                    char letras = 'A' + i;
                    text.setString(std::string(1, letras));
                    text.setPosition(letrasss + i * 100, 800);
                    ventanaJuego.draw(text);
                }

                // Dibujar los números (1-8)
                for (int i = 0; i < 8; ++i) {
                    char num = '8' - i;
                    text.setString(std::string(1, num));
                    text.setPosition(815, numeros + i * 100);
                    ventanaJuego.draw(text);
                }


                // Dibujar los peones blancos
                for (int i = 0; i < numPeones; i++)
                {
                    ventanaJuego.draw(peonesBlancos[i]);
                }

                // Dibujar los peones negros
                for (int i = 0; i < numPeones; i++)
                {
                    ventanaJuego.draw(peonesNegros[i]);
                }
                //Dibujar los rooks, caballos y bishops
                for (int i = 0; i < 2; i++)
                {
                    TorreBlanca.setTexture(texturaTorreBlanca);
                    TorreNegra.setTexture(texturaTorreNegra);

                    CaballoBlanco.setTexture(texturaCaballoBlanco);
                    CaballoNegro.setTexture(texturaCaballoNegro);

                    AlfilBlanco.setTexture(texturaAlfilBlanco);
                    AlfilNegro.setTexture(texturaAlfilNegro);

                    TorreBlanca.setPosition(i * 700, 700);
                    TorreNegra.setPosition(i * 700, 0);

                    CaballoBlanco.setPosition(i * 500 + 100, 700);
                    CaballoNegro.setPosition(i * 500 + 100, 0);

                    AlfilBlanco.setPosition(i * 300 + 200, 700);
                    AlfilNegro.setPosition(i * 300 + 200, 0);

                    ventanaJuego.draw(TorreBlanca);
                    ventanaJuego.draw(TorreNegra);

                    ventanaJuego.draw(CaballoBlanco);
                    ventanaJuego.draw(CaballoNegro);

                    ventanaJuego.draw(AlfilBlanco);
                    ventanaJuego.draw(AlfilNegro);
                }

                //QUEEN
                ReinaBlanca.setTexture(texturaReinaBlanca);
                ReinaNegra.setTexture(texturaReinaNegra);

                ReinaBlanca.setPosition(300, 700);
                ReinaNegra.setPosition(300, 0);

                ventanaJuego.draw(ReinaBlanca);
                ventanaJuego.draw(ReinaNegra);

                //KING
                ReyBlanco.setTexture(texturaReyBlanco);
                ReyNegro.setTexture(texturaReyNegro);

                ReyNegro.setPosition(400, 0);
                ReyBlanco.setPosition(400, 700);

                ventanaJuego.draw(ReyBlanco);
                ventanaJuego.draw(ReyNegro);

                ventanaJuego.draw(botonSalirJuego);
                if (ventanaJuego.isOpen())
                {
                    Event Cerrar;
                    while (ventanaJuego.pollEvent(Cerrar))
                    {
                        if (Cerrar.type == Event::Closed)
                            ventanaJuego.close();
                        else if (Cerrar.type == Event::MouseButtonPressed)
                        {
                            if (Cerrar.mouseButton.button == Mouse::Left)
                            {
                                Vector2i mousePos = Mouse::getPosition(ventanaJuego);
                                if (botonSalirJuego.getGlobalBounds().contains(mousePos.x, mousePos.y))
                                {
                                    ventanaJuego.close();

                                }
                            }
                        }
                    }
                }

            ventanaJuego.display();
        }
    }
    return 0;
}
