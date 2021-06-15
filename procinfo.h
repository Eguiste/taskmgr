#ifndef PROCINFO_H
#define PROCINFO_H

#ifdef linux
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>

#include <unistd.h>
#include <fcntl.h>
#include "version.h"
#include "sysinfo.h"

#include <fstream>
#include <numeric>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <signal.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <math.h>
#include <stdlib.h>



class ProcInfo
{
public:

    ProcInfo();

    QMap<QString, QStringList> get_proc_info();



private:
    QString get_proc_path(long pid);
    QString get_proc_user();
    QMap<QString, QString> get_process_info_from_pid(double& vm_usage, double& resident_set, long pid);

    // контейнер для хранения информации о процессах
    QMap<QString, QStringList> process_info;
    long total_memory;

};

#endif
#endif // PROCINFO_H
