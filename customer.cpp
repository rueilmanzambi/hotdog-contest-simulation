// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: customer.cpp
// Purpose: implementation file for header file customer.h containing class customer with member functions prototypes


#include <iostream>
#include "customer.h"
#include "hawtdawg.h"

using namespace std;



// Description: default constructor for class Customer. It assigns the values to member variables. 
//              Their names are taken from a file and other members are generated randomly or initialized
// Pre: The file containing the names has to be in the same directory as this file
// Post: Assigns values to member variables
Customer::Customer()
{
  int total_data = 0;
  static int current_num_data = 1;
  string customer_name;
  string walk_thru_file;

  ifstream fin;
  fin.open("names.dat");

  while(fin >> walk_thru_file)
    total_data++;

  fin.clear();
  fin.seekg(0);

  if (current_num_data <= total_data)
  {
    for (int i=0; i<current_num_data; i++)
      fin >> customer_name;
    current_num_data++;
  }
  else // if we are at the last name in the file
  {
    current_num_data = 1;
    for (int i=0; i<current_num_data; i++)
      fin >> customer_name;
    current_num_data++;
  }

  fin.close();

  m_name = customer_name;
  m_cash_money = rand() % (MAX_CASH - MIN_CASH) + MIN_CASH;
  m_weight = rand()%(MAX_WEIGHT - MIN_WEIGHT) + MIN_WEIGHT;
  m_alive = true;
  m_health_value = rand()%(MAX_HEALTH - MIN_HEALTH) + MIN_HEALTH;
  m_angered_meister = false;
  m_just_puked = false;
}


// Description: it's called when the customer eats the Hawt_dawg object
// Pre: the Hawt_dawg object is defined in another file and that file shoulb be include in this program
// Post: substract customer's money with the price of object and adds weight
void Customer::eat(Hawt_dawg & object)
{
  m_cash_money -= object.get_cost();
  m_weight += WEIGHT_INCREMENT;
}


// Description: gets and returns the name of the customer
// Pre: the calling object should exist in the customer class
// Post: returns the customer's name
string Customer:: get_name()
{
  string name = m_name;
  return name;
}


// Description: gets and returns the amount of money that the customer has
// Pre: the calling object should exist in the customer class
// Post: returns the amount of money that the customer has
float Customer::get_money()
{
  float money = m_cash_money;
  return money;
}


// Description: gets and returns the health value of the customer
// Pre: the calling object should exist in the customer class
// Post: returns the heatlh value of the customer
short Customer::get_health_value()
{
  short value = m_health_value;
  return value;
}


// Description: sets the customer's health value to HEALTH_DEAD
// Pre: the calling object should exist in the customer class
// Post: sets the customer's health value to HEALTH_DEAD 
void Customer::change_health_to_death_value()
{
  m_health_value = HEALTH_DEAD;
  return;
}


// Description: gets and returns the customer's weight
// Pre: the calling object should exist in the customer class
// Post: returns the customer's weight
int Customer::get_weight()
{
  int weight = m_weight;
  return weight;
}


// Description: gets and returns value of m_alive which determines if the customer is alive or not
// Pre: the calling object should exist in the customer class
// Post: returns the value of m_alive which determines if the customer is alive or not
bool Customer::get_alive()
{
  bool alive = m_alive;
  return alive;
}


// Description: gets and returns the value m_angered_meister which is a bool value on whether the customer angered the meister
// Pre: the calling object should exist in the customer class
// Post: returns the value of m_angered_meister
bool Customer::get_angered_meister()
{
  bool value = m_angered_meister;
  return value;
}

// Description: sets m_alive to the passed boolean value
// Pre: the calling object should exist in the customer class
// Post: sets m_alive to the passed boolean value
void Customer::change_alive(const bool value)
{
  m_alive = value;
  return;
}


// Description: sets m_angered_meister to the passed boolean value
// Pre: the calling object should exist in customer class
// Post: sets m_angered_meister to the passed boolean value
void Customer::change_angered_meister(const bool value)
{
  m_angered_meister = value;
  return;
}


// Description: sets m_cash_money to the passed floating value
// Pre: the calling object should exist in customer class
// Post: sets m_cash_money to the passed floating value
void Customer::change_money(const float money)
{
  m_cash_money = money;
  return;
}


// Description: overloads operator -= which decrements m_cash_money by the value of passed argument money
// Pre: the calling object should exist in customer class
// Post: decrements m_cash_money by the value of passed argument money and returns the result
float Customer::operator -= (const float money)
{
  m_cash_money -=  money;
  return m_cash_money;
}


// Description: overloads operator += which increments m_health_value by the value of passed argument health_value
// Pre: the calling object should exist in customer class
// Post: increments m_health_value by the value of passed argument health_value and returns the result
short Customer::operator += (const short health_value)
{
  m_health_value += health_value;
  return m_health_value;
}


// Description: overloads operator -= which decrements m_health_value by the value of passed argument health_value
// Pre: the calling object should exist in customer class
// Post: decrements m_health_value by the value of passed argument health_value and returns the result
short Customer::operator -= (const short health_value)
{
  m_health_value -= health_value;
  return m_health_value;
}


// Description: overloads operator /= which divides m_health_value by the the value of passed argument health_value
// Pre: the calling object should exist in customer class
// Post: divides m_health_value by the value of passed argument health_value and returns the result
short Customer::operator /= (const short health_value)
{
  m_health_value /= health_value;
  return m_health_value;
}


// Description: gets and returns the value of m_just_puked which is bool whether the customer just puked
// Pre: the calling object should exist in customer class
// Post: returns the value of m_just_puked
bool Customer::get_just_puked ()
{
  return m_just_puked;
}


// Description: sets the value of m_just_puked to the passed boolean value 
// Pre: the calling object should exist in customer class
// Post: sets the value of m_just_puked to the passed boolean value
void Customer::change_just_puked (const bool value)
{
  m_just_puked = value;
  return;
}


// Description: overloads insertion operator by assigning values of member variables for every element of customer_array[] to os and returns it
// Pre: calling oject has to be member of ostream class
// Post: assigns information about every element of customer_array[] to os and returns os to be printed where it's called
ostream & operator << (ostream & os,Customer customer_array[])
{
  for (int i = 0; i < NUM_CUSTOMERS; i++)
  {
    os << "    " << customer_array[i].get_name() << " " << customer_array[i].get_weight() << " lbs, has ";
    os << customer_array[i].get_health_value() << " health value" << " and $" << customer_array[i].get_money() << "." << endl; 
  }
  return os;
}
