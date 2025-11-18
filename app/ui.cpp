#include "app.hpp"
#include "imgui.h"
#include <GL/gl.h>
#include <cstdint>

uint32_t ON = 0xFFF00FFF;   // White
uint32_t OFF = 0xFF000000;  // Black

void Application::renderUI()
{

    updateTexture(ON, OFF);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("CHIP-8 Display", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNav|
        ImGuiWindowFlags_NoResize);

    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGui::Image((void*)(intptr_t)m_displayTexture, avail);
    ImGui::End();
    ImGui::PopStyleVar();

}


void Application::initTexture(){

    glGenTextures(1, &m_displayTexture);
    glBindTexture(GL_TEXTURE_2D, m_displayTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                m_display.WIDTH, m_display.HEIGHT,
                0, GL_RGBA, GL_UNSIGNED_BYTE,
                nullptr);

}

void Application::updateTexture(uint32_t color_on, uint32_t color_off){

    bool* displayBuffer = m_display.getBuffer();

    for (int i = 0; i < m_display.WIDTH * m_display.HEIGHT; i++){
        m_displayPixels[i] = displayBuffer[i] ? color_on : color_off;
    }

    glBindTexture(GL_TEXTURE_2D, m_displayTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                    m_display.WIDTH, m_display.HEIGHT,
                    GL_RGBA, GL_UNSIGNED_BYTE,
                    m_displayPixels.data());
}
