// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef max
#undef min
#include <math.h>

//OPENGL includes
#define GLEW_STATIC
#include "../3rd-party/glew-2.0.0/src/glew.h"
#include <GL/gl.h>
#pragma comment(lib,"opengl32.lib")