#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <iomanip>

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

int regIndexA, regIndexB, regIndexC, valB, valC, valA, result, regImed;

void print_reg_print_mem(){

   cout << "\n ################################## \n";
   cout << "\n Registers: \n";
   for (int i = 0; i< 32; i++){

         cout << "r" << i << ": " << register_set[i] << " ";
   }

   cout << "\n Memory: \n";
   for (int i = 0; i< 200; i++){

         cout << "[" << i << "]: " << program_memory[i] << " ";
   }

   cout << "\n ################################## \n";
}

// converts decimal string to hex string (8 digits)
string dec_to_hex(string str_decimal) {
   
   stringstream ss;  //create string stream object
   string str_hex;   //initialize string to store hex

   // convert string to decimal to hex, then output hex to ss object w/ 8 digits
   ss << "0x" << setfill('0') << setw(8) << right << hex << stoi(str_decimal);
   str_hex = ss.str();
   ss.str("");
   //cout << "dec: " << str_decimal << " hex: " << str_hex << "\n";
   return str_hex;
}

// converts hex string to decimal string
string hex_to_dec(string str_hex) {

   string str_dec = to_string(stoi(str_hex.substr(2), nullptr, 16));
   //cout << "hex: " << str_hex << " dec: " << str_dec << "\n";
   return str_dec;
}

//Generic opcode function runs the function value called for
void generic_function(string opcode, string regA, string regB, string regC, string imed, string offset, string ptr){

   switch(currentOpcode){
      case ADD:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex
         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex

         result = valB + valA;
         
         register_set[regIndexC] = dec_to_hex(to_string(result)); //convert to hex before storing in register

         cout << "ADD: " << register_set[regIndexA] << " + " << register_set[regIndexB] << " = " << result << " stored in " << regC << "\n";
         
         }
         break;
      case ADDI:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regImed = stoi(imed); //extract register number from regC and remove 'r'

         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex
         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex

         result = valA + regImed;
         
         register_set[regIndexB] = dec_to_hex(to_string(result)); //convert to hex before storing in register

         cout << "ADDI: " << register_set[regIndexA] << " + " << regImed << " = " << result << " stored in " << regB << "\n";

         }
         break;
      case SUB:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex
         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex

         result = valA - valB;
         
         register_set[regIndexC] = dec_to_hex(to_string(result)); //convert to hex before storing in register

         cout << "SUB: " << register_set[regIndexA] << " - " << register_set[regIndexB] << " = " << result << " stored in " << regC << "\n";

         }
         break;
      case MULT:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex
         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex

         result = valB * valA;

         register_set[regIndexC] = dec_to_hex(to_string(result)); //convert to hex before storing in register

         cout << "MULT: " << register_set[regIndexA] << " * " << register_set[regIndexB] << " = " << result << " stored in " << regC << "\n";

         }
         break;
      case LES:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex
         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex

         bool comp = false;

         if (valA < valB) comp = true;
         
         register_set[regIndexC] = dec_to_hex(to_string(comp)); //convert to hex before storing in register

         cout << "LES: " << register_set[regIndexA] << " < " << register_set[regIndexB] << " = " << comp << " stored in " << regC << "\n";

         }
         break;
      case EQL:
         {
         regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
         regIndexB = stoi(regB.substr(1)); //extract register number from regB and remove 'r'
         regIndexC = stoi(regC.substr(1)); //extract register number from regC and remove 'r'

         valA = stoi(hex_to_dec(register_set[regIndexA])); //assume contents of register_set are in hex
         valB = stoi(hex_to_dec(register_set[regIndexB])); //assume contents of register_set are in hex

         bool comp = false;

         if (valA == valB) comp = true;

         register_set[regIndexC] = dec_to_hex(to_string(comp)); //convert to hex before storing in register

         cout << "EQL: " << register_set[regIndexA] << " == " << register_set[regIndexB] << " = " << comp << " stored in " << regC << "\n";

         }
         break;
      case LW:
         {
            regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
            int ptrIndex = stoi(ptr.substr(1)); //gets the register index for the pointer and removes 'r'
            int offsetValue = stoi(offset); //parse the offset value

            //calculate the effective address by adding base register value and offset
            int address = stoi(hex_to_dec(register_set[ptrIndex])) + offsetValue; //assume contents of register_set are in hex

            if (address >= 0 && address < 200) { //if the address is greater than or equal to 0 and less than 200, the declared memory size
               register_set[regIndexA] = program_memory[address]; 
              cout << "Loaded value " << register_set[regIndexA] << " from " << program_memory[address]
                  << " into register " << regA << "\n";  //stores the value from regA in the calculated memory address
            } else {
               cerr << "Error: memory access out of bounds.\n";// else if it's out of bounds
            }
         }
         break;
      case SW:{
            regIndexA = stoi(regA.substr(1)); //extract register number from regA and remove 'r'
            int ptrIndex = stoi(ptr.substr(1)); //gets the register index for the pointer and removes 'r'
            int offsetValue = stoi(offset); //parse the offset value

            //calculate the effective address by adding base register value and offset
            int address = stoi(hex_to_dec(register_set[ptrIndex])) + offsetValue; //assume contents of register_set are in hex

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
         program_running = false; //set the main loop to false to stop the program
         cout << "Program halted.\n";
      }
         break;
      case NOP:{
         cout << "No operation performed.\n";
      }
         break;
      case DEFAULT:
         //Do nothing here
         break;
   }

   print_reg_print_mem();

}

void initilize_reg_mem(){

   for (int i = 0; i < 32; i++){
      register_set[i] = "0x00000000";
   }

   for (int i = 0; i < 200; i++){
      program_memory[i] = "0x00000000";
   }
}

// Outputs and returns instruction format in 8 digit hex: OPCODE(4 bits) + Register(5 bits) + Register(5 bits) + Register(5 bits) + Extra(13 bits)
// regC, imed, offset, ptr are optional parameters, default value = 0.
auto instruction_to_hex(string opcode, string regA, string regB, string regC = "0", string imed = "0", string offset = "0", string ptr = "0") {

   // if an offset or ptr value exists, value of imed = offset, value of regB = ptr
   if (stoi(offset) != 0) {
      imed = offset;
   }

   if (stoi(ptr.substr(1)) != 0) {
      regB = ptr;
   }
   
   // convert input values to binary
   bitset<4> op{(unsigned int)stoi((opcode))};           // store 4 bits for opcode
   bitset<5> rA{(unsigned int)stoi(regA.substr(1))};     // store 5 bits for register A, can be registers 0-31 (00000-11111) in memory
   bitset<5> rB{(unsigned int)stoi(regB.substr(1))};     // same as register A
   bitset<5> rC{(unsigned int)stoi(regC.substr(1))};     // same as register A
   bitset<13> im{(unsigned int)stoi(imed)};                            // store 13 bits for immediate;

   string instruct_string{op.to_string() + rA.to_string() + rB.to_string() + rC.to_string() + im.to_string()};
   stringstream ss; // create string stream object
   string result{}; // initalize string to store result

   // for every four characters in instruct_string (aka 4 bits)...
   for (int i = 0; i < instruct_string.length(); i = i + 4) {

      // convert 4-bits to decimal (unsigned int), then decimal to hex, then store in string stream object
      ss << hex << (bitset<4> {instruct_string.substr(i, 4)}).to_ulong() << "\n";
      
      result += ss.str();  // convert string stream object to string, append to result string

      // remove new line at end of string
      if (!result.empty() && result[result.length()-1] == '\n') {
         result.erase(result.length()-1);
      }   

      // remove contents of string string object in prep for next 4-bit to hex conversion
      ss.str("");
   }
   string str_hex = "0x" + result;
   cout << "Instruction Format: \n" << str_hex << "\n";
   cout << "\n ################################## \n";
   return str_hex; // return the hex string as 0x00000000
}

int main()
{
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
      string opcode = "00000000"; //Operation code used to determine which function is being called
      string regA = "00000000"; //Register A the first register
      string regB = "00000000"; //Register B the second register
      string regC = "00000000"; //Register C the third register
      string imed = "00000000"; //Imediate value
      string offset = "00000000"; //Offset Value used in lw/sw for offset from a pointer
      string ptr = "00000000"; //Pointer value for a memory location used in lw/sw
      
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
      instruction_to_hex(to_string(currentOpcode), regA, regB, regC, imed, offset, ptr);

      //The program running until halt
      //Current opcode set to default to prep for next loop
      currentOpcode = DEFAULT;


      //program_running = 0;  //###   For Debugging Will Remove later  ###

   }
}
