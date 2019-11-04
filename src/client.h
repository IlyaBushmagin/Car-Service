#ifndef CLIENT_H
#define CLIENT_H

#include <QList>
#include "car.h"
#include "service.h"

class Client
{
public:
    void setName(QString name);

    void setPhone(QString phone);

    void addService(Service *service);

    void removeService(int index);

    Car* getCar(void);

    Service* getService(int index);

    QString getName(void);

    QString getPhone(void);

    int serviceListSize(void);

private:
    Car car;
    QString name;
    QString phone;
    QList<Service*> serviceList;
};

#endif // CLIENT_H
