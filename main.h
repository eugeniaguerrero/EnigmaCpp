using namespace std;

int* get_configuration(string config_filename);
bool can_open_file(ifstream &in_stream);
bool is_num(string token);
bool valid_index(int index);
// specific checks for configuration files
void remove_whitespace(string &token);
bool valid_pb_file(string token);
bool valid_rot_file(string token);
bool valid_rf_file(string token);
string get_extension(string token);
bool contains(int elem, vector<int> numbers);
bool valid_plugboard_parameters(int size_of_config_array);
bool valid_rotor_mapping(int size_of_config_array);
bool valid_rotor_start_position(int index);
bool valid_reflector_parameters(int size_of_config_array);
