#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "loaders/stb_image.h"
#include <iostream>
#include <string>

void LoadTexture(GLuint &texture,const char* filePath, std::string ext);
