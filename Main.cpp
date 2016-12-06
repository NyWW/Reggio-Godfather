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
    struct Plane{
        int fuel;
        int currentFuel;
        int people;
        double cargo;
        char dOrA;
        int timeToExecute;
        double totalValue;
        bool grandKid;
        Plane *nextPlane = NULL;
        Plane *prevPlane = NULL;
    };
    struct timeUnit{
        int timeSpace;
        timeUnit *prevTime = NULL;
        timeUnit *nextTime = NULL;
        Plane *next = NULL;
    };

    struct stringArray{
        string inputs;
        stringArray *next = NULL;
    };

    GodfatherATC();
    void data();
    void statistic();
    void wait();
    void takingInput();
    void sorting(timeUnit *ptr1, Plane *ptr);
    void checking();
    bool checkInput(string a);
    void adding();
    void process(timeUnit *ptr1, Plane *ptr);
    void addDelayedPlane(timeUnit *ptrT,Plane *ptr);
    void addToNext(timeUnit *ptrT, Plane *ptr);
    int planeCounter(Plane *ptr);

    Plane *fuelDecrement(timeUnit *ptrT, Plane *ptr);
    Plane *split(Plane *head);
    Plane *mergee(Plane *first, Plane *second);
    Plane *mergeSort(Plane *head);





private:
    stringArray *head;
    stringArray *stringPtr;
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
    int departGC;
    int arriveGC;
    int departGCwait;
    int arriveGcwait;
    int arriveWait;
    int departWait;

    double safeCargo;
    double destroyedCargo;
    double avgGrandKidArrive;
    double avgGrandKidDepart;
    double avgTOWaitTime;
    double avgLDWaitTime;

};
GodfatherATC::GodfatherATC(){
    head = NULL;
    stringPtr = NULL;
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
    departGC = 0;
    arriveGC = 0;
    departGCwait = 0;
    arriveGcwait = 0;
    arriveWait = 0;
    departWait = 0;

    avgGrandKidArrive = 0;
    avgGrandKidDepart = 0;
    avgTOWaitTime = 0;
    avgLDWaitTime = 0;

}
void GodfatherATC::takingInput(){
    ifstream textfile;
    string sample;
    //textfile.open("FP.txt");
    textfile.open("new.txt");
    //textfile.open("AutomatedInput.txt");
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
                stringPtr = head;
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
    //data();
    return;
}
void GodfatherATC::adding(){
    stringPtr = head;
    //int test = 0;
    while(stringPtr != NULL){
        int cntForInput = 0;
        int inputLocation = 0;
        string nospace = "";
        for(int a = 0; a < (stringPtr -> inputs).size(); a++){ // get rid of all the spaces in the input.
            if((stringPtr -> inputs).at(a) != ' '){
                nospace += ((stringPtr -> inputs).at(a));
            }
        }
        nospace.append(",");
        //cout << ++test << endl;
        for(int i = 0; i < nospace.size(); i++)
            {
            if(nospace.at(i) == ','){
                if(cntForInput == 0)        //This is where we check the command, 0 means this part is a command input.
                {
                    if(nospace.at(inputLocation) == 'D')    //D means we do nothing and proceed to the next input segment
                    {
                        inputLocation = i + 1;
                        cntForInput++;
                    }
                    else if(nospace.at(inputLocation) == 'P')//P we call the function and break the loop so it does not fuck us up
                    {
                        statistic();
                        //cout << "printed" << endl;
                        break;
                    }
                    else if(nospace.at(inputLocation) == 'W')//Same thing applies to W
                    {
                        wait();
                        //cout << "waited" << endl;
                        break;
                    }

                }
                else if(cntForInput == 1) //when cnt is 1, which means the input is suppose to be the time unit
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
                        while((timePtr -> timeSpace) < tempInt && timePtr -> nextTime != NULL)             //Check if the time unit is bigger or equal, if not, move to the next time unit
                        {
                            timePtr = timePtr -> nextTime;
                        }
                        if(timePtr -> timeSpace == tempInt)                 //if the time unit is equal, we don't need to create a new time node
                        {
                            planePtr = timePtr -> next;
                            while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                            {                                           //have this way for now
                                planePtr = planePtr -> nextPlane;
                            }
                            if(planePtr ->timeToExecute != tempInt)
                            {
                                sorting(timeHead, timeHead ->next);
                                process(timeHead, timeHead ->next);
                                planePtr = timeHead ->next;
                            }
                            while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                            {                                           //have this way for now
                                planePtr = planePtr -> nextPlane;
                            }
                            Plane *temp = new Plane;
                            planePtr -> nextPlane = temp;
                            temp->prevPlane = planePtr;
                            planePtr = planePtr -> nextPlane;
                            temp = NULL;                                //No memory leak
                            delete temp;
                            planePtr -> timeToExecute = tempInt;
                            inputLocation = i + 1;
                            cntForInput++;
                        }
                        else if(timePtr -> timeSpace < tempInt)
                        {
                            sorting(timeHead, timeHead ->next);
                            process(timeHead, timeHead ->next);
                            planePtr = timeHead -> next;
                            while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                            {                                           //have this way for now
                                planePtr = planePtr -> nextPlane;
                            }
                            Plane *temp = new Plane;
                            planePtr -> nextPlane = temp;
                            temp->prevPlane = planePtr;
                            planePtr = planePtr -> nextPlane;
                            temp = NULL;                                //No memory leak
                            delete temp;
                            planePtr -> timeToExecute = tempInt;
                            inputLocation = i + 1;
                            cntForInput++;
                        }
                        else                                        //if the next time is larger than the time unit we want to add, that means we need to create a new time node
                        {

                            if(timePtr == timeHead){
                                timeUnit *temp = new timeUnit;
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
                                sorting(timeHead, timeHead ->next);
                                process(timeHead, timeHead ->next);

                                planePtr = timeHead -> next;
                                while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
                                {                                           //have this way for now
                                    planePtr = planePtr -> nextPlane;
                                }
                                Plane *temp = new Plane;
                                planePtr -> nextPlane = temp;
                                temp->prevPlane = planePtr;
                                planePtr = planePtr -> nextPlane;
                                temp = NULL;                                //No memory leak
                                delete temp;
                                planePtr -> timeToExecute = tempInt;
                                inputLocation = i + 1;
                                cntForInput++;
                            }
                        }
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
                    planePtr->currentFuel = tempFuel;
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

                    planePtr->totalValue = planePtr->cargo + (planePtr->people*hoomanValue);

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
        stringPtr = stringPtr -> next;
    }

    while(timeHead != NULL)
    {

        sorting(timeHead, timeHead->next);
        process(timeHead, timeHead->next);
        //checking();
    }

    cout << "awasd" << endl;
}

void GodfatherATC::process(timeUnit *ptr1, Plane *ptr){
    Plane *temp1 = ptr;
    Plane *temp2 = ptr-> nextPlane;
    ptr = ptr -> nextPlane -> nextPlane;
    if(ptr == NULL)
    {
        if(ptr1 ->nextTime == NULL)
        {
            timeUnit *lastTemp = timeHead;
            timeHead = NULL;
            delete lastTemp;
        }
        else
        {
            cout << "pass" << endl;
            ptr1 = ptr1 ->nextTime;
        }
    }
    else
    {
        ptr1 ->next = ptr;
        ptr -> prevPlane = NULL;
        temp2 -> nextPlane = NULL;

        numberOfPlanes += 2;
        totalTime = ptr1 -> timeSpace;
        relativeTime = ptr1 -> timeSpace;
        peopleSafeLanded += temp1 -> people;
        peopleSafeLanded += temp2 -> people;
        safeCargo += temp1 -> cargo;
        safeCargo += temp2 -> cargo;

        if(temp1 ->dOrA == 'A')
        {
            planeArrive++;
            arriveWait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
            if(temp1 ->grandKid == true)
            {
                arriveGC++;
                arriveGcwait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
            }
        }
        else
        {
            if(temp1 ->grandKid == true)
            {
                departGC++;
                departGCwait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
            }
            planeDepart++;
            departWait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
        }
        if(temp2 ->dOrA == 'A')
        {
            planeArrive++;
            arriveWait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
            if(temp2 -> grandKid == true)
            {
                arriveGC++;
                arriveGcwait += (ptr1 -> timeSpace) - (temp2 -> timeToExecute);
            }
        }
        else
        {
            if(temp2 ->grandKid == true)
            {
                departGC++;
                departGCwait += (ptr1 -> timeSpace) - (temp2 -> timeToExecute);
            }
            planeDepart++;
            departWait += (ptr1 -> timeSpace) - (temp1 -> timeToExecute);
        }
        //checking();
        fuelDecrement(ptr1,ptr);

        delete temp1;
        delete temp2;
    }
}
int GodfatherATC::planeCounter(Plane *ptr) {
        int indPlane = 0;
        while(ptr != NULL)
        {
            ptr = ptr -> nextPlane;
            indPlane++;
        }
    return indPlane;
}
void GodfatherATC::sorting(timeUnit *ptr1, Plane *ptr)
{
    ptr1 -> next = mergeSort(ptr);

}
void GodfatherATC::wait(){
    avgTOWaitTime = (double)departWait / (double)planeDepart;
    avgLDWaitTime = (double)arriveWait / (double)planeArrive;
    avgGrandKidArrive = (double)arriveGcwait / (double)arriveGC;
    avgGrandKidDepart = (double)departGCwait / (double)departGC;
}
void GodfatherATC::statistic(){
    cout << "Average take off wait time is " << avgTOWaitTime << " time units!"<<endl;
    cout << "Average landing wait time is " << avgLDWaitTime << " time units!"<<endl;
    cout << planeCrash << " planes crashed!" <<endl;
    cout << planeDepart << " planes departed!" <<endl;
    cout << planeArrive << " planes arrived!" <<endl;
    cout << peopleSafeLanded << " people landed safely!" <<endl;
    cout << peopleKilled << " people got killed!" <<endl;
    cout << grandKidKilled << " Grandchildren got killed!" << endl;
    cout << "Average wait time for a grandchild arriving is " << avgGrandKidArrive << " time units!"<<endl;
    cout << "Average wait time for a grandchild departing is " << avgGrandKidDepart << " time units!"<<endl;
    cout << safeCargo << " cargo landed safely!" <<endl;
    cout << destroyedCargo << " cargo got destroyed!" <<endl;
    cout << "Total time is " << totalTime + 1 << " time units!" << endl;

}
void GodfatherATC::data(){
    stringPtr = head;
    while(stringPtr != NULL){
        cout << stringPtr -> inputs << endl;
        stringPtr = stringPtr -> next;
    }
    return;
}
void GodfatherATC::checking(){
    timePtr = timeHead;
    int statsForNow = 1;

    while(timePtr != NULL)
    {
        sorting(timePtr, timePtr->next);
        cout << "At time " << timePtr -> timeSpace << endl;
        planePtr = timePtr -> next;
        while(planePtr != NULL)
        {
            numberOfPlanes++;
            statsForNow++;
            cout << "Plane is " << planePtr->dOrA << ", with fuel = " << planePtr->currentFuel << ", carrying " << planePtr->people << " and " << planePtr->cargo << " cargo with grandkid - ";
            cout << "------" << planePtr ->timeToExecute << endl;
            if(planePtr ->grandKid == true)
            {
                cout << "Yes." << endl;
            }
            else
            {
                cout << "No." << endl;
            }

            planePtr = planePtr -> nextPlane;


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

GodfatherATC::Plane* GodfatherATC::split(Plane *head)
{
    struct Plane *fast = head,*slow = head;
    while (fast -> nextPlane && fast-> nextPlane-> nextPlane)
    {
        fast = fast-> nextPlane -> nextPlane;
        slow = slow-> nextPlane;
    }
    struct Plane *temp = slow-> nextPlane;
    slow-> nextPlane = NULL;
    return temp;

}
GodfatherATC::Plane* GodfatherATC::mergee(Plane *first, Plane *second)
{
        // If first linked list is empty
    if (!first)
        return second;

    // If second linked list is empty
    if (!second)
        return first;

    // Pick the smaller value
    if (first -> fuel  < second -> fuel)
    {
        first -> nextPlane = mergee(first -> nextPlane,second);
        first-> nextPlane -> prevPlane = first;
        first-> prevPlane = NULL;
        return first;
    }
    else if(first -> fuel  == second -> fuel)
    {
        if((first -> grandKid == true && second ->grandKid == false))
        {
            first -> nextPlane = mergee(first -> nextPlane,second);
            first-> nextPlane -> prevPlane = first;
            first-> prevPlane = NULL;
            return first;
        }
        else if((first -> grandKid == true && second ->grandKid == true) || (first -> grandKid == false && second ->grandKid == false))
        {
            if( (first -> dOrA == 'A' && second ->dOrA == 'D'))
            {
                first -> nextPlane = mergee(first -> nextPlane,second);
                first-> nextPlane -> prevPlane = first;
                first-> prevPlane = NULL;
                return first;
            }
            else if((first -> dOrA == 'D' && second ->dOrA == 'D') || (first -> dOrA == 'A' && second ->dOrA == 'A'))
            {

                if(first -> totalValue > second -> totalValue)
                {
                    first -> nextPlane = mergee(first -> nextPlane,second);
                    first-> nextPlane -> prevPlane = first;
                    first-> prevPlane = NULL;
                    return first;
                }
                else
                {
                    second-> nextPlane = mergee(first,second-> nextPlane);
                    second-> nextPlane-> prevPlane = second;
                    second-> prevPlane = NULL;
                    return second;
                }

            }
            else
            {

                second-> nextPlane = mergee(first,second-> nextPlane);
                second-> nextPlane-> prevPlane = second;
                second-> prevPlane = NULL;
                return second;
            }
        }
        else
        {
            second-> nextPlane = mergee(first,second-> nextPlane);
            second-> nextPlane-> prevPlane = second;
            second-> prevPlane = NULL;
            return second;
        }
    }
    else
    {
        second-> nextPlane = mergee(first,second-> nextPlane);
        second-> nextPlane-> prevPlane = second;
        second-> prevPlane = NULL;
        return second;
    }

}
GodfatherATC::Plane* GodfatherATC::mergeSort(Plane *head)
{
    if (!head || !head-> nextPlane)
        return head;
    struct Plane *second = split(head);

    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the two sorted halves
    return mergee(head,second);
}
GodfatherATC::Plane* GodfatherATC::fuelDecrement(timeUnit *ptrT, Plane *ptr)
{
    Plane *through = ptr;
    Plane *headHere = ptr;
    while(through != NULL)
    {
        through -> currentFuel = through ->currentFuel - 1;
        if(through -> currentFuel == 0)
        {
            Plane *temp = through;

            if(temp -> prevPlane == NULL)
            {
                through = through -> nextPlane;
                ptrT ->next = through;
                timeHead ->next = through;
                through -> prevPlane = NULL;
                temp ->nextPlane = NULL;
            }
            else if(temp -> nextPlane == NULL)
            {
                temp -> prevPlane -> nextPlane = NULL;
                through = NULL;
                temp ->prevPlane = NULL;
            }
            else
            {
                through = through ->nextPlane;
                temp -> prevPlane -> nextPlane = temp ->nextPlane;
                temp -> nextPlane -> prevPlane = temp -> prevPlane;
                temp -> prevPlane = NULL;
                temp -> nextPlane = NULL;

            }

            destroyedCargo += temp ->cargo;
            planeCrash++;
            peopleKilled += temp ->people;

            if(temp->grandKid == true)
            {
                grandKidKilled++;
            }
            delete temp;
        }
        else if(through -> currentFuel < 20 && through ->dOrA == 'D')
        {
            Plane *temp = new Plane;
            temp = through;
            if(temp -> prevPlane == NULL)
            {
                through = through -> nextPlane;
                timeHead ->next = through;
                ptrT ->next = through;
                through -> prevPlane = NULL;
                temp ->nextPlane -> prevPlane = NULL;
                temp ->nextPlane = NULL;
            }
            else if(temp -> nextPlane == NULL)
            {
                temp -> prevPlane -> nextPlane = NULL;
                through = NULL;
                temp ->prevPlane = NULL;
            }
            else
            {
                temp -> prevPlane -> nextPlane = temp ->nextPlane;
                temp -> nextPlane -> prevPlane = temp -> prevPlane;
                temp -> prevPlane = NULL;
                temp -> nextPlane = NULL;
                through = through ->prevPlane;
            }

            addDelayedPlane(ptrT,temp);
            temp = NULL;
            delete temp;
        }
        else
        {
            through = through -> nextPlane;
        }
    }
    addToNext(timeHead,timeHead->next);

}
void GodfatherATC::addDelayedPlane(timeUnit *ptrT,Plane *ptr)
{
    timeUnit *temp = timeHead;
    ptr->currentFuel = ptr->fuel;
    int tempInt = ptrT -> timeSpace + 10;
    temp = timeHead;                                 //Make sure the pointer starts at the beginning of the time list so we can proceed.
    while((temp -> timeSpace) < tempInt && temp -> nextTime != NULL)             //Check if the time unit is bigger or equal, if not, move to the next time unit
    {
        //cout << timePtr -> timeSpace << endl;
        temp = temp -> nextTime;

    }

    if(temp -> timeSpace == tempInt)                 //if the time unit is equal, we don't need to create a new time node
    {

        planePtr = temp -> next;
        while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
        {                                           //have this way for now
            planePtr = planePtr -> nextPlane;
        }
        planePtr -> nextPlane = ptr;
        ptr->prevPlane = planePtr;
        planePtr = planePtr -> nextPlane;
    }
    else if(temp -> timeSpace < tempInt)
    {
        timeUnit *tempPl = new timeUnit;
        tempPl -> prevTime = temp;
        temp -> nextTime = tempPl;
        tempPl -> timeSpace = tempInt;
        temp = tempPl;
        tempPl = NULL;
        delete tempPl;
        temp -> next = ptr;
    }
    else                                        //if the next time is larger than the time unit we want to add, that means we need to create a new time node
    {
        timeUnit *tempTi = new timeUnit;
        if(temp == timeHead){
            timeHead = tempTi;
            tempTi -> nextTime = temp;                     //I made the time struct this way because of this kind of situation
            tempTi -> timeSpace = tempInt;
            temp -> prevTime = tempTi;
            temp = tempTi;
            tempTi = NULL;

            delete tempTi;                    //Since this is a new time node, we do not need to check if there is planes under
            temp -> next = ptr;
        }
        else
        {
            tempTi -> nextTime = temp;                     //I made the time struct this way because of this kind of situation
            tempTi -> prevTime = temp -> prevTime;                     //where we need to link the new time node to a previous and next time node
            tempTi -> timeSpace = tempInt;
            temp -> prevTime -> nextTime = tempTi;
            temp -> prevTime = tempTi;
            temp = tempTi;
            tempTi = NULL;
            delete tempTi;
        }
    }

}
void GodfatherATC::addToNext(timeUnit *ptrT, Plane *ptr)
{

    timeUnit *temp;
    int tempInt = ptrT ->timeSpace + 1;
    temp = timeHead;                                 //Make sure the pointer starts at the beginning of the time list so we can proceed.
    while((temp -> timeSpace) < tempInt && temp -> nextTime != NULL)             //Check if the time unit is bigger or equal, if not, move to the next time unit
    {
        temp = temp -> nextTime;
    }

    if(temp -> timeSpace == tempInt)                 //if the time unit is equal, we don't need to create a new time node
    {
        planePtr = temp -> next;
        timeHead = temp;
        timeUnit *tmp = temp ->prevTime;
        tmp ->nextTime = NULL;
        temp ->prevTime = NULL;
        while(planePtr -> nextPlane != NULL)        //we go to the last plane node, however, I am not sure if we compare it as we go, but lets
        {                                           //have this way for now
            planePtr = planePtr -> nextPlane;
        }
        planePtr -> nextPlane = ptr;
        ptr->prevPlane = planePtr;
        planePtr = planePtr -> nextPlane;
        delete tmp;
    }
    else if(temp -> timeSpace < tempInt)
    {
        timeUnit *tempPl = new timeUnit;
        timeUnit *tmp = temp;
        timeHead = tempPl;
        tempPl -> prevTime = NULL;
        temp -> nextTime = NULL;
        tempPl -> timeSpace = tempInt;
        temp = tempPl;
        tempPl = NULL;
        delete tempPl;
        delete tmp;
        temp -> next = ptr;
    }
    else                                        //if the next time is larger than the time unit we want to add, that means we need to create a new time node
    {
        timeUnit *tempTi = new timeUnit;
        if(temp == timeHead){
            timeHead = tempTi;
            tempTi -> nextTime = temp ->nextTime;                     //I made the time struct this way because of this kind of situation
            temp ->nextTime ->prevTime = tempTi;
            tempTi -> timeSpace = tempInt;
            timeUnit *tmp = temp;
            temp = tempTi;
            tempTi = tmp;
            tmp = NULL;
            delete tmp;
            delete tempTi;                    //Since this is a new time node, we do not need to check if there is planes under
            temp -> next = ptr;

        }
        else
        {
            timeHead = tempTi;
            tempTi ->next = ptr;
            timeUnit *tmp = temp ->prevTime;
            tempTi -> nextTime = temp;                     //I made the time struct this way because of this kind of situation
            tempTi -> timeSpace = tempInt;
            temp -> prevTime -> nextTime = NULL;
            temp -> prevTime = tempTi;
            temp = tempTi;
            tempTi = NULL;
            delete tmp;
            delete tempTi;
        }
    }
    temp = NULL;
    delete temp;

}
int main(){
    GodfatherATC Sherloc;
    Sherloc.takingInput();
    Sherloc.adding();
    //Sherloc.checking();


}
