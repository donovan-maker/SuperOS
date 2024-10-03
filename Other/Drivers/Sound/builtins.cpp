#pragma once
#include "sb16.cpp"

void Wait(int cycles) {
    while (cycles--) {
        // Busy wait to simulate a delay
    }
}

void PlayStartupJingle() {
    int notes[] = { 523, 659, 783, 1046 };
    int durations[] = { 2600000, 2200000, 2200000, 5000000 };

    int length = sizeof(notes) / sizeof(notes[0]);
    for (int i = 0; i < length; i++) {
        PlaySound(notes[i]);  // Play the note
        Wait(durations[i]);   // Wait for the duration
    }
    StopSound();
}