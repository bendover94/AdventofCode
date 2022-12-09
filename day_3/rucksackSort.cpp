#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//
// do this for each line
// split line in half
// compare 2 halfs and find common letter
// take corresponding int (1-52) of this line
// add all rucksack values / lines together

char corrspdgINT[]={'0','a','b','c','d','e','f','g',
                        'h','i','j','k','l','m','n','o',
                        'p','q','r','s','t','u','v','w','x','y','z',
                        'A','B','C','D','E','F','G',
                        'H','I','J','K','L','M','N','O',
                        'P','Q','R','S','T','U','V','W','X','Y','Z'};

struct Group
{
    std::string row1;
    std::string row2;
    std::string row3;
};

class RuckSack
{
    public:
        RuckSack(){}
        RuckSack(std::string first, std::string second): first_(first), second_(second){}
        ~RuckSack(){}

        void getInput(std::string fileNAME)
        {
            myfile.open(fileNAME, std::ios::in);

            while(getline(myfile, str)) // get lines until there are no more lines to get (EOF)
            {
                firstCPTMNT = str.substr(0, str.length()/2);
                secondCPTMNT = str.substr(str.length()/2, str.length());
                // std::cout << firstCPTMNT << std::endl;
                // std::cout << secondCPTMNT << std::endl;
                
                tmpSack = new RuckSack(firstCPTMNT, secondCPTMNT);
                ruckSacke.push_back(tmpSack);
            }
        }

        void showSacke()
        {
            RuckSack tmp;
            for (auto& itr : ruckSacke)
            {
                tmp.first_ = itr->first_;
                tmp.second_ = itr->second_;
                std::cout << tmp.first_ << " | ";
                std::cout << tmp.second_ << std::endl;
                std::cout << "\n";
            }
        }

        void showCommonLetter()
        {
            for (auto& itr: commonLetters)
                std::cout << itr << ", ";
            std::cout << "\n";
        }

        void getCommonLetters()
        {
            RuckSack tmp;
                        
            for (unsigned long i = 0; i < ruckSacke.size(); ++i)
            {
                std::size_t found;
                tmp.first_ = ruckSacke[i]->first_;
                tmp.second_ = ruckSacke[i]->second_;

                for (int j = 0; j < int(tmp.first_.length()); ++j)
                {
                    found = tmp.first_.find(tmp.second_[j]);
                    if (found!=std::string::npos)
                    {
                        // std::cout << "common Letter found at: " << found << " (" << tmp.first_[found] << ')' << '\n';
                        commonLetters.push_back(tmp.first_[found]);
                        break;
                    }
                }
            }
        }
    
        int calCSum()
        {
            int num;
            int sum = 0;
            int n = sizeof(corrspdgINT) / sizeof(corrspdgINT[0]);

            for (auto& itr : commonLetters)
            {
                auto letterr = std::find(corrspdgINT, corrspdgINT + n, itr);
            
                if (letterr != std::end(corrspdgINT))
                {
                    //std::cout << "Element " << itr << " is present at index "
                    //<< std::distance(corrspdgINT, letterr) << " in the given array" << std::endl;
                    num = int(std::distance(corrspdgINT, letterr));
                    sum += num;
                }
                else {std::cout << "char is not present in int list" << std::endl;}

            }
            //std::cout << sum << std::endl;
            return sum;
        }

        void getInputRND2(std::string fileNAME)
        {
            myfile.open(fileNAME, std::ios::in);
            lineTracker = 0;

            while(getline(myfile, str)) // get lines until there are no more lines to get (EOF)
            {  
                tmpString = str;
                //std::cout << tmpString << std::endl;
                stringSacke.push_back(tmpString);
                lineTracker++;
            }
        }

        void showStringSacke()
        {
            int groupTracker = 0;
            int groupCounter = 1;
            std::string tmp;

            std::cout << "Group #" << groupCounter << std::endl;
            
            for (auto& itr : stringSacke)
            {
                std::cout << itr << std::endl;
                
                groupTracker++; // to track every three lines and shove in a \n

                if (groupTracker == 3)
                {
                    groupTracker = 0;
                    groupCounter++; // to count and enum all groups
                    std::cout << "\n";
                    if (groupCounter != lineTracker / 3+1)
                        std::cout << "Group #" << groupCounter << std::endl;
                }
            }
        }


        void getCommonLetterRND2()
        {
            Group tmp;
            int N = 3;
            char commonCHAR;
            int index_IN_STRING_1;

            tmp.row1 = stringSacke[0];
            tmp.row2 = stringSacke[1];
            tmp.row3 = stringSacke[2];
            

            for (int i = 0; i < int(tmp.row1.size()); ++i)
            {
                for (int j = 0; j < int(tmp.row2.size()); ++j)
                {
                    for (int k = 0; k < int(tmp.row3.size()); ++k)
                    {
                        if (tmp.row3[k] == tmp.row2[j] && tmp.row3[k] == tmp.row1[i] && tmp.row1[i] == tmp.row2[j])
                        {
                            index_IN_STRING_1 = i;
                            break;
                        }
                    }
                }
            }
            commonCHAR = tmp.row1[index_IN_STRING_1]; 
            std::cout << "Found common letter ";
            std::cout << commonCHAR;
            commonLettersRND2.push_back(commonCHAR);
            stringSacke.erase(stringSacke.begin(), stringSacke.begin() + N);
        }
    
        void makeCommonLettersRND2()
        {
            for (int i = 1; i<= lineTracker / 3; ++i) // oder size/3
            {
                getCommonLetterRND2();
                std::cout << " in group " << i << std::endl;
            }
        }

        int calCSumRND2()
        {
            int num;
            int sum = 0;
            int n = sizeof(corrspdgINT) / sizeof(corrspdgINT[0]);


            for (auto& itr : commonLettersRND2)
            {
                auto letterr = std::find(corrspdgINT, corrspdgINT + n, itr);
                                            
                if (letterr != std::end(corrspdgINT))
                {
                    //std::cout << "Element " << itr << " is present at index "
                    //<< std::distance(corrspdgINT, letterr) << " in the given array" << std::endl;
                    num = int(std::distance(corrspdgINT, letterr));
                    sum += num;
                }
                else {std::cout << "char is not present in int list" << std::endl;}
            }
            
            //std::cout << sum << std::endl;
            return sum;
        }


        std::string first_;
        std::string second_;
        RuckSack * tmpSack = nullptr;
        std::vector<RuckSack*> ruckSacke;
        std::string tmpString;
        std::vector<std::string> stringSacke;
        std::vector<Group*> ruckSackeRND2;
        std::vector<char> commonLetters;
        std::vector<char> commonLettersRND2;
        int lineTracker;

        std::ifstream myfile;
        std::string str;
        std::string firstCPTMNT;
        std::string secondCPTMNT;
};



int main(int argc, char** argv)
{
    std::string fileNAME = "test.txt";

    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << "\n" << std::endl;

    // RuckSack sort1;
    // sort1.getInput(fileNAME);
    // sort1.showSacke();

    // Round 1
    // sort1.getCommonLetters();
    // sort1.showCommonLetter();
    // std::cout << sort1.calCSum() << std::endl;

    RuckSack sort2;

    sort2.getInputRND2(fileNAME);
    sort2.showStringSacke();
    sort2.makeCommonLettersRND2();
    std::cout << "\nSum: " << sort2.calCSumRND2() << std::endl;

    // sort2.showCommonLetterRND2();
    // std::cout << sort2.calCSumRND2() << std::endl;

    return 0;
}

