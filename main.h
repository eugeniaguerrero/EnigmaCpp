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

int* get_configuration(string config_filename);
bool is_num(string token);
// specific checks for configuration files
void remove_whitespace(string &token);
bool valid_pb_file(string token);
bool valid_rot_file(string token);
bool valid_rf_file(string token);
string get_extension(string token);
bool valid_rotor_mapping(vector<int>);
bool contains_duplicates(vector<int> mappings);
void print_vector(vector<int> mappings);

#endif
