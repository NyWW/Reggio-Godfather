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
    string cRand(int label);
};
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
                tempSample.append(tempChar);
                cntForOneInput++;
            }
            else if(cntForOneInput == 1)
            {
                tempSample.append(",");
                int a = fInt(maxTime);
                stringstream ss;
                ss << a;
                tempSample.append(ss.str());
                int b = rand()% 30 + 1;
                if(b == 1)
                {
                    tempSample.append(".05");
                }
                else if(b == 2)
                {
                    tempSample.append("R.");
                }
                else
                {

                }
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
                int ab = fInt(maxFuel);
                stringstream ss;
                ss << ab;
                tempSample.append(ss.str());
                int bc = rand()% 30 + 1;
                if(bc == 1)
                {
                    tempSample.append(".05");
                }
                else if(bc == 2)
                {
                    tempSample.append("R.");
                }
                else
                {

                }
                cntForOneInput++;
            }
            else if(cntForOneInput == 4)
            {
                tempSample.append(",");
                int abc = fInt(maxPeople);
                stringstream ss;
                ss << abc;
                tempSample.append(ss.str());
                int bcd = rand()% 30 + 1;
                if(bcd == 1)
                {
                    tempSample.append(".05");
                }
                else if(bcd == 2)
                {
                    tempSample.append("R.");
                }
                else
                {

                }
                cntForOneInput++;
            }
            else if(cntForOneInput == 5)
            {
                tempSample.append(",");
                double x = fRand(0,maxCargo);
                stringstream ss;
                ss << x;
                tempSample.append(ss.str());
                int y = rand()% 30 + 1;
                if(y == 1)
                {
                    tempSample.append(".05");
                }
                else if(y == 2)
                {
                    tempSample.append("R.");
                }
                else
                {

                }
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
                int z = rand()% 30 + 1;
                if(z == 1)
                {
                    tempSample.append("//");
                }
                else
                {

                }
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
        a = rand()% 8 + 1;
        if(a == 1)
        {
            return "d ";
        }
        else if(a == 2)
        {
            return "p ";
        }
        else if (a == 3)
        {
            return "w ";
        }
        else if(a == 4)
        {
            return "D";
        }
        else if(a == 5)
        {
            return "P";
        }
        else if (a == 6)
        {
            return "W ";
        }
        else if(a == 7)
        {
            return "*";
        }
        else
        {
            return "r ";
        }
    }
    else if(label == 2)
    {
        a = rand()% 6 + 1;
        if(a == 1)
        {
            return "d ";
        }
        else if(a == 2)
        {
            return "a ";
        }
        else if(a == 3)
        {
            return "D";
        }
        else if(a == 4)
        {
            return "A";
        }
        else if(a == 5)
        {
            return "*";
        }
        else
        {
            return "r ";
        }
    }
    else if(label == 3)
    {
        a = rand()% 6 + 1;
        if(a == 1)
        {
            return "y ";
        }
        else if(a == 2)
        {
            return "n ";
        }
        else if(a == 3)
        {
            return "Y ";
        }
        else if(a == 4)
        {
            return "N ";
        }
        else if(a == 5)
        {
            return "*";
        }
        else
        {
            return "r ";
        }
    }
    return c;
}



int main(){
    srand(time(NULL));

    Generator screwThemUp;
    screwThemUp.outputToText();

}
