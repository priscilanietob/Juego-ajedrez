#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Funci�n para cargar texturas desde un archivo
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
    RenderWindow ventana(VideoMode(600, 330), "Main Menu"); //Crear ventana para el menu de inicio

    Texture texturaFondo, texturaPlay, texturaSettings, texturaExit; //Crear las texturas de los botones
    cargarTextura(texturaFondo, "fondo.png");
    cargarTextura(texturaPlay, "Play_resized.png");
    cargarTextura(texturaSettings, "Settings_resized.png");
    cargarTextura(texturaExit, "Exit_resized.png");

    Sprite spriteFondo(texturaFondo);//Creo el sprite del fondo
    spriteFondo.setScale((float)ventana.getSize().x / spriteFondo.getTexture()->getSize().x, (float)ventana.getSize().y / spriteFondo.getTexture()->getSize().y); //Ajusta el tama�o del sprite del fondo a la ventana

    Sprite play(texturaPlay), Settings(texturaSettings), Exit(texturaExit); //Posicion de las texturas de botones (debe ser la misma que de los botones)
    play.setPosition(100, 50);
    Settings.setPosition(100, 150);
    Exit.setPosition(100, 250);

    // Creacion de botones
    RectangleShape botonPlay(Vector2f(200, 60)); //Tama�o y posicion de los botones
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
                        cout << "�Jugar ajedrez!" << endl;

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
