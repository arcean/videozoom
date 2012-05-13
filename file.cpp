#include <QDebug>
#include "file.h"

File::File(QObject *parent) :
    QObject(parent)
{
}

void File::copyFile()
{
    bool ret = QFile::copy("/opt/videozoom/data/camera.conf", "/etc/camera.conf");
    qDebug() << "RET" << ret;
    bool ret2 = QFile::exists("/opt/videozoom/data/camera.conf");
    bool ret3 = QFile::exists("/opt/videozoom/data/camera.conf");
    qDebug() << "RET2" << ret2;
    qDebug() << "RET3" << ret3;
}
