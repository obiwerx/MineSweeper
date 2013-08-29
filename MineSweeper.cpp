/*************************************
 ** CIST2361 C++ PROGRAMMING I       **
 ** MINESWEEPER UVA JUDGE CHALLENGE  **
 ** T. O'Brien 900221606             **
 ************************************/

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Global Constants//
const int rows = 105;           //You HAVE to declare a right value for 2D array prototypes - otherwise you get a compiler error.
const int columns = 105;        //So I created a const for ROWS and COLUMNS that is greater than the largest possible value.


//Function Prototypes//
void readFromFile(int, int, fstream &inputFile, char array[rows][columns]);             //function to read minefield data from file
void writeToFile(int, int, fstream &outputFile, char array[rows][columns]);             //function to write converted matrix to file
void processMineField(int, int, int &, char array[rows][columns]);                      //function to process minefield data and locate mines
void clearMineField(char array[rows][columns]);                                         //function to wipe the minefield array and prevent data issues
void convertCountToChar(int &, int &, int &, char array[rows][columns]);                //function to cast int to char
void validateRowsColumns(int, int);                                                     //function to verify that n < 0 and M > 101
void closeFiles(fstream &inputFile, fstream &outputFile);                               //close files properly

int main()
{
    int n, m;                                       //Rows and columns from file
    int count = 0, recordNum = 0;                   //Number of mines around the current location
    char mineField[rows][columns];                  //matrix to hold minefield
    
    fstream inputFile;                              //input file stream
    fstream outputFile;                             //output file stream
    inputFile.open("inputdata.dat");                //open inputdata.dat
    outputFile.open("outputdata.dat");              //open outputdata.dat
    
    while(true)                     //keep loop running until break condition occurs
    {
        inputFile >> n >> m;        //pull the rows and columns from the input file
        
        validateRowsColumns(n, m);
        
        if(n == 0 && m == 0 )       //if n and m are EVER 0...
        {
            break;                  //STOP THE LOOP!
        }
            
        readFromFile(n, m, inputFile, mineField);   //read minefield matrix from file
        
        
        for(int i = 1; i < n+1; i++)                                //Process the rows
        {
            for(int j = 1; j < m+1; j++)                            //Process the columns
            {
                if(mineField[i][j] == '*')                          //if a "mine" is located...
                {   
                    continue;                                       //carry on!
                }
                
                else                                                //otherwise...
                {
                    processMineField(i, j, count, mineField);       //process the number of mines adjacent to location
                }
                
                convertCountToChar(i, j, count, mineField);         //convert the int "count" to a char value for the matrix
            }
        }
        
        if(recordNum > 0)                                           //as long as there are a numbers to record
        {
            outputFile << endl;                                     //carriage return to the next row
        }
        
        recordNum++;                                                //increment counter
        outputFile << "Field #" << recordNum << ":\n";              //outputdata.dat minefield header output
        
        writeToFile(n, m, outputFile, mineField);                   //from here on we output the values
                
        clearMineField(mineField);                                  //since the minefield can vary in size, you HAVE to clear it.
        
    }
    
    closeFiles(inputFile, outputFile);
    
    system("pause");    //a pause for Windows
    return 0;           //return 0 to exit main.
}


/*EVERTHING BELOW THIS LINE IS FUNCTIONS FOR MAIN - SEE PROTOYPES AREA FOR A GENERAL IDEA
 OF WHAT THESE FUNCTIONS DO AND WHY THEY DO IT. */

void writeToFile(int n, int m, fstream &outputFile, char array[rows][columns])
{
    for(int i = 1; i < n+1; i++)                                //process rows
    {
        for(int j = 1; j < m+1; j++)                            //process columns
        {
            outputFile << array[i][j];                          //write location to minefield matrix
        }
        
        outputFile << endl;                                     //carriage return to the next row
    }
  
}


void readFromFile(int n, int m, fstream &inputFile, char array[rows][columns])
{
    //Read the values into the matrix
    for(int i = 1; i < n+1; i++)            //these are the rows
    {
        for(int j = 1; j < m+1; j++)        //these are the columns
        {
            inputFile >> array[i][j];       //this (i, j) location is pulled from file
        }
    }
}

void processMineField(int i, int j, int &count, char array[rows][columns])
{
    if(array[i-1][j-1] == '*')      //Looking for mine in ajacent squares
    {
        count++;                    //if it's there, increment counter -
    }
    if(array[i-1][j] == '*')        //all these "ifs" do that for each of
    {
        count++;                    //eight possible positions.
    }
    if(array[i-1][j+1] == '*')
    {
        count++;
    }
    if(array[i][j-1] == '*')
    {
        count++;
    }
    if(array[i][j+1] == '*')
    {
        count++;
    }
    if(array[i+1][j-1] == '*')
    {
        count++;
    }
    if(array[i+1][j] == '*')
    {
        count++;
    }
    if(array[i+1][j+1] == '*')
    {
        count++;
    }

}

void clearMineField(char array[rows][columns])
{
    for (int x=0; x < rows; ++x)         //clear all 105 rows
    {
        for (int y=0; y < columns; ++y)     //clear all 105 columns
        {
            array[x][y] = '.';          //clear by putting a '.'
        }
    }

}

void convertCountToChar(int &i, int &j, int &count, char array[rows][columns])
{
    //Create a buffer to convert the count to a char
    stringstream buffer;
    buffer << count;
    array[i][j] = buffer.str().at(0);
    
    count = 0; //Finally reset the counter
}

void validateRowsColumns(int n, int m)
{
    if(n < 0 || m > 101)
    {
        cout << "Field exceeds limits, check file and run again.\n";
        exit(1);
    }
}

void closeFiles(fstream &inputFile, fstream &outputFile)
{
    inputFile.close();
    outputFile.close();
}