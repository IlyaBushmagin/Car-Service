#include "mainwindow.h"
#include "clientform.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *carService, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->carService = carService;
    servicesBase = nullptr;
    servicesBaseSize = 0;
    clientsBase = new QList<Client>;
    clientsTable = new QStandardItemModel(this);
    clientsTable->setColumnCount(7);
    clientsTable->setHeaderData(0, Qt::Horizontal, "Марка");
    clientsTable->setHeaderData(1, Qt::Horizontal, "Модель");
    clientsTable->setHeaderData(2, Qt::Horizontal, "Год выпуска");
    clientsTable->setHeaderData(3, Qt::Horizontal, "VIN");
    clientsTable->setHeaderData(4, Qt::Horizontal, "Гос. номер");
    clientsTable->setHeaderData(5, Qt::Horizontal, "Владелец");
    clientsTable->setHeaderData(6, Qt::Horizontal, "Телефон");
    ui->setupUi(this);
    ui->clientsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->clientsTable->setModel(clientsTable);
    setServicesBase();
    setClientsBase();
    setClientsTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete clientsBase;
    delete clientsTable;
    if (servicesBase != nullptr)
    {
        delete [] servicesBase;
    }
}

void MainWindow::setServicesBase(void)
{
    QFile file(carService->applicationDirPath() + "/dat/servicesbase.dat");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream fin(&file);
        fin.setCodec("UTF-8");
        servicesBaseSize = fin.readLine().toInt();
        servicesBase = new Service[servicesBaseSize];
        for (int i = 0; i < servicesBaseSize; i++)
        {
            servicesBase[i].setName(fin.readLine());
            servicesBase[i].setCost(fin.readLine().toInt());
            servicesBase[i].setEngine(fin.readLine().toInt());
            servicesBase[i].setChassis(fin.readLine().toInt());
            servicesBase[i].setSteering(fin.readLine().toInt());
            servicesBase[i].setBrakeSystem(fin.readLine().toInt());
            servicesBase[i].setTransmission(fin.readLine().toInt());
            servicesBase[i].setMaintenance(fin.readLine().toInt());
            servicesBase[i].setDiagnostics(fin.readLine().toInt());
            servicesBase[i].setRepairs(fin.readLine().toInt());
            servicesBase[i].setIndex(i);
        }
        file.close();
    }
    else
    {
        QMessageBox::information(this, "Уведомление", "Ошибка открытия файла servicesbase.dat");
    }
}

void MainWindow::setClientsBase(void)
{
    QFile file(carService->applicationDirPath() + "/dat/clientsbase.dat");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream fin(&file);
        fin.setCodec("UTF-8");
        clientsBase->clear();
        Client *newClient;
        int serviceListSize = 0;
        int clientsBaseSize = fin.readLine().toInt();
        for (int i = 0; i < clientsBaseSize; i++)
        {
            newClient = new Client;
            newClient->getCar()->setMark(fin.readLine());
            newClient->getCar()->setModel(fin.readLine());
            newClient->getCar()->setYear(fin.readLine());
            newClient->getCar()->setVin(fin.readLine());
            newClient->getCar()->setNumber(fin.readLine());
            newClient->setName(fin.readLine());
            newClient->setPhone(fin.readLine());
            if (servicesBase != nullptr)
            {
                serviceListSize = fin.readLine().toInt();
                for (int j = 0; j < serviceListSize; j++)
                {
                    newClient->addService(&servicesBase[fin.readLine().toInt()]);
                }
            }
            clientsBase->append(*newClient);
            delete newClient;
        }
        file.close();
    }
    else
    {
        QMessageBox::information(this, "Уведомление", "Ошибка открытия файла clientsbase.dat");
    }
}

void MainWindow::setClientsTable(void)
{
    int rowCount = clientsBase->size();
    clientsTable->setRowCount(rowCount);
    for (int i = 0; i < rowCount; i++)
    {
        clientsTable->setData(clientsTable->index(i, 0), clientsBase->operator[](i).getCar()->getMark());
        clientsTable->setData(clientsTable->index(i, 1), clientsBase->operator[](i).getCar()->getModel());
        clientsTable->setData(clientsTable->index(i, 2), clientsBase->operator[](i).getCar()->getYear());
        clientsTable->setData(clientsTable->index(i, 3), clientsBase->operator[](i).getCar()->getVin());
        clientsTable->setData(clientsTable->index(i, 4), clientsBase->operator[](i).getCar()->getNumber());
        clientsTable->setData(clientsTable->index(i, 5), clientsBase->operator[](i).getName());
        clientsTable->setData(clientsTable->index(i, 6), clientsBase->operator[](i).getPhone());
    }
}

void MainWindow::saveClientsBase(void)
{
    QFile file(carService->applicationDirPath() + "/dat/clientsbase.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream fout(&file);
        fout.setCodec("UTF-8");
        int serviceListSize = 0;
        int clientsBaseSize = clientsBase->size();
        fout << clientsBaseSize << endl;
        for (int i = 0; i < clientsBaseSize; i++)
        {
            fout << clientsBase->operator[](i).getCar()->getMark() << endl;
            fout << clientsBase->operator[](i).getCar()->getModel() << endl;
            fout << clientsBase->operator[](i).getCar()->getYear() << endl;
            fout << clientsBase->operator[](i).getCar()->getVin() << endl;
            fout << clientsBase->operator[](i).getCar()->getNumber() << endl;
            fout << clientsBase->operator[](i).getName() << endl;
            fout << clientsBase->operator[](i).getPhone() << endl;
            serviceListSize = clientsBase->operator[](i).serviceListSize();
            fout << serviceListSize << endl;
            for (int j = 0; j < serviceListSize; j++)
            {
                fout << clientsBase->operator[](i).getService(j)->getIndex() << endl;
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::information(this, "Уведомление", "Ошибка открытия файла clientsbase.dat");
    }
}

void MainWindow::on_save_triggered(void)
{
    saveClientsBase();
}

void MainWindow::on_add_triggered(void)
{
    if (clientsBase->size() < 1000)
    {
        ui->clientsTable->selectionModel()->reset();
        ClientForm *clientForm = new ClientForm;
        clientForm->setServicesBase(servicesBase, servicesBaseSize);
        clientForm->setClientsBase(clientsBase);
        clientForm->setClient();
        clientForm->setModal(true);
        clientForm->exec();
        delete clientForm;
        setClientsTable();
    }
    else
    {
        QMessageBox::information(this, "Уведомление", "Достигнуто максимальное количество клиентов!");
    }
}

void MainWindow::on_refresh_triggered(void)
{
    setClientsBase();
    setClientsTable();
}

void MainWindow::on_delete__triggered(void)
{
    QModelIndex selectedRowIndex = ui->clientsTable->selectionModel()->currentIndex();
    if (ui->clientsTable->selectionModel()->isSelected(selectedRowIndex))
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this, "Уведомление", "Удалить запись о клиенте?", QMessageBox::Yes|QMessageBox::No);
        if (question == QMessageBox::Yes)
        {
            int selectedClient = selectedRowIndex.row();
            clientsBase->removeAt(selectedClient);
            ui->clientsTable->selectionModel()->reset();
            setClientsTable();
        }
    }
}

void MainWindow::on_clientsTable_activated(const QModelIndex &selectedClientIndex)
{
    ClientForm *clientForm = new ClientForm;
    int selectedClientNumber = selectedClientIndex.row();
    clientForm->setServicesBase(servicesBase, servicesBaseSize);
    clientForm->setClientsBase(clientsBase);
    clientForm->setClient(selectedClientNumber);
    clientForm->setModal(true);
    clientForm->exec();
    delete clientForm;
    setClientsTable();
}
