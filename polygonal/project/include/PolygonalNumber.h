#ifndef POLYGONALNUMBER_H
#define POLYGONALNUMBER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#define MIN_BASE 3
#define MIN_NUM 1
#define POINT_SIZE 4.0f
#define DEF_INDENT 20

#define CENTRAL_ANGLE(base) (360.0f / base)
#define GRAD_TO_RAD(grad) (grad * M_PI / 180.0f)

class PolygonalNumber {
public:
    PolygonalNumber(int base, int num, float indent);

    void draw(sf::RenderWindow &win);

    void SetPosition(float x, float y) {
        m_x = x;
        m_y = y;
    }

    void Increment() { appendGnomone(++m_num); }

    void Decrement() {
        if (m_num <= MIN_NUM) {
            return;
        }

        --m_num;
        points.pop_back();
    }

    int CalculateLineNumber() const;

    [[nodiscard]] int GetBase() const { return m_base; }
    [[nodiscard]] int GetNum() const { return m_num; }

private:
    struct Point {
        Point() : m_cond_x(0), m_cond_y(0) {}

        Point(float cond_x, float cond_y)
                : m_cond_x(cond_x), m_cond_y(cond_y) {
            point_body.setRadius(POINT_SIZE);
            point_body.setFillColor(sf::Color::Black);
        }

        sf::CircleShape point_body;

        float m_cond_x;
        float m_cond_y;
    };

    int m_base;
    int m_num;

    float m_central_angle;
    float m_x;
    float m_y;
    float m_indent;

    std::vector<std::vector<Point>> points;

    void appendGnomone(int n);
};


#endif //POLYGONALNUMBER_H
