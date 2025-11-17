#pragma once

#include "def.h"
#include <memory>
#include <random>
#include <vector>

#include "keypad.hpp"
#include "display.hpp"

class Cpu {

public:
    
    std::vector<byte> m_v;
    std::vector<byte> m_memory;
    
    word m_idx;
    word m_pc;
    
    std::vector<word> m_stack;
    byte m_sp;
    byte m_timerDelay;
    byte m_timerSound;

    const Display& m_display;
    const Keypad& m_keypad;

    std::default_random_engine m_randGen;
    std::uniform_int_distribution<byte> m_randByte;


    Cpu( const Display& display , const Keypad& keypad );

    void LoadROM(const char* filename);

};