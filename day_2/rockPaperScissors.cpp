#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


struct Points
{
    int win = 6;
    int draw = 3;
    int gotRock = 1;
    int gotPaper = 2;
    int gotSciss = 3;
    int loose = 0;
};

int points = 0;
std::ifstream myfile;       // to read the input file
std::string str;            // to store one line of file (as string)
int TOTAL_PLAYER_POINTS = 0;
int TOTAL_OPPONENT_PLAYER_POINTS = 0;


std::string translate(char toTranslate)
{
    std::string translated;
    
    switch (toTranslate)
    {
        case 'A':
            translated = "oP_ROCK ";
            break;
        case 'B':
            translated = "oP_Paper";
            break;
        case 'C':
            translated = "oP_SCISS";
            break;
        
        case 'X':
            translated = "P_ROCK ";
            break;
        case 'Y':
            translated = "P_Paper";
            break;
        case 'Z':
            translated = "P_SCISS";
            break;
        
        default:
            break;
    } 
    
    return translated; 
}

int getPPoints(char oP, char P)
{
    int tmp;
    Points p;

// Draw games
    if (oP == 'A' && P == 'X') points += p.draw;
    if (oP == 'B' && P == 'Y') points += p.draw;
    if (oP == 'C' && P == 'Z') points += p.draw;
// winning games
    if (oP == 'C' && P == 'X') points += p.win;
    if (oP == 'A' && P == 'Y') points += p.win;
    if (oP == 'B' && P == 'Z') points += p.win;
// loosing games
    if (oP == 'A' && P == 'Z') points += p.loose;
    if (oP == 'B' && P == 'X') points += p.loose;
    if (oP == 'C' && P == 'Y') points += p.loose;

    switch (P) // own points
    {    
        case 'X':
            points += p.gotRock; break;
        case 'Y':
            points += p.gotPaper; break;
        case 'Z':
            points += p.gotSciss; break;
        default:
            break;
    } 
    
    tmp = points;
    TOTAL_PLAYER_POINTS += points;
    points = 0;
    return tmp; 
}

int getoPPoints(char oP, char P)
{
    int tmp;
    Points p;

// Draw games
    if (oP == 'A' && P == 'X') points += p.draw;
    if (oP == 'B' && P == 'Y') points += p.draw;
    if (oP == 'C' && P == 'Z') points += p.draw;
// winning games
    if (oP == 'C' && P == 'Y') points += p.win;
    if (oP == 'A' && P == 'Z') points += p.win;
    if (oP == 'B' && P == 'X') points += p.win;
// loosing games
    if (oP == 'A' && P == 'Y') points += p.loose;
    if (oP == 'B' && P == 'Z') points += p.loose;
    if (oP == 'C' && P == 'X') points += p.loose;

    switch (oP) // own points
    { 
        case 'A':
            points += p.gotRock; break;
        case 'B':
            points += p.gotPaper; break;
        case 'C':
            points += p.gotSciss; break;
        default:
            break;
    } 

    tmp = points;
    TOTAL_OPPONENT_PLAYER_POINTS += points;
    points = 0;
    return tmp; 
}

int getPPoints_2ndRound(char oP, char P)
{
    int tmp;
    Points p;

    if (oP == 'A' && P == 'X')
    {
        points += p.loose;
        points += p.gotSciss;
    } 
    if (oP == 'B' && P == 'Y')
    {
        points += p.draw;
        points += p.gotPaper;
    } 
    if (oP == 'C' && P == 'Z')
    {
        points += p.win;
        points += p.gotRock;
    } 
    if (oP == 'C' && P == 'X') 
    {
        points += p.loose;
        points += p.gotPaper;
    }
    if (oP == 'A' && P == 'Y')
    {
        points += p.draw;
        points += p.gotRock;
    }
    if (oP == 'B' && P == 'Z')
    {
        points += p.win;
        points += p.gotSciss;
    }
    if (oP == 'A' && P == 'Z') 
    {
        points += p.win;
        points += p.gotPaper;
    }
    if (oP == 'B' && P == 'X') 
    {
        points += p.loose;
        points += p.gotRock;
    }
    if (oP == 'C' && P == 'Y') 
    {
        points += p.draw;
        points += p.gotSciss;
    }
    
    tmp = points;
    TOTAL_PLAYER_POINTS += points;
    points = 0;
    return tmp; 
}

int getoPPoints_2ndRound(char oP, char P)
{
    int tmp;
    Points p;

    if (oP == 'A' && P == 'X')
    {
        points += p.win;
        points += p.gotRock;
    } 
    if (oP == 'B' && P == 'Y')
    {
        points += p.draw;
        points += p.gotPaper;
    } 
    if (oP == 'C' && P == 'Z')
    {
        points += p.loose;
        points += p.gotSciss;
    } 
    if (oP == 'C' && P == 'X') 
    {
        points += p.win;
        points += p.gotSciss;
    }
    if (oP == 'A' && P == 'Y')
    {
        points += p.draw;
        points += p.gotRock;
    }
    if (oP == 'B' && P == 'Z')
    {
        points += p.loose;
        points += p.gotPaper;
    }
    if (oP == 'A' && P == 'Z') 
    {
        points += p.loose;
        points += p.gotRock;
    }
    if (oP == 'B' && P == 'X') 
    {
        points += p.win;
        points += p.gotPaper;
    }
    if (oP == 'C' && P == 'Y') 
    {
        points += p.draw;
        points += p.gotSciss;
    }

    tmp = points;
    TOTAL_OPPONENT_PLAYER_POINTS += points;
    points = 0;
    return tmp; 
}


void getInputFromFile(std::string fileNAME)
{
    char oP, P;

    myfile.open(fileNAME, std::ios::in);

    while(myfile >> oP >> P) // get lines until there are no more lines to get (EOF)        
    {
        //std::cout << "oP: " << oP << " P: " << P << std::endl;
        // std::cout << translate(oP) << "\t-\t";
        // std::cout << translate(P) << std::endl;

        // std::cout << getoPPoints(oP, P);
        // std::cout << " | ";
        // std::cout << getPPoints(oP, P) << std::endl;

        std::cout << getoPPoints_2ndRound(oP, P);
        std::cout << " | ";
        std::cout << getPPoints_2ndRound(oP, P) << std::endl;
    }
    myfile.close();
}



int main(int argc, char** argv)
{   
    std::string fileNAME = "test.txt";

    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << std::endl;

    getInputFromFile(fileNAME);
    std::cout << "ToPP: " << TOTAL_OPPONENT_PLAYER_POINTS << " | ";
    std::cout << "TPP:  " << TOTAL_PLAYER_POINTS << std::endl;

    return 0;
}