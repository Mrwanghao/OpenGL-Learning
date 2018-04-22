#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Camera.h"
#include "EngineEnum.h"

extern bool firstMouse;
extern double lastX;
extern double lastY;

void processInput(GLFWwindow *pWindow);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *pWindow, int pWidth, int pHeight);

GLuint load_image(std::string pTexFileName);
GLuint load_cube_map(std::vector<std::string> p_faces);


