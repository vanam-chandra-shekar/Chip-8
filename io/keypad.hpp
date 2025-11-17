#pragma once
#include <unordered_map>
#include <vector>

class Keypad {

public:
    static const int KEY_COUNT = 16;
    
    Keypad() 
        : m_Keys(KEY_COUNT, false)
    {}

    void PressKey(int key) {
        if (key >= 0 && key < KEY_COUNT) {
            m_Keys[key] = true;
        }
    }

    void ReleaseKey(int key) {
        if (key >= 0 && key < KEY_COUNT) {
            m_Keys[key] = false;
        }
    }

    bool IsKeyPressed(int key) const {
        if (key >= 0 && key < KEY_COUNT) {
            return m_Keys[key];
        }
        return false;
    }


private:
    std::vector<bool> m_Keys;

};