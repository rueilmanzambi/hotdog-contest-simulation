// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: customer.h
// Purpose: header file for implementation file customer.cpp. It contains the definition of class Customer and prototypes of all member functions


#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "hawtdawg.h"

using namespace std;


const int MIN_CASH = 25;
const int MAX_CASH = 75;
const int MIN_WEIGHT = 70;
const int MAX_WEIGHT = 300;
const short MIN_HEALTH = 1;
const short MAX_HEALTH = 100;
const int WEIGHT_INCREMENT = 4;
const int NUM_CUSTOMERS = 15;
const short HEALTH_DEAD = 0;

class Customer
{
  private:
    string m_name;
    float m_cash_money;
    short m_health_value;
    int m_weight;
    bool m_alive;
    bool m_angered_meister;
    bool m_just_puked;

  public:
    Customer();
    void eat(Hawt_dawg & object);  
    string get_name();
    float get_money();
    short get_health_value();
    int get_weight();
    bool get_alive();
    bool get_angered_meister();
    void change_alive(const bool value);
    void change_health_to_death_value();
    void change_angered_meister(const bool value);
    void change_money(const float money);
    float operator -= (const float money);
    short operator += (const short health_value);
    short operator -= (const short health_value); 
    short operator /= (const short health_value);
    friend ostream & operator << (ostream & os, Customer customer_array[]);
    bool get_just_puked ();
    void change_just_puked (const bool value);
};



#endif
