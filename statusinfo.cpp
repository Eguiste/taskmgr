#include "statusinfo.h"

StatusInfo::StatusInfo()
{
    previous_idle_time = 0, previous_total_time = 0;
}

// Получение информации о CPU
std::vector<size_t> StatusInfo::get_cpu_times()
{
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Пропустить преписку 'cpu'
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool StatusInfo::get_cpu_times(size_t &idle_time, size_t &total_time)
{
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}

// Получение статуса
QMap<QString, QString> StatusInfo::get_status_info()
{
    sys_info.clear();

    struct sysinfo info;

    // Информация об использовании памяти
    if (sysinfo(&info) != 0)
        qDebug()<< "Ошибка при чтении системной статистики";

    QString uptime=QString::number(info.uptime / 3600)+"ч " + QString::number(info.uptime % 3600 / 60)+ "м "+QString::number(info.uptime % 60)+"с";

    sys_info.insert("Время работы", uptime);
    sys_info.insert("Всего RAM МБ", QString::number(info.totalram/1024/1024));
    sys_info.insert("Свободно RAM МБ", QString::number((info.totalram-info.freeram)/1024/1024));


    // Информация о использовании процессора
    size_t idle_time, total_time;
    get_cpu_times(idle_time, total_time);

    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);

    previous_idle_time = idle_time;
    previous_total_time = total_time;
    sys_info.insert("CPU %", QString::number(utilization));

    return sys_info;
}
