#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
   vector<string> msg {"Hello", "World", "For", "CSE661/CSI655", "and Homework 2!"};

   for (const string& word : msg)
   {
      cout << word << " ";
   }
   cout << endl;
}