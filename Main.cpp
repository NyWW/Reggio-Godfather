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

const int hoomanValue = 20000;
const int refuelTime = 10;
const int maxFuel = 1000;


class GodfatherATC{
public:
    GodfatherATC();
    void data();
    void statistic();
    void wait();
    void takingInput();
    void sorting();
    void errorLine();


    struct stringArray{
        string inputs;
        stringArray *next = NULL;
    };

    struct Plane{
        int fuel;
        int people;
        double cargo;
        int timeToExecute;
        double totalValue;
        bool grandKid;
        Plane *nextPlane = NULL;
    };

    struct timeUnit{
        int timeSpace;
        timeUnit *prevTime = NULL;
        timeUnit *nextTime = NULL;
        Plane *next = NULL;
    };



private:
    stringArray *head;
    stringArray *ptr;
    stringArray *last;

    timeUnit *timePtr;
    timeUnit *timeHead;

    Plane *planePtr;

    int numberOfPlanes;
    int relativeTime;
    int planeCrash;
    int planeDepart;
    int planeArrive;
    int peopleSafeLanded;
    int peopleKilled;
    int grandKidKilled;
    int totalTime;

    double safeCargo;
    double destroyedCargo;
    double avgGrandKidArrive;
    double avgGrandKidDepart;
    double avgTOWaitTime;
    double avgLDWaitTime;

};
GodfatherATC::GodfatherATC(){
    head = NULL;
    ptr = NULL;
    last = NULL;

    timePtr = NULL;
    timeHead = NULL;

    numberOfPlanes = 0;
    relativeTime = 0;
    safeCargo = 0;
    destroyedCargo = 0;
    totalTime = 0;
    planeCrash = 0;
    planeDepart = 0;
    planeArrive = 0;
    peopleSafeLanded = 0;
    peopleKilled = 0;
    grandKidKilled = 0;

    avgGrandKidArrive = 0;
    avgGrandKidDepart = 0;
    avgTOWaitTime = 0;
    avgLDWaitTime = 0;

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
    ptr = head;
    while(ptr != NULL){
        string nospace = "";
        for(int a = 0; a < (ptr -> inputs).size(); a++){ // get rid of all the spaces in the input.
            if((ptr -> inputs).at(a) != ' '){
                nospace += ((ptr -> inputs).at(a));
                //if(!isdigit((ptr -> inputs).at(a)) && !isalpha((ptr -> inputs).at(a)) && (ptr -> inputs).at(a) != ','  && (ptr -> inputs).at(a) != '.')
            }
        }
        for(int i = 0; i < nospace.size(); i++){
            int cntForInput = 0;
            int inputLocation = 0;
            if(nospace.at(i) == ','){
                if(cntForInput == 0)        //This is where we check the command, 0 means command input.
                {
                    if(isdigit(nospace.at(inputLocation)))  //if the command is a number that means the input is wrong
                    {
                       errorLine();
                       break;
                    }
                    else if(isalpha(nospace.at(inputLocation))) // if it is a letter we check more
                    {
                        if(nospace.at(inputLocation) == 'D' || nospace.at(inputLocation) == 'd')    //D means we do nothing and proceed to the next input segment
                        {
                            inputLocation = i + 1;
                            cntForInput++;
                        }
                        else if(nospace.at(inputLocation) == 'P' || nospace.at(inputLocation) == 'p')//P we call the function and break the loop so it does not fuck us up
                        {
                            statistic();
                            break;
                        }
                        else if(nospace.at(inputLocation) == 'W' || nospace.at(inputLocation) == 'w')//Same thing applies to W
                        {
                            wait();
                            break;
                        }
                        else            //Any other letter means the input is wrong, and we stop proceeding to the next segment.
                        {
                            errorLine();
                            break;
                        }

                    }
                }
                else if(cntForInput == 1) //when cnt is 1, which means the input is suppose to be the time unit
                {
                    if(isdigit(nospace.at(inputLocation)))  //you check if the input is a number, if it is true
                    {
                        if(timeHead == NULL){               //you check if there exist a time unit already, if there is
                            timeUnit *temp = new timeUnit;  //creating a time unit
                            timeHead = temp;                //points the start of the time unit, does not change until we sort.
                            timePtr = temp;                 //this pointer moves around, gotta keep track of it
                            timePtr -> timeSpace = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());     //set the time space value to the input
                            temp = NULL;
                            delete  temp;               //no memory leak
                            Plane *temp1 = new Plane;   //creating a plane for this input string
                            timePtr -> next = temp1;    //link the time unit to the first plane
                            planePtr = temp1;           //This pointer also moves around, so we need to make sure where it is.
                            temp1 = NULL;
                            delete temp1;               //no memory leak.
                            inputLocation = i + 1;      //Do not forget to go to the next input segment
                            cntForInput++;              //Also, label the next input segment
                        }
                        else
                        {
                            int tempInt = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());  //For convenience, we make a temp for the input.
                            timePtr = timeHead;                                 //Make sure the pointer starts at the beginning of the time list so we can proceed.
                            while((timePtr -> timeSpace) < tempInt)             //Check if the time unit is bigger or equal, if not, move to the next time unit
                            {
                                timePtr = timePtr -> nextTime;
                            }
                            if(timePtr -> timeSpace == tempInt)                 //if the time unit is equal, we don't need to create a new time node
                            {
                                if(timePtr -> next == NULL)                     //However we still need to make sure if there is planes under that time unit, if not
                                {                                               //we create a new plane node
                                    Plane *temp = new Plane;
                                    timePtr -> next = temp;
                                    planePtr = temp;                            //DO NOT FORGET THIS
                                    temp = NULL;
                                    delete temp;
                                }
                                else                                            //if there planes under it already
                                {
                                    while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                                    {                                           //have this way for now
                                        planePtr = planePtr -> nextPlane;
                                    }
                                    Plane *temp = new Plane;
                                    planePtr -> nextPlane = temp;
                                    planePtr = planePtr -> nextPlane;
                                    temp = NULL;                                //No memory leak
                                    delete temp;
                                }

                            }
                            else //if the next time is larger than the time unit we want to add, that means we need to create a new time node
                            {
                                timeUnit *temp = new timeUnit;
                                temp -> nextTime = timePtr;                     //I made the time struct this way because of this kind of situation
                                temp -> prevTime = timePtr -> prevTime;         //where we need to link the new time node to a previous and next time node
                                timePtr -> prevTime = temp;
                                temp -> timeSpace = tempInt;
                                temp = NULL;
                                delete temp;
                                Plane *temp1 = new Plane;                       //Since this is a new time node, we do not need to check if there is planes under
                                timePtr -> next = temp1;
                                planePtr = temp1;
                                temp = NULL;
                                delete temp1;
                            }
                        }
                    }
                    else
                    {
                        errorLine();
                        break;
                    }
                }
            }
        }
    }


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
void GodfatherATC::errorLine(){
    cout << "Your input is wrong." << endl;

}

int main(){
    GodfatherATC Sherloc;
    Sherloc.takingInput();

}
