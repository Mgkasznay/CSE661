#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

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
         {
         int regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         int regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         int regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         register_set[regIndexC] = to_string(stoi(register_set[regIndexA]) + stoi(register_set[regIndexB]));

         }
         break;
      case ADDI:
         {
         int regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         int regIndexB = stoi(regB.substr(1)); //extract register number from regb and remove 'r'
         int numImed = stoi(imed); //extract imeddiate number

         register_set[regIndexB] = to_string(stoi(register_set[regIndexA]) + numImed);

         }
         break;
      case SUB:
         {
         int regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         int regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         int regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         register_set[regIndexC] = to_string(stoi(register_set[regIndexA]) - stoi(register_set[regIndexB]));

         }
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

void initilize_reg_mem(){

   for (int i = 0; i < 32; i++){
      register_set[i] = "0";
   }

   for (int i = 0; i < 200; i++){
      program_memory[i] = "0";
   }
}

// based on instruction, return a string that visually shows 32b hex equivalent
// OPCODE (4 bits) + Register(5 bits) + Register(5 bits) + Register(5 bits) + Extra(13 bits)
// regC, imed, offset, ptr are optional parameters, default value = 0.
// Example: instruction_to_hex(11, 1, 2, 3) -> b0886000
// Example: instruction_to_hex(11, 1, 2, 0, 4, 5, 6) -> b0980005
auto instruction_to_hex(unsigned int opcode, unsigned int regA, unsigned int regB, unsigned int regC = 0, unsigned int imed = 0, unsigned int offset = 0, unsigned int ptr = 0) {

   // if an offset or ptr value exists, value of imed = offset, value of regB = ptr
   if (offset != 0) {
      imed = offset;
   }

   if (ptr != 0) {
      regB = ptr;
   }

   // for debugging - print input, may remove later.
   cout << "Your input values: opcode: " << opcode << " regA: " << regA << " regB: " << regB 
      << " regC: " << regC << " imed: " << imed << " offset: " << offset << " ptr: " << ptr << "\n";
   
   // convert input values to binary
   bitset<4> op{opcode};   // store 4 bits for opcode
   bitset<5> rA{regA};     // store 5 bits for register A, can be registers 0-31 (00000-11111) in memory
   bitset<5> rB{regB};     // same as register A
   bitset<5> rC{regC};     // same as register A
   bitset<13> im{imed};    // store 13 bits for immediate;
   
   // for debugging - print binary, may remove later.
   cout << "Converted to binary: op: " << op << "\n" << "rA: " << rA << "\n" 
      << "rB: " << rB << "\n" << "rC: " << rC << "\n" << "im: " << im << "\n";

   string instruct_string{op.to_string() + rA.to_string() + rB.to_string() + rC.to_string() + im.to_string()};
   cout << "instruct_string:" << instruct_string << "\n";

   stringstream ss; // create string stream object
   string result{}; // initalize string to store result

   // for every four characters in instruct_string (aka 4 bits)...
   for (int i = 0; i < instruct_string.length(); i = i + 4) {

      // convert 4-bits to decimal (unsigned long integer), then decimal to hex, then store in string stream object
      ss << hex << (bitset<4> {instruct_string.substr(i, 4)}).to_ulong() << "\n";
      
      result += ss.str();  // convert string stream object to string, append to result string

      // remove new line at end of string
      if (!result.empty() && result[result.length()-1] == '\n') {
         result.erase(result.length()-1);
      }   

      // remove contents of string string object in prep for next 4-bit to hex conversion
      ss.str("");
   }

   return result; // return the hex string
}

// exact opposite of instruction_to_hex: given 32bit hex string, return components of instruction (ie. opcode, register, etc.)
// OPCODE (4 bits) + Register(5 bits) + Register(5 bits) + Register(5 bits) + Extra(13 bits)
// possible values for "component" parameter: opcode, regA, regB, regC, imed, offset, ptr
// Example: hex_to_instruction("b0886000", "opcode") -> 11
// Example: hex_to_instruction("b0980005", "regA") -> 1
string hex_to_instruction(string hex_string, string component) {

   cout << "Your input: hex_string: " << hex_string << " requested component: " << component << "\n";
   // convert hex to binary
   string temp_hex_str = "0x" + hex_string;
   stringstream ss;
   ss << hex << temp_hex_str;    // convert hex string to unsigned int, store in string stream object
   unsigned int hex_unsigned_int; // initialize variable to store unsigned int
   ss >> hex_unsigned_int; // take contents of string stream object, assign to hex_unsigned_int
   bitset<32> bin(hex_unsigned_int);   // store 32 bits for hex
   string bin_str = bin.to_string();

   cout << "Hex string converted to binary string: \n" << bin_str << "\n"; // convert to string

   // separate binary string into components (opcode 4 bits, registerA 5 bits, etc), 
   // then convert substrings to integer in decimal format, then convert back to string
   string op = bin_str.substr(0, 4);                  // get binary string
   string opcode = to_string(stoi(op, nullptr, 2));   // convert binary string to decimal integer, then convert back to string
   string rA = bin_str.substr(4, 5);                  // etc.
   string regA = to_string(stoi(rA, nullptr, 2));
   string rB = bin_str.substr(9, 5); 
   string regB = to_string(stoi(rB, nullptr, 2));
   string rC = bin_str.substr(14,5); 
   string regC = to_string(stoi(rC, nullptr, 2));
   string im = bin_str.substr(19, 13); 
   string imed = to_string(stoi(im, nullptr, 2));
   string offset{};
   string ptr{};

   if (imed != "0") {
      offset = imed;
      ptr = regB; 
   }

   // for debugging, may remove later - output binary and decimal representations of opcode, registers, etc.
   cout << "op: " << op << " opcode: " << opcode << "\n" << "rA: " << rA << " regA: " << regA << "\n"
      << "rB: " << rB << " regB: " << regB << "\n" << "rC: " << rC << " regC: " << regC << "\n"
      << "im: " << im << " imed: " << imed << "\n";

   // return value of requested component
   if (component == "opcode") {
      return opcode;
   }
   else if (component == "regA") {
      return regA;
   }
   else if (component == "regB") {
      return regB;
   }
   else if (component == "regC") {
      return regC;
   }
   else if (component == "imed") {
      return imed;
   }
   else if (component == "offset") {
      return offset;
   }
   else if (component == "ptr") {
      return ptr;
   } else {
   return "Default.";
   }
}

int main()
{
   // test instruction_to_hex()
   cout << "test instruction_to_hex(), last line is return value: \n" << instruction_to_hex(11, 1, 2, 3) << "\n";
   cout << "test instruction_to_hex(), last line is return value: \n" << instruction_to_hex(11, 1, 2, 0, 4, 5, 6) << "\n";

   // test hex_to_instruction()
   cout << "test hex_to_instruction(), last line is return value: \n" << hex_to_instruction("b0886000", "opcode") << "\n";
   cout << "test hex_to_instruction(), last line is return value: \n" << hex_to_instruction("b0980005", "regA") << "\n";

   initilize_reg_mem();

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
         cin >> regA >> regB >> imed;

         //Set the ENUM for the opcode
         currentOpcode = ADDI;

         cout << "RegA: " << regA << endl; //###   For Debugging Will Remove later  ###
         cout << "Imed: " << imed << endl;
         cout << "RegB: " << regB << endl;

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
