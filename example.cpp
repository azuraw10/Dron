#include <iostream>
#include "Dr3D_gnuplot_api.hh"
#include "silnik.h"

using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;
using std::cout;
using std::endl;

void wyswietlMenu()
{
    cout << "Menu\n";
    cout << "========\n";
    cout << "o - Zadaj zmiane orientacji.\n";
    cout << "r - Zadaj ruch na wprost\n";
    cout << "z - Zmień aktywnego drona.\n";
    cout << "c - Reset do położenia domyślnego.\n";
    cout << "m - Wyświetl menu.\n";
    cout << "k - Zakończ program.\n";
}

void wyswietlInfoOObiektachWektor()
{
    cout <<  "Aktualna ilosc obiektow Wektor: " << Wektor::liczbaIstniejacychObiektow() << endl;
    cout <<  "Laczna ilosc obiektow Wektor: " << Wektor::liczbaStworzonychObiektow() << endl;
}

bool odczytjWyborIWykonajAkcje(Silnik *silnik)
{
    cout << "Twoj wybor, m - menu:\n";

    char selection;

    cin >> selection;

    switch(selection) {
    case 'o': {
        cout << "Podaj wartosc kata obrotu w stopniach:";
        double kat;
        cin >> kat;
        silnik->obrocDrona(kat);
        wyswietlInfoOObiektachWektor();
        break;
    }
    case 'r': {
        cout << "Podaj wartosc kata (wznoszenia/opadania) w stopniach:";
        double kat;
        cin >> kat;
        cout << "Podaj wartosc odleglosci, na ktora ma sie przemiescic dron:";
        double odleglosc;
        cin >> odleglosc;
        silnik->wykonajRuchDrona(kat, odleglosc);
        wyswietlInfoOObiektachWektor();
        break;
    }
    case 'z': {
        cout << "Wybierz drona (1 - czerwony, 2 - zielony, 3 - zółty:";
        int d;
        cin >> d;
        if (d < 1 || d > 3) {
            cout << "Niepoprawny wybór!";
            break;
        }

        silnik->ustawAktywnegoDrona(static_cast<Silnik::DronId>(d));

        wyswietlInfoOObiektachWektor();
        break;
    }
    case 'c': {
        silnik->resetDoDomyslnegoPolozenia();
        wyswietlInfoOObiektachWektor();
        break;
    }
    case 'm': {
        wyswietlMenu();
        break;
    }
    case 'k': {
        return false;
    }
    default:
        cout<<"\n Niepoprawny wybór!";
    }

    cout<<"\n";

    return true;
}

void wait4key() {
  do {
    std::cout << "\n Press a key to continue..." << std::endl;
  } while(std::cin.get() != '\n');
}

int main() {
    // Dodaj dodatkowy zakres tak, żeby wszystkie obiekty Wektor zostały usunięte
    // przed komunikatem "koniec programu" - tak żeby wyswietlInfoOObiektachWektor wyświetliło,
    // że obecnie nie istnieje żaden obiekt Wektor.
    {
        Silnik silnik;

        wyswietlMenu();
        wyswietlInfoOObiektachWektor();
        while (odczytjWyborIWykonajAkcje(&silnik)) {}
    }

  std::cout << "Koniec programu!" << endl;
  wyswietlInfoOObiektachWektor();

  //wait4key();
  
  /*int a=api->draw_line(drawNS::Point3D(0,0,0),drawNS::Point3D(2,0,0)); //rysuje linię pomiędzy (0,0,0) a (2,0,0), zapamiętuje id kształtu w zmiennej a 
  api->draw_line(drawNS::Point3D(0,0,0),drawNS::Point3D(0,0,5),"red"); //rysuje czerwoną linie pomiędzy (0,0,0) a (0,0,5)

  cout << endl << "pojawiły się 2 linie: czarna i czerwona" << endl;  
  wait4key();

  api->erase_shape(a); //usuwa kształt o id a
  cout << "czarna linia zniknęła" << endl;

  wait4key();

  api->draw_polygonal_chain(vector<Point3D> {drawNS::Point3D(0,0,0),
	drawNS::Point3D(0,4,0),drawNS::Point3D(4,4,0),
	drawNS::Point3D(4,0,0),drawNS::Point3D(4,0,4)},"purple"); //rysuje fioletową łamaną
  cout << "pojawiła się fioletowa łamana" << endl;
  
  wait4key();
  api->change_ref_time_ms(1000);
  int b=api->draw_polygonal_chain(vector<Point3D> {drawNS::Point3D(0,0,0),
	drawNS::Point3D(0,-4,0),drawNS::Point3D(-4,-4,0),
	drawNS::Point3D(-4,0,0),drawNS::Point3D(-4,0,-4)},"green");
  cout << "pojawiła się zielona łamana" << endl;
  
  wait4key();
  api->change_shape_color(b,"yellow");//zmienia kolor
  cout << "zmiana koloru z zielonej na żółtą" << endl;

  wait4key();
  api->change_ref_time_ms(-1);//odświerzanie sceny zmienione na opcję "tylko za pomocą metody redraw()"

  api->draw_polyhedron(vector<vector<Point3D> > {{
	drawNS::Point3D(0,0,0), drawNS::Point3D(0,1,0), drawNS::Point3D(1,1,0)
      },{
	drawNS::Point3D(0,0,3), drawNS::Point3D(0,1,3), drawNS::Point3D(1,2,4)       
	  }},"blue");//rysuje niebieski graniastosłup
  cout << "nie pojawiła się niebieski graniastosłup" << endl;
  
  wait4key();

  api->redraw();//odświerzenie sceny
  cout << "dopiero teraz pojawiła się niebieski graniastosłup" << endl;

  wait4key();
  api->change_ref_time_ms(0);

  api->draw_surface(vector<vector<Point3D> > {{
	drawNS::Point3D(-4,-2,-4), drawNS::Point3D(-4,0,-4), drawNS::Point3D(-4,2,-4)
	  },{
	drawNS::Point3D(-2,-2,-4), drawNS::Point3D(-2,0,-4), drawNS::Point3D(-2,2,-4)       
	  },{
	drawNS::Point3D(-0,-2,-4), drawNS::Point3D(-0,0,-3), drawNS::Point3D(-0,2,-4)       
	  },{
	drawNS::Point3D(2,-2,-4), drawNS::Point3D(2,0,-4), drawNS::Point3D(2,2,-4)       
	  },{
	drawNS::Point3D(4,-2,-4), drawNS::Point3D(4,0,-4), drawNS::Point3D(4,2,-4)       
	  }},"grey");//rysuje szarą powierzchnie
  cout << "pojawiła się szara powierzchnia" << endl;

  
  wait4key();
  */
  
  //delete api;//dla zwykłych wskaźników musimy posprzątać
}
