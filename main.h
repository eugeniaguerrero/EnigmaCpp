#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "errors.h"
#include "utils.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "enigmaMachine.h"

using namespace std;

string get_extension(string token);
void remove_whitespace(string &token);
bool is_num(string token);
bool valid_rotor_mapping(vector<int>);
bool contains_duplicates(vector<int> mappings);

#endif