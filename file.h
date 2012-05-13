#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QFile>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = 0);

    void copyFile();
    
signals:
    
public slots:
    
};

#endif // FILE_H
