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
#include <sstream>

using namespace std;

class Generator{
public:
    double fRand(double fMin, double fMax);
    void outputToText();
    int fInt(int iMax);
    int timeUnit();
    string cRand(int label);
    int ti = 0;
    int fFuel(int a);
};
int Generator::fFuel(int a){

    int f = rand()%(a + 1) + 20;
    return f;


}
int Generator::timeUnit()
{
    int t = rand()% 10 + 1;
    if(t == 1)
    {
        ti++;
        return ti;
    }
    else
    {
        return ti;
    }
}
double Generator::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
void Generator::outputToText()
{
    int amt_of_inputs;
    int maxPeople;
    int maxTime;
    int maxFuel;
    double maxCargo;


    ofstream textfile;
    textfile.open("AutomatedInput.txt");
    if(textfile.fail()){
        cerr << "Error Opening File!" << endl;
        exit(1);
    }
    cout << "How many inputs do you want to make?" << endl;
    cin >> amt_of_inputs;
    cout << "What is the maximum time units do you want to have?" << endl;
    cin >> maxTime;
    cout << "What is the maximum capacity for fuel in one plane?" << endl;
    cin >> maxFuel;
    cout << "What is the maximum capacity for people in one plane?" << endl;
    cin  >> maxPeople;
    cout << "What is the maximum capacity for cargo in one plane?" << endl;
    cin >> maxCargo;

    for(int i = 0; i < amt_of_inputs; i++)
    {
        int cntForOneInput = 0;
        string tempSample = "";
        string tempChar;
        bool breakTheLoop = true;
        while(breakTheLoop)
        {
            if(cntForOneInput == 0)
            {
                tempChar = cRand(1);
                if(tempChar == "P" || tempChar == "W")
                {
                    tempSample.append(tempChar);
                    breakTheLoop = false;
                }
                else
                {
                    tempSample.append(tempChar);
                    cntForOneInput++;
                }


            }
            else if(cntForOneInput == 1)
            {
                tempSample.append(",");
                int a = timeUnit();
                stringstream ss;
                ss << a;
                tempSample.append(ss.str());
                cntForOneInput++;
            }
            else if(cntForOneInput == 2)
            {
                tempSample.append(",");
                tempChar = cRand(2);
                tempSample.append(tempChar);
                cntForOneInput++;
            }
            else if(cntForOneInput == 3)
            {
                tempSample.append(",");
                int ab;
                if(tempChar == "D")
                {
                    ab = fFuel(maxFuel);
                }
                else
                {
                    ab = fInt(maxFuel);
                }
                stringstream ss;
                ss << ab;
                tempSample.append(ss.str());
                cntForOneInput++;
            }
            else if(cntForOneInput == 4)
            {
                tempSample.append(",");
                int abc = fInt(maxPeople);
                stringstream ss;
                ss << abc;
                tempSample.append(ss.str());
                cntForOneInput++;
            }
            else if(cntForOneInput == 5)
            {
                tempSample.append(",");
                double x = fRand(0,maxCargo);
                stringstream ss;
                ss << x;
                tempSample.append(ss.str());
                cntForOneInput++;
            }
            else if(cntForOneInput == 6)
            {
                tempSample.append(",");
                tempChar = cRand(3);
                tempSample.append(tempChar);
                cntForOneInput++;
            }
            else if(cntForOneInput > 6)
            {
                breakTheLoop = false;
            }
        }

        textfile << tempSample << endl;

    }
    textfile.close();


}
int Generator::fInt(int iMax)
{
    int f = rand()%(iMax + 1);
    return f;

}
string Generator::cRand(int label){
    string c;
    int a;
    if(label == 1)
    {
        return "D";
    }
    else if(label == 2)
    {
        a = rand()% 2 + 1;
        if(a == 1)
        {
            return "D";
        }
        else if(a == 2)
        {
            return "A";
        }
    }
    else if(label == 3)
    {
        a = rand()% 2 + 1;
        if(a == 1)
        {
            return "Y";
        }
        else if(a == 2)
        {
            return "N";
        }
    }
    return c;
}



int main(){
    srand(time(NULL));

    Generator screwThemUp;
    screwThemUp.outputToText();

}
