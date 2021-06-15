#ifdef linux
#include "procinfo.h"

ProcInfo::ProcInfo()
{

}

// Получение информации о процессорах
QMap<QString, QStringList> ProcInfo::get_proc_info()
{
    process_info.clear();

    struct sysinfo inf;

    // Информация об использовании памяти
    if (sysinfo(&inf) != 0)
        qDebug()<< "Ошибка при чтении системной статистики";

    total_memory = inf.totalram / 1024;

    QStringList proc_ids, proc_path, proc_name, proc_user, proc_memory, proc_ppid, proc_priory, proc_starttime, proc_cpu;


    // Открытие директории с процессами
    DIR* proc = opendir("/proc");
    struct dirent* ent = 0;
    long pid;

    // Проверка на ошибку открытия
    if(proc == NULL)
    {
        qDebug()<<"Не удалось открыть директорию (/proc)";
        QCoreApplication::quit();
    }

    // Чтение директории proc
    while(ent = readdir(proc))
    {
        // отфильтровываем директории процессов
        if(!isdigit(*ent->d_name))
            continue;

        // id процесса
        pid = atoi(ent->d_name);

        double vm, rss;

        struct stat inf;
        char filename[20];
        sprintf(filename, "/proc/%ld", pid);
        stat(filename, &inf);
        struct passwd *pw = getpwuid(inf.st_uid);


        // Получаем информацию о процессах
        QMap<QString, QString> info = get_process_info_from_pid(vm, rss, pid);
        if (!info.isEmpty())
        {
            proc_ppid.append(info["PPID"]);
            proc_starttime.append(info["Время работы"]);
            proc_priory.append(info["Приоритет"]);
            proc_name.append(info["Имя процесса"]);
            proc_memory.append(info["Память%"]);
            proc_ids.append(QString::fromUtf8(ent->d_name));
            proc_user.append(pw->pw_name);
            proc_path.append(get_proc_path(pid));
            proc_cpu.append(info["CPU%"]);
        }
    }
    closedir(proc);

    process_info.insert("PID", proc_ids);
    process_info.insert("Путь", proc_path);
    process_info.insert("Имя процесса", proc_name);
    process_info.insert("Память%", proc_memory);
    process_info.insert("CPU%", proc_cpu);
    process_info.insert("PPID", proc_ppid);
    process_info.insert("Время работы", proc_starttime);
    process_info.insert("Приоритет", proc_priory);
    process_info.insert("Пользователь", proc_user);
    return process_info;

}

// Получение пути
QString ProcInfo::get_proc_path(long pid)
{
    char exePath[PATH_MAX];
    char arg1[20];
    sprintf(arg1, "/proc/%d/exe", pid);
    ssize_t len = ::readlink(arg1, exePath, sizeof(exePath));

    if (len == -1 )
        len = 0;

    exePath[len] = '\0';
    return QString::fromUtf8(exePath);
}

// Получение информации о процессах
QMap<QString,QString> ProcInfo::get_process_info_from_pid(double &vm_usage, double &resident_set,long proc_id)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;


   struct sysinfo inform;

   if (sysinfo(&inform) != 0)
       qDebug()<< "Ошибка при чтении системной статистики";

   vm_usage = 0.0;
   resident_set = 0.0;

   char filename[20];
   sprintf(filename, "/proc/%ld/stat", proc_id);
   ifstream stat_stream(filename, ios_base::in);

   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   long utime, stime, cutime, cstime;
   string priority, nice;
   string O, itrealvalue;


   unsigned long vsize;
   long rss;
   double starttime;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice
   >> O >> itrealvalue >> starttime >> vsize >> rss;

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
   vm_usage = (vsize/1024.0);
   resident_set = rss * page_size_kb;

   sprintf(filename, "/proc/%d/status", proc_id);

   unsigned long total_time = utime + stime;
   total_time = total_time + cutime + cstime;
   float seconds = inform.uptime - (starttime / (sysconf(_SC_CLK_TCK) / 1.0));
   float cpu_usage = 100.0 * ((total_time / (sysconf(_SC_CLK_TCK) / 1.0)) / seconds);

   int timeWorkInSeconds = inform.uptime - starttime/100;
   ifstream status_stream(filename, ios_base::in);

   string word;
   unsigned long memory_usage = NULL;
   while (status_stream >> word)
   {
       if (word == "VmData:")
       {
           stat_stream >> word;
           status_stream >> memory_usage;
           break;
       }
   }
   status_stream.close();
   QMap<QString, QString> info;
   if (state == "R" || memory_usage != NULL)
   {

       info.insert("PPID", QString::fromLocal8Bit(ppid.c_str()));
       info.insert("Приоритет", QString::fromLocal8Bit(priority.c_str()));
       info.insert("Время работы", QString::number(timeWorkInSeconds/3600) + "ч " + QString::number(timeWorkInSeconds % 3600 / 60) + "м " + QString::number(timeWorkInSeconds % 60) + "с");
       info.insert("Имя процесса", QString::fromLocal8Bit(comm.erase(0, 1).erase(comm.size() -1).c_str()));
       info.insert("Память%", QString::number(int(100 * (memory_usage / 1.0 / total_memory * 100.0)) / 100.0));
       info.insert("CPU%", QString::number(int(100 * cpu_usage) / 100.0));
   }

   return info;
}
#endif
