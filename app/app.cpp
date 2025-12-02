#include "app.hpp"
#include <GL/gl.h>
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <chrono>

static void error_callback(int error, const char* description)
{
    std::clog << "Error: " << description << "\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Application::processInput() {

    //keypad mapping
    for (const auto& [glfwKey, chip8Key] : m_keyMap) {
        if (glfwGetKey(window, glfwKey) == GLFW_PRESS) {
            m_keypad.setKey(chip8Key, true);
        } else {
            m_keypad.setKey(chip8Key, false);
        }
    }

    glfwPollEvents();
}




Application::Application(const char* title , int display_scale) 
    : m_title(title),
      m_display(display_scale),
      m_keypad(),
      m_cpu(m_display, m_keypad),
      m_displayTexture(0),
      m_displayPixels(m_display.HEIGHT * m_display.WIDTH)
{

    glfwSetErrorCallback(error_callback);
    
    if(!glfwInit()){
        std::clog<<"Failed to start GLFW\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    window = glfwCreateWindow(m_display.getWidth(), m_display.getHeight(), m_title, NULL, NULL);

    if(!window){
        std::clog<<"Unable to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    initTexture();

}

void Application::run(const char* romPath) {

    m_cpu.LoadROM(romPath);

    auto lastCycleDelay = std::chrono::high_resolution_clock::now();

    while(!glfwWindowShouldClose(window)){

        processInput();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui UI

        auto now = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::milli>(now - lastCycleDelay).count();

        if(dt >= 3.0f){ //500 Hz
            m_cpu.runCycle();
            lastCycleDelay = now;
            renderUI();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }


}

Application::~Application() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}