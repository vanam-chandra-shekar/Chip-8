#pragma once


#include <winscard.h>
class Display {
public:
    static const int WIDTH = 64;
    static const int HEIGHT = 32;
    int m_scale;

    constexpr int getWidth() const { return WIDTH * m_scale; }
    constexpr int getHeight() const { return HEIGHT * m_scale; }

    bool* buffer;

    Display(int scale) : m_scale(scale), buffer(new bool[WIDTH * HEIGHT]()) {
        
    }
    ~Display() { delete[] buffer; }

    inline void clear() {
        for (int i = 0; i < WIDTH * HEIGHT; ++i) {
            buffer[i] = false;
        }
    }

    void setPixel(int x, int y, bool value) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
        buffer[y * WIDTH + x] = value;
    }

    bool getPixel(int x , int y){
        return buffer[y * WIDTH + x];
    }

    bool* getBuffer() {
        return buffer;
    }
};