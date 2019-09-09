#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trimpic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startTrimPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QThread *Thread;
    TrimPic *Trim;
};

#endif // MAINWINDOW_H
