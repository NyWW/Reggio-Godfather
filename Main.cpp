#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cctype>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class GodfatherATC{
public:
    int numberOfPlanes;
    
    struct Header{
        Plane* first;
        Plane* last;
    }
    
    struct Plane{ 
        int fuel;
        int people;
        int cargo;
        int timeToExecute;
        
        bool grandKid;
        bool arrOrDep;
                
        Plane *ahead = NULL;
        Plane *behind = NULL;
    };

    //adds 
    void addToFront(int paramFuel, int paramPeople, int paramCargo, bool paramGk, bool paramArrive)
    {
        Plane* temp = new Node();
        
        if (created == false)
        {
            temp->fuel = paramFuel;
            temp->poeple = paramPeople;
            temp->cargo = paramCargo;
            temp->grandKid = paramGk;
            temp->arrOrDep = paramArrive;
            
            temp->next = NULL;
            temp->previous = NULL;
            
            head.first = temp;
            head.last = temp;
            
            created = true;
        }
        else
        {
            temp->fuel = paramFuel;
            temp->poeple = paramPeople;
            temp->cargo = paramCargo;
            temp->grandKid = paramGk;
            temp->arrOrDep = paramArrive;
                        
            temp->ahead = NULL;
            temp->behind = head.first;
                        
            head.first->next = temp;
            head.first = temp;
        }
        
        numberOfPlanes++;
    }



private:
    int relativeTime;
    double avgTakeoffWaitTime;
    double avgLandWaitTime;
    int planeCrashes;
    int planeDepartures;
    int planeArrivals;
    int peopleLanded;
    int peopleKilled;
    int grandKidKilled;
    double avgGrandKidArrive;
    double avgGrandKidDepart;
    int safeCargo;
    int destroyedCargo;
    int totalTime;
    
    Header head;

};

int main(){
    

}
