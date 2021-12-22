// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: main.cpp
// Purpose: main file for homework 7. It simulates a hawt dawg eating contest in which contestants eat a new hawt dawg in every round.
//          Sometimes, the hawt dawg contains a virulent pathogen which can trigger a chain of reactions. The contest ends when there's
//          only one contestant left, or if they are all dead, or if no one can afford to buy a hawt dawg. The meister wins when everyone is dead
//          and contestant(s) with the highest health value win(s) if no one can afford to buy a hawt dawg.


#include <iostream>
#include "contest_functions.h"

using namespace std;


int main()
{
  srand(time(0));

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  cout << "\t\t\tWelcome to the opening of Cletu's Famous Road Kill Cafe" << endl;
  cout << "\t\t\t-------------------------------------------------------" << endl;
  
  Customer customer_array[NUM_CUSTOMERS];
  Hawt_dawg dawg;
  Hawtdawgmeister meister("Cletus", MEISTER_STARTING_CASH);
  
  start_contest(dawg, customer_array, meister);  

  cout << "\nThank You for participating....Hope to see you soon!\n" << endl;

  return 0;
}
