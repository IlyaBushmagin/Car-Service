#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include "client.h"
#include "service.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *carService, QWidget *parent = nullptr);

    void setClientsBase(void);

    void saveClientsBase(void);

    void setServicesBase(void);

    void setClientsTable(void);

    ~MainWindow();

private slots:
    void on_save_triggered(void);

    void on_add_triggered(void);

    void on_refresh_triggered(void);

    void on_delete__triggered(void);

    void on_clientsTable_activated(const QModelIndex &selectedClientIndex);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *clientsTable;
    QApplication *carService;
    Service *servicesBase;
    QList<Client> *clientsBase;
    int servicesBaseSize;
};

#endif // MAINWINDOW_H
