#include <iostream>
#include <string>
#include "defs.h"

const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;


class Emulator {
    u8 workRam[8192]; // We allocate 8KiB of RAM
    u8 vidRam[8192];
    u8 screen[SCREEN_HEIGHT * SCREEN_WIDTH];
    

};
