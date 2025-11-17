#pragma once

#include <vector>

class Display {
public:
    static const int WIDTH = 64;
    static const int HEIGHT = 32;
    int m_scale;

    constexpr int getWidth() const { return WIDTH * m_scale; }
    constexpr int getHeight() const { return HEIGHT * m_scale; }

    std::vector<bool> m_Pixels;

    Display(int scale) : m_scale(scale), m_Pixels(WIDTH * HEIGHT, false) {}
};