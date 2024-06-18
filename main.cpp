#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include "bst.h"
#include "funkcje.h"
#include "tekstury.h"
#include "resource.h"
/**
 * \file
 * \brief Plik zawierający funkcję główną programu
 *
 * W tym pliku znajdują się funkcje obsługujące zdarzenia aplikacji oraz funkcja główna programu. Wykorzystano interfejs GLUT.
 */


tekstury T; /**< obiekt przechowujący dane tekstur OpenGL */
BST drzewo; /**< obiekt przechowujący dane drzewa BST */

void Initialize();
void ChangeSize(GLsizei w, GLsizei h);
void RenderScene();
void TimerFunc(int value);
void KeyPress(unsigned char button, int x, int y);

/** \brief Funkcja inicjalizująca
 *
 * Zawiera inicjalizację ustawień OpenGL, generowanie drzewa BST oraz ładowanie tekstur z plików.
 *
 */
void Initialize()
{
    int x;

    glClearColor(1.0,1.0,1.0,0.0);
    glEnable(GL_TEXTURE_2D);

    drzewo.generuj_nowe(15,30,0);

    T.korzen.laduj_teksture("img\\korzen.png");
    T.lewy.laduj_teksture("img\\lewy.png");
    T.prawy.laduj_teksture("img\\prawy.png");
    T.wyszukiwanie.laduj_teksture("img\\wyszukiwanie.png");
    T.legenda.laduj_teksture("img\\legenda.png");



    glMatrixMode(GL_PROJECTION);			// wybiera macierz rzutowania
	glLoadIdentity();					// resetuje macierz rzutowania

	// wyznacza proporcje obrazu
    glOrtho(0,800,0,600,1,-1);

    glMatrixMode(GL_MODELVIEW);				// wybiera macierz modelowania
	glLoadIdentity();						// resetuje macierz modelowania
}

/** \brief Funkcja uruchamiająca się przy zmianie rozmiaru okna
 *
 * \param w nowa szerokość okna
 * \param h nowa wysokość okna
 */
void ChangeSize(GLsizei w, GLsizei h)
    {

	if (h==0)				// unika dzielenia przez 0
		h=1;


	glViewport(0, 0, w, h);	// nadaje nowe wymairy oknu OpenGL
	glMatrixMode(GL_PROJECTION);			// wybiera macierz rzutowania
	glLoadIdentity();					// resetuje macierz rzutowania


	glOrtho(0,w,0,h,1,-1);

	glMatrixMode(GL_MODELVIEW);				// wybiera macierz modelowania
	glLoadIdentity();						// resetuje macierz modelowania

}

/** \brief Funkcja rysująca grafikę w oknie OpenGL
 *
 */
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

    drzewo.wyswietl_drzewo(&T);
    Wstaw_tekst(10,580,"Prawy przycisk myszy - menu         ESC - zakonczenie dzialania programu");

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D, T.legenda.ID);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
        glTexCoord2f(0.0f,1.0f);glVertex2i(0,101);
        glTexCoord2f(1.0f,1.0f);glVertex2i(128,101);
        glTexCoord2f(1.0f,0.0f);glVertex2i(128,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();

   glFlush();
   glutSwapBuffers();
}


/** \brief Funkcja wywoływana automatycznie co 20 milisekund
 *
 * \param value czas w milisekundach pomiędzy wywołaniami funkcji
 */
void TimerFunc(int value)
{


	glutTimerFunc(20, TimerFunc, 1);
}

/** \brief Funkcja obsługująca zdarzenie naciśnięcia klawisza
 *
 * \param button kod klawisza
 * \param x pozycja x kursora na ekranie
 * \param y pozycja y kursora na ekranie
 *
 */
void KeyPress(unsigned char button, int x, int y)
{
	switch (button)
	{

	case 27:
		exit(0);
	}
}

/** \brief Funkcja obsługująca okno dialogowe z podawaniem wartości węzła
 *
 */
BOOL CALLBACK PodajWartosc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND wartosc;
    switch (msg)
	{
	case WM_INITDIALOG:
		GetDlgItem(hwnd, WARTOSC);
		wartosc = SetFocus(wartosc);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, GetDlgItemInt(hwnd, WARTOSC, NULL, FALSE));
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}

	return FALSE;
}

/** \brief Funkcja obsługująca okno dialogowe wyświetlane przy generowaniu nowego drzewa
 *
 */
 BOOL CALLBACK NoweDrzewo(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND pole_ile;
	int ile,zakres;
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwnd, ILE, 10, true);
		SetDlgItemInt(hwnd, ZAKRES, 300, true);
		pole_ile = GetDlgItem(hwnd, ILE);
		SetFocus(pole_ile);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		    ile = GetDlgItemInt(hwnd, ILE, NULL, FALSE);
		    zakres = GetDlgItemInt(hwnd, ZAKRES, NULL, FALSE);
			EndDialog(hwnd, (ile<<16)+zakres);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}

	return FALSE;
}

/** \brief Funkcja wyświetlająca liczbę przeprowadzonych operacji
 *
 */
void statystyki()
{
    char tekst[100];
    sprintf(tekst,"Liczba porownan: %i\nLiczba przebiegow petli: %i\nLiczba przypisan: %i",
            drzewo.liczba_porownan, drzewo.liczba_przebiegow_petli, drzewo.liczba_przypisan);
    MessageBox(NULL,tekst,"Statystyki",0);
}

/** \brief Funkcja obsługująca menu kontekstowe
 *
 */
 void Menu (int id)
{
    int wartosc;
    wezel * w;

    switch (id)
    {
    case 1 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(PODAJWARTOSC), NULL, PodajWartosc);
        drzewo.dodaj(wartosc);
        break;
    case 2 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(PODAJWARTOSC), NULL, PodajWartosc);
        w = drzewo.wyszukaj(wartosc);
        if (w == NULL)
            MessageBox(NULL,"Nie ma takiego klucza!",NULL,0);
        break;
    case 21 :
        drzewo.wyczysc_wyszukiwanie(drzewo.korzen);
        break;
    case 3 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(PODAJWARTOSC), NULL, PodajWartosc);
        w = drzewo.wyszukaj(wartosc);
        drzewo.wyczysc_wyszukiwanie(drzewo.korzen);
        if (w == NULL)
            MessageBox(NULL,"Nie ma takiego klucza!",NULL,0);
        else
            drzewo.usun(w);
        break;
    case 31 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(NOWEDRZEWO), NULL, NoweDrzewo);
        drzewo.generuj_nowe(HIWORD(wartosc),LOWORD(wartosc),0);
        statystyki();
        break;
    case 32 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(NOWEDRZEWO), NULL, NoweDrzewo);
        drzewo.generuj_nowe(HIWORD(wartosc),LOWORD(wartosc),1);
        statystyki();
        break;
    case 33 :
        wartosc = DialogBox(NULL, MAKEINTRESOURCE(NOWEDRZEWO), NULL, NoweDrzewo);
        drzewo.generuj_nowe(HIWORD(wartosc),LOWORD(wartosc),2);
        statystyki();
        break;
    case 4 :
        exit (0);
        break;
    default :
        break;
    }
}
/** \brief Główna funkcja programu
 *
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    // Włączenie generatora liczb pseudolosowych
	srand(time(NULL));

	// Iniscjalizacja trybu graficznego
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Inicjalizacja rozmiaru okna OpenGL
    glutInitWindowSize(800, 600);

    // Utworzenie okna OpenGL
    glutCreateWindow("Drzewo BST");

    // Utworzenie menu kontekstowego
    glutCreateMenu (Menu);
       glutAddMenuEntry ("Dodaj nowy wezel", 1);
       glutAddMenuEntry ("Wyszukaj", 2);
       glutAddMenuEntry ("Wyczysc wyszukiwanie", 21);
       glutAddMenuEntry ("Usun wezel", 3);
       glutAddMenuEntry ("Generuj nowe drzewo losowo", 31);
       glutAddMenuEntry ("Generuj nowe drzewo rosnaco", 32);
       glutAddMenuEntry ("Generuj nowe drzewo malejaco", 33);
       glutAddMenuEntry ("Koniec", 4);
    glutAttachMenu (GLUT_RIGHT_BUTTON);

    // Przypisanie funkcji uruchamiającej się przy zmianie rozmiaru okna
    glutReshapeFunc(ChangeSize);

    // Przypisanie funkcji obsługującej zdarzenie naciśnięcia klawisza
    glutKeyboardFunc(KeyPress);

    // Przypisanie funkcji rysującej grafikę w oknie OpenGL
    glutDisplayFunc(RenderScene);

    // Przypisanie funkcji rysującej grafikę, gdy aplikacja działa w tle
	glutIdleFunc(RenderScene);

	// Inicjalizacja ustawień OpenGL, generowanie drzewa BST oraz ładowanie tekstur z plików.
    Initialize();

    // Funkcja timera, uruchamiana automatycznie co 20 milisekund
    glutTimerFunc(20, TimerFunc, 1);

    // Główna pętla aplikacji OpenGL
    glutMainLoop();

	return 0;
}
