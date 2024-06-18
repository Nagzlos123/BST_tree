#ifndef TEKSTURY_H_INCLUDED
#define TEKSTURY_H_INCLUDED

#include <windows.h>
#include <gl/gl.h>
#include "include/png.h"

/**
 * \file
 * \brief Plik zawierający definicje klas odpowiedzialnych za tekstury OpenGL wykorzystywane w programie
 *
 */

/** \brief Definicja klasy tekstura
 *
 * Klasa tekstura przechowuje informacje o pojedynczej teksturze OpenGL
 *
 */
class tekstura
{
public:
    GLuint ID ; /**< identyfikator tekstury */
    int szerokosc; /**< szerokość tekstury */
    int wysokosc; /**< wysokość tekstury */
    int alfa; /**< informacja o kanale przezroczystości */
    GLubyte *obraz; /**< dane tekstury */

    int laduj_teksture(char *name); /**< metoda ładująca teksturę z pliku graficznego
                                 *   \param name nazwa pliku graficznego */
};

/** \brief Definicja klasy tekstury
 *
 * Klasa tekstury przechowuje informacje o wszystkich teksturach OpenGL użytych w aplikacji
 *
 */
class tekstury
{
public:
    struct tekstura korzen;
    struct tekstura lewy;
    struct tekstura prawy;
    struct tekstura wyszukiwanie;
    struct tekstura legenda;
};


#endif // TEKSTURY_H_INCLUDED
