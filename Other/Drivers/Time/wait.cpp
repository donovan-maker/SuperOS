#pragma once
#include "cmos.cpp"
#include "../../Librarys/Typedefs.h"
#include "../IO/TextPrint.cpp"

uint_64 secondsTime(uint_8 hourI, uint_8 minuteI, uint_8 secondI) {
    return (hourI * 60 * 60) + (minuteI * 60) + secondI;
}

void wait(uint_64 seconds) {
    uint_64 us = seconds + secondsTime(hour, minute, second);
    uint_64 ct = secondsTime(hour, minute, second);
    PrintString(IntegerToString(seconds));
    PrintString("  ");
    PrintString(IntegerToString(us));
    PrintString("  ");
    PrintString(IntegerToString(secondsTime(hour, minute, second)));
    while (us != ct) {read_rtc();ct = secondsTime(hour, minute, second);}
}