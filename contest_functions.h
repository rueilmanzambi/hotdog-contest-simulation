// Programmer: Rueil Manzambi                  Section: 109
// Data: April 21, 2021
// File: contest_functions.h
// Purpose: header file for implementation file contest_functions.cpp containing all the functions that not class members for homework 7



#ifndef CONTEST_FUNCTIONS_H
#define CONTEST_FUNCTIONS_H

#include <iostream>
#include <string>
#include "hawtdawg.h"
#include "hawtdawgmeister.h"
#include "customer.h"

using namespace std;


const short HEALTH_VALUE_CHANGE = 2;
const int NO_CONTESTANT = 0;
const int ONLY_ONE_BROKE_CONTESTANT = 1;
const int VOMIT_CHANCE = 50;
const int FIRST_FOOD_FIGHT_CHANCE = 70;
const int OTHER_FOOD_FIGHT_CHANCE = 80;
const short HALVE_HEALTH_VALUE = 2;
const string BARF_STATEMENT[] = {"GAGGGG! BLAJJJCCCH", "BARBARA STREISAND!!","BROBRIBA TUUUMMMMM","BRAADAAFRR AMAANA DDAMAADA","BROOIEL VIIIUUUAAAA"};
const int SIZE_BARF_STATEMENT = 5;
const int MEISTER_TARGET_INDEX = 15;
const float NO_MONEY = 0;
const int MIN_CONTESTANT = 2;




void start_contest(Hawt_dawg & dawg,Customer customer_array[], Hawtdawgmeister & meister);
bool at_least_two_contestants(Hawt_dawg & dawg, Customer customer_array[]);
bool does_he_die(Customer customer_array[], int i);
bool alive_contestant_but_broke(Customer customer_array[], int i);
bool can_eat(Hawt_dawg & dawg,Customer customer_array[],int i);
void decide_winner(Hawt_dawg & dawg, Customer customer_array[], Hawtdawgmeister & meister);
void eats_but_no_reaction_print(Customer customer_array[], int i, const bool alive);
void print_winner(Customer customer_array[], int i);
Hawt_dawg make_new_dawg();
void print_meister_final_money(Hawtdawgmeister & meister);
void eats_and_pukes (Hawt_dawg & dawg, Customer customer_array[], int i, Hawtdawgmeister & meister);
bool does_he_toss (const bool first, Hawt_dawg & dawg, Customer customer_array[], int i);
bool does_he_puke ();
string generate_barf();
void tosses_dawg(Hawt_dawg & dawg, Customer customer_array[], int i, Hawtdawgmeister & meister);
int random_toss_target_index();



#endif
