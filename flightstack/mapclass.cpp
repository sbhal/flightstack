#include "mapclass.h"


//constructor
mapclass::mapclass(void)
{
    cityHead = nullptr;
    fpHead = nullptr;
    currentCity = '0';
    currentPrice = 0;
    cityCurrent = nullptr;
    fpCurrent = nullptr;
}
mapclass::~mapclass(void)
{
    cityNode *delcityNode;
    fpNode * delfpNode;
    while(cityHead != nullptr)
    {
        delcityNode = cityHead;
        cityHead = cityHead->next;
        delete delcityNode;
    }
    while(fpHead != nullptr)
    {
        delfpNode = fpHead;
        fpHead = fpHead->next;
        delete delfpNode;
    }
}
void mapclass::addCity(char cityName, bool isOrigin)
{
    cityNode *newCity = new cityNode;
    newCity->cityName = cityName;
    newCity->visited = false;
    newCity->isOrigin = isOrigin;
    newCity->next = nullptr;
    if((cityHead == nullptr) && (isOrigin == true))
    {
        //add to starting
        cityHead = newCity;
    } else {
		
        //add to the end
        cityNode *itr;
		for (itr = cityHead; (itr->next != nullptr) && (itr->cityName != cityName); itr = itr->next);
			if (itr->next == nullptr)
				itr->next = newCity;
			else {
				cout << "City already added" << endl;
			
		}
    }
    cout <<"Adding City - "<<cityName<<endl;
}

void mapclass::addFlight(char start, char end, int price)
{
    fpNode *newFlight = new fpNode;
    newFlight->nodeFlight.City = end;
    newFlight->nodeFlight.parentCity = start;
    newFlight->nodeFlight.price = price;
    newFlight->next = nullptr;
    if(fpHead == nullptr)
    {
        //add to starting
        fpHead = newFlight;
    } else {
        //add to the end
        fpNode *itr;
        for(itr = fpHead; itr->next != nullptr; itr=itr->next);
        itr->next = newFlight;
    }
    cout <<"Adding Flight - "<<start<<" to "<<end<< " with price "<< price<<endl;
}

void mapclass::markVisited(char cityName, bool visited)
{
    cityNode *itr;
    cout <<"Marking visited to City - "<<cityName<<endl;
    for(itr = cityHead; (itr->cityName != cityName) && (itr != nullptr); itr=itr->next);
    if (itr == nullptr) {
        cout <<"City Not found. Cannot mark city as visited"<<endl;
    } else {
        itr->visited = visited;
    }
}
bool mapclass::visitedCity(char cityName)
{
    cityNode *itr;
    for(itr = cityHead; (itr->cityName != cityName) && (itr != nullptr); itr=itr->next);
    if (itr == nullptr) {
        cout <<"City Not found. Cannot check if city as visited"<<endl;

    }
    return itr->visited;
}
void mapclass::setCurrentCity(char cityName)
{
    currentCity = cityName;
    cityNode *itr;
    cout <<"Setting Current City - "<<cityName<<endl;
    for(itr = cityHead; (itr->cityName != cityName) && (itr != nullptr); itr=itr->next);
    if (itr == nullptr) {
        cout <<"City Not found. Cannot check if city as visited"<<endl;
    }
    cityCurrent = itr;
}
void mapclass::clear()
{
    currentFlightPath.~stackP();
    //cityHead = nullptr;
    //fpHead = nullptr;
    //currentCity = '0';
    currentPrice = 0;
    //cityCurrent = nullptr;
    fpCurrent = nullptr;
    cout <<" Clearing mapclass "<<endl;
}

bool mapclass::search(char destination)
{
    //search() searches the flightmap iteratively to find a path to Dest from CurrentCity
	cout << "Flight Search Started for destination " << destination << endl;
    fpNode *flightNode = fpHead;
    bool isDeeperNodeFound = false;
    char topcity;
    cityNode *CCity = cityCurrent; //Initialization
    currentFlightPath.push(cityCurrent->cityName);
    while (currentFlightPath.getCount() > 0)
    {
        topcity = currentFlightPath.peek();
        //CCity = topcity;
        //setCurrentCity(topcity);
        cityCurrent->visited = true;
        if(cityCurrent->cityName == destination)
            return true; //terminate
        //For each flight in FlightList:
        for(flightNode = fpHead; flightNode != nullptr; flightNode = flightNode->next)
        {
            if ((flightNode->nodeFlight.parentCity == topcity) &&
                    !visitedCity(flightNode->nodeFlight.City)) {
                //If flight.origin is cityCurrent:
                //If flight.destination is unmarked:
                if(flightNode->nodeFlight.City == destination) {
					currentFlightPath.push(flightNode->nodeFlight.City);
                    cout <<"--------------> City Found"<<endl;
                    return true;
                } else {
                    currentFlightPath.push(flightNode->nodeFlight.City);
                    isDeeperNodeFound = true;
                }
                break; //breaks for loop
            }
        }
        //If no push occurs in this iteration:
        if (!isDeeperNodeFound)
            currentFlightPath.pop();
        //search Ends
    }
    cout <<"City Not found "<<currentCity << " to "<<destination<<endl;
    return false;
}

int mapclass::getRoutePrice(char backTrack[])
{
    int TotalCost = 0;
    int count = 0;
    fpNode *flightNode = fpHead;
    char topcity = currentFlightPath.peek(); //Initialization
    //currentFlightPath.pop();
    char top2city = currentFlightPath.peek(); //Initialization
	cout <<"getRoutePrice called with stack count is "<< currentFlightPath.getCount() <<endl;

    while (currentFlightPath.getCount() > 1)
    {
        topcity = currentFlightPath.peek();
        currentFlightPath.pop();
        top2city = currentFlightPath.peek();
		cout << "topcity is " << topcity << "and top2city is " << top2city << endl;
        //For each flight in FlightList:
        for(flightNode = fpHead; flightNode != nullptr; flightNode = flightNode->next)
        {
            if ((flightNode->nodeFlight.City == topcity) &&
                    (flightNode->nodeFlight.parentCity == top2city)) {
                //CCity = flightNode->nodeFlight.parentCity;
                TotalCost += flightNode->nodeFlight.price;
                backTrack[count++] = topcity;
                break; //breaks for loop
            }
        }
    }
	backTrack[count++] = currentCity;
	cout << "returning total cost as " << TotalCost << endl;
    return TotalCost;
}
