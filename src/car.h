#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    void setMark(QString mark);

    void setModel(QString model);

    void setYear(QString year);

    void setVin(QString vin);

    void setNumber(QString number);

    QString getMark(void);

    QString getModel(void);

    QString getYear(void);

    QString getVin(void);

    QString getNumber(void);

private:
    QString mark;
    QString model;
    QString year;
    QString vin;
    QString number;
};

#endif // CAR_H
