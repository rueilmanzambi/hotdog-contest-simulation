// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: hawtdawgmeister.cpp
// Purpose: implementation file for header file hawtdawgmeister.h. It contains the functions defintions of all member functions of class Hawtdawgmeister


#include <iostream>
#include "hawtdawgmeister.h"

using namespace std;


// Description: constructor for class Hawtdawgmeister, it's called at the beginning of the contest
// Pre: it has to be passed these two arguments for it to be executed
// Post: assigns each argument to the respective name and assigns m_starting_money to m_money 
Hawtdawgmeister::Hawtdawgmeister(const string name, const float cash)
{
  m_name = name;
  m_money = cash;
  m_starting_money = m_money;
}


// Description: overloads operator += which increments m_money by the passed floating value money
// Pre: the calling object should exist in Hawtdawgmeister class
// Post: increments m_money by the passed floating value money and returns the result
float Hawtdawgmeister::operator += (const float money)
{
  m_money += money;
  return m_money;
}


// Description: overloads operator -= which decrements m_money by the passed floating value money
// Pre: the calling object should exist in Hawtdawgmeister class
// Post: increments m_money by the passed floating value money and returns the result
float Hawtdawgmeister::operator -= (const float money)
{
  m_money -= money;
  return m_money;
}


// Description: gets and returns the name of calling object
// Pre: the calling object should exist in Hawtdawgmeister class
// Post: returns the name of calling object
string Hawtdawgmeister::get_name()
{
  return m_name;
}


// Description: gets and returns the amount of money that the calling object has
// Pre: the calling object should exist in Hawtdawgmeister class
// Post: returns the amount of money that the calling object has
float Hawtdawgmeister::get_money()
{
  return m_money;
}


// Description: gets and returns the amount of the starting money of the calling object
// Pre: the calling object should exist in Hawtdawgmeister class
// Post: returns the amount of the starting money of the calling object
float Hawtdawgmeister::get_starting_money()
{
  return m_starting_money;
}

