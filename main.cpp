// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <iterator>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int, char);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	char s = argv[2][0];
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n, s);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n, char s)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;

	map <_sex, vector <Slav *> > mapOfSlavs_sex;

	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.

	srand(time(NULL));
	vectorOfSlavs.push_back(&slavs[0]);
	for( int i = 1; i < n; ++i )
    {
        int where = rand() % vectorOfSlavs.size();
        vectorOfSlavs.insert( vectorOfSlavs.begin() + where, &slavs[i] );
    }

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze

	vector <Slav *>::iterator it_vectorOfSlavs = vectorOfSlavs.begin();
	while(it_vectorOfSlavs != vectorOfSlavs.end())
	{
     	cout << (*it_vectorOfSlavs)->description() << endl;
     	it_vectorOfSlavs++;
	}



	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.

	for(int i = 0; i < n; ++i)
		setOfSlavs.insert(vectorOfSlavs[i]);

	vectorOfSlavs.clear();

	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór

	set <Slav *>::iterator it_setOfSlavs = setOfSlavs.begin(), it_e_setOfSlavs = setOfSlavs.begin();
	
	while(it_setOfSlavs != setOfSlavs.end())
	{
		mapOfSlavs[*it_setOfSlavs++] = *it_setOfSlavs++;
		setOfSlavs.erase(it_e_setOfSlavs++);
		setOfSlavs.erase(it_e_setOfSlavs++);
	}

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	
	map <Slav *, Slav *>::iterator it_mapOfSlavs = mapOfSlavs.begin();
	while(it_mapOfSlavs != mapOfSlavs.end())
	{
     	cout << (*it_mapOfSlavs).first->description() << " " 
     		 << (*it_mapOfSlavs).second->description() << endl;
     	it_mapOfSlavs++;
	}
	
	REPORT_CONTAINERS;


	//Zadanie na 5

	for(int i =0; i < n; ++i)
	{
		if(slavs[i].sex() == male)
			mapOfSlavs_sex[male].push_back(&slavs[i]);
		else
			mapOfSlavs_sex[female].push_back(&slavs[i]);
	}

	
	vector <Slav *>::iterator iter = mapOfSlavs_sex[male].begin();
	if(s =='m')
	{
		if(mapOfSlavs_sex[male].empty())
			cout << "There are no male Slavs" << endl;

		else
		{
			cout << "Men:" << endl;
			while(iter != mapOfSlavs_sex[male].end())
			{
     			cout << (*iter)->description() << endl;
     			iter++;
     		}
     	}
     }
		
	else if(s == 'f')
	{
		if(mapOfSlavs_sex[female].empty())
			cout << "There are no female Slavs" << endl;

		else
		{
			cout << "Women:" << endl;
			iter = mapOfSlavs_sex[female].begin();

			while(iter != mapOfSlavs_sex[female].end())
			{
     			cout << (*iter)->description() << endl;
     			iter++;
     		}
     	}
    }
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.

	for(int i=0; i < n; ++i)
		queueOfSlavs.push(&slavs[i]);

	REPORT_ADAPTERS;

		// Przenieś Słowian z kolejki do stosu.

	printf("## stack\n");
	while (!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}


	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	while(!stackOfSlavs.empty())
	{
		cout << stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;


}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
