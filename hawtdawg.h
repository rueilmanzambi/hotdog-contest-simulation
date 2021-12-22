// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: hawtdawg.h
// Purpose: header file for implementation hawtdawg.cpp. It contains the definition of the class Hawt_dawg and the prototypes of all member functions



#ifndef HAWTDAWG_H
#define HAWTDAWG_H

#include <iostream>
#include  <string>
#include <cstdlib>
#include <ctime>

using namespace std;


const int MAX_ACCEPTABLE_VALUE = 4;
const int PROBABILITY_PATHOGEN = 10;
const int PROBABILITY_CHEESE_RELISH = 50;
const int MAX_PROBABILITY = 100;
const int MIN_PROBABILITY = 1;
const float PRICE_ANIMAL = 0.75;
const float PRICE_ONION = 0.5;
const float PRICE_PICKLE = 0.25;
const float PRICE_BREAD = 0.5;
const float PRICE_RELISH = 0.25;
const float PRICE_CHEESE = 0.5;


class Hawt_dawg
{
  private:
    int m_num_animals;
    int m_ounce_onion;
    int m_num_pickles;
    bool m_contain_relish;
    bool m_contain_cheese;
    bool m_virulent_pathogen;
    float m_cost;

  public:
    Hawt_dawg(const int num_animals, const int ounce_onion, const int num_pickles, const bool contain_relish, const bool contain_cheese, const bool virulent_pathogen);
    Hawt_dawg();
    float get_cost();
    bool get_pathogen();
    friend ostream & operator << (ostream & os, const Hawt_dawg & class_object);       
   
};


#endif
