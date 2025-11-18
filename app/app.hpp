#pragma once 

#include "cpu.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>

class Application {

public:

    Application(const char* title , int display_scale);
    ~Application();
    void run();

    void renderUI();

private:

    GLFWwindow* window;
    const char* m_title;
    Display m_display;
    Keypad m_keypad;
    Cpu m_cpu;
    GLuint m_displayTexture {0};
    std::vector<uint32_t> m_displayPixels;

    void initTexture();
    void updateTexture(uint32_t color_on, uint32_t color_off);

};