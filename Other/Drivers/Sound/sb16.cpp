#pragma once
#include "../../Librarys/Typedefs.h"
#include "../IO/IO.cpp"

void PlaySound(uint_32 hz){
    uint_32 d = 1193180 / hz;
    outb(0x43, 0xB6);
    outb(0x42, (uint_8) (d & 0xFF));
    outb(0x42, (uint_8) ((d >> 8) & 0xFF));
    outb(0x61, inb(0x61) | 0x3);
}

void StopSound(){
    outb(0x61, inb(0x61) & 0xFC);
}