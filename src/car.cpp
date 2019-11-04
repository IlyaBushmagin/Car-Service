#include "car.h"

void Car::setMark(QString mark)
{
    this->mark = mark;
}

void Car::setModel(QString model)
{
    this->model = model;
}

void Car::setYear(QString year)
{
    this->year = year;
}

void Car::setVin(QString vin)
{
    this->vin = vin;
}

void Car::setNumber(QString number)
{
    this->number = number;
}

QString Car::getMark(void)
{
    return mark;
}

QString Car::getModel(void)
{
    return model;
}

QString Car::getYear(void)
{
    return year;
}

QString Car::getVin(void)
{
    return vin;
}

QString Car::getNumber(void)
{
    return number;
}
