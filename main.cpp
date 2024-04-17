#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// Función para cargar texturas desde un archivo
bool cargarTextura(sf::Texture& textura, const string& archivo)
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
  // Crear la ventana
  sf::RenderWindow ventana(sf::VideoMode(1200, 1200), "Tablero de Ajedrez");//tamanio del tablero

  // Crear el cuadro para el tablero
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


  return 0;
}

