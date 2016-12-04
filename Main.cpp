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
    void checking();
    bool checkInput(string a);
    void adding();
    
    
    struct stringArray{
        string inputs;
        stringArray *next = NULL;
    };
    
    struct Plane{
        int fuel;
        int people;
        double cargo;
        char dOrA;
        int timeToExecute; //time planned for departure
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
    //textfile.open("FP.txt");
    //textfile.open("TS.txt");
    textfile.open("AutomatedInput.txt");
    if(textfile.fail()){
        cerr << "Error Opening File!" << endl;
        exit(1);
    }
    while(!textfile.eof()){
        getline(textfile, sample);
        bool wrongInput = false;
        string nospace = "";
        for(int a = 0; a < sample.size(); a++){ // get rid of all the spaces in the input.
            if((sample).at(a) != ' '){
                
                nospace += toupper(((sample).at(a)));
            }
        }
        sample = nospace;
        nospace = nospace.append(",");
        /*textfile >> sample;
         cout << sample << endl;
         result += sample;
         result.append(" ");
         */
        wrongInput = checkInput(nospace);
        if(wrongInput == false)
        {
            stringArray *temp = new stringArray;
            temp -> inputs = sample;
            if(head == NULL){
                head = temp;
                ptr = head;
                last = head;
            }
            else{
                last -> next = temp;
                last  = temp;
            }
            temp = NULL;
            delete temp;
        }
        else
        {
            cout << "Input '" << sample << "' is a wrong input, thus it is skipped." << endl;
        }
        
    }
    textfile.close();
    data();
    return;
}
void GodfatherATC::adding(){
    ptr = head;
    //int test = 0;
    while(ptr != NULL){
        int cntForInput = 0;
        int inputLocation = 0;
        string nospace = "";
        for(int a = 0; a < (ptr -> inputs).size(); a++){ // get rid of all the spaces in the input.
            if((ptr -> inputs).at(a) != ' '){
                nospace += ((ptr -> inputs).at(a));
            }
        }
        nospace.append(",");
        //cout << ++test << endl;
        for(int i = 0; i < nospace.size(); i++){
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
                            cout << "printed" << endl;
                            break;
                        }
                        else if(nospace.at(inputLocation) == 'W' || nospace.at(inputLocation) == 'w')//Same thing applies to W
                        {
                            wait();
                            cout << "waited" << endl;
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
                        int tempInt = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());  //For convenience, we make a temp for the input.
                        //cout << tempInt << "right now" << endl;
                        if(timeHead == NULL){               //you check if there exist a time unit already, if there is
                            timeUnit *temp = new timeUnit;  //creating a time unit
                            timeHead = temp;                //points the start of the time unit, does not change until we sort.
                            timePtr = temp;                 //this pointer moves around, gotta keep track of it
                            timePtr -> timeSpace = tempInt;     //set the time space value to the input
                            temp = NULL;
                            delete  temp;               //no memory leak
                            Plane *temp1 = new Plane;   //creating a plane for this input string
                            timePtr -> next = temp1;    //link the time unit to the first plane
                            planePtr = temp1;           //This pointer also moves around, so we need to make sure where it is.
                            temp1 = NULL;
                            delete temp1;               //no memory leak.
                            planePtr -> timeToExecute = tempInt;
                            inputLocation = i + 1;      //Do not forget to go to the next input segment
                            cntForInput++;              //Also, label the next input segment
                            //cout <<"------------------" << endl;
                        }
                        else
                        {
                            
                            
                            timePtr = timeHead;                                 //Make sure the pointer starts at the beginning of the time list so we can proceed.
                            //cout << timeHead ->timeSpace << endl;
                            while((timePtr -> timeSpace) < tempInt && timePtr -> nextTime != NULL)             //Check if the time unit is bigger or equal, if not, move to the next time unit
                            {
                                //cout << timePtr -> timeSpace << endl;
                                timePtr = timePtr -> nextTime;
                                
                            }
                            
                            if(timePtr -> timeSpace == tempInt)                 //if the time unit is equal, we don't need to create a new time node
                            {
                                
                                planePtr = timePtr -> next;
                                while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                                {                                           //have this way for now
                                    planePtr = planePtr -> nextPlane;
                                }
                                Plane *temp = new Plane;
                                planePtr -> nextPlane = temp;
                                planePtr = planePtr -> nextPlane;
                                temp = NULL;                                //No memory leak
                                delete temp;
                                planePtr -> timeToExecute = tempInt;
                                inputLocation = i + 1;
                                cntForInput++;
                            }
                            else if(timePtr -> timeSpace < tempInt)
                            {
                                timeUnit *temp = new timeUnit;
                                
                                temp -> prevTime = timePtr;
                                timePtr -> nextTime = temp;
                                temp -> timeSpace = tempInt;
                                timePtr = temp;
                                temp = NULL;
                                delete temp;
                                Plane *temp1 = new Plane;                       //Since this is a new time node, we do not need to check if there is planes under
                                timePtr -> next = temp1;
                                planePtr = temp1;
                                temp1 = NULL;
                                delete temp1;
                                planePtr -> timeToExecute = tempInt;
                                
                                inputLocation = i + 1;
                                cntForInput++;
                                
                            }
                            else //if the next time is larger than the time unit we want to add, that means we need to create a new time node
                            {
                                
                                //cout << tempInt << endl;
                                //cout << timePtr -> timeSpace << endl;
                                //cout << timeHead -> timeSpace << endl;
                                //cout << timePtr ->prevTime ->timeSpace << endl;
                                timeUnit *temp = new timeUnit;
                                if(timePtr == timeHead){
                                    timeHead = temp;
                                    temp -> nextTime = timePtr;                     //I made the time struct this way because of this kind of situation
                                    temp -> timeSpace = tempInt;
                                    timePtr -> prevTime = temp;
                                    timePtr = temp;
                                    temp = NULL;
                                    delete temp;
                                    Plane *temp1 = new Plane;                       //Since this is a new time node, we do not need to check if there is planes under
                                    timePtr -> next = temp1;
                                    planePtr = temp1;
                                    temp1 = NULL;
                                    delete temp1;
                                    planePtr -> timeToExecute = tempInt;
                                    inputLocation = i + 1;
                                    cntForInput++;
                                }
                                else
                                {
                                    temp -> nextTime = timePtr;                     //I made the time struct this way because of this kind of situation
                                    temp -> prevTime = timePtr -> prevTime;                     //where we need to link the new time node to a previous and next time node
                                    temp -> timeSpace = tempInt;
                                    timePtr -> prevTime -> nextTime = temp;
                                    timePtr -> prevTime = temp;
                                    timePtr = temp;
                                    temp = NULL;
                                    delete temp;
                                    Plane *temp1 = new Plane;                       //Since this is a new time node, we do not need to check if there is planes under
                                    timePtr -> next = temp1;
                                    planePtr = temp1;
                                    temp1 = NULL;
                                    delete temp1;
                                    planePtr -> timeToExecute = tempInt;
                                    inputLocation = i + 1;
                                    cntForInput++;
                                }
                            }
                        }
                    }
                    
                    else
                    {
                        errorLine();
                        break;
                    }
                }
                else if(cntForInput == 2)
                {
                    if(nospace.at(inputLocation) == 'D')
                        planePtr->dOrA = 'D';
                    else
                        planePtr->dOrA = 'A';
                    
                    inputLocation = i + 1;
                    cntForInput++;
                }
                else if(cntForInput == 3)
                {
                    int tempFuel = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());
                    planePtr->fuel =tempFuel;
                    
                    
                    inputLocation = i + 1;
                    cntForInput++;
                    
                }
                else if(cntForInput == 4)
                {
                    int tempPeople = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());
                    planePtr->people = tempPeople;
                    
                    inputLocation = i + 1;
                    cntForInput++;
                    
                }
                else if(cntForInput == 5)
                {
                    double tempCargo = atof(nospace.substr(inputLocation,(i - inputLocation)).c_str());
                    planePtr->cargo = tempCargo;
                    
                    inputLocation = i + 1;
                    cntForInput++;
                    
                }
                else if(cntForInput == 6)
                {
                    if(nospace.at(inputLocation) == 'Y')
                        planePtr->grandKid = true;
                    else
                        planePtr->grandKid = false;
                    
                    inputLocation = i + 1;
                    cntForInput++;
                }
                else
                {
                    inputLocation = i + 1;
                    cntForInput++;
                }
            }
        }
        
        
        ptr = ptr -> next;
    }
    
}
timeUnit GodfatherATC::sorting(timeUnit* timeHeader){//sorts 1 y-axis 
    
}

void GodfatherATC::wait(timeUnit* timeHeader){//handles departures, arrivals in one time unit
    if (planeCounter(timeHeader) == 1) //only 1 plane specified for time slot, allows it to depart/arrive, moves to next
    {
        if (timeHeader.nextPlane->dOrA == 'd' || timeHeader.nextPlane->dOrA == 'D')
        {
            cout << "Plane departing from runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        else if(timeHeader.nextPlane->dOrA == 'a' || timeHeader.nextPlane->dOrA == 'A')
        {
            cout << "Plane arriving to runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        
        //requires deletion to be included, documentation of the values 
    }
    else if (planeCounter(timeHeader) == 2)
    {
        if (timeHeader.nextPlane->dOrA == 'd' || timeHeader.nextPlane->dOrA == 'D')
        {
            cout << "Plane departing from runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        else if(timeHeader.nextPlane->dOrA == 'a' || timeHeader.nextPlane->dOrA == 'A')
        {
            cout << "Plane arriving to runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        
        Plane* secondPlaneSlot = timeHeader.nextPlane->next; //accepts/sends the planes at the second runway
        
        if (secondPlaneSlot -> dOrA == 'a' || secondPlaneSlot->dOrA == 'A')
        {
            cout << "Plane arriving to runway 2 at time: " << timeHeader.timeSpace << "\n";
        }
        else if (secondPlaneSlot -> dOrA == 'd' || secondPlaneSlot->dOrA == 'D')
        {
            cout << "Plane departing from runway 2 at time: " << timeHeader.timeSpace << "\n";
        }
       
        //requires deletion to be included, documentation of the values 
    }
    else if (planeCounter(timeHeader) > 2)
    {
        sorting(timeHeader); //sorts based on criteria set by designers, falls through list sending items, eventually transferring overflow
                            //to the next time slot
        if (timeHeader.nextPlane->dOrA == 'd' || timeHeader.nextPlane->dOrA == 'D')
        {
            cout << "Plane departing from runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        else if(timeHeader.nextPlane->dOrA == 'a' || timeHeader.nextPlane->dOrA == 'A')
        {
            cout << "Plane arriving to runway 1 at time: " << timeHeader.timeSpace << "\n";
        }
        
        Plane* secondPlaneSlot = timeHeader.nextPlane->next; //accepts/sends the planes at the second runway
        
        if (secondPlaneSlot -> dOrA == 'a' || secondPlaneSlot->dOrA == 'A')
        {
            cout << "Plane arriving to runway 2 at time: " << timeHeader.timeSpace << "\n";
        }
        else if (secondPlaneSlot -> dOrA == 'd' || secondPlaneSlot->dOrA == 'D')
        {
            cout << "Plane departing from runway 2 at time: " << timeHeader.timeSpace << "\n";
        }
        
        //delete both of the previous, link the following 
        
        Plane* tempSlot = secondPlaneSlot->nextPlane;
        
        while (tempSlot != NULL)
        {
            --tempSlot.fuel; //decrements fuel of plane that is being shifted to next slot
            shiftToNext(tempSlot, timeHeader); //appends to end of next time unit's list
            
            tempSlot = tempSlot->nextPlane; //begins process with next in line
        }
        
        //all overflow traffic into next time slot has gas decrememnted, otherwise, no change
    }    
}

void GodfatherATC::statistic()
{
    
}
        
void GodfatherATC::shiftToNext(Plane* planeToShift, timeUnit* timeSlot)
{ 
    timeUnit* nextTime = timeSlot.next;
    
    Plane* endOfNextSlot = walkToEnd(nextTime->nextPlane);
    
    endOfNextSlot->nextPlane = planeToShift;
    planeToShift->previousPlane = endOfNextSlot;
    
}

Plane* GodfatherATC::walkToEnd(Plane* currentPlane)
{
    if currentPlane == NULL)
    {
        return currentPlane;
    }
    else 
    {
        return walkToEnd(currentPlane->next);
    }
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
void GodfatherATC::checking(){
    timePtr = timeHead;
    //cout << timeHead -> timeSpace << endl;
    int statsForNow = 1;
    while(timePtr != NULL)
    {
        cout << "At time " << timePtr -> timeSpace << endl;
        //cout << timePtr ->timeSpace << " unit"<< endl;
        planePtr = timePtr -> next;
        while(planePtr != NULL)
        {
            //cout << statsForNow << endl;
            statsForNow++;
            cout << "Plane is " << planePtr->dOrA << ", with fuel = " << planePtr->fuel << ", carrying " << planePtr->people << " and " << planePtr->cargo << " cargo with grandkid - " << planePtr->grandKid << endl;
            planePtr = planePtr -> nextPlane;
            cout<<"######################################"<<endl;
            cout<<"#               _                    #"<<endl;
            cout<<"#             -=\\`\\                  #"<<endl;
            cout<<"#         |\\ ____\\_\\___              #"<<endl;
            cout<<"#       -=\\c` ''''''''' `)           #"<<endl;
            cout<<"#          `~~~~~/ /~~`            #"<<endl;
            cout<<"#            -==/ /                  #"<<endl;
            cout<<"#              '-'                   #"<<endl;
            cout<<"######################################"<<endl;
        }
        
        timePtr = timePtr -> nextTime;
    }
    
    
}
bool GodfatherATC::checkInput(string a){
    int cntForInput = 0;
    int inputLocation = 0;
    bool tempBool = false;
    for(int i = 0; i < a.size(); i++){
        if(a.at(i) == ',')
        {
            if(cntForInput == 0)
            {
                if(i != 1)
                {
                    //cout << i << endl;
                    tempBool = true;
                }
                if(a.at(inputLocation) == 'D' || a.at(inputLocation) == 'P' || a.at(inputLocation) == 'W')
                {
                    if(a.size() > 2 && a.at(inputLocation) != 'D')
                    {
                        tempBool = true;
                    }
                    cntForInput++;
                    inputLocation = i + 1;
                }
                else
                {
                    
                    tempBool = true;
                }
                
            }
            else if(cntForInput == 1)
            {
                string tTime = "";
                //cout << a << endl;
                //cout << inputLocation << " " << i << endl;
                
                tTime = a.substr(inputLocation, i - inputLocation);
                //cout << tTime << endl;
                for(int x = 0; x < tTime.size(); x++)
                {
                    if(!isdigit(tTime.at(x)))
                    {
                        tempBool = true;
                    }
                }
                cntForInput++;
                inputLocation = i + 1;
            }
            else if(cntForInput == 2)
            {
                if(i != inputLocation + 1)
                {
                    //cout << i << endl;
                    tempBool = true;
                }
                if(a.at(inputLocation) == 'D' || a.at(inputLocation) == 'A')
                {
                    cntForInput++;
                    inputLocation = i + 1;
                }
                else
                {
                    
                    tempBool = true;
                }
                
            }
            else if(cntForInput == 3)
            {
                string tFuel = "";
                //cout << a << endl;
                //cout << inputLocation << " " << i << endl;
                
                tFuel = a.substr(inputLocation, i - inputLocation);
                //cout << tFuel << endl;
                for(int y = 0; y < tFuel.size(); y++)
                {
                    if(!isdigit(tFuel.at(y)))
                    {
                        tempBool = true;
                    }
                }
                cntForInput++;
                inputLocation = i + 1;
                
            }
            else if(cntForInput == 4)
            {
                string tPeople = "";
                //cout << a << endl;
                //cout << inputLocation << " " << i << endl;
                
                tPeople = a.substr(inputLocation, i - inputLocation);
                //cout << tPeople << endl;
                for(int y = 0; y < tPeople.size(); y++)
                {
                    if(!isdigit(tPeople.at(y)))
                    {
                        tempBool = true;
                    }
                }
                cntForInput++;
                inputLocation = i + 1;
                
            }
            else if(cntForInput == 5)
            {
                string tCargo = "";
                int pCounter = 0;
                //cout << a << endl;
                //cout << inputLocation << " " << i << endl;
                
                tCargo = a.substr(inputLocation, i - inputLocation);
                //cout << tCargo << endl;
                for(int y = 0; y < tCargo.size(); y++)
                {
                    if(!isdigit(tCargo.at(y)))
                    {
                        if(tCargo.at(y) != '.')
                        {
                            tempBool = true;
                        }
                        else
                        {
                            pCounter++;
                        }
                    }
                }
                if(pCounter > 1)
                {
                    tempBool = true;
                }
                else
                {
                    cntForInput++;
                    inputLocation = i + 1;
                }
                
            }
            else if(cntForInput == 6)
            {
                if(i != inputLocation + 1)
                {
                    //cout << i << endl;
                    tempBool = true;
                }
                if(a.at(inputLocation) == 'N' || a.at(inputLocation) == 'Y')
                {
                    cntForInput++;
                    inputLocation = i + 1;
                }
                else
                {
                    
                    tempBool = true;
                }
            }
            else if(cntForInput > 6)
            {
                tempBool = true;
            }
        }
    }
    return tempBool;
}

int main(){
    GodfatherATC Sherloc;
    Sherloc.takingInput();
    Sherloc.adding();
    Sherloc.checking();
}

