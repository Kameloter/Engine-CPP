#ifndef COLOR_H
#define COLOR_H
#include <glm.hpp>
#include "Color.h"

class Color
{
    public:
        static  glm::vec3 Red;
        static  glm::vec3 Green;
        static  glm::vec3 Blue;
        static  glm::vec3 White;
        static  glm::vec3 Black;
        static  glm::vec3 Maroon;
        static  glm::vec3 SkyBlue;
        static  glm::vec3 Cyan;
        static  glm::vec3 ForestGreen;
        static  glm::vec3 Gold;
        static  glm::vec3 Pink;
        static  glm::vec3 Orange;
        static  glm::vec3 Tomato;
};

glm::vec3 Color::Red = glm::vec3(1,0,0);
glm::vec3 Color::Green = glm::vec3(0,1,0);
glm::vec3 Color::Blue = glm::vec3(0,0,1);
glm::vec3 Color::White = glm::vec3(1);
glm::vec3 Color::Black = glm::vec3(0);
glm::vec3 Color::Maroon = glm::vec3( 0.690196f, 0.188235f, 0.376471f);
glm::vec3 Color::SkyBlue = glm::vec3(0.529412f, 0.807843f, 0.921569f);
glm::vec3 Color::Cyan = glm::vec3(0,1,1);
glm::vec3 Color::ForestGreen = glm::vec3(0.133333f,0.545098f,0.133333f);
glm::vec3 Color::Gold = glm::vec3(1,0.843137f,0);
glm::vec3 Color::Pink = glm::vec3(1,0.752941f,0.796078f);
glm::vec3 Color::Orange = glm::vec3(1, 0.647059f, 0);
glm::vec3 Color::Tomato = glm::vec3(1, 0.388235f, 0.278431f);

#endif // COLOR_H
