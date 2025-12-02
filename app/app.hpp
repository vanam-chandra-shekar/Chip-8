#pragma once 

#include "cpu.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <unordered_map>

class Application {

public:

    Application(const char* title , int display_scale);
    ~Application();
    void run(const char* romPath);

    void renderUI();

private:

    GLFWwindow* window;
    const char* m_title;
    Display m_display;
    Keypad m_keypad;
    Cpu m_cpu;
    GLuint m_displayTexture {0};
    std::vector<uint32_t> m_displayPixels;
    std::unordered_map<int, int> m_keyMap {
        {GLFW_KEY_1 , 0x1},
        {GLFW_KEY_2 , 0x2},
        {GLFW_KEY_3 , 0x3},
        {GLFW_KEY_4 , 0xC},
        {GLFW_KEY_Q , 0x4},
        {GLFW_KEY_W , 0x5},
        {GLFW_KEY_E , 0x6},
        {GLFW_KEY_R , 0xD},
        {GLFW_KEY_A , 0x7},
        {GLFW_KEY_S , 0x8},
        {GLFW_KEY_D , 0x9},
        {GLFW_KEY_F , 0xE},
        {GLFW_KEY_Z , 0xA},
        {GLFW_KEY_X , 0x0},
        {GLFW_KEY_C , 0xB},
        {GLFW_KEY_V , 0xF}

    };

    void initTexture();
    void updateTexture(uint32_t color_on, uint32_t color_off);
    void processInput();

};