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

class Godfather{
public:
    struct Plane{
        char Data;
        int Fuel;
        int PPL;
        int Cargo;
        bool GC;
        Plane *Left = NULL;
        Plane *Right = NULL;
    };




private:
    int RelativeTime;
    double AvgTOWaitTime;
    double AvgLDWaitTime;
    int PlaneCrash;
    int PlaneDepart;
    int PlaneArrive;
    int PPLSafeLanded;
    int PPLKilled;
    int GCKilled;
    double AvgGCArrive;
    double AvgGCDepart;
    int SafeCargo;
    int DestroyedCargo;
    int TotalTime;

};
int main(){


}
