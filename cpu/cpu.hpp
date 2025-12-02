#pragma once

#include "def.h"
#include <random>
#include <vector>

#include "keypad.hpp"
#include "display.hpp"

const unsigned int PROGRAM_START = 0x200;
const unsigned int FONT_SET_START = 0x50;

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

    Display& m_display;
    Keypad& m_keypad;

    std::default_random_engine m_randGen;
    std::uniform_int_distribution<byte> m_randByte;


    Cpu( Display& display , Keypad& keypad );

    void LoadROM(const char* filename);
    void runCycle();

private:
    void OP_00E0(word opcode);
    void OP_00EE(word opcode);
    void OP_1nnn( word opcode );
    void OP_2nnn( word opcode );
    void OP_3xkk( word opcode );
    void OP_4xkk( word opcode );
    void OP_5xy0( word opcode );
    void OP_6xkk( word opcode );
    void OP_7xkk( word opcode );
    void OP_8xy0(byte x , byte y);
    void OP_8xy1(byte x , byte y);
    void OP_8xy2(byte x , byte y);
    void OP_8xy3(byte x , byte y);
    void OP_8xy4(byte x , byte y);
    void OP_8xy5(byte x , byte y);
    void OP_8xy6(byte x , byte y);
    void OP_8xy7(byte x , byte y);
    void OP_8xyE(byte x , byte y);
    void OP_9xy0( word opcode );
    void OP_Annn( word opcode );
    void OP_Bnnn( word opcode );
    void OP_Cxkk( word opcode );
    void OP_Dxyn( word opcode );
    void OP_Ex9E( word opcode );
    void OP_ExA1( word opcode );
    void OP_Fx07( word opcode );
    void OP_Fx0A( word opcode );
    void OP_Fx15( word opcode );
    void OP_Fx18( word opcode );
    void OP_Fx1E( word opcode );
    void OP_Fx29( word opcode );
    void OP_Fx33( word opcode );
    void OP_Fx55( word opcode );
    void OP_Fx65( word opcode );
    void OP_0Table( word opcode );
    void OP_8Table( word opcode );
    void OP_ETable( word opcode );
    void OP_FTable( word opcode );

    using OpFunc = void (Cpu::*)(word);

    OpFunc dispachTable[16];

};