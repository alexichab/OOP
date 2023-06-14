#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum {
    LEFT = 1,
    RIGHT,
    TOP,
    BOT
};

class Shape : public sf::ConvexShape
{
private:
    sf::Vector2f speed;

public:
    Shape();
    void setSpeed(sf::Vector2f _speed);
    void setSpeed(float _x, float _y);
    sf::Vector2f getSpeed(void);
    virtual void move(sf::Vector2i win, sf::Vector2f offset);
    virtual void move(int winX, int winY, float offsetX, float offsetY);
    virtual void move(sf::Vector2i win, float offsetX, float offsetY);
    virtual void move(int winX, int winY, sf::Vector2f offset);
};

class Ellipse : public Shape
{
private:
    sf::Vector2f radius;
    const int pointCount = 90;
    void updatePoints(void);
    void setPointCount();
    void setPoint();

public:
    Ellipse(sf::Vector2f _radius);
    Ellipse(float _radiusX, float _radiusY);
    Ellipse();
    void setRadius(sf::Vector2f _radius);
    void setRadius(float _radiusX, float _radiusY);
    sf::Vector2f getRadius(void);
    void move(sf::Vector2i win, sf::Vector2f offset);
};

class Rectangle : public Shape
{
private:
    sf::Vector2f size;
    void updatePoints();
    void setPointCount();
    void setPoint();

public:
    Rectangle(sf::Vector2f _size);
    Rectangle(float _w, float _h);
    Rectangle();
    void setSize(sf::Vector2f _size);
    void setSize(float _w, float _h);
    sf::Vector2f getSize(void);
    void move(sf::Vector2i win, sf::Vector2f offset);
};
// Human
class Human : public Rectangle
{
private:
    float speed;
    std::vector<Shape *> child;
public:
    Human();
    Human(float Speed);
    void moveElements(Shape* shapes);
    void control(sf::Vector2i win, int Direction, Human* shapes);
    std::vector<Shape *> getChild();
};