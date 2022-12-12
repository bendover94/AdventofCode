#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

std::ifstream myFile;       // to read the input file


class Crate
{
    public:
        Crate(){}
        Crate(int line, int column, char filling) : line_(line), column_(column), filling_(filling){}
        virtual ~Crate(){for (auto& itr : crates) delete itr;}

        void getCrates(std::string fileNAME)
        {
            std::string str;
            myFile.open(fileNAME, std::ios::in);

            int nextColumn = 0;
            bool visuals = false;
            
            column_ = 0;
            line_ = 0;

            while(getline(myFile, str))
            {
                line_++;
                //std::cout << str << std::endl;
                for (int i = 0; i < int(str.length()); ++i)
                {
                    if (str[i] == '1') // escape after stack visuals
                    {
                        visualsOver_ = true;
                        break;
                    }

                    else if (str[i] == '[' && !visualsOver_) // get the crate visuals
                    {
                        visuals = true;
                        nextColumn++;
                        filling_ = str[i+1];
                        if (i == 0) column_ = 1;
                        if (i == 4) column_ = 2;
                        if (i == 8) column_ = 3;
                        if (i == 12) column_ = 4;
                        if (i == 16) column_ = 5;
                        if (i == 20) column_ = 6;
                        if (i == 24) column_ = 7;
                        if (i == 28) column_ = 8;
                        if (i == 32) column_ = 9;
                    }
                }

                if (visuals)
                {
                    std::cout << "line " << line_ << " has " << nextColumn << " Columns" << std::endl;
                    nextColumn = 0;
                    visuals = false;
                    tmp_c = new Crate(line_, column_, filling_);
                    crates.push_back(tmp_c);
                }
            }

            myFile.close();
        }

        void showCrates()
        {
            std::cout << "\nrow | column | filling" << std::endl;

            for (auto& itr : crates)
            {
                std::cout << itr->line_ << "\t" << itr->column_ << "\t" << itr->filling_ << std::endl;
            }
        }

    private:
        int line_;
        int column_;
        char filling_;
        bool visualsOver_ = false;
        Crate * tmp_c = nullptr;
        std::vector<Crate*> crates;
};



class Instruction
{
    public:
        Instruction(){std::cout << "\nInstruction constructed";}
        Instruction(int what, int from, int to) : what_(what), from_(from), to_(to){}
        virtual ~Instruction(){for (auto& itr : instructions) delete itr;}

        void getInstructions(std::string fileNAME)
        {
            std::string del_move, del_from, del_to, str;
            
            myFile.open(fileNAME, std::ios::in);

            while(getline(myFile, str))
            {
                for (int i = 0; i < int(str.length()); ++i)
                {
                    if (str[i] == 'm') // escape after stack visuals
                    {
                        myFile.seekg(-str.length(), std::ios::cur);
                        while (myFile >> del_move >> what_ >> del_from >> from_ >> del_to >> to_)
                        {
                            instrCNTR++;
                            std::cout << "feeding instructions\n";
                            //std::cout << "instr# " << instrCNTR << ": Move crate: " << what_ << " from: " << from_ << " to: " << to_ << std::endl;
                            tmp_i = new Instruction(what_, from_, to_);
                            instructions.push_back(tmp_i);
                        }
                    }
                }
            }
        }

        void showInstructions()
        {
            std::cout << "\ncrate | from | to" << std::endl;
            instrCNTR = 0;

            for (auto& itr : instructions)
            {
                instrCNTR++;
                std::cout << "instruction# " << instrCNTR << ": Move crate: " << itr->what_ << " from: " << itr->from_ << " to: " << itr->to_ << std::endl;    
            }
        }

    private:
        int what_;
        int from_;
        int to_;
        int instrCNTR = 0;
        Instruction * tmp_i = nullptr;
        std::vector<Instruction*> instructions;

};


class Stack : public Crate, public Instruction
{
    public:
        Stack(){}
        ~Stack(){}

};




int main(int argc, char** argv)
{   
    std::string fileNAME = "test.txt";
    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << std::endl;

    Crate rnd1_c;
    rnd1_c.getCrates(fileNAME);
    rnd1_c.showCrates();
    
    Instruction rnd1_i;
    rnd1_i.getInstructions(fileNAME);
    rnd1_i.showInstructions();

    return 0;
} 