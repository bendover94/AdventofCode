#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>

std::ifstream myFile;       // to read the input file


class Crate
{
    public:
        Crate(){}
        Crate(int line, int column, char filling) : line_(line), column_(column), filling_(filling){}
        virtual ~Crate(){}

        void getCrates(std::string fileNAME)
        {
            std::string str;
            myFile.open(fileNAME, std::ios::in);

            
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
                        break;
                    }

                    else if (str[i] == '[') // get the crate visuals
                    {
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


                        tmp_c = new Crate(line_, column_, filling_);
                        crates.push_back(tmp_c);
                    }
                }
            }

            myFile.close();
        }

        void showCrates()
        {
            std::cout << "\nline | column | filling" << std::endl;

            for (auto& itr : crates)
            {
                std::cout << itr->line_ << "\t" << itr->column_ << "\t" << itr->filling_ << std::endl;
            }
        }

        std::vector<Crate*> getCrates()
        {
            return crates;
        }

    
        int line_;
        int column_;
        char filling_;
        Crate * tmp_c = nullptr;
        std::vector<Crate*> crates;
};



class Instruction
{
    public:
        Instruction(){}
        Instruction(int howMany, int from, int to) : howMany_(howMany), from_(from), to_(to){}
        virtual ~Instruction(){}

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
                        while (myFile >> del_move >> howMany_ >> del_from >> from_ >> del_to >> to_)
                        {
                            instrCNTR++;
                            //std::cout << "feeding instructions\n";
                            //std::cout << "instr# " << instrCNTR << ": Move crate: " << what_ << " from: " << from_ << " to: " << to_ << std::endl;
                            tmp_i = new Instruction(howMany_, from_, to_);
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
                std::cout << "instruction# " << instrCNTR << ": Move crate: " << itr->howMany_ << " from: " << itr->from_ << " to: " << itr->to_ << std::endl;    
            }
        }

        std::vector<Instruction*> getInstrucions()
        {
            return instructions;
        }
    
        int howMany_;
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
        ~Stack()
        {
            for (auto& itr : crates) delete itr;
            for (auto& itr : instructions) delete itr;
        }

        void makeStacks(std::vector<Crate*> crates)
        {
            Crate * tmp_c;

            for (auto itr = crates.rbegin(); itr != crates.rend(); ++itr)
            {
                tmp_c = *itr;

                if (tmp_c->column_ == 1) stack_1.push(tmp_c->filling_);
                if (tmp_c->column_ == 2) stack_2.push(tmp_c->filling_);
                if (tmp_c->column_ == 3) stack_3.push(tmp_c->filling_);
                if (tmp_c->column_ == 4) stack_4.push(tmp_c->filling_);
                if (tmp_c->column_ == 5) stack_5.push(tmp_c->filling_);
                if (tmp_c->column_ == 6) stack_6.push(tmp_c->filling_);
                if (tmp_c->column_ == 7) stack_7.push(tmp_c->filling_);
                if (tmp_c->column_ == 8) stack_8.push(tmp_c->filling_);
                if (tmp_c->column_ == 9) stack_9.push(tmp_c->filling_);                
            }

            allStacks.push_back(stack_1);
            allStacks.push_back(stack_2);
            allStacks.push_back(stack_3);
            allStacks.push_back(stack_4);
            allStacks.push_back(stack_5);
            allStacks.push_back(stack_6);
            allStacks.push_back(stack_7);
            allStacks.push_back(stack_8);
            allStacks.push_back(stack_9);
        }


        void showStack()
        {
            for (auto& itr : allStacks)
            {
                if (itr.size() != 0)
                {
                    stackCounter++;
                    std::cout << "\nStack " << stackCounter << " Size:" << itr.size() << std::endl;
                    int siZe = int(itr.size());
                    
                    for (int i = 0; i<siZe; ++i)
                    {
                        std::cout << itr.top() << std::endl;
                        itr.pop();
                    }      
                }
            }
        }

        void reArrangeStacks(std::vector<Instruction*> instructions)
        {
            std::stack<char> get_from;
            std::stack<char> move_to;
            char tmp;
            
            for (auto& itr_instr : instructions)
            {
                if (itr_instr->from_ == 1) get_from = stack_1;
                if (itr_instr->from_ == 2) get_from = stack_2;
                if (itr_instr->from_ == 3) get_from = stack_3;
                if (itr_instr->from_ == 4) get_from = stack_4;
                if (itr_instr->from_ == 5) get_from = stack_5;
                if (itr_instr->from_ == 6) get_from= stack_6;
                if (itr_instr->from_ == 7) get_from = stack_7;
                if (itr_instr->from_ == 8) get_from = stack_8;
                if (itr_instr->from_ == 9) get_from = stack_9;

                if (itr_instr->to_ == 1) move_to = stack_1;
                if (itr_instr->to_ == 2) move_to = stack_2;
                if (itr_instr->to_ == 3) move_to = stack_3;
                if (itr_instr->to_ == 4) move_to = stack_4;
                if (itr_instr->to_ == 5) move_to = stack_5;
                if (itr_instr->to_ == 6) move_to = stack_6;
                if (itr_instr->to_ == 7) move_to = stack_7;
                if (itr_instr->to_ == 8) move_to = stack_8;
                if (itr_instr->to_ == 9) move_to = stack_9;
                

                for (int i = 0; i < itr_instr->howMany_; ++i)
                {
                    tmp = get_from.top();
                    move_to.push(tmp);
                    get_from.pop();
                }
            }
        }

        int stackCounter = 0; 
        std::stack<char> stack_1, stack_2, stack_3, stack_4, stack_5, stack_6, stack_7, stack_8, stack_9;
        std::vector<std::stack<char>> allStacks;
};




int main(int argc, char** argv)
{   
    std::string fileNAME = "test.txt";
    if (argc > 1) fileNAME = argv[1];
    std::cout << "Using input file: " << fileNAME << std::endl;

    Crate rnd1_c;
    rnd1_c.getCrates(fileNAME);
    rnd1_c.showCrates();
    std::vector<Crate*> crates = rnd1_c.getCrates();

    
    Instruction rnd1_i;
    rnd1_i.getInstructions(fileNAME);
    rnd1_i.showInstructions();
    std::vector<Instruction*> instructions = rnd1_i.getInstrucions();

    Stack rnd1_s;
    rnd1_s.makeStacks(crates);
    rnd1_s.showStack();
    rnd1_s.reArrangeStacks(instructions);
    rnd1_s.showStack();


    return 0;
} 