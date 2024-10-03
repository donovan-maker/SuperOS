#include "../Drivers/IO/TextPrint.cpp"
#include "../Drivers/IDT/IDT.cpp"
#include "../Drivers/Memory/MemoryMap.cpp"
#include "../Drivers/Sound/builtins.cpp"
#include "../Librarys/PianoMapping.h"
#include "../Drivers/Time/cmos.cpp"
#include "../Drivers/Time/wait.cpp"

extern const char SuccessAscii[];

char* TextBuffer;
bool KeyboardEnabled = false;
bool LeftShiftPressed = false;
bool RightShiftPressed = false;
uint_8 LastScanCode;
uint_8 NMIDisableBit = 0;

void KeyboardHandler(uint_8 scanCode, uint_8 chr) {
    if (KeyboardEnabled){
        if (chr != 0){
            switch (LeftShiftPressed | RightShiftPressed) {
                case true:
                    PrintChar(chr - 32);
                    break;
                case false:
                    PrintChar(chr);
                    break;
            }
        } else {
            switch (scanCode) {
            case 0x8E: //Backspace
                SetCursorPosition(CursorPosition - 1);
                PrintChar(' ');
                SetCursorPosition(CursorPosition - 1);
                break;
            case 0x2A: //Left Shift
                LeftShiftPressed = true;
                break;
            case 0xAA: //Left Shift Released
                LeftShiftPressed = false;
                break;
            case 0x36: //Right Shift
                RightShiftPressed = true;
                break;
            case 0xB6: //Right Shift Released
                RightShiftPressed = false;
                break;
            }
        }
    }
    TextBuffer += scanCode;
    LastScanCode = scanCode;
}

void WaitForEnter() {
    while (LastScanCode != 0x1C){}
    while (LastScanCode != 0x9C){}
}

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    ClearScreen();

    PrintString("Initializing IDT\n\r");
    InitializeIDT();
    MainKeyboardHandler = KeyboardHandler;

    PrintString("Getting RAM Data\n\r");
    MemoryMapEntry** UsableMemoryMaps = GetUsableMemoryRegions();
    uint_64 MemUsable = 0;
    for (uint_8 i = 0; i < UsableMemoryRegionCount; i++) {
        MemoryMapEntry* memMap = UsableMemoryMaps[i];
        MemUsable += UsableMemoryMaps[i]->RegionLength;
    }
    uint_8 MBofRAM = MemUsable/1024/1024;
    PrintString(IntegerToString(MBofRAM));
    PrintString("MB of usable RAM.\n\r");

    read_rtc();
    PrintString("The time is: ");
    PrintString(IntegerToString(hour));
    PrintString(":");
    if (minute < 10){
        PrintString("0");
    }
    PrintString(IntegerToString(minute));

    PrintString("\n\n\r--------------------------------------------------------------------------------\n\r");
    PrintString(SuccessAscii);

    // Play startup jingle
    PlayStartupJingle();

    //wait(2);

    // Piano test
    PrintString("\n\rPress enter to play piano!");
    WaitForEnter();
    PrintString("\n\rReady");
    while (true){
        uint_32 note = PianoMapping::ScanCodeLookupTable[LastScanCode];
        if (note > 260){
            if (note < 524){
                PlaySound(note);
            } else {
                StopSound();
            }
        } else {
            StopSound();
        }
    }
    return;
}