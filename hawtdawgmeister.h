// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: hawtdawgmeister.h
// Purpose: header file for implementation file hawtdawgmeister.cpp. It contains the definition of the class Hawtdawgmeister and the prototypes of all member functions


#ifndef HAWTDAWGMEISTER_H
#define HAWTDAWGMEISTER_H

#include <iostream>
#include <string>

using namespace std;


const float MEISTER_STARTING_CASH = 150.00;

class Hawtdawgmeister
{
  private:
    string m_name = "Cletus";
    float m_money;
    float m_starting_money;

  public:
    Hawtdawgmeister(const string name, const float cash);
    float operator += (const float money);
    float operator -= (const float money);
    string get_name();
    float get_money();
    float get_starting_money();

};




#endif
