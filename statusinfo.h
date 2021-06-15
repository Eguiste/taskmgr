#ifndef STATUSINFO_H
#define STATUSINFO_H
#include <vector>
#include <fstream>
#include <numeric>
#include <QMap>
#include <sys/sysinfo.h>
#include <QDebug>

class StatusInfo
{
public:
    StatusInfo();
    QMap<QString, QString> get_status_info();

private:
    std::vector<size_t> get_cpu_times();
    bool get_cpu_times(size_t &idle_time, size_t &total_time);

    size_t previous_idle_time, previous_total_time;
    QMap<QString,QString> sys_info;
};

#endif // STATUSINFO_H
