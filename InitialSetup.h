#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class InitialWindow; }
QT_END_NAMESPACE

class InitialWindow : public QMainWindow
{
    Q_OBJECT

public:
    InitialWindow(QWidget *parent = nullptr);
    ~InitialWindow();

private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

private:
    Ui::InitialWindow *ui;
};
#endif // INITIALWINDOW_H
