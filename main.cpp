#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class Tablero {
    int columna;
    int renglon;
    enum Color { Blanca, Negra };
    Color turnoActual = Color::Blanca;

public:
    Tablero() {}
    ~Tablero() {}

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
    Tablero* tablero;

    //constructor y destructor
    Pieza(Color _color, Tipo _tipo) :
        color(_color), tipo(_tipo) {}
    ~Pieza() {}

    //gets
    Color getColor() const { return static_cast<Color>(color); }
    Tipo getTipo() const { return static_cast<Tipo>(tipo); }

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

    bool esJaque(Pieza::Color color) {
        // Buscar el rey del color especificado
        Pieza* rey = nullptr;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (tablero[i][j] && tablero[i][j]->getTipo() == Pieza::Rey && tablero[i][j]->getColor() == color) {
                    rey = tablero[i][j];
                    break;
                }
            }
        }
        if (!rey) return false;

        // Verificar si alguna pieza contraria puede capturar al rey
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (tablero[i][j] && tablero[i][j]->getColor() != color) {
                    if (tablero[i][j]->puedeMoverse(rey->columna, rey->renglon, tablero)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool esJaquemate(Pieza::Color color) {
        // Verificar si hay alguna jugada posible para evitar el jaque
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (tablero[i][j] && tablero[i][j]->getColor() == color) {
                    for (int k = 0; k < 8; ++k) {
                        for (int l = 0; l < 8; ++l) {
                            if (tablero[i][j]->puedeMoverse(k, l, tablero)) {
                                Pieza* piezaTemporal = tablero[k][l];
                                tablero[k][l] = tablero[i][j];
                                tablero[i][j] = nullptr;
                                if (!estaEnJaque(color)) {
                                    tablero[i][j] = tablero[k][l];
                                    tablero[k][l] = piezaTemporal;
                                    return false;
                                }
                                tablero[i][j] = tablero[k][l];
                                tablero[k][l] = piezaTemporal;
                            }
                        }
                    }
                }
            }
        }
        return true;
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
        else
        {
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
bool cargarTextura(Texture& textura, const string& archivo) {
    if (!textura.loadFromFile(archivo)) {
        cerr << "Error al cargar el archivo " << archivo << endl;
        return false;
    }
    return true;
}


int tamanioTablero = 56;
Sprite piezas[32];

/*int tablero[8][8] =  //Representacion de las piezas como un valor
{ -1, -2, -3, -5, -4, -3, -2, -1, // Piezas blancas num positivos y negras negativos
  -6, -6, -6, -6, -6, -6, -6, -6, // Peones = 6
   0,  0,  0,  0,  0,  0,  0,  0, // Torre = 1
   0,  0,  0,  0,  0,  0,  0,  0, // Caballo = 2
   0,  0,  0,  0,  0,  0,  0,  0, // Alfil = 3
   0,  0,  0,  0,  0,  0,  0,  0, // Dama = 4
   6,  6,  6,  6,  6,  6,  6,  6, // Rey = 5
   1,  2,  3,  4,  5,  3,  2,  1, // Celda vacia = 0
};*/

int main()
{
    // Inicialización del tablero
    Tablero tablero;
    tablero.displayTurno();

    bool MoverReinaB = false, MoverReinaN = false; //para saber si una pieza se esta moviendo
    bool MoverPeonB[8] = { false }, MoverPeonN[8] = { false }; //para saber si una pieza se esta moviendo
    bool MoverReyB = false, MoverReyN = false;
    bool MoverTorreB[2] = { false }, MoverTorreN[2] = { false };
    bool MoverCaballoB[2] = { false }, MoverCaballoN[2] = { false };
    bool MoverAlfilB[2] = { false }, MoverAlfilN[2] = { false };

    float dx = 0, dy = 0; //las coordenadas de las piezas

    RenderWindow ventanaMenu(VideoMode(600, 330), "Main Menu"); //Crear ventana para el menú de inicio

    Texture texturaFondo, texturaPlay, texturaSettings, texturaExit; //Crear las texturas de los botones
    cargarTextura(texturaFondo, "fondo.png");
    cargarTextura(texturaPlay, "Play_resized.png");
    cargarTextura(texturaSettings, "Settings_resized.png");
    cargarTextura(texturaExit, "Exit_resized.png");

    Sprite spriteFondo(texturaFondo); //Crear el sprite del fondo
    spriteFondo.setScale((float)ventanaMenu.getSize().x / spriteFondo.getTexture()->getSize().x, (float)ventanaMenu.getSize().y / spriteFondo.getTexture()->getSize().y); //Ajusta el tamaño del sprite del fondo a la ventana
    Sprite play(texturaPlay), settings(texturaSettings), exit(texturaExit); //Posición de las texturas de botones (debe ser la misma que de los botones)
    play.setPosition(100, 50);
    settings.setPosition(100, 150);
    exit.setPosition(100, 250);

    //Creación de botones
    RectangleShape botonPlay(Vector2f(200, 60)); //Tamaño y posición de los botones
    botonPlay.setPosition(100, 50);

    RectangleShape botonSettings(Vector2f(200, 60));
    botonSettings.setPosition(100, 150);

    RectangleShape botonExit(Vector2f(200, 60));
    botonExit.setPosition(100, 250);

    RectangleShape botonExitGame(Vector2f(100, 60));
    botonExitGame.setPosition(850, 900);
    botonExitGame.setFillColor(Color::Red);

    RenderWindow ventanaJuego(VideoMode(1000, 1000), "Tablero");
    ventanaJuego.setVisible(false);

    //Funciones que agarran las imagenes del archivo y las adjudican a las piezas
    Texture texturaPeonBlanco, texturaPeonNegro; // Texturas de peones
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

    Sprite TorreNegra[2], TorreBlanca[2], CaballoNegro[2], CaballoBlanco[2], AlfilBlanco[2], AlfilNegro[2], ReinaNegra, ReinaBlanca, ReyBlanco, ReyNegro; //creacion de sprites

    //Posiciones iniciales de los peones
    const int numPeones = 8;
    Sprite peonesBlancos[numPeones], peonesNegros[numPeones]; //creacion de sprites de los peones y como son 8 se creo en forma de arreglo

    for (int i = 0; i < numPeones; i++) //ciclito para establecer la textura y posicion de cada peon
    {
        peonesBlancos[i].setTexture(texturaPeonBlanco);
        peonesNegros[i].setTexture(texturaPeonNegro);
        peonesBlancos[i].setPosition(i * 100, 600);
        peonesNegros[i].setPosition(i * 100, 100);
    }


    for (int i = 0; i < 2; i++)
    {
        TorreBlanca[i].setTexture(texturaTorreBlanca);
        TorreNegra[i].setTexture(texturaTorreNegra);
        CaballoBlanco[i].setTexture(texturaCaballoBlanco);
        CaballoNegro[i].setTexture(texturaCaballoNegro);
        AlfilBlanco[i].setTexture(texturaAlfilBlanco);
        AlfilNegro[i].setTexture(texturaAlfilNegro);

        TorreNegra[i].setPosition(i * 700, 0);
        TorreBlanca[i].setPosition(i * 700, 700);
        CaballoNegro[i].setPosition(i * 500 + 100, 0);
        CaballoBlanco[i].setPosition(i * 500 + 100, 700);
        AlfilNegro[i].setPosition(i * 300 + 200, 0);
        AlfilBlanco[i].setPosition(i * 300 + 200, 700);
    }

    //establecer posicion de la reina y rey
    ReinaBlanca.setTexture(texturaReinaBlanca);
    ReinaNegra.setTexture(texturaReinaNegra);
    ReinaNegra.setPosition(300, 0);
    ReinaBlanca.setPosition(300, 700);

    ReyBlanco.setTexture(texturaReyBlanco);
    ReyNegro.setTexture(texturaReyNegro);
    ReyNegro.setPosition(400, 0);
    ReyBlanco.setPosition(400, 700);

    bool Menu = true;

    while (ventanaMenu.isOpen() || ventanaJuego.isOpen())
    {
        if (Menu)
        {
            Event event;
            while (ventanaMenu.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    ventanaMenu.close();
                }
                if (event.type == Event::MouseButtonPressed)
                {
                    Vector2f mousePos = ventanaMenu.mapPixelToCoords(Mouse::getPosition(ventanaMenu));
                    if (botonPlay.getGlobalBounds().contains(mousePos))
                    {
                        ventanaMenu.setVisible(false);
                        ventanaJuego.setVisible(true);
                        Menu = false;
                    }
                    if (botonExit.getGlobalBounds().contains(mousePos))
                    {
                        ventanaMenu.close();
                    }
                }
            }
            ventanaMenu.clear();
            ventanaMenu.draw(spriteFondo);
            ventanaMenu.draw(play);
            ventanaMenu.draw(settings);
            ventanaMenu.draw(exit);
            ventanaMenu.display();
        }
        else
        {
            Event event;
            while (ventanaJuego.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    ventanaJuego.close();
                }
                ///////drag and drop//////////////
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        Vector2i pos = Mouse::getPosition(ventanaJuego);
                        if (botonExitGame.getGlobalBounds().contains(pos.x, pos.y))
                        {
                            ventanaJuego.setVisible(false);
                            ventanaMenu.setVisible(true);
                            Menu = true;
                        }
                        if (ReinaBlanca.getGlobalBounds().contains(pos.x, pos.y))
                        {
                            MoverReinaB = true;
                            dx = pos.x - ReinaBlanca.getPosition().x;
                            dy = pos.y - ReinaBlanca.getPosition().y;
                        }
                        if (ReinaNegra.getGlobalBounds().contains(pos.x, pos.y))
                        {
                            MoverReinaN = true;
                            dx = pos.x - ReinaNegra.getPosition().x;
                            dy = pos.y - ReinaNegra.getPosition().y;
                        }
                        for(int i = 0; i < 8; i++)
                        {
                            if (peonesBlancos[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverPeonB[i] = true;
                                dx = pos.x - peonesBlancos[i].getPosition().x;
                                dy = pos.y - peonesBlancos[i].getPosition().y;
                            }
                        }
                        for(int i = 0; i < 8; i++)
                        {
                            if (peonesNegros[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverPeonN[i] = true;
                                dx = pos.x - peonesNegros[i].getPosition().x;
                                dy = pos.y - peonesNegros[i].getPosition().y;
                            }
                        }
                        if (ReyNegro.getGlobalBounds().contains(pos.x, pos.y))
                        {
                            MoverReyN = true;
                            dx = pos.x - ReyNegro.getPosition().x;
                            dy = pos.y - ReyNegro.getPosition().y;
                        }
                        if (ReyBlanco.getGlobalBounds().contains(pos.x, pos.y))
                        {
                            MoverReyB = true;
                            dx = pos.x - ReyBlanco.getPosition().x;
                            dy = pos.y - ReyBlanco.getPosition().y;
                        }
                        for(int i = 0; i < 2; i++)
                        {
                            if (CaballoBlanco[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverCaballoB[i] = true;
                                dx = pos.x - CaballoBlanco[i].getPosition().x;
                                dy = pos.y - CaballoBlanco[i].getPosition().y;
                            }
                            if (CaballoNegro[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverCaballoN[i] = true;
                                dx = pos.x - CaballoNegro[i].getPosition().x;
                                dy = pos.y - CaballoNegro[i].getPosition().y;
                            }
                            if (AlfilBlanco[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverAlfilB[i] = true;
                                dx = pos.x - AlfilBlanco[i].getPosition().x;
                                dy = pos.y - AlfilBlanco[i].getPosition().y;
                            }
                            if (AlfilNegro[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverAlfilN[i] = true;
                                dx = pos.x - AlfilNegro[i].getPosition().x;
                                dy = pos.y - AlfilNegro[i].getPosition().y;
                            }
                            if (TorreBlanca[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverTorreB[i] = true;
                                dx = pos.x - TorreBlanca[i].getPosition().x;
                                dy = pos.y - TorreBlanca[i].getPosition().y;
                            }
                            if (TorreNegra[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                MoverTorreN[i] = true;
                                dx = pos.x - TorreNegra[i].getPosition().x;
                                dy = pos.y - TorreNegra[i].getPosition().y;
                            }

                        }

                    }
                }

                if (event.type == Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        MoverReinaB = false, MoverReinaN = false;
                        MoverReyB = false, MoverReyN = false;
                    }
                }
                if (event.type == Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            MoverCaballoB[i] = false, MoverCaballoN[i] = false;
                            MoverAlfilB[i] = false, MoverAlfilN[i] = false;
                            MoverTorreB[i] = false, MoverTorreN[i] = false;
                        }

                    }
                }
                if (event.type == Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            MoverPeonB[i] = false;
                            MoverPeonN[i] = false;
                        }
                    }
                }
            }
            Vector2i pos = Mouse::getPosition(ventanaJuego);
            if (MoverReinaB) // Movimiento de la reina Blanca
            {
                ReinaBlanca.setPosition(pos.x - dx, pos.y - dy);
                //funcion de restriccion de reina
            }
            if (MoverReinaN) // Movimiento de la reina Negra
            {
                ReinaNegra.setPosition(pos.x - dx, pos.y - dy);
            }
            for(int i = 0; i < 8; i++)
            {
                if (MoverPeonB[i]) //Movimiento de peones blancos
                {
                    peonesBlancos[i].setPosition(pos.x - dx, pos.y - dy);
                }
                if (MoverPeonN[i]) //Movimiento de peones negros
                {
                    peonesNegros[i].setPosition(pos.x - dx, pos.y - dy);
                }
            }
            if (MoverReyB)
            {
                ReyBlanco.setPosition(pos.x - dx, pos.y - dy);
            }
            if (MoverReyN)
            {
                ReyNegro.setPosition(pos.x - dx, pos.y - dy);
            }
            for (int i = 0; i < 2; i++)
            {
                if (MoverCaballoB[i])
                {
                    CaballoBlanco[i].setPosition(pos.x - dx, pos.y - dy);

                }
                if (MoverCaballoN[i])
                {
                    CaballoNegro[i].setPosition(pos.x - dx, pos.y - dy);
                }
                if (MoverAlfilB[i])
                {
                    AlfilBlanco[i].setPosition(pos.x - dx, pos.y - dy);
                }
                if (MoverAlfilN[i])
                {
                    AlfilNegro[i].setPosition(pos.x - dx, pos.y - dy);
                }
                if (MoverTorreB[i])
                {
                    TorreBlanca[i].setPosition(pos.x - dx, pos.y - dy);
                }
                if (MoverTorreN[i])
                {
                    TorreNegra[i].setPosition(pos.x - dx, pos.y - dy);
                }

            }
            ventanaJuego.clear();

            // Dibujar el tablero
            RectangleShape cuadro(Vector2f(100, 100)); // Tamaño de cada cuadro
            bool colorBlanco = true;
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

            // Cargar la tipografía arial para las coordenadas
            Font font;
            if (!font.loadFromFile("arial.ttf.ttf"))
            {
                cerr << "Error al cargar el archivo de letra." << endl;
                return 0;
            }

            // Define el texto, su tamaño y color
            Text text;
            text.setFont(font);
            text.setCharacterSize(30);
            text.setFillColor(Color::White);

            // Posiciones iniciales para letras y numeros
            int letrasss = 30;
            int numeros = 40;

            // Dibujar las letras (A-H)
            for (int i = 0; i < 8; ++i)
            {
                char letras = 'A' + i;
                text.setString(string(1, letras));
                text.setPosition(letrasss + i * 100, 800);
                ventanaJuego.draw(text);
            }

            // Dibujar los numeros (1-8)
            for (int i = 0; i < 8; ++i)
            {
                char num = '8' - i;
                text.setString(string(1, num));
                text.setPosition(815, numeros + i * 100);
                ventanaJuego.draw(text);
            }

            for (int i = 0; i < numPeones; i++)
            {
                ventanaJuego.draw(peonesBlancos[i]);
                ventanaJuego.draw(peonesNegros[i]);
            }

            // Dibujar los rooks, caballos y bishops
            for (int i = 0; i < 2; i++)
            {

                ventanaJuego.draw(TorreBlanca[i]);
                ventanaJuego.draw(TorreNegra[i]);
                ventanaJuego.draw(CaballoBlanco[i]);
                ventanaJuego.draw(CaballoNegro[i]);
                ventanaJuego.draw(AlfilBlanco[i]);
                ventanaJuego.draw(AlfilNegro[i]);
            }

            // Dibujar la reina
            ventanaJuego.draw(ReinaBlanca);
            ventanaJuego.draw(ReinaNegra);

            // Dibujar el rey
            ventanaJuego.draw(ReyBlanco);
            ventanaJuego.draw(ReyNegro);

            ventanaJuego.draw(botonExitGame);

            ventanaJuego.display();
        }
    }
    return 0;
}
