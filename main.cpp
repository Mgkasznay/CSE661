#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//Program running value set false on a halt command
bool program_running = 1;

//Array containing the 32 registers. 31 general purpose registers r0-r30 and one memory pointer register r31 or gp
string register_set[32];

//Array containing Program data memory starting at memory address 0
string program_memory[200];

//ENUM for switch case used in generic function call
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

//Current Opcode the current opcode running
opCode currentOpcode;

//Generic opcode function runs the function value called for
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
      case SW:{
         //Add Code Here
            int regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
            int ptrIndex = stoi(ptr.substr(1)); //gets the register index for the pointer and removes 'r'
            int offsetValue = stoi(offset); //parse the offset value

            int address = stoi(register_set[ptrIndex]) + offsetValue; //calculate the effective address by adding base register value and offset
            if (address >= 0 && address < 200) { //if the address is greater than or equal to 0 and less than 200, the declared memory size
               program_memory[address] = register_set[regIndexA]; 
              cout << "Stored value " << register_set[regIndexA] << " from " << regA
                  << " into memory [" << address << "]\n";  //stores the value from regA in the calculated memory address
            } else {
               cerr << "Error: memory access out of bounds.\n";// else if it's out of bounds
            }
         }
         break;
      case HALT:{
         //Add Code Here
         program_running = false; //set the main loop to false to stop the program
         cout << "Program halted.\n";
      }
         break;
      case NOP:{
         //Add Code Here
         cout << "No operation performed.\n";
      }
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

      //###   For Debugging Will Remove later  ###
      vector<string> msg {"Hello", "CLASS", "For", "CSE661/CSI655", "and Homework 2!"};

      for (const string& word : msg)
      {
         cout << word << " ";
      }
      cout << endl;

      //Initial grab of the arguments
      string opcode; //Operation code used to determine which function is being called
      string regA; //Register A the first register
      string regB; //Register B the second register
      string regC; //Register C the third register
      string imed; //Imediate value
      string offset; //Offset Value used in lw/sw for offset from a pointer
      string ptr; //Pointer value for a memory location used in lw/sw

      //Print the starting line charecter
      cout << "> ";
      //Get the opcode from the command line
      cin >> opcode;
      //###   For Debugging Will Remove later  ###
      cout << "Opcode: " << opcode << endl; 

      //Funtion in the format: opcode reg, reg, reg
      //Example Format: add r1, r2, r3
      if(opcode == "add" | opcode == "sub" | opcode == "mult" | opcode == "les" | opcode == "eql"){

         //Sets the value to the correct ENUM value for use later
         if(opcode == "add") currentOpcode = ADD;
         else if(opcode == "sub") currentOpcode = SUB;
         else if(opcode == "mult") currentOpcode = MULT;
         else if(opcode == "les") currentOpcode = LES;
         else currentOpcode = EQL;

         //Pulls in the registers from the command line
         cin >> regA >> regB >> regC;

         cout << "RegA: " << regA << endl; //###   For Debugging Will Remove later  ###
         cout << "RegB: " << regB << endl;
         cout << "RegC: " << regC << endl;

      }
      //Checks if function is the format: opcode reg, imed, reg
      //Example format: addi r1, 5, r2
      else if(opcode == "addi"){

         //Gets the registers and imediate from the command line
         cin >> regA >> imed >> regC;

         //Set the ENUM for the opcode
         currentOpcode = ADDI;

         cout << "RegA: " << regA << endl; //###   For Debugging Will Remove later  ###
         cout << "Imed: " << imed << endl;
         cout << "RegC: " << regC << endl;

         //Will add a section here to remove , from arguments

      }
      //checks if the function is in the format: opcode reg, offset(ptr)
      //Example Format is: lw gp, 8(gp)
      else if(opcode == "lw" | opcode == "sw"){

         //Set the ENUM value for the correct function
         if(opcode == "lw") currentOpcode = LW;
         else currentOpcode = SW;

         //Gets the register and immiate value from the command line
         cin >> regA >> imed;

         //Open and closed parathesis values
         string openP = "(";
         string closeP = ")";

         //Find the parathesis
         auto posS = imed.find(openP);
         auto posE = imed.find(closeP);
         posE = posE - posS - 1;
         //Save just the offset value
         offset = imed.substr(0,posS);
         posS++;
         //Save just the pointer value
         ptr = imed.substr(posS,posE);

         cout << "RegA: " << regA << endl; //###   For Debugging Will Remove later  ###
         cout << "Imed: " << imed << endl;
         cout << "Offset: " << offset << endl;
         cout << "Ptr: " << ptr << endl;

      }
      //Save the ENUM value for halt and nop
      else if(opcode == "halt") currentOpcode = HALT;
      else if(opcode == "nop") currentOpcode = NOP;
      //Else not a valid function value
      else{

         currentOpcode = DEFAULT;
         cout << "Opcode not Valid" << endl;

      }

      //Call the generic function
      generic_function(opcode, regA, regB, regC, imed, offset, ptr);

      //The program running until halt
      //Current opcode set to default to prep for next loop
      currentOpcode = DEFAULT;


      //program_running = 0;  //###   For Debugging Will Remove later  ###

   }
}
