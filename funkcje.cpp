#include "funkcje.h"
#include <string.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
/**
 * \file
 * \brief Plik zawierający implementacje funkcji ogólnego przeznaczenia
 *
 */


void Wstaw_tekst( int x, int y, char *st)
{
    int l,i;

    l=strlen( st ); // see how many characters are in text string.
    glRasterPos2i( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]); // Print a character on the screen
    }
}


void Wstaw_liczbe( int x, int y, int liczba)
{
    int l,i;
    char st[10];
    itoa(liczba,st,10);
    l=strlen( st ); // see how many characters are in text string.
    glRasterPos2i( x-l*5, y-8); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]); // Print a character on the screen
    }
}
