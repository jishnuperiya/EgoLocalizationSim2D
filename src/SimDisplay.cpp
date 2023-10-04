#include "SimDisplay.h"
#include <iostream>


SimDisplay::SimDisplay()
  :mScreenWidth(0),
   mScreenHeight(0),
   mSDLWindow(nullptr),
   mSDLRenderer(nullptr),
   mSDLMainFont(nullptr)
 {}

 SimDisplay::~SimDisplay()
 {
    SDL_destroyRenderer();
 }

 bool SimDisplay::SDL_createRenderer(std::string title)
 {

    mScreenHeight=SimDisplay::DISPLAY_HEIGHT;
    mScreenWidth=SimDisplay::DISPLAY_WIDTH;

    mViewWidth = mScreenWidth;
    mViewHeight = mScreenHeight;
    mViewXOffset = 0.0;
    mViewYOffset = 0.0;
    
    // Create window
    mSDLWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenWidth, mScreenHeight, SDL_WINDOW_MAXIMIZED );
    if (mSDLWindow == nullptr)
    {
      std::cout << SDL_GetError() << std::endl;
      return false;
    }

    // Create Renderer
    mSDLRenderer = SDL_CreateRenderer( mSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( mSDLRenderer == nullptr )
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_destroyRenderer();
        return false;
    }

    // Create Font
    mSDLMainFont = TTF_OpenFont( "Roboto-Regular.ttf", 18 );
    if( mSDLMainFont == nullptr )
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
    if (mSDLRenderer != nullptr)
    {
        SDL_DestroyRenderer( mSDLRenderer );
        mSDLRenderer = nullptr;
    }

    // Destroy Window
    if(mSDLWindow != nullptr)
    {
        SDL_DestroyWindow(mSDLWindow);
        mSDLWindow = nullptr;
    }

    // Destroy Font
    if(mSDLMainFont != nullptr)
    {
        TTF_CloseFont(mSDLMainFont);
        mSDLMainFont = nullptr;
    }
}

void SimDisplay::showScreen()
{
    if (mSDLRenderer != nullptr)
    {
        SDL_RenderPresent( mSDLRenderer );
    }
}


void SimDisplay::setDrawColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha){SDL_SetRenderDrawColor( mSDLRenderer, red, green, blue, alpha );}

void SimDisplay::drawBackgroundMesh(){
    setDrawColour(101, 101, 101);
    for (int x = -SimDisplay::MESH_SIZE; x <= SimDisplay::MESH_SIZE; x += SimDisplay::MESH_SPACEING) {
        drawLine(Vector2(x, -SimDisplay::MESH_SIZE), Vector2(x, SimDisplay::MESH_SIZE));
    }
    for (int y = -SimDisplay::MESH_SIZE; y <= SimDisplay::MESH_SIZE; y += SimDisplay::MESH_SPACEING) {
        drawLine(Vector2(-SimDisplay::MESH_SIZE, y), Vector2(SimDisplay::MESH_SIZE, y));
    }
}


void SimDisplay::clearScreen()
{
    if (mSDLRenderer != nullptr)
    {
        //Clear screen
        SDL_SetRenderDrawColor( mSDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( mSDLRenderer );
    }
}

void SimDisplay::drawLine(const Vector2& startPos, const Vector2& endPos)
{
    Vector2 p1 = transformPoint(startPos);
    Vector2 p2 = transformPoint(endPos);
    SDL_RenderDrawLine( mSDLRenderer, p1.x, p1.y, p2.x, p2.y );
}


Vector2 SimDisplay::transformPoint(const Vector2& point)
{
    double dx = point.x - mViewXOffset;
    double dy = point.y - mViewYOffset;
    double y = mScreenHeight - (dx/mViewHeight)*mScreenHeight;
    double x = (dy/mViewWidth)*mScreenWidth;
    return Vector2(x,y);
}