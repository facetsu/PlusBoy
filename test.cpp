#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "defs.h"
#include <bitset>
#include <filesystem>

using namespace std;

bool validateTitle (int defaults[], int checker[]);
string get_cart_type(ifstream &romRead);
string get_cart_size(ifstream &romRead);

/* This is default Gameboy title which all cartridges must
    pass a check agaisnt for the bootloader to continue.
    If the cartridhe does not match this hexdump at the specified
    address, the bootrom locks up and the Gameboy must be reset*/
static int bitmap[48] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
};

string romType;

int main() {
    char title[16];
    char romsets[48];
    int convRomset[48];
    string cartType;
    string cartSize;
    ifstream romRead;
    string filename;
    int temp1;
    u8 temp2;

    cout << "Please enter a file to open. (correct path required if not in this folder)\n";
    cin >> filename;

    romRead.open(filename, ios::binary | ios::in);
    if (!romRead) {
        return -1;  // checks if our input stream was opened correctly
    }

    romRead.seekg(0x0134, ios::beg);         //places our read pointer at the starting position for cart titles (0x0134)
    romRead.read(title, 0x10);               // reads the cart title. they must always fit into 0xF long bytes (16 bytes).
    cout << "The internal cartridge title is: " << title << endl << endl;

    romRead.seekg(0x0104, ios::beg);
    romRead.read(romsets, 0x30);

    cout << "The ROMs bootcheck sum is:                  ";
    for (int i = 0; i < 48; i++) {
        temp1 = romsets[i];
        temp2 = u8(temp1);
        temp1 = temp2;
        convRomset[i] = temp1;
        cout << hex << uppercase << convRomset[i] << " ";
    }

    cout << endl;
    cout << "The required bootsum is:                    ";
    for (int i = 0; i < 48; i++) {
        cout << int(bitmap[i]) << " ";
    }
    cout << endl;

    validateTitle(bitmap, convRomset);

    cartType = get_cart_type(romRead);
    cout << "Our cart's type is: " << cartType << endl << endl;

    cartSize = get_cart_size(romRead);
    cout << "Our cart's size is " << cartSize << endl;

    
    return 0;
}

bool validateTitle (int defaults[], int checker[]) {
    for(int i = 0; i < 48; i++) {
        if (checker[i] != defaults[i]) {
            cout << "The title hexdump does not match! Not a genuine cartridge." << endl << endl;
            return false;
        }
    }
    cout << endl << "The cartridge title hexdump is validated. Continuing." << endl << endl;
    return true;
}

string get_cart_type(ifstream &romRead) {
    char temp[2];
    int type;
    
    romRead.seekg(0x0147, ios::beg);   
    romRead.read(temp, 1);

    type = u8(temp[0]);
    cout << hex << "Cart-type hex is: 0x" << type << endl;

    switch (type) {
        case 0x00 : 
            return "ROM ONLY";
        case 0x01 :
            return "MBC1";
        case 0x02 :
            return "MBC1+RAM";
        case 0x03 :
            return "MBC1+RAM+BATTERY";
        case 0x05 :
            return "MBC2";
        case 0x06 :
            return "MBC2+BATTERY";
        case 0x08 :
            return "ROM+RAM ";
        case 0x09 :
            return "ROM+RAM+BATTERY";
        case 0x0B :
            return "MMM01";
        case 0x0C :
            return "MMM01+RAM";
        case 0x0D :
            return "MMM01+RAM+BATTERY";
        case 0x0F :
            return "MBC3+TIMER+BATTERY";
        case 0x10 :
            return "MBC3+TIMER+RAM+BATTERY";
        case 0x11 :
            return "MBC3";
        case 0x12 :
            return "MBC3+RAM";
        case 0x13 :
            return "MBC3+RAM+BATTERY";
        case 0x19 :
            return "MBC5";
        case 0x1A :
            return "MBC5+RAM";
        case 0x1B :
            return "MBC5+RAM+BATTERY";
        case 0x1C :
            return "MBC5+RUMBLE";
        case 0x1D :
            return "MBC5+RUMBLE+RAM";
        case 0x1E :
            return "MBC5+RUMBLE+RAM+BATTERY";
        case 0x20 :
            return "MBC6";
        case 0x22 :
            return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case 0xFC :
            return "POCKET CAMERA";
        case 0xFD :
            return "BANDAI TAMA5";
        case 0xFE :
            return "HuC3";
        case 0xFF :
            return "HuC1+RAM+BATTERY";
        default :
            return "ERROR";
    } 
    return "FAILURE";
}

string get_cart_size(ifstream &romRead) {
    char temp[2];
    int size;

    romRead.seekg(0x0148, ios::beg);   
    romRead.read(temp, 1);

    size = u8(temp[0]);
    cout << hex << "Cart-size hex is: 0x" << size << endl;
    
    switch (size) {
        case 0x00 :
            return "32 KiB | 2 ROM BANKS";
        case 0x01 :
            return "64 KiB | 4 ROM BANKS";
        case 0x02 :
            return "128 KiB | 8 ROM BANKS";
        case 0x03 :
            return "256 KiB | 16 ROM BANKS";
        case 0x04 :
            return "512 KiB | 32 ROM BANKS";
        case 0x05 :
            return "1 MiB | 64 ROM BANKS";
        case 0x06 :
            return "2 MiB | 128 ROM BANKS";
        case 0x07 :
            return "4 MiB | 256 ROM BANKS";
        case 0x08 :
            return "8 MiB | 512 ROM BANKS";
        case 0x52 :
            return "1.1 MiB | 72 ROM BANKS";
        case 0x53 :
            return "1.2 MiB | 80 ROM BANKS";
        case 0x54 :
            return "1.5 MiB | 96 ROM BANKS";
        default :
            return "ERROR";
    }
    return "ERROR";
}