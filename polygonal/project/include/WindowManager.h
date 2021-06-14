#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>

#include "PolygonalNumber.h"

#define WIN_TITLE "POLYGONAL NUMBERS"
#define FONT_SIZE 24

class WindowManager {
public:
    WindowManager() = delete;

    WindowManager(unsigned int win_width, unsigned int win_height, std::string font_file, PolygonalNumber &pn);

    void Dispatch();

private:
    sf::RenderWindow win;
    sf::Font font;
    sf::Text text;
    sf::Vector2u win_size;

    PolygonalNumber &polygonal_number;

    void draw();
    std::string getTextInfo();
    void keyboardHandler();
};

#endif //WINDOWMANAGER_H
