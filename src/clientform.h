#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QStringListModel>
#include <QMessageBox>
#include <QDialog>
#include "client.h"
#include "service.h"

namespace Ui
{
    class ClientForm;
}

class ClientForm : public QDialog
{
    Q_OBJECT

public:
    explicit ClientForm(QWidget *parent = nullptr);

    void setServicesBase(Service *servicesBase, int servicesBaseSize);

    void setClientsBase(QList<Client> *clientsBase);

    void setClient(int selectedClientNumber);

    void setClient(void);

    void setClientData(void);

    void getClientData(void);

    void setServiceList(void);

    void setFoundServicesList(void);

    void setSelectedServicesList(void);

    void calculateCost(void);

    void search(void);

    ~ClientForm();

private slots:
    void on_ok_clicked(void);

    void on_delete__clicked(void);

    void on_add_clicked(void);

    void on_reset_clicked(void);

    void on_engine_clicked(void);

    void on_transmission_clicked(void);

    void on_steering_clicked(void);

    void on_chassis_clicked(void);

    void on_repairs_clicked(void);

    void on_diagnostics_clicked(void);

    void on_maintenance_clicked(void);

    void on_brakeSystem_clicked(void);

    void on_searchBar_textEdited(void);

private:
    Ui::ClientForm *ui;
    QStringListModel *foundServicesList;
    QStringListModel *selectedServicesList;
    QList<Client> *clientsBase;
    QList<Service*> *serviceList;
    Client *client;
    Service *servicesBase;
    int selectedClientNumber;
    int servicesBaseSize;
    bool newClient;
};

#endif // CLIENTFORM_H
