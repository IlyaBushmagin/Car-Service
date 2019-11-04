#include "client.h"

void Client::setName(QString name)
{
    this->name = name;
}

void Client::setPhone(QString phone)
{
    this->phone = phone;
}

void Client::addService(Service *service)
{
    serviceList.append(service);
}

void Client::removeService(int index)
{
    serviceList.removeAt(index);
}

Car* Client::getCar(void)
{
    return &car;
}

Service* Client::getService(int index)
{
    return serviceList[index];
}

QString Client::getName(void)
{
    return name;
}

QString Client::getPhone(void)
{
    return phone;
}

int Client::serviceListSize(void)
{
    return serviceList.size();
}
