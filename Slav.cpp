#include "Slav.h"
#include <fstream>
#include <string>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); //leniwa inicjalizacja
	//dzieki "static" wykona sie tylko raz, ale inicjalizacja nastąpi
	//dopiero w momencie pierwszego użycia obiektu

	_name = names[rand() % amountOfNames];
	_id = _counter++;

}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

 _sex Slav::sex()
{
	return (_name[_name.length()-1] == 'a' ? female : male);
}