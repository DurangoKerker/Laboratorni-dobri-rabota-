#include <dos.h>
#include <conio.h>
#include <stdio.h>

#define NUM_VOWELS 20 // 20 - because of doubled pressing of button.
// When you press button one time, the handler recieve a message on move down and up, so
// i need to increase this counter

// Pointer to the old interrupt handler
void interrupt (*oldKeyboardISR)(...);

// Global variables
int vowelCount = 0;      // Vowel counter
int blockDigits = 0;     // Flag for blocking digits

// ASCII code table for conversion
unsigned char scanToAscii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,  0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,   0,  'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0,  '*', 0,  ' ', 0,  0,  0,   0,  0,  0,  0, 
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0
};

// New keyboard interrupt handler
void interrupt newKeyboardISR(...) {
    unsigned char scanCode = inp(0x60); // Read the scan code
    unsigned char asciiCode = scanToAscii[scanCode & 0x7F]; // Convert to ASCII

    // Check for vowels
    if (asciiCode == 'A' || asciiCode == 'E' || asciiCode == 'I' || 
        asciiCode == 'O' || asciiCode == 'U' || 
        asciiCode == 'a' || asciiCode == 'e' || asciiCode == 'i' || 
        asciiCode == 'o' || asciiCode == 'u') {
        vowelCount++; // Increment vowel counter
    }

    // Block digits
    if (asciiCode >= '0' && asciiCode <= '9' && blockDigits) {
        // Don't pass the interrupt further
        outp(0x20, 0x20); // End the interrupt processing
        return;
    }

    // Unblock after 10 vowels
    if (vowelCount == NUM_VOWELS) {
        blockDigits = !blockDigits; // Toggle the flag
        vowelCount = 0;             // Reset the counter
    }

    // Pass control to the old interrupt handler
    oldKeyboardISR();
    outp(0x20, 0x20); // End the interrupt processing
}

void main() {
    clrscr();

    // Set the new interrupt handler
    oldKeyboardISR = getvect(9);   // Save the old handler
    setvect(9, newKeyboardISR);    // Set the new handler

    // Main program loop
    printf("Enter characters. Entering digits will be blocked after 10 vowels.\n");
    printf("Press ESC to exit.\n");
    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 27) { // ESC to exit
                break;
            }

            // Ignore digits output if they are blocked
            if (blockDigits && ch >= '0' && ch <= '9') {
                continue;
            }

            printf("%c", ch); // Output the character
        }
    }

    // Restore the old interrupt handler
    setvect(9, oldKeyboardISR);

    printf("\nProgram has ended.\n");
}
