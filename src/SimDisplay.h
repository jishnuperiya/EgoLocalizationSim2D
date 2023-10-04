#ifndef SimDisplay_H
#define SimDisplay_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <string>


struct Vector2
{
    double x,y;
    Vector2():x(0.0),y(0.0){};
    Vector2(double _x, double _y):x(_x),y(_y){};
};

class SimDisplay
{
    public:

    SimDisplay();
    ~SimDisplay();

    bool SDL_createRenderer(std::string title, int displayWidth, int displayHeight);
    void SDL_destroyRenderer();

    void showScreen();
    void clearScreen();


    double getScreenWidth()const {return mScreenWidth;}
    double getScreenHeight() const {return mScreenHeight;}
    double getScreenAspectRatio() const {return getScreenWidth()/getScreenHeight(); }


    void setDrawColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=0xFF);
    void drawLine(const Vector2& startPos, const Vector2& endPos);
            

    private:

     Vector2 transformPoint(const Vector2& point);


    int mScreenWidth;
    int mScreenHeight;

    double mViewWidth;
    double mViewHeight;
    double mViewXOffset;
    double mViewYOffset;

    SDL_Window* mSDLWindow;
    SDL_Renderer* mSDLRenderer;
    TTF_Font *mSDLMainFont;

};

#endif // SimDisplay_H
