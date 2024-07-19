#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "defs.h"
#include <bitset>
#include <filesystem>

//https://gbdev.io/pandocs/The_Cartridge_Header.html

using namespace std;

bool validateTitle (int defaults[], int checker[]);
string get_cart_type(ifstream &romRead);
string get_cart_size(ifstream &romRead);
string get_region_code(ifstream &romRead);
string get_ram_size(ifstream &romRead);
string get_licensee_code(ifstream &romRead);

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
    string cartRegion;
    string ramSize;
    string licensee;

    ifstream romRead;
    string filename;
    int temp1;
    u8 temp2;

    cout << "\nPlease enter a file to open. (correct path required if not in this folder)\n";
    cin >> filename;

    romRead.open(filename, ios::binary | ios::in);
    if (!romRead) {
        return -1;  // checks if our input stream was opened correctly
    }

    romRead.seekg(0x0134, ios::beg);         // places our read pointer at the starting position for cart titles (0x0134)
    romRead.read(title, 0x09);               // reads the cart title. they must always fit into 0xF long bytes (16 bytes).
    cout << endl << "The internal cartridge title is: " << title << endl << endl;

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
    cout << "Our cart's rom size is " << cartSize << endl << endl;

    ramSize = get_ram_size(romRead);
    cout << "Our cart's ram size is " << ramSize << endl << endl;

    cartRegion = get_region_code(romRead);
    cout << "This cartridge has a market destination of: " << cartRegion << endl;

    licensee = get_licensee_code(romRead);
    cout << "TESTING:" << licensee << endl;
    
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

string get_ram_size(ifstream &romRead) {
    char temp[2];
    int size;

    romRead.seekg(0x0149, ios::beg);   
    romRead.read(temp, 1);

    size = u8(temp[0]);
    cout << hex << "Cart ram-size hex is: 0x" << size << endl;
    
    switch (size) {
        case 0x00 :
            return "0 KiB | No RAM";
        case 0x01 :
            return "- UNUSED -";
        case 0x02 :
            return "8 KiB | 1 Bank";
        case 0x03 :
            return "32 KiB | 8 KiB * 4";
        case 0x04 :
            return "128 KiB | 8 KiB * 16";
        case 0x05 :
            return "64 KiB | 8 KiB  * 8";
        default :
            return "ERROR";
    }
    return "ERROR";
}

string get_region_code(ifstream &romRead) {
    char temp[2];
    int dest;

    romRead.seekg(0x014A, ios::beg);   
    romRead.read(temp, 1);

    dest = u8(temp[0]);
    if (dest == 0x00) {
        return "Japan";
    }
    else {
        return "Overseas (NA | EU)";
    }
}

string get_licensee_code(ifstream &romRead) {
    char temp[2];
    int license;

    romRead.seekg(0x014B, ios::beg);
    romRead.read(temp, 1);

    license = u8(temp[0]);

    // if the new licensee code must be used
    if (license == 0x33) { 

        romRead.seekg(0x0144, ios::beg);
        romRead.read(temp, 2);

        if (!isdigit(temp[0]) || !isdigit(temp[1])) {
            if (temp[0] == '9') {
                return "Bottom Up";
            }
            else if (temp[0] == 'A') {
                return "Konami";
            }
            else if (temp[0] == 'B') {
                return "MTO";
            }
            else {
                return "Kodansha";
            }
        }

        int lCode = stoi(temp);

        switch(lCode) {
            case 0:
                return "NONE";
            case 1:
                return "Nintendo Research & Development";
            case 8:
                return "Capcom";
            case 13:
                return "Electronic Arts";
            case 18:
                return "Hudson Soft";
            case 19:
                return "B-AI";
            case 20:
                return "KSS";
            case 22:
                return "Planning Office WADA";
            case 24:
                return "PCM Complete";
            case 25:
                return "San-X";
            case 28:
                return "Kemco";
            case 29:
                return "SETA Corporation";
            case 30:
                return "Viacom";
            case 31:
                return "Nintendo";
            case 32:
                return "Bandai";
            case 33:
                return "Ocean Software / Acclaim Entertainment";
            case 34:
                return "Konami";
            case 35:
                return "HectorSoft";
            case  37:
                return "Taito";
            case 38:
                return "Hudson Soft";
            case 39:
                return "Banpresto";
            case 41:
                return "Ubi Soft";
            case 42:
                return "Atlus";
            case 44:
                return "Malibu Interactive";
            case 46:
                return "Angel";
            case 47:
                return "Bullet-Proof Software";
            case 49:
                return "Irem";
            case 50:
                return "Absolute";
            case 51:
                return "Acclaim Entertainment";
            case 52:
                return "Activision";
            case 53:
                return "Sammy USA Corportation";
            case 54:
                return "Konami";
            case 55:
                return "Hi Tech Expressions";
            case 56:
                return "LJN";
            case 57:
                return "Matchbox";
            case 58:
                return "Mattel";
            case 59:
                return "Milton Bradley Company";
            case 60:
                return "Titus Interactive";
            case 61:
                return "Virgin Games Ltd.";
            case 64:
                return "Lucasfilm Games";
            case 67:
                return "Ocean Software";
            case 69:
                return "EA (Electronic Arts)";
            case 70:
                return "Infogrames";
            case 71:
                return "Interplay Entertainment";
            case 72:
                return "Broderbund";
            case 73:
                return "Sculptured Software";
            case 75:
                return "The Sales Curve Limited";
            case 78:
                return "THQ";
            case 79:
                return "Accolade";
            case 80:
                return "Misawa Entertainment";
            case 83:
                return "Iozc";
            case 86:
                return "Tokuma Shoten";
            case 87:
                return "Tsukuda Original";
            case 91:
                return "Chunsoft Co.";
            case 92:
                return "Video System";
            case 93:
                return "Ocean Software / Acclaim Entertainment";
            case 95:
                return "Varie";
            case 96:
                return "Yonezawa/'spal";
            case 97:
                return "Kaneko";
            case 99:
                return "Pack-In-Video";
            default:
                return "ERROR: NOT FOUND";
        };
    }
    return "ERROR: NOT FOUND";

}