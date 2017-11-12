using namespace std;

int* get_configuration(string config_filename);
bool can_open_file(ifstream &in_stream);
bool is_num(string token);
bool valid_index(string token);
// specific checks for configuration files
bool valid_pb_file(string token);
bool valid_rot_file(string token);
bool valid_rf_file(string token);
string get_extension(string token);
bool contains(int elem, int (&array)[26], int array_size);
bool valid_plugboard_parameters(int size_of_config_array);
bool valid_rotor_mapping(string token);
bool valid_rotor_start_position(string token);
bool valid_reflector_parameters(string token);
