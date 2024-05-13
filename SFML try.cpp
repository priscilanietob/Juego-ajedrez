#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

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
        std::cerr << "Error al cargar el archivo de letra." << std::endl;
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
                        Texture texturaTorre_Negra, texturaTorre_Blanca;
                        cargarTextura(texturaTorre_Negra, "Torre_Negra.png");
                        cargarTextura(texturaTorre_Blanca, "Torre_Blanca.png");   
                        
                        //TEXTURAS DE CABALLOS/KNIGHTS
                        Texture texturaCaballo_Negro, texturaCaballo_Blanco;
                        cargarTextura(texturaCaballo_Negro, "Caballo_Negro.png");
                        cargarTextura(texturaCaballo_Blanco, "Caballo_Blanco.png");

                        //TEXTURAS DE ALFIL/BISHOP
                        Texture texturaAlfil_Negro, texturaAlfil_Blanco;
                        cargarTextura(texturaAlfil_Negro, "Alfil_Negro.png");
                        cargarTextura(texturaAlfil_Blanco, "Alfil_Blanco.png");

                        //TEXCTURAS DE LA REINA/QUEEN
                        Texture texturaReina_Negra, texturaReina_Blanca;
                        cargarTextura(texturaReina_Negra, "Reina_Negra.png");
                        cargarTextura(texturaReina_Blanca, "Reina_Blanca.png");

                        //TEXTURAS DEL REY/KING
                        Texture texturaRey_Negro, texturaRey_Blanco;
                        cargarTextura(texturaRey_Negro, "Rey_Negro.png");
                        cargarTextura(texturaRey_Blanco, "Rey_Blanco.png");

                        Sprite Torre_Negra, Torre_Blanca, Caballo_Negro, Caballo_Blanco, Alfil_Blanco, Alfil_Negro, Reina_Negra, Reina_Blanca, Rey_Blanco, Rey_Negro;

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

                                // posiciones iniciales en la ventana para hacer la impresion de letras y numeros
                                int letrasss = 30;
                                int numeros = 40;

                                // Dibujar las letras (A-H)
                                for (int i = 0; i < 8; ++i) {
                                    char letras = 'A' + i;
                                    text.setString(std::string(1, letras));
                                    text.setPosition(letrasss + i * 100, 800);
                                    ventana.draw(text);
                                }

                                // Dibujar los números (1-8)
                                for (int i = 0; i < 8; ++i) {
                                    char num = '8' - i;
                                    text.setString(std::string(1, num));
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
                                Torre_Blanca.setTexture(texturaTorre_Blanca);
                                Torre_Negra.setTexture(texturaTorre_Negra);    

                                Caballo_Blanco.setTexture(texturaCaballo_Blanco);
                                CaballoNegro.setTexture(texturaCaballoNegro);

                                Alfil_Blanco.setTexture(texturaAlfil_Blanco);
                                Alfil_Negro.setTexture(texturaAlfil_Negro);

                                Torre_Negra.setPosition(i * 700, 0);
                                Torre_Blanca.setPosition(i * 700, 700);
                                
                                Caballo_Negro.setPosition(i * 500 + 100, 0);
                                Caballo_Blanco.setPosition(i * 500 + 100, 700);

                                Alfil_Negro.setPosition(i * 300 + 200, 0);
                                Alfil_Blanco.setPosition(i * 300 + 200, 700);

                                ventana.draw(Torre_Blanca);
                                ventana.draw(Torre_Negra);
                                
                                ventana.draw(Caballo_Blanco);
                                ventana.draw(Caballo_Negro);

                                ventana.draw(Alfil_Blanco);
                                ventana.draw(Alfil_Negro);
                            }       

                            //QUEEN
                            Reina_Blanca.setTexture(texturaReina_Blanca);
                            Reina_Negra.setTexture(texturaReina_Negra);

                            Reina_Negra.setPosition(300, 0);
                            Reina_Blanca.setPosition(300, 700);

                            ventana.draw(Reina_Blanca);
                            ventana.draw(Reina_Negra);

                            //KING
                            Rey_Blanco.setTexture(texturaRey_Blanco);
                            Rey_Negro.setTexture(texturaRey_Negro);

                            Rey_Negro.setPosition(400, 0);
                            Rey_Blanco.setPosition(400, 700);

                            ventana.draw(Rey_Blanco);
                            ventana.draw(Rey_Negro);

                            ventana.draw(botonExitGame);
                            
                            // Mostrar la ventana
                            ventana.display();

                        }
                        cout << "¡Jugar ajedrez!" << endl;

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
