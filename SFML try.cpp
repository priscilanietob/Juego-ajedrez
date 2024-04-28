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
                        RenderWindow ventana(VideoMode(1200, 1200), "Tablero");
                        sf::RectangleShape cuadro(sf::Vector2f(150, 150));//tamanio de cada cuadro
                        bool colorBlanco = true;

                        // Funciones que imprimen las imagenes de los peones
                        sf::Texture texturaPeonBlanco, texturaPeonNegro;//imagenes png
                        cargarTextura(texturaPeonBlanco, "peon_blanco.png");
                        cargarTextura(texturaPeonNegro, "peon_negro.png");

                        // Posiciones iniciales de los peones
                        const int numPeones = 8;
                        sf::Sprite peonesBlancos[numPeones];
                        sf::Sprite peonesNegros[numPeones];

                        for (int i = 0; i < numPeones; i++)
                        {
                            //for para establecer la posicion de las piezas
                            peonesBlancos[i].setTexture(texturaPeonBlanco);
                            peonesNegros[i].setTexture(texturaPeonNegro);

                            peonesBlancos[i].setPosition(i * 150, 900);
                            peonesNegros[i].setPosition(i * 150, 150);
                        }

                        while (ventana.isOpen()) //hace que se mantenga abierta la ventana
                        {
                            sf::Event evento;
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
                                    cuadro.setPosition(j * 150, i * 150);
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

                            // Mostrar la ventana
                            ventana.display();
                        }

                        cout << "¡Jugar ajedrez!" << endl;
                    }
                    else if (botonExit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
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
        ventana.draw(botonExit);
        ventana.draw(Exit);
        ventana.display();
    }   
    return 0;
}
