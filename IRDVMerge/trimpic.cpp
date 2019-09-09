#include "trimpic.h"
#include <QPainter>
#include <QDir>
#include "omp.h"
TrimPic::TrimPic(QObject *parent) : QObject(parent)
{

}
TrimPic::~TrimPic()
{
    unlockButton(true);
}

void TrimPic::TrimPicture()
{
    //init path
    QDir dir(Path);
    //init pic size
    int index=0;
    //get File Name
    QStringList name,filters;
    filters<< "*.irdv" <<"*.IRDV";
    name=dir.entryList(filters,QDir::Files|QDir::Readable,QDir::Name);
    //is the dir empty?
    if(name.count()==0)
    {
        echoInfo(QString("文件夹中不含有效文件。"));
        unlockButton(true);
        quit();
        return;
    }
    else
    {
        echoInfo(QString("文件合成中……"));
    }
    dir.mkdir("result");
    //batch progress
    int showindex=0;
    FILE *fp_result,*fp_source;
    QString result=Path+"//result//result.irdv";
    fp_result=fopen(result.toStdString().c_str(),"wb");
    fseeko64(fp_result,sizeof(IRDVFILE_HEAD),SEEK_SET);
    for(int i=0;i<name.count();i++)
    {
        QString source=Path+"//"+name[i];
        fp_source=fopen(source.toStdString().c_str(),"rb");

        fseeko64(fp_source,0,SEEK_END);
        int64_t data=ftello64(fp_source)-sizeof(IRDVFILE_HEAD);
        fseeko64(fp_source,sizeof(IRDVFILE_HEAD),SEEK_SET);
        uchar buf[5000];
        for(int64_t p=0;p<data;p+=5000)
        {

            fread(buf,5000,1,fp_source);
            fwrite(buf,5000,1,fp_result);
            emit progress(p*100/data);
        }
        fclose(fp_source);

        emit progress(i*100/name.count());
    }
    fseeko64(fp_result,0,SEEK_SET);


    //head
    QString source=Path+"//"+name[name.count()-1];
    fp_source=fopen(source.toStdString().c_str(),"rb");

    fseeko64(fp_source,0,SEEK_SET);
    uchar buf[sizeof(IRDVFILE_HEAD)];
    fread(buf,sizeof(IRDVFILE_HEAD),1,fp_source);
    fwrite(buf,sizeof(IRDVFILE_HEAD),1,fp_result);
    fclose(fp_source);
    fclose(fp_result);




    emit progress(100);
    echoInfo(QString("图像已保存在")+Path+QString("/result文件夹下。"));
    unlockButton(true);
    quit();

}
