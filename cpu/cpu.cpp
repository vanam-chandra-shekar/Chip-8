#include "cpu.hpp"
#include "def.h"

#include <chrono>
#include <fstream>
#include <iosfwd>
#include <random>


const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const unsigned int PROGRAM_START = 0x200;
const unsigned int FONT_SET_START = 0x50;

Cpu::Cpu(const Display& display , const Keypad& keypad) 
    :   m_v(16, 0),
        m_memory(0xFFF, 0),
        m_idx(0), m_pc(0),
        m_stack(16, 0),
        m_sp(0),
        m_randGen(std::chrono::system_clock::now().time_since_epoch().count()),
        m_keypad(keypad),
        m_display(display)
{
    m_pc = PROGRAM_START;

    for(unsigned int i=0;i<FONT_SET_START;i++){
        m_memory[FONT_SET_START + i] = fontset[i];
    }

    m_randByte = std::uniform_int_distribution<byte>(0,255U);

};


void Cpu::LoadROM(const char* filename) {
    std::ifstream file(filename , std::ios::binary  | std::ios::ate);;

    if(!file.good())
        throw std::runtime_error("Unable to open ROM file");

    if (file.is_open()){

        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0,std::ios::beg);
        file.read(buffer, size);
        file.close();


        for(long i=0;i<size;i++){
            m_memory[PROGRAM_START + i] = buffer[i];
        }


        delete [] buffer;

    }

};