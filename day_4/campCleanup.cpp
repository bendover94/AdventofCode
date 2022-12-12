#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

std::ifstream myFile;       // to read the input file


void getInput(std::string fileNAME)
{
    myFile.open(fileNAME, std::ios::in);
    
    std::string line;
    int fE_first_int, fE_last_int, sE_first_int, sE_last_int;
    char minus, beistrich;
    int fullyContainCNTR = 0;
    std::string fi, se;
    std::size_t found_in_fi, found_in_se;
    int lineNUMBR = 1;


//     std::string line, firstElve, secondElve, fE_first, fE_last, sE_first, sE_last;
//     while (getline(myFile, line))
//     {
//         // std::cout << line << "(string)" << std::endl;
// // split line into first and second Elve
//         firstElve = line.substr(0, line.find(','));
//         secondElve = line.substr(line.find(',')+1, line.length());
//         // std::cout << "firstElve:\t" << firstElve << "(string)" << std::endl;
//         // std::cout << "secondElve:\t" << secondElve << "(string)" << std::endl;
// // split first Elve and second Elve into start and end number (string)
//         fE_first = firstElve.substr(0, firstElve.find('-'));
//         fE_last = firstElve.substr(firstElve.find('-')+1, firstElve.length());
//         sE_first = secondElve.substr(0, secondElve.find('-'));
//         sE_last = secondElve.substr(secondElve.find('-')+1, secondElve.length());
//         // std::cout << "firstElve:\t" << fE_first << '.' << fE_last << "(strings)" << std::endl;
//         // std::cout << "secondElve:\t" << sE_first << '.' << sE_last << "(strings)" << std::endl;
// // convert start and end number string to int
//         fE_first_int = stoi(fE_first);
//         fE_last_int = stoi(fE_last);
//         sE_first_int = stoi(sE_first);
//         sE_last_int = stoi(sE_last);
//         // std::cout << "firstElve:\t" << fE_first_int << '.' << fE_last_int << "(int)" << std::endl;
//         // std::cout << "secondElve:\t" << sE_first_int << '.' << sE_last_int << "(int)" << std::endl;
// // logic
//        }

    while (myFile >> fE_first_int >> minus >> fE_last_int >> beistrich >> sE_first_int >> minus >> sE_last_int)
        {
                fi = "";
                se = "";

                // std::cout << fE_first_int << minus << fE_last_int << beistrich << sE_first_int << minus << sE_last_int << std::endl;
                for (int i = fE_first_int; i<=fE_last_int; ++i)
                {
                        fi += std::to_string(i);
                        fi += '.';
                }
                for (int i = sE_first_int; i<=sE_last_int; ++i)
                {
                        se += std::to_string(i);
                        se += '.';
                }
                
                
                found_in_fi = fi.find(se);
                found_in_se = se.find(fi);
                
                if (found_in_fi!=std::string::npos)
                {
                        fullyContainCNTR++;
                        std::cout << lineNUMBR << ": " << fi << " | " << se << " at " << found_in_fi << std::endl;
                }
                else if (found_in_se!=std::string::npos)
                {
                        fullyContainCNTR++;
                        std::cout << lineNUMBR << ": " << fi << " | " << se << " at " << found_in_se << std::endl;
                }

                lineNUMBR++;
        }
                std::cout << "fully contained in: " << fullyContainCNTR << std::endl; 


}

int main(int argc, char** argv)
{   
    std::string fileNAME = "input.txt";
    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << std::endl;

    getInput(fileNAME);

    return 0;
} 