#include "InitialSetup.h"
#include "ui_InitialSetup.h"

#include "HardDriveInfo.h"
#include "MainWindow.h"

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
        {
            auto info = new HardDriveInfo();
            info->m_accessTime       = ui->lineEdit_accessTime->text().toFloat();
            info->m_rotationDelay    = ui->lineEdit_rotationDelay->text().toFloat();
            info->m_transferSpeed    = ui->lineEdit_transferSpeed->text().toFloat();
            info->m_cylinders        = ui->lineEdit_cylinders->text().toInt();
            info->m_heads            = ui->lineEdit_heads->text().toInt();
            info->m_sectors          = ui->lineEdit_sectors->text().toInt();

            auto mainWindow = new MainWindow(this, info);
            mainWindow->show();
            hide();

            break;
        }
    default:
        break;
    }
}

void InitialWindow::on_pushButton_prev_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_prev->setEnabled(false);
}
