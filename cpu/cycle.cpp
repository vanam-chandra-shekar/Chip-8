#include "cpu.hpp"
#include <stdexcept>


void Cpu::runCycle() {
    
    uint16_t opcode = (m_memory[m_pc] << 8) | m_memory[m_pc + 1];
    m_pc += 2;

    byte firstNibble = (opcode & 0xF000u) >> 12u;

    if (firstNibble > 0xF ){
        throw std::runtime_error("Unknown opcode encountered");
    }


    (this->*dispachTable[firstNibble])(opcode);

    // Update timers
    if(m_timerDelay > 0){
        --m_timerDelay;
    }

    if(m_timerSound > 0){
        --m_timerSound;
    }

}




