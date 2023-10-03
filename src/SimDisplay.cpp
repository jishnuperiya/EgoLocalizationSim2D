#include "SimDisplay.h"
#include <iostream>
SimDisplay::SimDisplay()
:m_displayWidth(0),
 m_displayHeight(0)
 {}

 SimDisplay::~SimDisplay()
 {

 }

 bool SimDisplay::createRenderer(std::string title, int displayWidth, int displayHeight)
 {

    this->m_displayHeight=displayHeight;
    this->m_displayWidth=displayWidth;

    std::cout << "inside the create renderer function"<<std::endl;

    return true;
 }