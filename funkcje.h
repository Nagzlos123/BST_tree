#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
/**
 * \file
 * \brief Plik zawierający nagłówki funkcji ogólnego przeznaczenia
 *
 */

 /** \brief Funkcja wstawia tekst w oknie OpenGL
  *
  * \param x pozycja x na ekranie
  * \param y pozycja y na ekranie
  * \param st ciąg znaków do wyświetlenia
  *
  */
void Wstaw_tekst( int x, int y, char *st);

/** \brief Funkcja wstawia liczbę w oknie OpenGL
  *
  * \param x pozycja x na ekranie
  * \param y pozycja y na ekranie
  * \param liczba liczba do wyświetlenia
  *
  */
void Wstaw_liczbe( int x, int y, int liczba);

#endif // FUNKCJE_H_INCLUDED
