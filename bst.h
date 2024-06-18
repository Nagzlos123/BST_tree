#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
#include "tekstury.h"
/**
 * \file
 * \brief Plik zawierający definicje klas dla drzewa BST
 *
 */

/** \brief Definicja klasy wezel
 *
 * Klasa wezel zawiera strukturê pojedynczego wêz³a drzewa BST
 *
 */
class wezel
{
public:
    int klucz;/**< wartość jaką przechowuje węzeł */
    bool stan_wyszukania;/**< okresla czy wezel jest na drodze wyszukiwania */
    wezel*lewy;  /**< wskaźnik na lewego potomka */
    wezel*prawy; /**< wskaźnik na prawego potomka */
    wezel*rodzic; /**< wskaźnik na rodzica */

    /** \brief metoda znajdująca maksymalną wartość klucza wśród potomków węzła
     *
     * \return wskaźnik do węzła z maksymalną wartością klucza
     *
     */
    wezel * maximum()
    {
      wezel * x = this;

       while(x->prawy)
        x = x->prawy;

      return x;
    }

    /** \brief metoda znajdująca poprzednika węzła
     *
     * \return wskaźnik na poprzednika węzła
     *
     */
    wezel * poprzednik()
    {
        wezel*x=this;
      if(x->lewy) return x->lewy->maximum();

      wezel * y;

      do
      {
        y = x;
        x = x->rodzic;
      } while(x && (x->prawy != y));

      return x;
    }
    /** \brief metoda usuwająca węzeł i jego potomków
     *
     */
    bool usun()
    {
         if (lewy == NULL && prawy == NULL)
            return true;
       if(lewy)
        {
            if (lewy->usun())
            {
                delete lewy;
                lewy = NULL;
            }

        }
        if(prawy)
        {
           if (prawy->usun())
            {
                delete prawy;
                prawy = NULL;
            }
         }

        return false;
    }

};

/** \brief Definicja klasy BST
 *
 * Klasa BST przechowuje wskaźnik do drzewa BST oraz zawiera
 * metody zarządzające drzewem.
 *
 */
class BST
{
public:
    wezel*korzen;               /**< wskaźnik na korzeń drzewa */
    int liczba_porownan;        /**< liczba porównań (statystyczna) */
    int liczba_przebiegow_petli;/**< liczba przebiegów pętli (statystyczna) */
    int liczba_przypisan;       /**< liczba przypisań (statystyczna) */
    BST();                      /**< konstruktor klasy BST */

    void generuj_nowe(int ile, int zakres, int uporzadkowanie); /**< metoda generująca nowe drzewo
                                                                 *   \param ile liczba węzłów
                                                                 *   \param zakres zakres generowanych wartości węzła
                                                                 *   \param uporzadkowanie rodzaj uporządkowania */
    void dodaj(int wartosc);    /**< metoda dodająca nowy węzeł do drzewa
                                 *   \param wartosc określa wartość, która będzie wstawiona do węzła*/

     wezel*wyszukaj(int klucz); /**< metoda wyszukująca węzła o podanej wartości klucza */
     void wyczysc_wyszukiwanie(wezel * W); /**< metoda czyszcząca węzły kolorowane w trakcie wyszukiwania */
    wezel*usun(wezel*x); /**< metoda usuwająca węzeł */
    void wyswietl(int x, int y, int rozpietosc,wezel*W,int kolor,tekstury*T);     /**< metoda wyświetlająca węzeł drzewa
                                 *   \param x pozycja x na ekranie
                                 *   \param y pozycja y na ekranie
                                 *   \param rozpietosc odległość między węzłami potomnymi
                                 *   \param W wskaźnik na węzeł
                                 *   \param kolor kolor węzła (niebieski - korzeń, czerwony - prawy potomek, zielony - lewy potomek)
                                 *   \param T wskaźnik na obiekt przechowujący tekstury */

    void wyswietl_drzewo(tekstury*T);     /**< metoda wyświetlająca całe drzewo BST
                                            *   \param T wskaźnik na obiekt przechowujący tekstury */
};

#endif // BST_H_INCLUDED
