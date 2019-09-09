#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Thread=new QThread;
    Trim=new TrimPic;
    Trim->moveToThread(Thread);
    connect(Thread,SIGNAL(started()),Trim,SLOT(TrimPicture()));
    connect(Trim,SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(Trim,SIGNAL(quit()),Thread,SLOT(quit()));
    connect(Trim,SIGNAL(unlockButton(bool)),ui->startTrimPushButton,SLOT(setEnabled(bool)));
    connect(Trim,SIGNAL(echoInfo(QString)),ui->infoLabel,SLOT(setText(QString)));
    //Let the OS to do GC
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startTrimPushButton_clicked()
{
    QFileDialog *QF=new QFileDialog(this);
    QF->setFileMode(QFileDialog::Directory);
    QF->setWindowTitle(QString("打开含有IRDV的文件夹"));
    QF->setDirectory(QString("./"));
    QString Path;
    if(QF->exec())
    {
        QStringList FP;
        FP=QF->selectedFiles();
        if(!FP.isEmpty())
        {
            Path=FP[0];
        }
        else
        {
            return;
        }
    }
    if(Path=="")//fix linux related issues
        return;
    ui->startTrimPushButton->setEnabled(false);

    Trim->Path=Path;
    Thread->start();
}

