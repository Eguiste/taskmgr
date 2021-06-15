#ifndef KILLER_H
#define KILLER_H
#include <QString>
#include <QMessageBox>
#include <signal.h>
#include <QDebug>

class Killer
{
public:
    Killer();
    static void kill_process(QString PID);
};



#endif // KILLER_H
