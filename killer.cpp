#include "killer.h"

// Завершение процесса
void Killer::kill_process(QString PID)
{
    errno = 0;
    int  killReturn;

    pid_t pid = PID.toInt();
    killReturn = kill(pid, SIGTERM);

    if(killReturn == -1)
    {
        if( errno == ESRCH)
            qDebug() << "Не существует!";
        else if( errno == EPERM) // Нет прав для отправки сигнала на завершения
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Недостаточно прав для завершения процесса!");
            msgBox.exec();
        }
        else
            qDebug()<< "Сигнал на завершение отправлен!";
    }
}
