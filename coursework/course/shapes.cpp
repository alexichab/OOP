#include "shapes.hpp"
#include <cmath>
#include <SFML/Graphics/ConvexShape.hpp>

// shape
Shape::Shape() : sf::ConvexShape()
{
    speed.x = 0;
    speed.y = 0;
}
void Shape::setSpeed(sf::Vector2f _speed)
{
    speed = _speed;
}
void Shape::setSpeed(float _x, float _y)
{
    setSpeed(sf::Vector2f(_x, _y));
}
sf::Vector2f Shape::getSpeed(void)
{
    return speed;
}

void Shape::move(sf::Vector2i win, sf::Vector2f offset)
{
    setFillColor(sf::Color::Green);
}

void Shape::move(int winX, int winY, float offsetX, float offsetY)
{
    move(sf::Vector2i(winX, winY), sf::Vector2f(offsetX, offsetY)); // Основное движение
}

void Shape::move(sf::Vector2i win, float offsetX, float offsetY)
{
    move(win, sf::Vector2f(offsetX, offsetY));
}
void Shape::move(int winX, int winY, sf::Vector2f offset)
{
    move(sf::Vector2i(winX, winY), offset);
}

// ellipse
Ellipse::Ellipse(sf::Vector2f _radius) : Shape()
{
    setRadius(_radius);
}

Ellipse::Ellipse(float _radiusX, float _radiusY) : Shape()
{
    setRadius(_radiusX, _radiusY);
}

Ellipse::Ellipse() : Shape()
{
    setFillColor(sf::Color::White);
    setRadius(35, 35);
}

void Ellipse::updatePoints()
{
    if (getPointCount() != pointCount)
        Shape::setPointCount(pointCount);

    float rad, x, y;
    for (int i = 0; i < pointCount; i++)
    {
        rad = (360 / pointCount * i) / (360 / M_PI / 2);
        x = cos(rad) * radius.x;
        y = sin(rad) * radius.y;
        Shape::setPoint(i, sf::Vector2f(x, y));
    }
}

void Ellipse::setRadius(sf::Vector2f _radius)
{
    radius.x = (_radius.x) ? _radius.x : 0;
    radius.y = (_radius.y) ? _radius.y : 0;

    updatePoints();
}

void Ellipse::setRadius(float _radiusX, float _radiusY)
{
    setRadius(sf::Vector2f(_radiusX, _radiusY));
}

sf::Vector2f Ellipse::getRadius(void)
{
    return radius;
}

void Ellipse::move(sf::Vector2i win, sf::Vector2f offset)
{
    sf::Vector2f pos = getPosition();

    if (pos.x < 50 && getSpeed().x < 0) 
        return;
    else if (pos.x > 670 && getSpeed().x > 0) 
        return;
    else if (pos.y < 30 && getSpeed().y < 0) 
        return;
    else if (pos.y > 460 && getSpeed().y > 0) 
        return;
    
    setPosition(getPosition() + offset);
}

// rectangle
Rectangle::Rectangle(sf::Vector2f _size) : Shape()
{
    setSize(_size);
}

Rectangle::Rectangle(float _w, float _h) : Shape()
{
    setSize(_w, _h);
}

Rectangle::Rectangle() : Shape()
{
    setFillColor(sf::Color::Yellow);
    setSize(30, 100);
    setOrigin(getSize().x / 2, getSize().y / 2);
}

void Rectangle::updatePoints()
{
    if (getPointCount() != 4)
        Shape::setPointCount(4);
    Shape::setPoint(0, sf::Vector2f(0, 0));
    Shape::setPoint(1, sf::Vector2f(size.x, 0));
    Shape::setPoint(2, sf::Vector2f(size.x, size.y));
    Shape::setPoint(3, sf::Vector2f(0, size.y));
}

void Rectangle::setSize(sf::Vector2f _size)
{
    size.x = (_size.x) ? _size.x : 0;
    size.y = (_size.y) ? _size.y : 0;

    updatePoints();
}

void Rectangle::setSize(float _w, float _h)
{
    size.x = (_w) ? _w : 0;
    size.y = (_h) ? _h : 0;

    updatePoints();
}

sf::Vector2f Rectangle::getSize(void)
{
    return size;
}

void Rectangle::move(sf::Vector2i win, sf::Vector2f offset)
{
    sf::Vector2f pos = getPosition();
    if (pos.x < 50 && getSpeed().x < 0) 
        return;
    else if (pos.x > 670 && getSpeed().x > 0) 
        return;
    else if (pos.y < 30 && getSpeed().y < 0) 
        return;
    else if (pos.y > 460 && getSpeed().y > 0) 
        return;
    
    setPosition(getPosition() + offset);
}

Human::Human() : speed{4}
{
    // speed = 3.0;
    setFillColor(sf::Color::Green);
    setSize(70, 140);
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Ellipse());
}

Human::Human(float Speed) 
{
    speed = Speed;
    setFillColor(sf::Color::Green);
    setSize(70, 140);
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Rectangle());
    child.push_back(new Ellipse());
}

std::vector<Shape *> Human::getChild()
{
    return child;
}

void Human::moveElements(Shape* shapes)
{
    child[0]->setPosition(shapes->getPosition().x , shapes->getPosition().y + 140); //leg 1
    child[1]->setPosition(shapes->getPosition().x + 40, shapes->getPosition().y + 140);//leg 2
    child[2]->setPosition(shapes->getPosition().x - 30, shapes->getPosition().y);//arm 1
    child[3]->setPosition(shapes->getPosition().x + 70, shapes->getPosition().y);//arm 2
    child[4]->setPosition(shapes->getPosition().x + 19, shapes->getPosition().y - 85);//head 
}

void Human::control(sf::Vector2i win, int Direction, Human* shapes)
{
    switch (Direction)
    {
    case LEFT:
        shapes->setSpeed(speed * -1, 0);
        break;
    
    case RIGHT:
        shapes->setSpeed(speed, 0);
        break;

    case TOP:
        shapes->setSpeed(0, speed * -1);
        break;

    case BOT:
        shapes->setSpeed(0, speed);
        break;
    
    default:
        return;
    }

    shapes->move(win, shapes->getSpeed());
    shapes->moveElements(shapes);
}