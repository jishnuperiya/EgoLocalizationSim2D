#ifndef SimDisplay_H
#define SimDisplay_H

#include <string>



class SimDisplay
{
    public:

    SimDisplay();
    ~SimDisplay();

    bool createRenderer(std::string title, int displayWidth, int displayHeight);

    private:
    int m_displayWidth;
    int m_displayHeight;


};








#endif // SimDisplay_H
