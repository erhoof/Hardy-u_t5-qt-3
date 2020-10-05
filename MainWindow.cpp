#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

#include "HardDrive.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Hard Drive Scheme Table View
    ui->tableView->setModel(&m_hardDriveModel);

    // Set sizing
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->show();

    // New Requests List
    ui->listView_new->setModel(&m_newReqModel);
    ui->listView_new->show();

    timerId = startTimer(250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRequest()
{
    RequestModel newReq;
    newReq.id = m_curId;
    newReq.creationTime = QTime::currentTime();
    newReq.finishTime = newReq.creationTime;
    newReq.filename = randomCharSeq(5) + '.' + randomCharSeq(3);
    newReq.cylinder = rand() % HardDrive::instance()->cylindersCount();
    newReq.sector = rand() % HardDrive::instance()->sectorsCount();

    m_newReqModel.addRequest(newReq);

    m_curId++;
}

QString MainWindow::randomCharSeq(int length)
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    for(int i=0; i<length; i++)
    {
       int index = rand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
    }

    return randomString;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (rand() %10 == 1)
    {
        qDebug() << "new req!";
        addRequest();
    }

    m_curSector++; // Next Sector
    if (m_curSector == HardDrive::instance()->sectorsCount())
        m_curSector = 0;
    m_hardDriveModel.m_curSector = m_curSector;
}
