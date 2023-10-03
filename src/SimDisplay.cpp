#include "SimDisplay.h"
#include <iostream>
SimDisplay::SimDisplay()
:m_displayWidth(0),
 m_displayHeight(0),
 m_sdlWindow(nullptr)
 {}

 SimDisplay::~SimDisplay()
 {

 }

 bool SimDisplay::SDL_createRenderer(std::string title, int displayWidth, int displayHeight)
 {

    this->m_displayHeight=displayHeight;
    this->m_displayWidth=displayWidth;

    m_sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, SDL_WINDOW_MAXIMIZED );
    if (m_sdlWindow == nullptr)
    {
      std::cout << SDL_GetError() << std::endl;
      return false;
    }
    return true;
 }

  void SimDisplay::showScreen()
  {
  std::cout<<"next implement showScreen function"<<std::endl;
  }