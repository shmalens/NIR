#include <sstream>
#include <SFML/Graphics.hpp>

#include "WindowManager.h"
#include "PolygonalNumber.h"

WindowManager::WindowManager(unsigned int win_width, unsigned int win_height, std::string font_file, PolygonalNumber &pn)
        : win_size(sf::Vector2u(win_width, win_height)),
          win(sf::VideoMode(win_width, win_height), WIN_TITLE),
          polygonal_number(pn) {
    if (!font.loadFromFile(font_file)) {
        throw std::exception();
    }

    text.setFont(font);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color::Black);
}

void WindowManager::Dispatch() {
    win_size = win.getSize();
    polygonal_number.SetPosition((float)win_size.x / 2, (float)win_size.y / 2);

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                keyboardHandler();
            }

            draw();
        }
    }
}

void WindowManager::draw() {
    win.clear(sf::Color::White);

    std::string text_info = getTextInfo();
    text.setString(text_info);
    polygonal_number.draw(win);
    win.draw(text);
    win.display();
}

std::string WindowManager::getTextInfo() {
    std::stringstream info;
    info << "Base: " << polygonal_number.GetBase() << '\n'
    << "Number: " << polygonal_number.GetNum() << '\n'
    << "Equal to " << polygonal_number.CalculateLineNumber() << " line number";
    return info.str();
}

void WindowManager::keyboardHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        polygonal_number.Increment();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        polygonal_number.Decrement();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        int curr_base = polygonal_number.GetBase();
        curr_base = (curr_base <= MIN_BASE ? MIN_BASE : --curr_base);
        int curr_num = polygonal_number.GetNum();
        polygonal_number = PolygonalNumber(curr_base, curr_num, DEF_INDENT);
        polygonal_number.SetPosition((float)win_size.x / 2, (float)win_size.y / 2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        int curr_base = polygonal_number.GetBase();
        int curr_num = polygonal_number.GetNum();
        polygonal_number = PolygonalNumber(++curr_base, curr_num, DEF_INDENT);
        polygonal_number.SetPosition((float)win_size.x / 2, (float)win_size.y / 2);
    }
}
