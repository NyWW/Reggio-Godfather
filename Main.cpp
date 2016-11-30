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
    
    struct Plane{ 
        int fuel;
        int people;
        int cargo;
        int timeToExecute;
        
        bool grandKid;
        bool arrOrDep;
        
        
        Plane *left = NULL;
        Plane *right = NULL;
    };




private:
    int relativeTime;
    double avgTOWaitTime;
    double avgLDWaitTime;
    int planeCrash;
    int planeDepart;
    int planeArrive;
    int peopleSafeLanded;
    int peopleKilled;
    int grandKidKilled;
    double avgGrandKidArrive;
    double avgGrandKidDepart;
    int safeCargo;
    int destroyedCargo;
    int totalTime;

};

int main(){
    

}
