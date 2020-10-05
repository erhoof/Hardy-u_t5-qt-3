#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "HardDriveTableModel.h"
#include "NewRequestsModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    HardDriveTableModel m_hardDriveModel;
    NewRequestsModel m_newReqModel;

    // Request ID
    uint m_curId = 0;
    uint m_curSector = 0;
    uint m_curCylinder = 0;

    void addRequest();
    QString randomCharSeq(int length);

    int timerId;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
