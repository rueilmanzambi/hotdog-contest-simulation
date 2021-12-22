// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: contest_functions.cpp
// Purpose: Implemention file for header file contest_functions.h. It contains the definitions all functions that are not class members for homework 7


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "contest_functions.h"

using namespace std;


// Description: first non class member function to be called, it starts the contest and other functions to handle the result
// Pre: arguments objects are filled in main
// Post: returns nothing, it takes care of the contest and calls other functions to decide on the result
void start_contest(Hawt_dawg & dawg, Customer customer_array[], Hawtdawgmeister & meister)
{
  int round = 0;  
  bool still_competing;

  cout << "Begin the Contest!!!" << endl;  
  cout << "The Contestants are:" << endl << endl;
  cout << customer_array << endl;

  do
  { 

    if (at_least_two_contestants(dawg, customer_array)) // makes new dawg every round and checks if at least two contest with enough money and alive
      still_competing = true;
    else
      still_competing = false;

    round++;
    cout << "\n-------------------------- ROUND #" << round << " ---------------------------\n" << endl;

    cout << "Hawt dawg price: $" << dawg.get_cost() << "\n" <<endl;
         
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
      if (!customer_array[i].get_just_puked())// can't eat on same round if you puked
      {
        if (can_eat(dawg,customer_array,i))
        {
          customer_array[i].eat(dawg);
          customer_array[i] -= HEALTH_VALUE_CHANGE;
          meister += dawg.get_cost();
          if (customer_array[i].get_money() < NO_MONEY)
            customer_array[i].change_money(NO_MONEY);// NO_MONEY = $0.00
          
          if (customer_array[i].get_health_value() <= HEALTH_DEAD)
          {
            customer_array[i].change_alive(false);
            customer_array[i].change_health_to_death_value();//change to 0
            eats_but_no_reaction_print(customer_array, i, false);
          }
          else
          {
            if (dawg.get_pathogen())//checks for pathogen
            {
              if (does_he_die(customer_array, i))
              {
                customer_array[i].change_alive(false);
                customer_array[i].change_health_to_death_value();
                eats_but_no_reaction_print(customer_array, i, false);
              }
              else
                eats_and_pukes (dawg, customer_array, i, meister);
            }
            else
              eats_but_no_reaction_print(customer_array, i, true);
          }
        }
      }
      else
        customer_array[i].change_just_puked(false);
    }
  } while (still_competing); 
  decide_winner(dawg, customer_array, meister);
  print_meister_final_money(meister);  

  return;
}

// Description: It makes a new hawtdawg and returns it. It's called at the start of every round;
// Pre: None
// Post: returns the new dawg
Hawt_dawg make_new_dawg()
{
  Hawt_dawg dawg;
  return dawg;
}


// Description: makes new dawg by reference, checks if there are at least two contestants that are alive 
//              and capable of buying the hawtdawg and returns a bool value according to the result
// Pre: dawg has to be passed by reference to so that we have the same dawg object in the whole program
// Post: makes a new dawg, returns true if it finds at least two contestants that are able to buy the new dawg and are alive, 
//       returns false otherwise 
bool at_least_two_contestants(Hawt_dawg & dawg, Customer customer_array[])
{
  bool return_value;
  int num_people = 0;
  dawg = make_new_dawg();

  for (int i = 0; i < NUM_CUSTOMERS; i++)
  {
    bool can_buy = customer_array[i].get_money() >= dawg.get_cost();
    if (customer_array[i].get_alive() && (!customer_array[i].get_angered_meister()) && can_buy)
      num_people++;
  }
  if (num_people >= MIN_CONTESTANT)
    return_value = true;
  else
    return_value = false;
    
  return return_value;
} 


// Description: checks if the customer with the index of the passed int argument i can eat
//              returns true if he can, returns false otherwise
// Pre: arguments objects already have values prior to function call
// Post: returns true if customer with the index of the passed int argument i can eat
//       returns false otherwise
bool can_eat(Hawt_dawg & dawg, Customer customer_array[],int i)
{
  bool return_value;
  bool can_buy = customer_array[i].get_money() >= dawg.get_cost();

  if (customer_array[i].get_alive() && (!customer_array[i].get_angered_meister()) && can_buy)
    return_value = true;
  else
    return_value = false;

  return return_value;
}


// Description: determines if the contestant with index i dies based on a random number generator. If the generated number is 
//              greater than his health value, then he dies and returns true, otherwise, he lives and returns false
// Pre: the m_health_value of the contestant has to have value
// Post: returns true if the contestant dies, returns false otherwise
bool does_he_die(Customer customer_array[], int i)
{
  bool return_value;
  int rand_num;
  rand_num = rand()%(MAX_PROBABILITY + MIN_PROBABILITY);
  if(rand_num > customer_array[i].get_health_value())
    return_value = true;
  else
    return_value = false;
  return return_value;  
}


// Description: ckecks if the customer with index i is alive, is still a contestant. This function is called when there isn't
//              contestant who can afford the dawg in a round
// Pre: No one shoulb be able to afford the dawg for this function to return the right answer
// Post: returns true if the customer wih index i is alive and still a contestant
//       returns false otherwise 
bool alive_contestant_but_broke(Customer customer_array[], int i)
{
  bool return_value;
  if (customer_array[i].get_money() < NO_MONEY)
    customer_array[i].change_money(NO_MONEY);
  if (customer_array[i].get_alive() && (!customer_array[i].get_angered_meister()))
    return_value = true;
  else
    return_value = false;
  return return_value;
}


// Description: This function is called when there aren't at least two contestants that can eat anymore. it checks and decides who win(s)
//              it calls another function to print the information of the winner(s), only meister is printed here if he wins
// Pre: at most one person has to be able to eat the dawg for this function to execute accurately
// Post: decides who the winner(s) is or are, calls other other functions to print them, only meister is printed here if he wins
void decide_winner(Hawt_dawg & dawg, Customer customer_array[], Hawtdawgmeister & meister)
{
  int num_with_max_health = 0;
  short max_health = 0;
  int num_finalists = 0;
  bool found_winner = false;

  for (int i = 0; i < NUM_CUSTOMERS; i++)
  {
    if (can_eat(dawg, customer_array,i))// can only be true once, because at most 1 person can eat
    {
      cout << "\n....The winner is....:\n";
      print_winner(customer_array, i);
      found_winner = true;
    }
  }
  if (!found_winner) // if no one can eat, we find alive contestans that are broke
  {
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
      if (alive_contestant_but_broke(customer_array, i))
        num_finalists++;
    }
    if (num_finalists <= NO_CONTESTANT)
    {
      cout << "\nThere are no more contestants that are alive. The contest is over!" << endl; 
      cout << meister.get_name() << " is the winner!" << endl;
    }
    else
    {
      for (int i = 0; i < NUM_CUSTOMERS; i++)
      {
        if (alive_contestant_but_broke(customer_array,i))
        {
          if (customer_array[i].get_health_value() > max_health)
            max_health = customer_array[i].get_health_value();
        }
      }
      for (int i = 0; i < NUM_CUSTOMERS; i++)
      {
        if (alive_contestant_but_broke(customer_array,i))
        {
          if (customer_array[i].get_health_value() == max_health)// number of broke contestants with the highest health value
            num_with_max_health++;
        }
      }

      if (num_with_max_health == ONLY_ONE_BROKE_CONTESTANT)
      {
        for (int i = 0; i < NUM_CUSTOMERS; i++)
        {
          if (alive_contestant_but_broke(customer_array,i))
          {
            if (customer_array[i].get_health_value() == max_health)
            {
              cout << "\nThere are no more contestants that can afford to buy a hawt dawg." << endl;
              cout << "The winner is the contestant with the highest health value." << endl;
              cout << "....And that is...:"<<endl;
              print_winner(customer_array, i);
            }
          }
        }
      }
      else // more than one broke contestant with the same highest health value
      {
        cout << "\nThere are no more contestants that can afford to buy a hawt dawg." <<endl;
        cout << "The winner is the contestant with the highest health value." << endl;
        cout << "In this case, we have more than one person with the same highest health value, so they are all winners!" << endl;
        cout << "....And they are....: " << endl;
        for (int i = 0; i < NUM_CUSTOMERS; i++)
        {
          if (alive_contestant_but_broke(customer_array,i))
          {
            if (customer_array[i].get_health_value() == max_health)
              print_winner(customer_array, i);
          }
        }
      }
    }
  }

return;
}


// Description: prints the attributes of the contestant with index i, prints ALIVE if argument alive is true
//              or print DEAD otherwise
// Pre: the customer attributes are already filled prior to the function call
// Post: prints the attributes of the contestant with index i, prints ALIVE if argument alive is true
//       or prints DEAD otherwise
void eats_but_no_reaction_print(Customer customer_array[], int i, const bool alive)
{
  cout << "    " << customer_array[i].get_name() << " eats a dawg wt " << customer_array[i].get_weight() << ", ";
  cout << "health value " << customer_array[i].get_health_value() << ", $"<< customer_array[i].get_money() << " left ... ";
  (alive)?cout <<"ALIVE":cout << "DEAD";
  cout << endl;

  return;
}

// Description: prints the attributes of the contestant with index i
// Pre: the customer attributes are already filled prior to the function call
// Post: prints attributes of the contestant with index i
void print_winner(Customer customer_array[], int i)
{
  cout << customer_array[i].get_name() << " " << customer_array[i].get_weight() << " lbs, has ";
  cout << customer_array[i].get_health_value() << " health value" << " and $" << customer_array[i].get_money() << " left." << endl;

  return;
}

// Description: prints the financial situation of meister at the end of the game
// Pre: the function has to be called at the end of the game for an accurate result
// Post: prints the financial situation of meister at the end of the game
void print_meister_final_money(Hawtdawgmeister & meister)
{
  cout << "\n" << meister.get_name() << " made $" << meister.get_money() - meister.get_starting_money() << "!" << endl;
  cout << "He now has $" << meister.get_money() << "!" << endl;

  return;
}

// Description: it's called when a customer eats and pukes, it takes care of the chain reaction that might happen as a result of vomiting
// Pre: the contestant is not dead, but only vomits
// Post: checks if other contestants in the chain reaction decide to toss the dawg or vomit or don't react at all
void eats_and_pukes (Hawt_dawg & dawg, Customer customer_array[], int i, Hawtdawgmeister & meister)
{
  bool finish_puke = false;

  cout << "    " << customer_array[i].get_name() << " eats a dawg wt " << customer_array[i].get_weight() << ", ";
  cout << "health value " << customer_array[i].get_health_value() << ", $" << customer_array[i].get_money()<< " left ... ALIVE AND BARFS!" << endl;

  customer_array[i] /= HALVE_HEALTH_VALUE;

  for (int j = i+1; j < NUM_CUSTOMERS; j++) // walks down the array
  {
    if (!finish_puke)
    {
      if (customer_array[j].get_alive())
      {
        if (does_he_puke())
        {
          customer_array[j].change_just_puked(true); 
          cout << "        " << customer_array[j].get_name() << " barfs " << generate_barf() << endl;
          customer_array[j] /= HALVE_HEALTH_VALUE;
        }
        else
        {
          if (does_he_toss(true, dawg, customer_array, j)) // true is for whether the contestant is the first to start tossing dawg
          {
            cout << "        " << customer_array[j].get_name() << " doesn't barf" << endl;
            tosses_dawg(dawg, customer_array, j, meister);
          }
          else // no reaction
          {
            cout << "        " << customer_array[j].get_name() << " doesn't barf" << endl;
            finish_puke = true;
          } 
        }
      }
      else
        finish_puke = true;
    }
  }

  if (!finish_puke) // walks up the array
  {
    for (int j = i-1; j >= 0; j--)        // same code  as walking down //
    {
      if (!finish_puke)
      {
        if (customer_array[j].get_alive())
        {
          if (does_he_puke())
          {
            customer_array[j].change_just_puked(true);
            cout << "        " << customer_array[j].get_name() << " barfs " << generate_barf() << endl;
            customer_array[j] /= HALVE_HEALTH_VALUE;
          }
          else
          {
            if (does_he_toss(true, dawg, customer_array, j))
            {
              cout << "        " << customer_array[j].get_name() << " doesn't barf" << endl;
              tosses_dawg(dawg, customer_array, j, meister);
            }
            else
            {
              cout << "        " << customer_array[j].get_name() << " doesn't barf" << endl;
              finish_puke = true;
            }
          }
        }
        else
          finish_puke = true;
      }
    }
  }

  return;
}


// Description: it's called to determine if a contestant pukes. it generates a random number and returns false
//              if the number is greater than to probability of vomiting, returns false otherwise
// Pre: make sure the constants have the right values for a good execution
// Post: returns false if random number is greater than the probability of vomiting, returns false otherwise
bool does_he_puke ()
{
  bool return_value;
  int rand_num = rand()%(MAX_PROBABILITY) + MIN_PROBABILITY;
  if (rand_num > VOMIT_CHANCE)
    return_value = false;
  else
    return_value = true;

  return return_value;
}


// Description: generates a barfing statement taken from the array BARF_STATEMENT with an index generated as a random number
// Pre: make sure SIZE_BARF_STATEMENT is the size the array BARF_STATEMENT for this function to execute correctly
// Post: generates and returns a barfing statement taken from the array BARF_STATEMENT with an index generated as a random number
string generate_barf ()
{
  string barf;
  int rand_num = rand()%SIZE_BARF_STATEMENT;
  barf = BARF_STATEMENT[rand_num];
  return barf;
}


// Description: determines if the contestant with index i decides to toss the dawg, based on a random number generation
//              returns false if the random number is greater than the probability of tossing for the first time or for 
//              other contestants in the chain reaction or if contestant cannot afford to toss, returns true otherwise
// Pre: argument first is only true when the contestant is the first one to initiate a food fight, the function would
//      execute correctly if this is repected
// Post: returns false if the random number is greater than the probability of tossing for the first time or for other
//        other contestants in the chain reaction or if a contestant cannot afford to toss, returns true otherwise
bool does_he_toss(const bool first, Hawt_dawg & dawg, Customer customer_array[], int i)
{
  bool return_value;

  int rand_num = rand()%(MAX_PROBABILITY) + MIN_PROBABILITY;
  if (first) // only if contestant is the first to initiate a food fight
  {
    if (rand_num > FIRST_FOOD_FIGHT_CHANCE)
      return_value = false;
    else
      return_value = true;
  }
  else
  {
    if (rand_num > OTHER_FOOD_FIGHT_CHANCE)
      return_value = false;
    else
    {
      if (customer_array[i].get_money() >= dawg.get_cost())
        return_value = true;
      else
        return_value = false;
    }
  }
  return return_value;
}


// Description: takes care of the food fight chain reaction
// Pre: the contestant at index i has to start tossing for this function to be called
// Post: takes care of the food fight chain reaction
void tosses_dawg(Hawt_dawg & dawg, Customer customer_array[], int i, Hawtdawgmeister & meister)
{
  bool still_tossing = true;
  bool first_cycle = true;
  int toss_index;
  int new_toss_index;
  

  while (still_tossing)
  {
    if (first_cycle) // if contestant is the first to start the food fight
    {
      new_toss_index = random_toss_target_index();
      first_cycle = false;
      toss_index = i;
      cout << "            " << customer_array[toss_index].get_name() << " tosses dawg at ";
      (new_toss_index == MEISTER_TARGET_INDEX)?cout << meister.get_name():cout << customer_array[new_toss_index].get_name();
      cout << endl;
      customer_array[toss_index] += HEALTH_VALUE_CHANGE;
      customer_array[toss_index] -= dawg.get_cost();
    }
    else
    {
      if (still_tossing)
      {
        if (customer_array[toss_index].get_alive())
        {
          if (does_he_toss(false, dawg, customer_array, toss_index)) // argument false because contestant is not the first to start the food fight
          {
            new_toss_index = random_toss_target_index();
            cout << "            " << customer_array[toss_index].get_name() << " tosses dawg at ";
            (new_toss_index == MEISTER_TARGET_INDEX)?cout << meister.get_name():cout << customer_array[new_toss_index].get_name();
            cout << endl;
            customer_array[toss_index] += HEALTH_VALUE_CHANGE;
            customer_array[toss_index] -= dawg.get_cost();
          }
          else
            still_tossing = false; // someone decides not to toss
        }
        else
          still_tossing = false;// to make sure we have no dead contestant in the food fight
      }
    }
    if (new_toss_index == MEISTER_TARGET_INDEX) // food fight stops if meister is hit
    {
      customer_array[toss_index].change_angered_meister(true);
      meister += customer_array[toss_index].get_money();
      customer_array[toss_index].change_money(NO_MONEY);
      still_tossing = false;
    }
    else
    {
      if (!customer_array[new_toss_index].get_alive()) // food fight stops if a dead contest is hit
        still_tossing = false;
    }
    toss_index = new_toss_index; 
  }
  return;
}


// Description: generates a random number from 0 to NUM_CUSTOMERS + 1, inclusive and returns it
// Pre: None
// Post: generates a random number from 0 to NUM_CUSTOMERS + 1 inclusive and returns it
int random_toss_target_index()
{
  int value;
  value = rand()%(NUM_CUSTOMERS + 1);
  return value;
}
