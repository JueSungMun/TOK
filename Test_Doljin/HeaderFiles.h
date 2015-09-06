#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <tchar.h>
#include "Objects.h"
#include <iostream>

using namespace std;

#ifdef UNICODE
  #ifndef _UNICODE
    #define _UNICODE
  #endif
#endif
#ifdef _UNICODE
  #ifndef UNICODE
    #define UNICODE
  #endif
#endif

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define IMG_BG _T("..\\Resource\\Sword.png")
#define IMG_CARD_ATTACK _T("..\\Resource\\Card_Attack.png")

#pragma warning( default : 4996 ) 
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")