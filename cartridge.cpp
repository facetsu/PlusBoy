#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "defs.h"
#include <filesystem>

using namespace std;


struct rom {
    
};

static char bitmap[48] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
};


int main() {
    string filepath;
    u8 size = filesystem::file_size();

    cout << "Please enter the name of the ROM you want to test.\n";
    cin >> filepath;
    cout << filepath << endl;
    fstream myfile;
    myfile.open(filepath);
}

/*bool checkBitmaps() {
    string filepath;

    cout << "Please enter the name of the ROM you want to test.";
    cin >> filepath;
    fstream myfile;
    myfile.open(filepath);
  
  return 0;
} */