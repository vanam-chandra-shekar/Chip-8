#include "cpu.hpp"
#include "def.h"
#include <stdexcept>

void Cpu::OP_00E0( word opcode ) {
    // Clear the display
    m_display.clear();

}

void Cpu::OP_00EE( word opcode ) {
    // RET : Return from subroutine
    --m_sp;
    m_pc = m_stack[m_sp];
}

void Cpu::OP_1nnn( word opcode ) {
    // JMP : Jumps to nnn
    word nnn = opcode & 0x0FFFu;
    m_pc = nnn;

}

void Cpu::OP_2nnn( word opcode ) {
    m_stack[m_sp] = m_pc;
    ++m_sp;
    word nnn = opcode & 0x0FFFu;
    m_pc = nnn;

}

void Cpu::OP_3xkk( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte kk = (opcode & 0x00FFu);

    if(m_v[x] == kk){
        m_pc += 2;
    }

}

void Cpu::OP_4xkk( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte kk = (opcode & 0x00FFu);

    if(m_v[x] != kk){
        m_pc +=2;
    }

}

void Cpu::OP_5xy0( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte y = (opcode & 0x00F0u) >> 4u;

    if(m_v[x] == m_v[y]){
        m_pc += 2;
    }

}

void Cpu::OP_6xkk( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte kk = (opcode & 0x00FFu);

    m_v[x] = kk;

}

void Cpu::OP_7xkk( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte kk = (opcode & 0x00FFu);

    m_v[x] += kk;

}

void Cpu::OP_8xy0( byte x , byte y ) {

    m_v[x] = m_v[y];
}

void Cpu::OP_8xy1(byte x ,byte y ) {
    m_v[x] |= m_v[y];
}

void Cpu::OP_8xy2(byte x ,byte y ) {
    m_v[x] &= m_v[y];
}

void Cpu::OP_8xy3(byte x ,byte y ) {
    m_v[x] ^= m_v[y];
}

void Cpu::OP_8xy4(byte x ,byte y ) {

    word sum = m_v[x] + m_v[y];

    if(sum > 255u){
        m_v[0xF] = 1u;
    }
    else{
        m_v[0xF] = 0u;
    }

    m_v[x] = sum & 0xFFu;

}

void Cpu::OP_8xy5(byte x ,byte y ) {

    if(m_v[x] > m_v[y]){
        m_v[0xF] = 1u;
    }
    else{
        m_v[0xF] = 0u;
    }

    m_v[x] = m_v[x] - m_v[y];

}

void Cpu::OP_8xy6(byte x ,byte y ) {

    m_v[0xF] = (m_v[x] & 0x1u);

    m_v[x] >>= 1;

}

void Cpu::OP_8xy7(byte x ,byte y ) {

    if(m_v[y] > m_v[x]){
        m_v[0xF] = 1u;
    }
    else{
        m_v[0xF] = 0u;
    }

    m_v[x] = m_v[y] - m_v[x];

}

void Cpu::OP_8xyE(byte x ,byte y ) {

    m_v[0xF] = (m_v[x] & 0x80u) >> 7u;

    m_v[x] <<= 1;

}


void Cpu::OP_9xy0( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;
    byte y = (opcode & 0x00F0u) >> 4u;

    if(m_v[x] != m_v[y]){
        m_pc += 2;
    }

}

void Cpu::OP_Annn( word opcode ) {
    word nnn = opcode & 0x0FFF;
    m_idx = nnn;
}

void Cpu::OP_Bnnn( word opcode ) {
    word nnn = opcode & 0x0FFF;

    m_pc = nnn + m_v[0];
}

void Cpu::OP_Cxkk( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;
    byte kk = (opcode & 0x00FF);
    
    m_v[x] = m_randByte(m_randGen) & kk;

}

void Cpu::OP_Dxyn( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;
    byte y = (opcode & 0x00F0u) >> 4u;
    byte height = (opcode & 0x000F);


    byte xPos = m_v[x] % m_display.getWidth();
    byte yPos = m_v[y] % m_display.getHeight();

    m_v[0xF] = 0;
    
    
    for(unsigned int row = 0; row < height; ++row){

        byte spriteByte = m_memory[m_idx + row];
        
        for(unsigned int col=0;col < 8;++col){
            byte spritePixel = spriteByte & (0x80u >> col);
            bool screenPixel = m_display.getPixel((xPos + col) , (yPos + row));

            if(spritePixel){

                if(screenPixel){
                    m_v[0xF] = 1;
                }

                m_display.setPixel((xPos + col), (yPos + row), screenPixel ^ 1);
            }

        }

    }

}

void Cpu::OP_Ex9E( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;

    if(m_keypad.IsKeyPressed(m_v[x])){
        m_pc += 2;
    }

}

void Cpu::OP_ExA1( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;

    if(!m_keypad.IsKeyPressed(m_v[x])){
        m_pc += 2;
    }

}

void Cpu::OP_Fx07( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;

    m_v[x] = m_timerDelay;

}

void Cpu::OP_Fx0A( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    bool keyPressed = false;

    for(int key = 0; key < Keypad::KEY_COUNT; ++key){
        if(m_keypad.IsKeyPressed(key)){
            m_v[x] = key;
            keyPressed = true;
            break;
        }
    }

    if(!keyPressed){
        m_pc -= 2;
    }

}

void Cpu::OP_Fx15( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;

    m_timerDelay = m_v[x];
}

void Cpu::OP_Fx18( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    m_timerSound = m_v[x];

}

void Cpu::OP_Fx1E( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    m_idx += m_v[x];

}

void Cpu::OP_Fx29( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    byte digit = m_v[x];

    m_idx = FONT_SET_START + (digit * 5);

}

void Cpu::OP_Fx33( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    byte value = m_v[x];

    m_memory[m_idx + 2] = value % 10;
    value /= 10;
    m_memory[m_idx + 1] = value % 10;
    value /= 10;
    m_memory[m_idx] = value % 10;

}

void Cpu::OP_Fx55( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    for(int i=0;i<=x;++i){
        m_memory[m_idx + i] = m_v[i];
    }

}

void Cpu::OP_Fx65( word opcode ) {

    byte x = (opcode & 0x0F00u) >> 8u;

    for(int i=0;i<=x;++i){
        m_v[i] = m_memory[m_idx + i];
    }

}


void Cpu::OP_0Table( word opcode ) {
    switch(opcode & 0x000Fu){
        case 0x0000:
            OP_00E0(opcode);
            break;
        case 0x000E:
            OP_00EE(opcode);
            break;
        default:
            throw std::runtime_error("Unknown opcode [0x0000]: " + std::to_string(opcode));
    }
}

void Cpu::OP_8Table( word opcode ) {
    byte x = (opcode & 0x0F00u) >> 8u;
    byte y = (opcode & 0x00F0u) >> 4u;

    switch(opcode & 0x000Fu){
        case 0x0000:
            OP_8xy0(x , y);
            break;
        case 0x0001:
            OP_8xy1(x , y);
            break;
        case 0x0002:
            OP_8xy2(x , y);
            break;
        case 0x0003:
            OP_8xy3(x , y);
            break;
        case 0x0004:
            OP_8xy4(x , y);
            break;
        case 0x0005:
            OP_8xy5(x , y);
            break;
        case 0x0006:
            OP_8xy6(x , y);
            break;
        case 0x0007:
            OP_8xy7(x , y);
            break;
        case 0x000E:
            OP_8xyE(x , y);
            break;
        default:
            throw std::runtime_error("Unknown opcode [0x8000]: " + std::to_string(opcode));
    }
}

void Cpu::OP_ETable( word opcode ) {
    switch(opcode & 0x00FFu){
        case 0x009E:
            OP_Ex9E(opcode);
            break;
        case 0x00A1:
            OP_ExA1(opcode);
            break;
        default:
            throw std::runtime_error("Unknown opcode [0xE000]: " + std::to_string(opcode));
    }
}

void Cpu::OP_FTable( word opcode ) {
    switch(opcode & 0x00FFu){
        case 0x0007:
            OP_Fx07(opcode);
            break;
        case 0x000A:
            OP_Fx0A(opcode);
            break;
        case 0x0015:
            OP_Fx15(opcode);
            break;
        case 0x0018:
            OP_Fx18(opcode);
            break;
        case 0x001E:
            OP_Fx1E(opcode);
            break;
        case 0x0029:
            OP_Fx29(opcode);
            break;
        case 0x0033:
            OP_Fx33(opcode);
            break;
        case 0x0055:
            OP_Fx55(opcode);
            break;
        case 0x0065:
            OP_Fx65(opcode);
            break;
        default:
            throw std::runtime_error("Unknown opcode [0xF000]: " + std::to_string(opcode));
    }
}



