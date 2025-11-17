#pragma once 

#include "cpu.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include <GLFW/glfw3.h>

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

};