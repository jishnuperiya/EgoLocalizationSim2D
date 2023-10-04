#include "SimDisplay.h"
#include <iostream>
SimDisplay::SimDisplay()
:m_displayWidth(0),
 m_displayHeight(0),
 m_sdlWindow(nullptr),
 m_sdlRenderer(nullptr),
 m_sdlMainFont(nullptr)
 {}

 SimDisplay::~SimDisplay()
 {
  SDL_destroyRenderer();
 }

 bool SimDisplay::SDL_createRenderer(std::string title, int displayWidth, int displayHeight)
 {

    this->m_displayHeight=displayHeight;
    this->m_displayWidth=displayWidth;
    
    // Create window
    m_sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, SDL_WINDOW_MAXIMIZED );
    if (m_sdlWindow == nullptr)
    {
      std::cout << SDL_GetError() << std::endl;
      return false;
    }

    // Create Renderer
    m_sdlRenderer = SDL_CreateRenderer( m_sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( m_sdlRenderer == nullptr )
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_destroyRenderer();
        return false;
    }

    // Create Font
    m_sdlMainFont = TTF_OpenFont( "Roboto-Regular.ttf", 18 );
    if( m_sdlMainFont == nullptr )
    {
        std::cout << "Failed to load font! SDL_ttf Error: " <<  TTF_GetError() << std::endl;
        SDL_destroyRenderer();
        return false;
    }
    return true;
 }



void SimDisplay::SDL_destroyRenderer()
{
    // Destroy Renderer
    if (m_sdlRenderer != nullptr)
    {
        SDL_DestroyRenderer( m_sdlRenderer );
        m_sdlRenderer = nullptr;
    }

    // Destroy Window
    if(m_sdlWindow != nullptr)
    {
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = nullptr;
    }

    // Destroy Font
    if(m_sdlMainFont != nullptr)
    {
        TTF_CloseFont(m_sdlMainFont);
        m_sdlMainFont = nullptr;
    }
}

void SimDisplay::showScreen()
{
    if (m_sdlRenderer != nullptr)
    {
        SDL_RenderPresent( m_sdlRenderer );
    }
}

void SimDisplay::clearScreen()
{
    if (m_sdlRenderer != nullptr)
    {
        //Clear screen
        SDL_SetRenderDrawColor( m_sdlRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( m_sdlRenderer );
    }
}