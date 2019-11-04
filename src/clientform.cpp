#include "clientform.h"
#include "ui_clientform.h"

ClientForm::ClientForm(QWidget *parent) : QDialog(parent), ui(new Ui::ClientForm)
{
    this->setFixedSize(880, 420);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    foundServicesList = new QStringListModel(this);
    serviceList = new QList<Service*>;
    selectedServicesList = new QStringListModel(this);
    servicesBase = nullptr;
    servicesBaseSize = 0;
    ui->setupUi(this);
    ui->mark->setMaxLength(20);
    ui->model->setMaxLength(20);
    ui->year->setMaxLength(4);
    ui->year->setValidator(new QIntValidator(this));
    ui->vin->setMaxLength(17);
    ui->number->setMaxLength(9);
    ui->owner->setMaxLength(50);
    ui->phone->setMaxLength(18);
    ui->phone->setValidator(new QIntValidator(this));
    ui->searchBar->setMaxLength(60);
    ui->foundServicesList->setModel(foundServicesList);
    ui->selectedServicesList->setModel(selectedServicesList);
}

ClientForm::~ClientForm()
{
    delete ui;
    delete client;
    delete serviceList;
    delete foundServicesList;
    delete selectedServicesList;
}

void ClientForm::setServicesBase(Service *servicesBase, int servicesBaseSize)
{
    this->servicesBase = servicesBase;
    this->servicesBaseSize = servicesBaseSize;
    setServiceList();
}

void ClientForm::setClientsBase(QList<Client> *clientsBase)
{
    this->clientsBase = clientsBase;
}

void ClientForm::setClient(int selectedClientNumber)
{
    client = new Client (clientsBase->operator[](selectedClientNumber));
    this->selectedClientNumber = selectedClientNumber;
    newClient = false;
    setClientData();
    setSelectedServicesList();
}

void ClientForm::setClient(void)
{
    client = new Client;
    newClient = true;
}

void ClientForm::setClientData(void)
{
    ui->mark->setText(client->getCar()->getMark());
    ui->model->setText(client->getCar()->getModel());
    ui->year->setText(client->getCar()->getYear());
    ui->vin->setText(client->getCar()->getVin());
    ui->number->setText(client->getCar()->getNumber());
    ui->owner->setText(client->getName());
    ui->phone->setText(client->getPhone());
}

void ClientForm::getClientData(void)
{
    client->getCar()->setMark(ui->mark->text());
    client->getCar()->setModel(ui->model->text());
    client->getCar()->setYear(ui->year->text());
    client->getCar()->setVin(ui->vin->text());
    client->getCar()->setNumber(ui->number->text());
    client->setName(ui->owner->text());
    client->setPhone(ui->phone->text());
}

void ClientForm::setServiceList(void)
{
    for (int i = 0; i < servicesBaseSize; i++)
    {
        serviceList->append(&servicesBase[i]);
    }
    setFoundServicesList();
}

void ClientForm::setFoundServicesList(void)
{
    QModelIndex to;
    int serviceListSize = serviceList->size();
    foundServicesList->removeRows(0, foundServicesList->rowCount());
    foundServicesList->insertRows(0, serviceListSize);
    for (int i = 0; i < serviceListSize; i++)
    {
        to = foundServicesList->index(i);
        foundServicesList->setData(to, serviceList->operator[](i)->getName());
    }
}

void ClientForm::setSelectedServicesList(void)
{
    QModelIndex to;
    int serviceListSize = client->serviceListSize();
    selectedServicesList->removeRows(0, selectedServicesList->rowCount());
    selectedServicesList->insertRows(0, serviceListSize);
    for (int i = 0; i < serviceListSize; i++)
    {
        to = selectedServicesList->index(i);
        selectedServicesList->setData(to, client->getService(i)->getName());
    }
    calculateCost();
}

void ClientForm::search(void)
{
    serviceList->clear();
    QString keyword = ui->searchBar->text();
    bool emptyFirstFilter = !(ui->engine->isChecked() || ui->brakeSystem->isChecked() || ui->steering->isChecked()
                           || ui->chassis->isChecked() || ui->transmission->isChecked());
    bool emptySecondFilter = !(ui->repairs->isChecked() || ui->diagnostics->isChecked() || ui->maintenance->isChecked());
    for (int i = 0; i < servicesBaseSize; i++)
    {
        if (servicesBase[i].getName().contains(keyword, Qt::CaseInsensitive))
        {
            if (emptyFirstFilter && emptySecondFilter)
            {
                serviceList->append(&servicesBase[i]);
            }
            else
            {
                bool secondFilterPassed = (ui->repairs->isChecked() && servicesBase[i].isRepairs())
                                       || (ui->diagnostics->isChecked() && servicesBase[i].isDiagnostics())
                                       || (ui->maintenance->isChecked() && servicesBase[i].isMaintenance());
                if (emptyFirstFilter && secondFilterPassed)
                {
                    serviceList->append(&servicesBase[i]);
                }
                else
                {
                    bool firstFilterPassed = (ui->engine->isChecked() && servicesBase[i].isEngine())
                                          || (ui->brakeSystem->isChecked() && servicesBase[i].isBrakeSystem())
                                          || (ui->steering->isChecked() && servicesBase[i].isSteering())
                                          || (ui->chassis->isChecked() && servicesBase[i].isChassis())
                                          || (ui->transmission->isChecked() && servicesBase[i].isTransmission());
                    if (emptySecondFilter && firstFilterPassed)
                    {
                        serviceList->append(&servicesBase[i]);
                    }
                    else
                    {
                        if (firstFilterPassed && secondFilterPassed)
                        {
                            serviceList->append(&servicesBase[i]);
                        }
                    }
                }
            }
        }
    }
    setFoundServicesList();
}

void ClientForm::calculateCost(void)
{
    int cost = 0;
    for (int i = 0; i < client->serviceListSize(); i++)
    {
        cost = cost + client->getService(i)->getCost();
    }
    ui->costLabel->setNum(cost);
}

void ClientForm::on_ok_clicked(void)
{
    bool emptyPartOfForm = ui->mark->text().isEmpty() || ui->model->text().isEmpty() || ui->year->text().isEmpty()
                        || ui->vin->text().isEmpty() || ui->number->text().isEmpty() || ui->owner->text().isEmpty()
                        || ui->phone->text().isEmpty() || (client->serviceListSize() == 0);
    if (!emptyPartOfForm)
    {
        getClientData();
        if(newClient)
        {
            clientsBase->append(*client);
        }
        else
        {
            clientsBase->operator[](selectedClientNumber) = *client;
        }
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Уведомление", "Заполните все поля и выберите услуги!");
    }
}

void ClientForm::on_delete__clicked(void)
{
    QModelIndex selectedServiceIndex = ui->selectedServicesList->selectionModel()->currentIndex();
    if (ui->selectedServicesList->selectionModel()->isSelected(selectedServiceIndex))
    {
        client->removeService(selectedServiceIndex.row());
        ui->selectedServicesList->selectionModel()->reset();
        setSelectedServicesList();
    }
}

void ClientForm::on_add_clicked(void)
{
    QModelIndex selectedServiceIndex = ui->foundServicesList->selectionModel()->currentIndex();
    if (ui->foundServicesList->selectionModel()->isSelected(selectedServiceIndex))
    {
        bool newService = true;
        int serviceIndex = serviceList->operator[](selectedServiceIndex.row())->getIndex();
        int serviceListSize = client->serviceListSize();
        for (int i = 0; i < serviceListSize; i++)
        {
            if (client->getService(i)->getIndex() == serviceIndex)
            {
                newService = false;
                break;
            }
        }
        if (newService)
        {
            client->addService(&servicesBase[serviceIndex]);
            setSelectedServicesList();
        }
        ui->foundServicesList->selectionModel()->reset();
    }
}

void ClientForm::on_reset_clicked(void)
{
    ui->engine->setChecked(false);
    ui->brakeSystem->setChecked(false);
    ui->steering->setChecked(false);
    ui->chassis->setChecked(false);
    ui->transmission->setChecked(false);
    ui->repairs->setChecked(false);
    ui->diagnostics->setChecked(false);
    ui->maintenance->setChecked(false);
    ui->searchBar->clear();
    serviceList->clear();
    setServiceList();
}

void ClientForm::on_engine_clicked(void)
{
    search();
}

void ClientForm::on_transmission_clicked(void)
{
    search();
}

void ClientForm::on_steering_clicked(void)
{
    search();
}

void ClientForm::on_chassis_clicked(void)
{
    search();
}

void ClientForm::on_repairs_clicked(void)
{
    search();
}

void ClientForm::on_diagnostics_clicked(void)
{
    search();
}

void ClientForm::on_maintenance_clicked(void)
{
    search();
}

void ClientForm::on_brakeSystem_clicked(void)
{
    search();
}

void ClientForm::on_searchBar_textEdited(void)
{
    search();
}
