// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: hawtdawg.cpp
// Purpose: implementation file for header file dawtdawg.h. It contains the definitions of all member functions of the class Hawt_dawg


#include <iostream>
#include "hawtdawg.h"

using namespace std;



// Description: constructor for Hawt_dawg, it takes all member variables except m_cost
// Pre: will execute only if it's called with this amount of argument and their respective types
// Post: assigns each argument value to the respect member variable, computes the price the hawt dawg and assigns it to m_cost
Hawt_dawg::Hawt_dawg(const int num_animals, const int ounce_onion, const int num_pickles, const bool contain_relish, const bool contain_cheese, const bool virulent_pathogen)
{
  m_num_animals = num_animals;
  m_ounce_onion = ounce_onion;
  m_num_pickles = num_pickles;
  m_contain_relish = contain_relish;
  m_contain_cheese = contain_cheese;
  m_virulent_pathogen = virulent_pathogen;

  if (m_contain_relish && m_contain_cheese)
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_RELISH)+(PRICE_BREAD)+(PRICE_CHEESE);
  else if (m_contain_relish && (!m_contain_cheese))
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_RELISH)+(PRICE_BREAD);
  else if ((!m_contain_relish) && m_contain_cheese)
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_BREAD)+(PRICE_CHEESE);
  else
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_BREAD);
}


// Description: default constructor for class Hawt_dawg. It assigns values to member variables randomly and computes the price that it assigns to m_cost
// Pre: has to be called without argument to be executed
// Post: assigns values to member variables randomly and computs the price of the hawt dawg, and assigns it to m_cost
Hawt_dawg::Hawt_dawg()
{
  int probability;

  m_num_animals = rand()%(MAX_ACCEPTABLE_VALUE + MIN_PROBABILITY);
  m_ounce_onion = rand()%(MAX_ACCEPTABLE_VALUE + MIN_PROBABILITY);
  m_num_pickles = rand()%(MAX_ACCEPTABLE_VALUE + MIN_PROBABILITY);

  probability = rand()%(MAX_PROBABILITY) + MIN_PROBABILITY;
  if (probability <= PROBABILITY_PATHOGEN)
    m_virulent_pathogen = true;
  else
    m_virulent_pathogen = false;

  probability = rand()%(MAX_PROBABILITY) + MIN_PROBABILITY;
  if (probability <= PROBABILITY_CHEESE_RELISH)
    m_contain_cheese = true;
  else
    m_contain_cheese = false;

  probability = rand()%(MAX_PROBABILITY) + MIN_PROBABILITY;
  if (probability <= PROBABILITY_CHEESE_RELISH)
    m_contain_relish = true;
  else
    m_contain_relish = false;

  if (m_contain_relish && m_contain_cheese)
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_RELISH)+(PRICE_BREAD)+(PRICE_CHEESE);
  else if (m_contain_relish && (!m_contain_cheese))
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_RELISH)+(PRICE_BREAD);
  else if ((!m_contain_relish) && m_contain_cheese)
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_BREAD)+(PRICE_CHEESE);
  else
    m_cost = (m_num_animals * PRICE_ANIMAL)+(m_ounce_onion*PRICE_ONION)+(m_num_pickles*PRICE_PICKLE)+(PRICE_BREAD);
}


// Description: gets and returns the cost of the hawt_dawg
// Pre: the calling object should exist in Hawt_dawg class
// Post: returns the m_cost, which is the cost of the hawt_dawg
float Hawt_dawg::get_cost()
{
  return m_cost;
}


// Description: gets and returns m_virulent_pathogen which is a boolean value for whether the hawt dawg contains a virulent pathogen
// Pre: the calling object should exist in Hawt_dawg class
// Post: returns m_virulent_pathogen
bool Hawt_dawg::get_pathogen()
{
  return m_virulent_pathogen;
}


// Description: overloads insertion operator by assigning values of member variables of Hawt_dawg class_object to os and returns os
// Pre: the calling object should be a member of ostream class
// Post: assigns values of member variables of Hawt_dawg class_object to os and returns it to be printed where it's called
ostream & operator << (ostream & os, const Hawt_dawg & class_object)
{
  os << "The hawt dawg contains:\n";
  os << class_object.m_num_animals << " animal(s)\n";
  os << class_object.m_ounce_onion << " ounce(s) of onions\n";
  os << class_object.m_num_pickles << " pickle(s)\n";
  if (class_object.m_contain_relish)
    os << "Relish\n";
  if (class_object.m_contain_cheese)
    os << "Cheese\n";
  os << "The cost of the hawt dawg is: " << class_object.m_cost << endl;
  return os;
} 

