#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

bool program_running = 1;


string register_set[32];
string program_memory[200];

enum opCode {
   ADD,
   ADDI,
   SUB,
   MULT,
   LES,
   EQL,
   LW,
   SW,
   HALT,
   NOP,
   DEFAULT
};

opCode currentOpcode;

void generic_function(string opcode, string regA, string regB, string regC, string imed, string offset, string ptr){

   switch(currentOpcode){
      case ADD:
         //Add Code Here
         break;
      case ADDI:
         //Add Code Here
         break;
      case SUB:
         //Add Code Here
         break;
      case MULT:
         //Add Code Here
         break;
      case LES:
         //Add Code Here
         break;
      case EQL:
         //Add Code Here
         break;
      case LW:
         //Add Code Here
         break;
      case SW:
         //Add Code Here
         break;
      case HALT:
         //Add Code Here
         break;
      case NOP:
         //Add Code Here
         break;
      case DEFAULT:
         //Do nothing here
         break;
   }

}

void print_reg_print_mem(){
   // Do something
}

void opcode_to_hex(){
   //Do something
}

int main()
{
   
   while(program_running){

      //Starting Hello World Statement Remove Later
      vector<string> msg {"Hello", "CLASS", "For", "CSE661/CSI655", "and Homework 2!"};

      for (const string& word : msg)
      {
         cout << word << " ";
      }
      cout << endl;

      //Initial grab of the arguments
      string opcode;
      string regA;
      string regB;
      string regC;
      string imed;
      string offset;
      string ptr;

      cout << "> ";
      cin >> opcode;
      cout << "Opcode: " << opcode << endl; //Will replace with more useful code?

      //Could add a make lower case here for ease of use

      if(opcode == "add" | opcode == "sub" | opcode == "mult" | opcode == "les" | opcode == "eql"){

         if(opcode == "add") currentOpcode = ADD;
         else if(opcode == "sub") currentOpcode = SUB;
         else if(opcode == "mult") currentOpcode = MULT;
         else if(opcode == "les") currentOpcode = LES;
         else currentOpcode = EQL;

         cin >> regA >> regB >> regC;

         cout << "RegA: " << regA << endl; //Will Replace later
         cout << "RegB: " << regB << endl;
         cout << "RegC: " << regC << endl;

      }
      else if(opcode == "addi"){

         cin >> regA >> imed >> regC;

         currentOpcode = ADDI;

         cout << "RegA: " << regA << endl; //Will Replace later
         cout << "Imed: " << imed << endl;
         cout << "RegC: " << regC << endl;

         //Will add a section here to remove , from arguments

      }
      else if(opcode == "lw" | opcode == "sw"){

         if(opcode == "lw") currentOpcode = LW;
         else currentOpcode = SW;

         //Expected Format is: lw gp, 8(gp)

         cin >> regA >> imed;

         string openP = "(";
         string closeP = ")";

         //Remove offset and store in a varible
         auto posS = imed.find(openP);
         auto posE = imed.find(closeP);
         posE = posE - posS - 1;
         offset = imed.substr(0,posS);
         posS++;
         ptr = imed.substr(posS,posE);

         cout << "RegA: " << regA << endl; //Will Replace later
         cout << "Imed: " << imed << endl;
         cout << "Offset: " << offset << endl;
         cout << "Ptr: " << ptr << endl;

      }
      else if(opcode == "halt" | opcode == "nop"){

         if(opcode == "halt") currentOpcode = HALT;
         else currentOpcode = NOP;

         // valid command set varibles here:

         //Set command to stop operation (halt)
         //Set command to skip a loop (nop)

      }
      else{

         currentOpcode = DEFAULT;
         cout << "Opcode not Valid" << endl;

      }

      generic_function(opcode, regA, regB, regC, imed, offset, ptr);

      //Will be used to be the program running until halt add later
      program_running = 0;

   }
}
