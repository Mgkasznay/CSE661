#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

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

// based on instruction, return a string that visually shows 32b hex equivalent
// OPCODE (4 bits) + Register(5 bits) + Register(5 bits) + Register(5 bits) + Extra(13 bits)
// example: instruction_to_hex(11, 1, 2, 3, 4, 5, 6) returns b0886004
auto instruction_to_hex(unsigned int opcode, unsigned int regA, unsigned int regB, unsigned int regC, unsigned int imed, unsigned int offset, unsigned int ptr) {

   // convert all to binary
   // may need additional code here: ex. Lw r1, 8(gp) where regA = r1, regB = gp, imed = 8, ptr = gp

   // show what was input
   cout << "You input opcode: " << opcode << " regA: " << regA << " regB: " << regB << " regC: " << regC << " imed: " << imed << " offset: " << offset << " ptr: " << ptr << "\n";
   // store 4 bits for opcode
   bitset<4> op{opcode};
   cout << "op: " << op << "\n";

   // store 5 bits for register A, can be registers 0-31 in memory
   bitset<5> rA{regA};
   cout << "rA: " << rA << "\n";

   // store 5 bits for register B, can be registers 0-31 in memory
   bitset<5> rB{regB};
   cout << "rB: " << rB << "\n";

   // store 5 bits for register C, can be registers 0-31 in memory
   bitset<5> rC{regC};
   cout << "rC: " << rC << "\n";

   // store 13 bits for immediate; if there is an offset, the value of the offset will be stored here
   bitset<13> im{imed};
   cout << "im: " << im << "\n";

   cout << "string op: " << op << "\n";
   string instruct_string{op.to_string() + rA.to_string() + rB.to_string() + rC.to_string() + im.to_string()};
   cout << "instruct_string:" << instruct_string << "\n";

   stringstream ss; // create string stream object
   string result{}; // initalize string to store result

   // for every four characters in instruct_string (aka 4 bits)...
   for (int i = 0; i < instruct_string.length(); i = i + 4) {

      // convert four character string to decimal (unsigned long integer), 
      // then convert decimal to hex and store in string stream object
      ss << hex << (bitset<4> {instruct_string.substr(i, 4)}).to_ulong() << "\n";

      // convert string stream object to string, append to result string
      result += ss.str();

      // there is a new line at end of string. get rid of it
      if (!result.empty() && result[result.length()-1] == '\n') {
         result.erase(result.length()-1);
      }   

      // remove contents of string string object in prep for conversion of next four characters to hex
      ss.str("");
   }

   // print resulting string, which visually shows hex
   // cout << "result: " << result << "\n";

   // return the hex string
   return result;
}

int main()
{
   // test instruction_to_hex()
   cout << "test instruction_to_hex(), last line is return value: \n" << instruction_to_hex(11, 1, 2, 3, 4, 5, 6) << "\n";

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
