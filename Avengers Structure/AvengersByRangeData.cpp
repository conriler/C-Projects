/* Name: (Jaskaran Chawla)
Date: (4/10/2022) Section:
Module 11:
Section: 0006
Assignment: (Assignment#11)
Due Date: (4/11/2022)
About this project: (import and export from a file while prooving ability to use structures)
Assumptions: ()
 All work below was performed by (Jaskaran Chawla) */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <iomanip>

//Define both the range structure and a structure to store the attributes of said structure
using namespace std;
struct range{
    int Lowest = 0;
    int secondLowst = 0;
    int middle = 0;
    int thirdHighest = 0;
    int secondHighest = 0;
    int highest = 0;
};
struct genderDeath{
    int male = 0;
    double female =0;
    int dead = 0;
    int alive = 0;
    double totalIn = 0;            //total amount of avengers in each category
};

void DefineArrays(string [], string [], string [], int []);
void DeadAvengersName(string [], string [], vector<int> &deadIndex);
void DeadAvengerVectorSet(string [], vector<int> &deadIndex);
void AliveAvengerByGender(string avengerGender[], string avengerDeath[], int numAppearances[]);
void RangeArrayDefine(int [], range [], string [], string [], genderDeath[]);
void CheckGender(string [], int , genderDeath &, string []);
void PrintHighestDead(genderDeath [], range [], string []);
const int NUM_AVENGERS =173;//Setting array sizes
void DisplayRange(genderDeath check[]);
void PrintHighestDead(genderDeath [], range [], string []);
void FemaleFinder(genderDeath [], range [], string []);
void DisplayRange(genderDeath check[], string rangeNames[]);

int main()
{
    cout << "Welcome to the Avengers program!" <<endl;
    ifstream avengersData;
    range valueR[NUM_AVENGERS];
    range array;
    vector<int> deadIndex;//Defining vectors
    string rangeNames[6] = {"<=750", "> 750 and <=1500", "> 1500 and <=2250",  "> 2250 and <=3000", "> 3000 and <=3750",
              "> 3750 and <=4500"};              //For when it is necesarry to output the range titles
    string avengersNames[NUM_AVENGERS];              //
    string avengerGender[NUM_AVENGERS];
    string avengerDeath[NUM_AVENGERS];
    int numAppearances[NUM_AVENGERS];                //Creating string and int arrays
    genderDeath check[6];                            //One index per range
    DefineArrays(avengersNames, avengerGender, avengerDeath, numAppearances);        //Defining all arrays from output file
    RangeArrayDefine(numAppearances, valueR, avengerGender, avengerDeath, check);    //define the structure array
    char userProgramOption;          //Define variables
    char userInput;
    while (userProgramOption != 'Z')
    {
        cout << "A) Display Data \n";
        cout << "B) Find Range with the largest number of Avengers who have died\n";
        cout << "C) Find Range with the largest percentage of Avengers who are female\n";
        cout << "D) Quit" <<endl;
        cout << "Select an option (A-D)..";
        cin >> userInput;
        userProgramOption = toupper(userInput);          //Allows user to enter the lowercase
        if (userProgramOption == 'A')
        {
            DisplayRange(check, rangeNames);                            //Runs the display function
            userProgramOption = 'V';
        }
        else if (userProgramOption == 'B')
        {
            PrintHighestDead(check, valueR, rangeNames);    //
            userProgramOption = 'V';
        }
        else if (userProgramOption == 'C')
        {
            FemaleFinder(check, valueR, rangeNames);
            userProgramOption = 'V';
        }
        else if(userProgramOption == 'D')
        {
            cout << "Thanks for using!" <<endl;
            userProgramOption = 'Z';
        }
        else
            cout << "Please select a vaild input" <<endl;
    }


    /*                                                               //Runs an alternative program
        {
        DeadAvengersName(avengersNames,avengerDeath, deadIndex);
    }
    else if(toupper(userProgramOption) == 'B')      //Allows user to enter the lowercase
    {
         cout <<"Display count of Avengers who have never Died by gender..."<<endl;
         AliveAvengerByGender(avengerGender, avengerDeath, numAppearances);
    }
    else
    cout<<"Invalid option entered"<<endl;
        */
    return 0;
}

void DefineArrays(string avengersNames[], string avengerGender[], string avengerDeath[], int numAppearances[])
{
    ifstream dataFile;
    dataFile.open("AvengersData.txt");        //Connects program to file
    if(dataFile)
    {

       string names,app,gender,death;           //gets all the colums name
       int index = 0;
       while (dataFile >>names>>app>>gender>>death)
       {
           avengersNames[index] = names;             //Define arrays
           numAppearances[index] = stoi(app);
           avengerGender[index] = gender;
           avengerDeath[index] = death;
           index++;
       }

    }
    dataFile.close();  //closes access to datafile

}
void DeadAvengersName(string avengersNames[], string avengerDeath[], vector<int> &deadIndex)
{   freopen( "OutputA.txt", "w", stdout );     //Redirects output to OutputA.txt
    ofstream outputFile;      //creates object
    //outputFile.open("OutputA.txt");
    DeadAvengerVectorSet(avengerDeath, deadIndex);
    cout<<"Display name and count of Avengers who have died at least once "<<endl;
    //outputFile <<"Display name and count of Avengers who have died at least once "<<endl;
    cout<<"The following Avengers have died at least once .... " <<endl;
    //outputFile <<"The following Avengers have died at least once .... "<<endl;

    for(int i =0; i < deadIndex.size(); i++)
    {
        cout <<avengersNames[(deadIndex.at(i))]<<endl;             //Output values in the dead index vector
        //outputFile <<avengersNames[(deadIndex.at(i))]<<endl;
    }
    double numberOfDead = deadIndex.size();
    double percent = (numberOfDead/NUM_AVENGERS* 100);
    cout<<"The number of Avengers have died at least once = " << deadIndex.size() <<endl;
    cout<<"The percentage of Avengers have died at least once " << percent <<endl;
    //outputFile <<"The number of Avengers have died at least once = " << deadIndex.size() <<endl;
    //outputFile <<"The percentage of Avengers have died at least once " << percent <<endl;

}

void DeadAvengerVectorSet(string avengerDeath[], vector<int> &deadIndex)
{
    double amountOfDead = 0;
    for(int i = 0; i < NUM_AVENGERS; i++)
    {
        if(avengerDeath[i] == "YES")
        {
            deadIndex.push_back(i);        //Push a new dead into the vector
        }
    }

}
void AliveAvengerByGender(string avengerGender[], string avengerDeath[], int numAppearances[])
{
    //ofstream outputFile;
    //freopen( "OutputB.txt", "w", stdout );          //Redirects test to output B
    cout <<"Display count of Avengers who have never Died by gender..."<<endl;
    double appAverageM =0, appAverageF=0, numOfMen = 0, numOfWo;
    for(int i = 0; i < NUM_AVENGERS; i++)
    {
        if(avengerDeath[i] == "NO" && avengerGender[i] == "MALE")
        {
            appAverageM += numAppearances[i];      //Ads to the average
            numOfMen++;
        }
        else if(avengerDeath[i] == "NO" && avengerGender[i] == "FEMALE")
        {
            appAverageF += numAppearances[i];      //Ads to the average
            numOfWo++;
        }


    }
    cout <<"The average number of appearances of Avengers who have never Died " <<endl;   //Writes appearances and all
    cout << "male  = " <<(appAverageM/numOfMen)<<endl;
    cout << appAverageF << " " << numOfWo <<endl;
    cout << "Female =" <<(appAverageF/numOfWo) <<endl;

}

void RangeArrayDefine(int numAppearances[], range valueR[], string avengerGender[], string avengerDeath[],
                      genderDeath check[])
{
    ifstream avFile;
    avFile.open("AvengersData.txt");

    if(avFile)
    {   int i= 0;
        string names, app, d, u;        //creates necessary conditions
        while(avFile  >>names>>app>>d>>u)    //loops through all the required vars
        {

            if(stoi(app) <= 750)
            {
                valueR[i].Lowest++;     //Adds to the respective variables
                CheckGender(avengerGender, i, check[0], avengerDeath);
                check[0].totalIn++;     //Adds to total amount for the range

            }
            else if(stoi(app) >750 && stoi(app) <= 1500)
            {
                valueR[i].secondLowst++;
                CheckGender(avengerGender, i, check[1], avengerDeath);
                check[1].totalIn++;
            }
            else if(stoi(app) >1500 && stoi(app) <= 2250)
            {
                valueR[i].middle++;
                CheckGender(avengerGender, i, check[2], avengerDeath);
                check[2].totalIn++;
            }
            else if(stoi(app) >2250 && stoi(app) <= 3000)
            {
                valueR[i].thirdHighest++;
                CheckGender(avengerGender, i, check[3], avengerDeath);
                check[3].totalIn++;

            }
            else if(stoi(app) >3000 && stoi(app) <= 3750)
            {
                valueR[i].secondHighest++;
                CheckGender(avengerGender, i, check[4], avengerDeath);
                check[4].totalIn++;

            }
            else if(stoi(app) >3750 && stoi(app) <= 4500)
            {
                valueR[i].highest++;
                CheckGender(avengerGender, i, check[5], avengerDeath);
                check[5].totalIn++;

            }
             i++;
        }

    }
            avFile.close();
    }


void CheckGender(string avengerGender[], int i, genderDeath & toCheck, string avengerDeath[])
{
    if (avengerGender[i] == "MALE")    //If male add to male
        toCheck.male++;
    else
        toCheck.female++;


    if (avengerDeath[i] == "YES")      //id dead add to dead
        toCheck.dead++;
    else
        toCheck.alive++;
 }

 void DisplayRange(genderDeath check[], string rangeNames[])
 {
     cout <<setw(17)<<"Range" <<  setw(15) << right << "Num Females" << setw(15) << right << "Num Males"<<
          setw(15) <<right << "Num Died Once"  << setw(15) << right << "Num Never Died Once"<<endl;   //first row
    string rangeSelector = "<=750";
    for(int i = 0;i <= 5 ;i++)
    {

        cout <<setw(17)<<rangeNames[i] <<  setw(15) << right << check[i].female << setw(15) << right << check[i].male<<
        setw(18) <<right << check[i].dead << setw(16) << right << check[i].alive<<endl;
                    //Puts down the rest of the range using the array

    }

 }

void PrintHighestDead(genderDeath check[], range valueR[], string rangeNames[])
{
    int max = check[0].dead;        //sets the max to zero
    int maxIndex = 0;
    for(int i= 1;i < 6;i++)
    {
        if(check[(i)].dead > max)   //Replaces value if check is less then max
        {
            max = check[(i)].dead;
            maxIndex = i;
        }
    }
    cout << rangeNames[maxIndex] <<endl;     //Potrays the correct range

}
void FemaleFinder(genderDeath check[], range valueR[], string rangeNames[])
{   int maxIndex = 0;
    int max = check[0].female/check[0].totalIn;
    for (int i = 1; i < 6; i++)
    {
        double x = check[(i - 1)].female / check[(i - 1)].totalIn;
        double y = check[i].female / check[i].totalIn;                //For simplicity put both into variables
        if (max < x)
        {
            max = i;
        }
    }

    cout << rangeNames[max] <<endl;

}




/*
 * chawla@linprog8.cs.fsu.edu:~/COP3363/Chapter11>a.out
Welcome to the Avengers program!
A) Display Data
B) Find Range with the largest number of Avengers who have died
C) Find Range with the largest percentage of Avengers who are female
D) Quit
Select an option (A-D)..A
            Range    Num Females      Num Males  Num Died OnceNum Never Died Once
            <=750             51             96                53              94
 > 750 and <=1500              6              8                 8               6
> 1500 and <=2250              1              5                 2               4
> 2250 and <=3000              0              2                 2               0
> 3000 and <=3750              0              3                 3               0
> 3750 and <=4500              0              1                 1               0
A) Display Data
B) Find Range with the largest number of Avengers who have died
C) Find Range with the largest percentage of Avengers who are female
D) Quit
Select an option (A-D)..B
<=750
A) Display Data
B) Find Range with the largest number of Avengers who have died
C) Find Range with the largest percentage of Avengers who are female
D) Quit
Select an option (A-D)..d
Thanks for using!
chawla@linprog8.cs.fsu.edu:~/COP3363/Chapter11>

 *
 */