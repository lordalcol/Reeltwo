#ifndef ServoSequencer_h
#define ServoSequencer_h

#include "ReelTwo.h"
#include "core/AnimatedEvent.h"
#include "ServoDispatch.h"

// Offset value specified in per-mille (per thousand)
#define SEQUENCE_RANGE_LIMIT(offsetFromMin, offsetFromMax) \
{ uint16_t(~0), (((offsetFromMin)>>8)&0xFF), (((offsetFromMin)>>0)&0xFF), (((offsetFromMax)>>8)&0xFF), (((offsetFromMax)>>0)&0xFF) },

/**
  * \struct ServoStep
  *
  * \brief Single frame of servo animation. Time is specified in centi seconds (1/100th of a second)
  */
struct ServoStep
{
    uint16_t cs; /* centiseconds: 1/100th of a second*/
    uint8_t servo1_8;
    uint8_t servo9_16;
    uint8_t servo17_24;
    uint8_t servo25_32;
};

typedef struct ServoStep ServoSequence[];

static const ServoSequence SeqPanelAllOpen PROGMEM =
{
    { 20,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
};

static const ServoSequence SeqPanelAllClose PROGMEM =
{
    { 20,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelAllOpenClose PROGMEM =
{
    { 300,  0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 150,  0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelAllOpenCloseLong PROGMEM =
{
    { 1000, 0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 150,  0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelAllFlutter PROGMEM =
{
    // Twenty permille (per thousand) offset from start/end positions
    SEQUENCE_RANGE_LIMIT(200, 200)
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    SEQUENCE_RANGE_LIMIT(0, 0)
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelAllFOpenCloseRepeat PROGMEM =
{
    // Twenty permille (per thousand) offset from start/end positions
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 10,   0b11111111, 0b11111111, 0b11111111, 0b11111111 },
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelWave PROGMEM =
{
    { 30,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00100000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00010000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelWaveFast PROGMEM =
{
    { 15,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00100000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00010000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00010000, 0b00000000, 0b00000000 },
    { 30,   0b00000000, 0b00100000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 15,   0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelOpenCloseWave PROGMEM =
{
    { 20,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11000000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11100000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11110000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11111000, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11111100, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11111110, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11111111, 0b00000000, 0b00000000, 0b00000000 },
    { 20,   0b11111111, 0b10000000, 0b00000000, 0b00000000 },
    { 20,   0b11111111, 0b11000000, 0b00000000, 0b00000000 },
    { 20,   0b11111111, 0b11100000, 0b00000000, 0b00000000 },
    { 80,   0b11111111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b01111111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00111111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00011111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00001111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00000111, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00000011, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00000001, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00000000, 0b11110000, 0b00000000, 0b00000000 },
    { 20,   0b00000000, 0b01110000, 0b00000000, 0b00000000 },
    { 20,   0b00000000, 0b00110000, 0b00000000, 0b00000000 },
    { 20,   0b00000000, 0b00010000, 0b00000000, 0b00000000 },
    { 40,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelMarchingAnts PROGMEM =
{
    // Alternating pattern of on/off
    { 20,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 100,  0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelAlternate PROGMEM =
{
    // Alternating pattern of on/off
    { 20,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 50,   0b10101010, 0b10101010, 0b10101010, 0b10101010 },
    { 50,   0b01010101, 0b01010101, 0b01010101, 0b01010101 },
    { 100,  0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

// 1-4 panels
// 5-6 large panels
// 7-10 pie panels
// 11-12 mini doors
// 13 pie door
static const ServoSequence SeqPanelDance PROGMEM =
{
    { 10,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 4 pie, 1 by one
    { 45,   0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b00000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 4 side, 1 by one
    { 45,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11110000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b01110000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00110000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00010000, 0b00000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 4 pies. 2 by 2
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 2 large sides
    { 45,   0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11111100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b01111100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00011100, 0b00000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // interleaved
    { 45,   0b01010000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b10100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 2nd interleaved
    { 45,   0b00000011, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b10101010, 0b10000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b10101010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b01010101, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b10101010, 0b10000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
    { 45,   0b11000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00110000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00001100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11001100, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b00110011, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11001100, 0b11000000, 0b00000000, 0b00000000 },

    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // transition
    { 45,   0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b01100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },

    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 }, // good
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000001, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b10101010, 0b10000000, 0b00000000, 0b00000000 },
    { 45,   0b01010101, 0b01000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b11111111, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b00000011, 0b11000000, 0b00000000, 0b00000000 },
    { 45,   0b11111100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,   0b00000000, 0b00001000, 0b00000000, 0b00000000 }, // tip of the hat
    { 500,  0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

static const ServoSequence SeqPanelLongDisco PROGMEM =
{
    { 15,    0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 15,    0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 15,    0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 3.45 seconds
    { 36000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 6 minutes
    { 2200,  0b00000000, 0b00000000, 0b00000000, 0b00000000 }, // 22 seconds
};

static const ServoSequence SeqPanelLongHarlemShake PROGMEM =
{
    { 45,    0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b10000000, 0b00000000, 0b00000000 },
    { 45,    0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000010, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000100, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00010000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00100000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b10000000, 0b00000000, 0b00000000, 0b00000000 },
    { 45,    0b00000000, 0b00000000, 0b00000000, 0b00000000 },
};

#define SEQUENCE_PLAY_ONCE(sequencer, sequence, groupMask) \
    (sequencer).play(sequence, SizeOfArray(sequence), groupMask)
#define SEQUENCE_PLAY_ONCE_SPEED(sequencer, sequence, groupMask, speed) \
    (sequencer).play(sequence, SizeOfArray(sequence), groupMask, speed)
#define SEQUENCE_PLAY_ONCE_VARSPEED(sequencer, sequence, groupMask, minspeed, maxspeed) \
    (sequencer).playVariableSpeed(sequence, SizeOfArray(sequence), groupMask, minspeed, maxspeed)
#define SEQUENCE_PLAY_RANDOM_STEP(sequencer, sequence, groupMask) \
    (sequencer).play(&sequence[random(SizeOfArray(sequence))], 1, groupMask)
#define SEQUENCE_PLAY_ONCE_VARSPEED_EASING(sequencer, sequence, groupMask, minspeed, maxspeed, onEasing, offEasing) \
    (sequencer).playVariableSpeed(sequence, SizeOfArray(sequence), groupMask, minspeed, maxspeed, 0.0, 1.0, onEasing, offEasing)


/**
  * \ingroup Core
  *
  * \class ServoSequencer
  *
  * \brief Plays a sequence of servo commands using a servo group mask
  */
class ServoSequencer : public AnimatedEvent
{
public:
    ServoSequencer(ServoDispatch& dispatch) :
        fDispatch(dispatch)
    {
        stop();
    }

    void playVariableSpeed(const ServoStep* sequence, uint16_t length, uint32_t servoGroupMask,
            uint16_t speedMinMS, uint16_t speedMaxMS, float startPos = 0.0, float endPos = 1.0,
            float (*onEasingMethod)(float) = nullptr, float (*offEasingMethod)(float) = NULL)
    {
        stop();
        fSequence = (ServoStep*)sequence;
        fServoGroupMask = servoGroupMask;
        fLength = length;
        fStartPos = startPos;
        fEndPos = endPos;
        fSpeedMinMS = speedMinMS;
        fSpeedMaxMS = speedMaxMS;
        fNextStepMS = millis();
        fOffsetFromStart = 0;
        fOffsetFromEnd = 0;
        fIndex = 0;
        fOnEasingMethod = onEasingMethod;
        fOffEasingMethod = offEasingMethod;
    }

    void play(const ServoStep* sequence, uint16_t length, uint32_t servoGroupMask,
            uint16_t speedMS = 0, float startPos = 0.0, float endPos = 1.0)
    {
        playVariableSpeed(sequence, length, servoGroupMask, speedMS, speedMS, startPos, endPos);
    }

    void stop()
    {
        fSequence = NULL;
        fLength = 0;
        fNextStepMS = 0;
    }

    inline bool isFinished() const
    {
        return (fSequence == nullptr);
    }

    virtual void animate() override
    {
        unsigned long currentTime;
        if (fSequence == NULL || (currentTime = millis()) < fNextStepMS)
            return;
        if (fIndex >= fLength)
        {
            stop();
            return;
        }
        uint32_t servoSetMask = 0;
        const ServoStep* step = &fSequence[fIndex];
        while (pgm_read_word(&step->cs) == uint16_t(~0))
        {
            // Check for an initial range limiting step
            uint16_t offsetFromStart = 0;
            uint16_t offsetFromEnd = 0;
            offsetFromStart |= (uint32_t)pgm_read_byte(&step->servo1_8) << 8;
            offsetFromStart |= (uint32_t)pgm_read_byte(&step->servo9_16);
            offsetFromEnd |= (uint32_t)pgm_read_byte(&step->servo17_24) << 8;
            offsetFromEnd |= (uint32_t)pgm_read_byte(&step->servo25_32);
            fOffsetFromStart = (offsetFromStart / 1000.0);
            fOffsetFromEnd = (offsetFromEnd / 1000.0);
            fIndex++;
            if (fIndex >= fLength)
            {
                stop();
                return;
            }
            step = &fSequence[fIndex];
        }
        servoSetMask |= (uint32_t)pgm_read_byte(&step->servo1_8) << 24;
        servoSetMask |= (uint32_t)pgm_read_byte(&step->servo9_16) << 16;
        servoSetMask |= (uint32_t)pgm_read_byte(&step->servo17_24) << 8;
        servoSetMask |= (uint32_t)pgm_read_byte(&step->servo25_32) << 0;
        uint32_t ms = pgm_read_word(&fSequence[fIndex].cs) * 10L;
        fNextStepMS = currentTime + fSpeedMinMS + ms;
        fDispatch.moveServoSetTo(fServoGroupMask, servoSetMask, 0,
            fSpeedMinMS, fSpeedMaxMS, fEndPos-fOffsetFromEnd, fStartPos+fOffsetFromStart, fOnEasingMethod, fOffEasingMethod);
        fIndex++;
    }

    inline ServoDispatch& dispatch()
    {
        return fDispatch;
    }

private:
    ServoDispatch& fDispatch;
    ServoStep* fSequence;
    uint16_t fLength = 0;
    uint16_t fIndex = 0;
    float fOffsetFromStart;
    float fOffsetFromEnd;
    float fStartPos;
    float fEndPos;
    uint16_t fSpeedMinMS;
    uint16_t fSpeedMaxMS;
    uint32_t fServoGroupMask;
    uint32_t fNextStepMS;
    float (*fOnEasingMethod)(float);
    float (*fOffEasingMethod)(float);
};

#endif
