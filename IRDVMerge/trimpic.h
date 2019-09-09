#ifndef TRIMPIC_H
#define TRIMPIC_H

#include <QObject>
#include <QImage>
struct IRDVFILE_HEAD
{
    quint32 fccType='I'+256*'R'+65536*'D'+16777216*'V';//IRDV
    quint32 flags=0;
    quint32 width=1000;
    quint32 height=1012;
    quint32 bitCount=16;
    quint32 imgSize=1000*1012;
    quint32 length=0;
    double rate=0;
    double xRes=0;
    double yRes=0;
    double imgParam[16];
    char name[64]="IRDV";
    char calFile[64];

};
class TrimPic : public QObject
{
    Q_OBJECT
public:
    explicit TrimPic(QObject *parent = nullptr);
    ~TrimPic();
    QString Path;
    int LineWidth;
    int width;
    int height;
    int w;
    int h;
    int quality=80;
    int forceResize=0;

signals:
    void progress(int progress);
    void echoInfo(QString info);
    void unlockButton(bool T);
    void quit();
private:
    QImage resizeAndFullfill(QImage input,int w,int h);
public slots:
    void TrimPicture();


};

#endif // TRIMPIC_H
