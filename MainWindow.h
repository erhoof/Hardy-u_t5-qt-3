#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class HardDriveTableModel;
class NewRequestsModel;
class SortedReqListModel;
class DoneReqListModel;

class HardDrive; // Placeholder to easify header
struct HardDriveInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, HardDriveInfo *info = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    HardDrive *m_hardDrive;

    HardDriveTableModel *m_hardDriveModel;
    NewRequestsModel *m_newReqModel;
    SortedReqListModel *m_sortedReqModel;
    DoneReqListModel *m_doneReqModel;

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
