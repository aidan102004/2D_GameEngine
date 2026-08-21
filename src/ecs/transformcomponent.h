#pragma once

#include "components.h"

class TransformComponent : public Component
{
    private:
        int xpos = 0;
        int ypos = 0;
    public:
        TransformComponent()
        {
            xpos = 0;
            ypos = 0;
        }
        TransformComponent(int x, int y)
        {
            xpos = x;
            ypos = y;
        }
        int x() {return xpos;}
        int y() {return ypos;}

        void init() override
        {
            xpos = 0;
            ypos = 0;
        }

        void update() override
        {
            xpos++;
            ypos++;
        }
        void setPos(int x, int y)
        {
            xpos = x;
            ypos = y;
        }
};