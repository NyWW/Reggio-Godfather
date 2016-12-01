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
    GodfatherATC();
    void data();
    void statistic();
    void wait();
    void takingInput();
    void sorting();

    struct stringArray{
        string inputs;
        stringArray *next = NULL;
    };

    struct Plane{
        int fuel;
        int people;
        int cargo;
        int timeToExecute;
        bool grandKid;
        Plane *left = NULL;
        Plane *right = NULL;
    };




private:
    stringArray *head;
    stringArray *ptr;
    stringArray *last;

    int numberOfPlanes;
    int relativeTime;
    int planeCrash;
    int planeDepart;
    int planeArrive;
    int peopleSafeLanded;
    int peopleKilled;
    int grandKidKilled;
    int safeCargo;
    int destroyedCargo;
    int totalTime;

    double avgGrandKidArrive;
    double avgGrandKidDepart;
    double avgTOWaitTime;
    double avgLDWaitTime;

};
GodfatherATC::GodfatherATC(){
    head = NULL;
    ptr = NULL;
    last = NULL;

    int numberOfPlanes = 0;
    int relativeTime = 0;
    int safeCargo = 0;
    int destroyedCargo = 0;
    int totalTime = 0;
    int planeCrash = 0;
    int planeDepart = 0;
    int planeArrive = 0;
    int peopleSafeLanded = 0;
    int peopleKilled = 0;
    int grandKidKilled = 0;

    double avgGrandKidArrive = 0;
    double avgGrandKidDepart = 0;
    double avgTOWaitTime = 0;
    double avgLDWaitTime = 0;

}
void GodfatherATC::takingInput(){
    ifstream textfile;
    string sample;
    textfile.open("FP.txt");
    if(textfile.fail()){
        cerr << "Error Opening File!" << endl;
        exit(1);
    }
    while(!textfile.eof()){
        getline(textfile, sample);
        /*textfile >> sample;
        cout << sample << endl;
        result += sample;
        result.append(" ");
        */

        stringArray *temp = new stringArray;

        temp -> inputs = sample;
        if(head == NULL){
            head = temp;
            ptr = head;
            last  = head;
        }
        else{
            last -> next = temp;
            last  = temp;
        }
        temp = NULL;
        delete temp;
    }
    textfile.close();
    data();
    return;
}
void GodfatherATC::sorting(){

}
void GodfatherATC::wait(){

}
void GodfatherATC::statistic(){

}
void GodfatherATC::data(){
    ptr = head;
    while(ptr != NULL){
        cout << ptr -> inputs << endl;
        ptr = ptr -> next;
    }
    return;
}

int main(){
    GodfatherATC Sherloc;
    Sherloc.takingInput();

}
