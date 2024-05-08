#ifndef SELOS_H
#define SELOS_H
#include <Arduino.h>
#include <avr/pgmspace.h>

// Melody Data
// ----------------------------------------------------------------------------
// This is the human readable/editable version of melodies.  We start by making
// some macros for each of the 12 notes we can play in each of the 8 octaves
// we can (maybe, depending on your tone()'s abilities) play.
//
// If you scroll down to after these macros you will see how they are used to
// construct arrays of notes/silences that make up each melody.
//
// The "DURATION" is the duration of the note to play (or silence) in units
// of tempo.  For example, to encode a C in the 4th Octave (commonly
// called Middle-C) for 10ms with a "tempoToPlay = 5" (ms), that would be
//  NOTE_C_4(2)
// because 2 durations of a 5ms tempo is 10ms :-)
//
// The maximum duration for a note or silence is 255, if you need longer, then
// simply use two notes and they will join togethor, eg for a 355 duration...
//  NOTE_C_4(255), NOTE_C_4(100)

// Octave 0 Note Codes
#define NOTE_C_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000000)
#define NOTE_CS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000001)
#define NOTE_D_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000010)
#define NOTE_DS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000011)
#define NOTE_E_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000100)
#define NOTE_F_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000101)
#define NOTE_FS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000110)
#define NOTE_G_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000111)
#define NOTE_GS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001000)
#define NOTE_A_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001001)
#define NOTE_AS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001010)
#define NOTE_B_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001011)

// Octave 1 Note Codes
#define NOTE_C_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010000)
#define NOTE_CS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010001)
#define NOTE_D_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010010)
#define NOTE_DS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010011)
#define NOTE_E_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010100)
#define NOTE_F_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010101)
#define NOTE_FS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010110)
#define NOTE_G_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010111)
#define NOTE_GS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011000)
#define NOTE_A_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011001)
#define NOTE_AS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011010)
#define NOTE_B_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011011)

// Octave 2 Note Codes
#define NOTE_C_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100000)
#define NOTE_CS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100001)
#define NOTE_D_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100010)
#define NOTE_DS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100011)
#define NOTE_E_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100100)
#define NOTE_F_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100101)
#define NOTE_FS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100110)
#define NOTE_G_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100111)
#define NOTE_GS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101000)
#define NOTE_A_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101001)
#define NOTE_AS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101010)
#define NOTE_B_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101011)

// Octave 3 Note Codes
#define NOTE_C_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110000)
#define NOTE_CS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110001)
#define NOTE_D_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110010)
#define NOTE_DS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110011)
#define NOTE_E_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110100)
#define NOTE_F_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110101)
#define NOTE_FS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110110)
#define NOTE_G_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110111)
#define NOTE_GS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111000)
#define NOTE_A_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111001)
#define NOTE_AS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111010)
#define NOTE_B_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111011)

// Octave 4 Note Codes
#define NOTE_C_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000000)
#define NOTE_CS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000001)
#define NOTE_D_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000010)
#define NOTE_DS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000011)
#define NOTE_E_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000100)
#define NOTE_F_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000101)
#define NOTE_FS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000110)
#define NOTE_G_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000111)
#define NOTE_GS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001000)
#define NOTE_A_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001001)
#define NOTE_AS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001010)
#define NOTE_B_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001011)

// Octave 5 Note Codes
#define NOTE_C_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010000)
#define NOTE_CS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010001)
#define NOTE_D_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010010)
#define NOTE_DS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010011)
#define NOTE_E_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010100)
#define NOTE_F_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010101)
#define NOTE_FS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010110)
#define NOTE_G_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010111)
#define NOTE_GS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011000)
#define NOTE_A_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011001)
#define NOTE_AS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011010)
#define NOTE_B_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011011)

// Octave 6 Note Codes
#define NOTE_C_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100000)
#define NOTE_CS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100001)
#define NOTE_D_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100010)
#define NOTE_DS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100011)
#define NOTE_E_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100100)
#define NOTE_F_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100101)
#define NOTE_FS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100110)
#define NOTE_G_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100111)
#define NOTE_GS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101000)
#define NOTE_A_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101001)
#define NOTE_AS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101010)
#define NOTE_B_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101011)

// Octave 7 Note Codes
#define NOTE_C_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110000)
#define NOTE_CS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110001)
#define NOTE_D_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110010)
#define NOTE_DS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110011)
#define NOTE_E_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110100)
#define NOTE_F_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110101)
#define NOTE_FS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110110)
#define NOTE_G_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110111)
#define NOTE_GS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111000)
#define NOTE_A_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111001)
#define NOTE_AS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111010)
#define NOTE_B_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111011)

// Octave 8 Note Codes
#define NOTE_C_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000000)
#define NOTE_CS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000001)
#define NOTE_D_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000010)
#define NOTE_DS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000011)
#define NOTE_E_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000100)
#define NOTE_F_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000101)
#define NOTE_FS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000110)
#define NOTE_G_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000111)
#define NOTE_GS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001000)
#define NOTE_A_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001001)
#define NOTE_AS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001010)
#define NOTE_B_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001011)

#define NOTE_SILENT(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001111)

// The melodies must be named Melody0 .. Melody{NUMBER_OF_MELODIES-1}, and
// each must also have a MelodyX_Length defined.
#define NUMBER_OF_MELODIES 1

// Track 0 -
static const uint16_t Melody0[] PROGMEM = {
    NOTE_B_6(255),
    NOTE_B_6(255),
    NOTE_B_6(74),
    NOTE_SILENT(185),
    NOTE_A_6(255),
    NOTE_A_6(52),
    NOTE_G_6(255),
    NOTE_G_6(255),
    NOTE_G_6(43),
    NOTE_A_6(255),
    NOTE_A_6(255),
    NOTE_A_6(43),
    NOTE_G_6(123),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(24),
    NOTE_G_6(255),
    NOTE_G_6(237),
    NOTE_SILENT(255),
    NOTE_SILENT(144),
    NOTE_E_6(255),
    NOTE_E_6(255),
    NOTE_E_6(164),
    NOTE_FS_6(215),
    NOTE_E_6(255),
    NOTE_E_6(22),
    NOTE_FS_6(123),
    NOTE_SILENT(31),
    NOTE_E_6(255),
    NOTE_E_6(21),
    NOTE_D_6(255),
    NOTE_D_6(255),
    NOTE_D_6(255),
    NOTE_D_6(255),
    NOTE_D_6(25),
    NOTE_E_6(255),
    NOTE_E_6(255),
    NOTE_E_6(227),
    NOTE_D_6(255),
    NOTE_D_6(52),
    NOTE_E_6(255),
    NOTE_E_6(113),
    NOTE_C_7(255),
    NOTE_C_7(145),
    NOTE_B_6(30),
    NOTE_SILENT(122),
    NOTE_B_6(255),
    NOTE_B_6(145),
    NOTE_A_6(31),
    NOTE_SILENT(152),
    NOTE_G_6(255),
    NOTE_G_6(255),
    NOTE_G_6(13),
    NOTE_B_6(255),
    NOTE_B_6(175),
    NOTE_A_6(30),
    NOTE_SILENT(255),
    NOTE_SILENT(255),
    NOTE_SILENT(255),
    NOTE_SILENT(255),
    NOTE_A_6(255),
    NOTE_A_6(53),
    NOTE_G_6(255),
    NOTE_G_6(21),
    NOTE_A_6(30),
    NOTE_SILENT(255),
    NOTE_SILENT(53),
    NOTE_G_6(255),
    NOTE_G_6(52),
    NOTE_B_6(255),
    NOTE_B_6(255),
    NOTE_B_6(197),
    NOTE_SILENT(184),
    NOTE_A_6(31),
    NOTE_SILENT(215),
    NOTE_G_6(255),
    NOTE_G_6(255),
    NOTE_G_6(255),
    NOTE_G_6(34),
    NOTE_A_6(255),
    NOTE_A_6(255),
    NOTE_A_6(104),
    NOTE_G_6(185),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(255),
    NOTE_FS_6(24),
    NOTE_G_6(255),
    NOTE_G_6(255),
    NOTE_G_6(43),
    NOTE_SILENT(255),
    NOTE_SILENT(145),
    NOTE_E_6(255),
    NOTE_E_6(255),
    NOTE_E_6(255),
    NOTE_E_6(64),
    NOTE_FS_6(246),
};
static const uint16_t Melody0_Length = sizeof(Melody0) / sizeof(uint16_t);

#endif