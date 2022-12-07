#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Elf
{
    public:
        Elf(){}
        ~Elf(){myfile.close();} 

        void getInputFromFile(std::string fileNAME)
        {
            myfile.open(fileNAME, std::ios::in);
            
            while(getline(myfile, str)) // get lines until there are no more lines to get (EOF)
            {
                if (str != "") // if line is not blank, convert string to int and sum up until blank line
                {
                    num = stoi(str);
                    rucksackSumme += num; 
                }
                else        // if there is a blank line, push the acual elf's backpack into vector and reset sumVar
                {
                    elfen.push_back(rucksackSumme);
                    rucksackSumme = 0; 
                }
            }
            elfen.push_back(rucksackSumme);
            elfen.shrink_to_fit();
        }

        void showRucksacke()
        {
            int counter = 1;

            for (auto& itr : elfen)
            {
                std::cout << "Rucksack von Elf " << counter << ":\t";
                std::cout << itr << std::endl;
                counter++;
            }
        }

        int getBestCollector()
        {
            std::sort(elfen.begin(), elfen.end());
            return elfen.back();
        }

        int getBestTHREECollectors()
        {
            int num = 0;

            std::sort(elfen.begin(), elfen.end());
            for (unsigned long i= elfen.size(); i >= (elfen.size()-3); --i)
                num += elfen[i];

            return num;
        }

    private:
        std::ifstream myfile;       // to read the input file
        std::string str;            // to store one line of file (as string)
        int num = 0;                // to store one line of file (as int)
        int rucksackSumme = 0;      // to sum up the calorie sum of one elf
        std::vector<int> elfen;     // to store al elf's calorie sums

    // ofstream     Creates and writes to files
    // ifstream     Reads from files
    // fstream	    A combination of ofstream and ifstream: creates, reads, and writes to files
};


int main(int argc, char** argv)
{   
    Elf bois;   
    //int winner;
    int top3;
    std::string fileNAME = "test.txt";

    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << std::endl;

    bois.getInputFromFile(fileNAME);
    //bois.showRucksacke();
    //winner = bois.getBestCollector();
    top3 = bois.getBestTHREECollectors();
    //bois.showRucksacke();
    //std::cout << "The Elf with the biggest backpack gathered: " << winner << " calories." << std::endl;
    std::cout << "The 3 best collectors gathered: " << top3 << " calories in total." << std::endl; 

    return 0;
}