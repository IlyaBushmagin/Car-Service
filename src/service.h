#ifndef SERVICE_H
#define SERVICE_H

#include <QString>

class Service
{
public:
    void setName(QString name);

    void setEngine(bool engine);

    void setBrakeSystem(bool brakeSystem);

    void setSteering(bool steering);

    void setTransmission(bool transmission);

    void setChassis(bool chassis);

    void setRepairs(bool repairs);

    void setDiagnostics(bool diagnostics);

    void setMaintenance(bool maintenance);

    void setIndex(int index);

    void setCost(int cost);

    bool isEngine(void);

    bool isBrakeSystem(void);

    bool isSteering(void);

    bool isTransmission(void);

    bool isChassis(void);

    bool isRepairs(void);

    bool isDiagnostics(void);

    bool isMaintenance(void);

    int getIndex(void);

    int getCost(void);

    QString getName(void);

private:
    QString name;
    bool engine;
    bool brakeSystem;
    bool steering;
    bool transmission;
    bool chassis;
    bool repairs;
    bool diagnostics;
    bool maintenance;
    int index;
    int cost;
};

#endif // SERVICE_H
