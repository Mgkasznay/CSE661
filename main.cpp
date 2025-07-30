#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool program_running = 1;

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

      cout << "> ";
      cin >> opcode;
      cout << "Opcode: " << opcode << endl; //Will replace with more useful code?

      //Could add a make lower case here for ease of use

      if(opcode == "add" | opcode == "sub" | opcode == "addi" | opcode == "mult" | opcode == "les" | opcode == "eql"){

         cin >> regA >> regB >> regC;

         cout << "RegA: " << regA << endl; //Will Replace later
         cout << "RegB: " << regB << endl;
         cout << "RegC: " << regC << endl;

      }
      else if(opcode == "lw" | opcode == "sw"){

         cin >> regA >> imed;

         //Add section here to remove offset and store in a varible

         cout << "RegA: " << regA << endl; //Will Replace later
         cout << "Imed: " << imed << endl;

      }
      else if(opcode == "halt" | opcode == "nop"){

         // valid command set varibles here:

         //Set command to stop operation (halt)
         //Set command to skip a loop (nop)

      }
      else{

         cout << "Opcode not Valid" << endl;

      }

      //Will add a section here to remove , from arguments

      //Will be used to be the program running until halt add later
      program_running = 0;

   }
}
