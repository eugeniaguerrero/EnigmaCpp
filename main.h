using namespace std;

int* get_configuration(string config_filename);
bool can_open_file(string config_filename);
bool is_num(string token);
bool contains_only_nums(string config_filename);
bool contains_valid_indexes(string config_filename);
// specific checks for configuration files
bool valid_config_file(string config_filename);
bool valid_pb_file(string config_filename);
bool valid_rot_file(string config_filename);
bool valid_rf_file(string config_filename);
string get_extension(string config_filename);
