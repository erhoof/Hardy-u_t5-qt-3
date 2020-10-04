#include "InitialSetup.h"
#include "ui_InitialSetup.h"

InitialWindow::InitialWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InitialWindow)
{
    ui->setupUi(this);
}

InitialWindow::~InitialWindow()
{
    delete ui;
}


void InitialWindow::on_pushButton_next_clicked()
{
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        ui->stackedWidget->setCurrentIndex(1);
        ui->pushButton_prev->setEnabled(true);
        break;
    case 1:
        // TODO: Next window
        break;
    default:
        break;
    }
}

void InitialWindow::on_pushButton_prev_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_prev->setEnabled(false);
}
