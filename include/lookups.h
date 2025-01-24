#include <string>
#include <iostream>
#include "defs.h"

using namespace std;

std::string get_cart_type(u8 input);

std::string get_cart_size(u8 input);

std::string get_ram_size(u8 input);

string get_region_code(u8 input);

string get_licensee_code(u8 input, u8 newLicense[]);