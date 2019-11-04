#include "service.h"

void Service::setName(QString name)
{
    this->name = name;
}

void Service::setEngine(bool engine)
{
    this->engine = engine;
}

void Service::setBrakeSystem(bool brakeSystem)
{
    this->brakeSystem = brakeSystem;
}

void Service::setSteering(bool steering)
{
    this->steering = steering;
}

void Service::setTransmission(bool transmission)
{
    this->transmission = transmission;
}

void Service::setChassis(bool chassis)
{
    this->chassis = chassis;
}

void Service::setRepairs(bool repairs)
{
    this->repairs = repairs;
}

void Service::setDiagnostics(bool diagnostics)
{
    this->diagnostics = diagnostics;
}

void Service::setMaintenance(bool maintenance)
{
    this->maintenance = maintenance;
}

void Service::setCost(int cost)
{
    this->cost = cost;
}

void Service::setIndex(int index)
{
    this->index = index;
}

bool Service::isEngine(void)
{
    return engine;
}

bool Service::isBrakeSystem(void)
{
    return brakeSystem;
}

bool Service::isSteering(void)
{
    return steering;
}

bool Service::isTransmission(void)
{
    return transmission;
}

bool Service::isChassis(void)
{
    return chassis;
}

bool Service::isRepairs(void)
{
    return repairs;
}

bool Service::isDiagnostics(void)
{
    return diagnostics;
}

bool Service::isMaintenance(void)
{
    return maintenance;
}

int Service::getIndex(void)
{
    return index;
}

int Service::getCost(void)
{
    return cost;
}

QString Service::getName(void)
{
    return name;
}
