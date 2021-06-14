#include <vector>
#include <math.h>

#include "PolygonalNumber.h"

PolygonalNumber::PolygonalNumber(int base, int num, float indent) :
        m_indent(indent), m_x(0), m_y(0) {
    if (base < MIN_BASE || num < MIN_NUM) {
        throw std::exception();
    }
    m_base = base;
    m_num = num;
    m_central_angle = CENTRAL_ANGLE(m_base);

    for (int i = MIN_NUM; i <= m_num; ++i) {
        appendGnomone(i);
    }
}

void PolygonalNumber::appendGnomone(int n) {
    std::vector<Point> gnomone;
    std::vector<std::pair<Point, Point>> edges(m_base);
    if (n == 1) {
        Point new_point(m_x, m_y);
        gnomone.emplace_back(new_point);
        points.push_back(gnomone);
        return;
    }

    float gnomone_center_indent = m_indent * ((float) n - 1);

    for (int i = 0; i < m_base; ++i) {
        float curr_angle = m_central_angle * (float) i;
        float curr_x = gnomone_center_indent * std::cos(GRAD_TO_RAD(curr_angle));
        curr_x += (m_base % 2 == 0 ? gnomone_center_indent : gnomone_center_indent * -1);
        float curr_y = gnomone_center_indent * std::sin(GRAD_TO_RAD(curr_angle));
        Point new_point(curr_x, curr_y);
        gnomone.push_back(new_point);

        edges[i].first = new_point;
        if (i == 0) {
            edges[edges.capacity() - 1].second = new_point;
        } else {
            edges[i - 1].second = new_point;
        }
    }

    if (n == 2) {
        points.push_back(gnomone);
        return;
    }

    int parts = n - 1;

    for (int i = 0; i < edges.size(); ++i) {
        Point &p1 = edges[i].first;
        Point &p2 = edges[i].second;

        for (int j = 1; j < parts; ++j) {
            float lambda = (float) j / ((float) parts - (float) j);
            float intermediate_x = (p1.m_cond_x + lambda * p2.m_cond_x) / (1 + lambda);
            float intermediate_y = (p1.m_cond_y + lambda * p2.m_cond_y) / (1 + lambda);

            Point intermediate_point(intermediate_x, intermediate_y);
            gnomone.push_back(intermediate_point);
        }
    }

    points.push_back(gnomone);
}

void PolygonalNumber::draw(sf::RenderWindow &win) {
    float is_odd = (m_base % 2 == 0 ? -1.0f : 1.0f);
    float addition_x = m_x + m_indent * m_num * is_odd;
    float addition_y = m_y;

    for (std::vector<Point> &gnomone : points) {
        for (Point &point : gnomone) {
            point.point_body.setPosition(sf::Vector2f(point.m_cond_x + addition_x, point.m_cond_y + addition_y));
            win.draw(point.point_body);
        }
    }
}

int PolygonalNumber::CalculateLineNumber() const {
    return (m_base * (m_num * m_num - m_num)) / 2 - m_num * m_num + 2 * m_num;
}