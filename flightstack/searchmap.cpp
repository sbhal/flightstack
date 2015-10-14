#include <iostream>
#include "mapclass.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int main ()
{
    char start;
    char end;
    char originCity;
    int price;
    mapclass map;
#if 1
	stackP A;
	A.push('A');
	cout << A.getCount() << endl;
	A.push('B');
	cout << A.getCount() << endl;
	cout << A.peek() << endl;
	A.pop();
	cout << A.peek() << endl;
	A.~stackP();
	//cin >> start; 
#endif

    ifstream input("testfile1.txt");
    ofstream output("outfile.txt");

    input >> originCity;

    map.addCity(originCity, true /*isOrigin*/);
	map.setCurrentCity(originCity);


    while( input >> start >> end >> price )
    {
        // process the data using your own logic;

        // For example, store a flight into associated linked list
        map.addFlight(start, end, price);
        map.addCity( end, false /*isOrigin*/);
        //see section 3 - Mapclass

    }
	output << left << setw(15) << "Destination";
	output << left << setw(18) << "Flight Route from " << setw(3)<< originCity;
	output << left << setw(14) << "Total Cost" << endl;
    
	for(cityNode *itr = map.cityHead; itr->next != nullptr; itr=itr->next)
    {
        //map.setCurrentCity(itr->cityName);
        if(map.search(itr->cityName)) {
            const int stack_size = map.currentFlightPath.getCount();
            char *backtrack = new char[stack_size];
            int cost = map.getRoutePrice(backtrack);
            
			output << left << setw(15) << itr->cityName;
			
			//output << left << setw(19); 
			for(int i = stack_size -1; i>=0; i--)
            {
                output << backtrack[i] << " ";   //outputting the file using array

            }
			output << setfill(' ')<< setw(21-(stack_size*2))<<" ";
            

            output <<"$"<< cost << endl;
            map.clear();
        }
    }
}

