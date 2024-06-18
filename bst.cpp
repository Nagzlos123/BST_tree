#include "bst.h"
#include "funkcje.h"
using namespace std;

/**
 * \file
 * \brief Plik zawierający implementację metod klasy BST
 *
 */

BST::BST()
{
    korzen = NULL;
}

void BST::generuj_nowe(int ile, int zakres, int uporzadkowanie)
{
    int x;
    if (korzen)
    {
        korzen->usun();
        korzen = NULL;
    }
    liczba_porownan = 0;
    liczba_przebiegow_petli = 0;
    liczba_przypisan = 0;


    for (int i=0;i<ile;i++)
    {
        switch (uporzadkowanie)
        {
        case 0:
            x= rand()%zakres;
            break;
        case 1:
            x= i*zakres/ile;
            break;
        case 2:
            x= zakres-i*zakres/ile;
            break;
        }
        dodaj(x);
    }

}

void BST::dodaj(int wartosc)
{
    wezel*y = NULL; //Bendzie wskazywa³ na rodzica nowego wêz³a.
    wezel*x = korzen;//S³u¿y do wyszukania miejsca do wstawienia.

    wezel*nowy = new wezel;//Osobny wêze³ który pó¿niej podepne do drzewa.
    nowy->klucz = wartosc;
    nowy->lewy = NULL;
    nowy->prawy = NULL;
    nowy->rodzic = NULL;
    nowy->stan_wyszukania=false;
    liczba_przypisan += 8;

    while(x != NULL)// Wyszukuje miejsce potomka
    {
        liczba_przebiegow_petli++;
        liczba_porownan++;
        if(wartosc==x->klucz)
        {
            delete nowy;
            return;
        }
        y = x;      liczba_przypisan++;
        liczba_porownan++;
        if(wartosc < x->klucz)
        {
            x = x->lewy; liczba_przypisan++;//X przeskakuje do lewego potomka.

        }else
        {
            x = x->prawy; liczba_przypisan++;
        }

    }
    nowy->rodzic= y;    liczba_przypisan++;
    liczba_porownan++;
    if(y == NULL)
    {
        korzen = nowy; liczba_przypisan++;//Dziecko staje siê praojcem(korzeniem).
    }
    else
    {
        liczba_porownan++;
        if(wartosc < y->klucz)
        {
            y->lewy = nowy;liczba_przypisan++;
        }

        else
        {
            y->prawy = nowy;liczba_przypisan++;
        }

    }
}
void  BST::wyswietl(int x, int y, int rozpietosc,wezel*W,int kolor,tekstury*T)
{
    if(W==NULL) return;

    // wybór koloru węzła w zależności od rodzaju
    switch(kolor)
    {
        case 1 : glBindTexture(GL_TEXTURE_2D, T->korzen.ID);break;
        case 2 : glBindTexture(GL_TEXTURE_2D, T->lewy.ID);break;
        case 3 : glBindTexture(GL_TEXTURE_2D, T->prawy.ID);break;
    }

    if(W->stan_wyszukania==true)
    {
        glBindTexture(GL_TEXTURE_2D, T->wyszukiwanie.ID);
    }
    // włączenie kanału przezroczystości oraz teksturowania
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);

    // rysowanie węzła przy użyciu wybranej tekstury
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex2i(x-15,y-15);
        glTexCoord2f(0.0f,1.0f);glVertex2i(x+15,y-15);
        glTexCoord2f(1.0f,1.0f);glVertex2i(x+15,y+15);
        glTexCoord2f(1.0f,0.0f);glVertex2i(x-15,y+15);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    // wstawienie wartości liczbowej węzła
    glColor3f(0.0f,0.0f,0.0f);
    Wstaw_liczbe(x,y,W->klucz);


    // rysowanie lewego potomka
    if (W->lewy)
    {
        glBegin(GL_LINES);
            glVertex2i(x-11,y-11);
            glVertex2i(x-rozpietosc,y-60);
        glEnd();
        wyswietl(x-rozpietosc,y-60,rozpietosc/2,W->lewy,2,T);
    }

    // rysowanie prawego potomka
    if (W->prawy)
    {
         glBegin(GL_LINES);
            glVertex2i(x+11,y-11);
            glVertex2i(x+rozpietosc,y-60);
        glEnd();
        wyswietl(x+rozpietosc,y-60,rozpietosc/2,W->prawy,3,T);
    }
}
wezel* BST::wyszukaj(int klucz)
{
    wezel*x=korzen;
    liczba_porownan = 0;
    while(x)
    {
        x->stan_wyszukania=true;
      if(x->klucz==klucz)
            return x;
      if(x->klucz> klucz)
         x= x->lewy;
         else
            x=x->prawy;
    }

return NULL;
}

void BST::wyczysc_wyszukiwanie(wezel * W)
{
    if(W==NULL) return;

    W->stan_wyszukania = false;
    wyczysc_wyszukiwanie(W->lewy);
    wyczysc_wyszukiwanie(W->prawy);

}

wezel* BST::usun(wezel*x)
{

  wezel * rodzic = x->rodzic, * poprzednik;

  if((x->lewy) && (x->prawy))
  {
    poprzednik = usun(x->poprzednik());
    poprzednik->lewy = x->lewy;   if(poprzednik->lewy)  poprzednik->lewy->rodzic  = poprzednik;
    poprzednik->prawy = x->prawy; if(poprzednik->prawy) poprzednik->prawy->rodzic = poprzednik;
  }
  else poprzednik = (x->lewy) ? x->lewy : x->prawy;

  if(poprzednik) poprzednik->rodzic = rodzic;

  if(!rodzic) korzen = poprzednik;
  else if(rodzic->lewy == x) rodzic->lewy = poprzednik; else rodzic->prawy = poprzednik;

  return x;
}
void BST::wyswietl_drzewo(tekstury*T)
{



    wyswietl(400,500,200,korzen,1,T);

}
