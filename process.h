#ifndef PROCESS_H
#define PROCESS_H

#include <QProcess>

class Process : public QProcess
{
    Q_OBJECT
public:
    explicit Process(QObject *parent = 0);
    
signals:
    
public slots:
    void rebootPhone();
    void copyFile(QString oldName, QString newName);
    bool fileExists(QString fileName);
    void removeFile(QString fileName);
    
};

#endif // PROCESS_H
