#include <QFile>
#include <QDebug>
#include "process.h"

Process::Process(QObject *parent) :
    QProcess(parent)
{
}

void Process::copyFile(QString oldName, QString newName)
{
    QString program = "/opt/videozoom/bash/copyFile";
    QStringList arguments;

    arguments << oldName << newName;
    this->start(program, arguments);
    this->waitForFinished();
}

void Process::removeFile(QString fileName)
{
    QString program = "/opt/videozoom/bash/removeFile";
    QStringList arguments;

    arguments << fileName;
    this->start(program, arguments);
    this->waitForFinished();
}

bool Process::fileExists(QString fileName)
{
    return QFile::exists(fileName);
}

void Process::rebootPhone()
{
    QString program = "/opt/videozoom/bash/reboot";

    this->start(program);
    this->waitForFinished();
}
