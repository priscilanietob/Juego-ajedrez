#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

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

    bool isCheck(){
        //revisar si esta en jaque
        return false;
    }

    bool isCheckmate(){
        //revisar si esta en jaque mate
        return false;
    }

    bool isSpaceOccupied(){
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
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){

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
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){
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

        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){
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
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){
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

    /*void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        //reglas de movimiento especificas de la dama
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){
            if (condicion de la pieza) {
                cout << "Mensaje de la pieza." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }*/
};

class Rey : public Pieza{
public:
    //constructor y destructor
    Rey(Color _color) :
        Pieza(_color, Tipo::Rey){}
    ~Rey(){}

    /*void mover(int col_inicial, int ren_inicial, int col_final, int ren_final){
        //reglas de movimiento especificas del rey
        if(Pieza::dentroTablero(col_inicial, ren_inicial, col_final, ren_final) && (!isCheck()) && (!isCheckmate()) && (!isSpaceOccupied())){
            if (condicion de la pieza) {
                cout << "Mensaje de la pieza." << endl;
                Pieza::actualizarPosicion(col_inicial, ren_inicial, col_final, ren_final);
                //cambio turno
            } else {
                cout << "Jugada invalida." << endl;
            }
        }
    }*/
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
    sf::Font font;
    if (!font.loadFromFile("arial.ttf.ttf")) { //busca el archivo de font y despliega error si no se encuentra.
        std::cerr << "Error loading font file." << std::endl;
        return 0;
    }

    RenderWindow ventana(VideoMode(600, 330), "Main Menu"); //Crear ventana para el menu de inicio

    Texture texturaFondo, texturaPlay, texturaSettings, texturaExit; //Crear las texturas de los botones
    cargarTextura(texturaFondo, "fondo.png");
    cargarTextura(texturaPlay, "Play_resized.png");
    cargarTextura(texturaSettings, "Settings_resized.png");
    cargarTextura(texturaExit, "Exit_resized.png");

    Sprite spriteFondo(texturaFondo);//Creo el sprite del fondo
    spriteFondo.setScale((float)ventana.getSize().x / spriteFondo.getTexture()->getSize().x, (float)ventana.getSize().y / spriteFondo.getTexture()->getSize().y); //Ajusta el tamaño del sprite del fondo a la ventana

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

    RectangleShape botonExitGame(Vector2f(100, 60));
    botonExitGame.setPosition(850, 900);
    botonExitGame.setFillColor(Color::Red);

    // Bucle principal
    while (ventana.isOpen())
    {
        Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
                ventana.close();
            else if (evento.type == Event::MouseButtonPressed)
            {
                if (evento.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(ventana); //Se almacena la posicion del mouse en el vector2i que es de dos dimensiones X y Y
                    if (botonPlay.getGlobalBounds().contains(mousePos.x, mousePos.y)) //Para checar si en los limites del boton esta el mouse dando clic
                    {
                         // Crear el cuadro para el tablero
                        RenderWindow ventana(VideoMode(1000, 1000), "Tablero");
                        RectangleShape cuadro(Vector2f(100, 100));//tamanio de cada cuadro
                        bool colorBlanco = true;

                        // Funciones que imprimen las imagenes de los peones
                        Texture texturaPeonBlanco, texturaPeonNegro;//TEXTURAS DE PEONES
                        cargarTextura(texturaPeonBlanco, "peon_blanco_resized.png");
                        cargarTextura(texturaPeonNegro, "peon_negro_resized.png");

                        //TEXTURAS DE TORRES/ROOKS
                        Texture texturaBRook, texturaWRook;
                        cargarTextura(texturaBRook, "Rook B_resized.png");
                        cargarTextura(texturaWRook, "Rook W_resized.png");

                        //TEXTURAS DE CABALLOS/KNIGHTS
                        Texture texturaBKnight, texturaWKnight;
                        cargarTextura(texturaBKnight, "BKnight_resized.png");
                        cargarTextura(texturaWKnight, "WKnight_resized.png");

                        //TEXTURAS DE ALFIL/BISHOP
                        Texture texturaBBishop, texturaWBishop;
                        cargarTextura(texturaBBishop, "BBishop_resized.png");
                        cargarTextura(texturaWBishop, "WBishop_resized.png");

                        //TEXCTURAS DE LA REINA/QUEEN
                        Texture texturaBQueen, texturaWQueen;
                        cargarTextura(texturaBQueen, "BQueen_resized.png");
                        cargarTextura(texturaWQueen, "WQueen_resized.png");

                        //TEXTURAS DEL REY/KING
                        Texture texturaBKing, texturaWKing;
                        cargarTextura(texturaBKing, "BKing_resized.png");
                        cargarTextura(texturaWKing, "WKing_resized.png");

                        Sprite BRook, WRook, BKnight, WKnight, WBishop, BBishop, BQueen, WQueen, WKing, BKing;

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

                        while (ventana.isOpen()) //hace que se mantenga abierta la ventana
                        {
                            Event evento;
                            while (ventana.pollEvent(evento))
                            {
                                if (evento.type == sf::Event::Closed)
                                    ventana.close();
                            }

                            // Dibujar el tablero
                            for (int i = 0; i < 8; ++i)
                            {
                                for (int j = 0; j < 8; ++j)
                                {
                                    cuadro.setFillColor(colorBlanco ? sf::Color::White : sf::Color::Black);
                                    cuadro.setPosition(j * 100, i * 100);
                                    ventana.draw(cuadro);
                                    colorBlanco = !colorBlanco;
                                }
                                colorBlanco = !colorBlanco;
                            }


                                //define el texto, su tamanio y color
                                sf::Text text;
                                text.setFont(font);
                                text.setCharacterSize(30);
                                text.setFillColor(sf::Color::White);

                                // posiciones iniciales para letras y numeros
                                int letrasss = 30;
                                int numeros = 40;

                                // Dibujar las letras (A-H)
                                for (int i = 0; i < 8; ++i) {
                                    char letter = 'A' + i;
                                    text.setString(std::string(1, letter));
                                    text.setPosition(letrasss + i * 100, 800);
                                    ventana.draw(text);
                                }

                                // Dibujar los números (1-8)
                                for (int i = 0; i < 8; ++i) {
                                    char number = '8' - i;
                                    text.setString(std::string(1, number));
                                    text.setPosition(815, numeros + i * 100);
                                    ventana.draw(text);
                                }


                            // Dibujar los peones blancos
                            for (int i = 0; i < numPeones; i++)
                            {
                                ventana.draw(peonesBlancos[i]);
                            }

                            // Dibujar los peones negros
                            for (int i = 0; i < numPeones; i++)
                            {
                                ventana.draw(peonesNegros[i]);
                            }
                            //Dibujar los rooks, caballos y bishops
                            for (int i = 0; i < 2; i++)
                            {
                                WRook.setTexture(texturaWRook);
                                BRook.setTexture(texturaBRook);

                                WKnight.setTexture(texturaWKnight);
                                BKnight.setTexture(texturaBKnight);

                                WBishop.setTexture(texturaWBishop);
                                BBishop.setTexture(texturaBBishop);

                                BRook.setPosition(i * 700, 0);
                                WRook.setPosition(i * 700, 700);

                                BKnight.setPosition(i * 500 + 100, 0);
                                WKnight.setPosition(i * 500 + 100, 700);

                                BBishop.setPosition(i * 300 + 200, 0);
                                WBishop.setPosition(i * 300 + 200, 700);

                                ventana.draw(WRook);
                                ventana.draw(BRook);

                                ventana.draw(WKnight);
                                ventana.draw(BKnight);

                                ventana.draw(WBishop);
                                ventana.draw(BBishop);
                            }

                            //QUEEN
                            WQueen.setTexture(texturaWQueen);
                            BQueen.setTexture(texturaBQueen);

                            BQueen.setPosition(300, 0);
                            WQueen.setPosition(300, 700);

                            ventana.draw(WQueen);
                            ventana.draw(BQueen);

                            //KING
                            WKing.setTexture(texturaWKing);
                            BKing.setTexture(texturaBKing);

                            BKing.setPosition(400, 0);
                            WKing.setPosition(400, 700);

                            ventana.draw(WKing);
                            ventana.draw(BKing);

                            ventana.draw(botonExitGame);

                            // Mostrar la ventana
                            ventana.display();

                        }
                        cout << "¡Jugar ajedrez!" << endl;

                        Torre torrePrueba(Pieza::Blanca);

                        //vertical
                        torrePrueba.mover(1,1,1,8);
                        torrePrueba.mover(2,5,2,7);

                        //horizontal
                        torrePrueba.mover(4,2,8,2);
                        torrePrueba.mover(1,3,2,3);


                    }
                    else if (botonExit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        ventana.close();
                    }

                    else if (botonExitGame.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        cout << "ola";
                        ventana.close();
                    }
                }
            }
        }

        //Crear y mostrar en la ventana los sprites
        ventana.clear();
        ventana.draw(spriteFondo);
        ventana.draw(botonPlay);
        ventana.draw(play);
        ventana.draw(botonSettings);
        ventana.draw(Settings);
        ventana.draw(botonExitGame);
        ventana.draw(Exit);
        ventana.display();
    }

    return 0;
}
