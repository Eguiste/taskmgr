#include "taskmgr.h"
#include "ui_taskmgr.h"

taskmgr::taskmgr(QWidget *parent): QMainWindow(parent), ui(new Ui::taskmgr)
{
    ui->setupUi(this);

    procInfo = new ProcInfo();
    statusInfo = new StatusInfo();
    active_features << "Имя процесса" << "PID" << "PPID" << "Пользователь" << "Время работы" << "Приоритет" << "Память%" << "CPU%" << "Путь";
    status_puncts << "Время работы" << "Всего RAM МБ" << "Свободно RAM МБ" << "CPU %";

    // Создание объекта модели
    model = new QStandardItemModel;
    searchModel = new QStandardItemModel;

    // Заполнение процессов
    taskmgr::fill_proc_table();

    // Заполнене статус бара
    taskmgr::fill_status_bar();
    //ui->ProcTable->setSortingEnabled(true);
    SelectRow = -1;
    SelectRowSearch = -1;
    selectColumn = -1;

    connect(ui->ProcTable->horizontalHeader(), SIGNAL(sectionClicked (int)), this, SLOT(selectionClicked(int)));

    connect(&timer,SIGNAL(timeout()),this,SLOT(timer_slot()));
    timer.start(1000);
}

// Срабатывание таймера
void taskmgr::timer_slot()
{
    refresh_proc_table();
    refresh_status_bar();
}

// Заполнение процессов в таблицу
void taskmgr::fill_proc_table()
{
    QStandardItem *item;

    QMap<QString, QStringList> proc_info = procInfo->get_proc_info();

    // Заполнение заголовков таблицы
    foreach(QString active_punct, active_features)
        horizontalHeader.append(active_punct);

    model->setHorizontalHeaderLabels(horizontalHeader);
    searchModel->setHorizontalHeaderLabels(horizontalHeader);

    // Вставка строк в таблицу
    int i = 0, j;
    foreach(QString active_punct, active_features)
    {
        j = 0;
        foreach(QString str, proc_info[active_punct])
        {
            item = new QStandardItem(str);
            item->setEditable(0); // lock items
            model->setItem(j, i, item);
            j++;
        }
        i++;
    }
    RowCount = j;
    ui->ProcTable->setModel(model);
    ui->ProcTable->resizeColumnsToContents();
}

// Заполнение статус бара
void taskmgr::fill_status_bar()
{
    QMap<QString,QString> status_bar_info = statusInfo->get_status_info();

    QString Status_string="Количество процессов: "+ QString::number(RowCount) + "   |   ";
    foreach(QString status_punct, status_puncts)
    {
        Status_string+=status_punct + ": " + status_bar_info[status_punct] + "   |   ";
    }
    ui->StatusLabel->setText(Status_string);
}


// Обновление таблицы
void taskmgr::refresh_proc_table()
{
    QMap<QString, QStringList> proc_info = procInfo->get_proc_info();
    int i = 0, j;
    QStandardItem *item;
    foreach(QString active_punct, active_features)
    {
        j=0;
        foreach(QString str, proc_info[active_punct])
        {
            //qDebug() << i << "\t" << j;
            // Добавление новое ячейки, если создался процесс
            if(j >= RowCount)
            {
                //qDebug() << "Найден новый процесс!";
                item = new QStandardItem(str);
                item->setEditable(0);
                model->setItem(j, i, item);
            }
            // Обновление значения старой ячейки
            else
                model->item(j, i)->setData(str, Qt::DisplayRole);
                // счетчик строк
            j++;
        }
        // счетчик столбцов
        i++;
    }
    //qDebug() << "***********************************" << j;
    if (j < RowCount)
        for(int row = model->rowCount() - 1; row != j - 1; row--)
            model->removeRow(row);

    RowCount = j;
    if (SelectRow > RowCount)SelectRow = RowCount;

    // обновление поиска
    if (query != "")
        search();

    // сортировка и возврат курсора
    if (selectColumn != -1)
        sorting();


}

// Клик на ячейку таблицы
void taskmgr::on_ProcTable_clicked(const QModelIndex &index)
{
    if (query == "")
    {
        SelectRow = index.row();
        SelectColumn = index.column();
    }
    else
    {
        SelectRowSearch = index.row();
        SelectColumnSearch = index.column();
    }
}

// Обновление статус бара
void taskmgr::refresh_status_bar()
{
    QMap<QString,QString> status_bar_info = statusInfo->get_status_info();

    QString Status_string="Количество процессов: " + QString::number(RowCount)+"   |   ";
    foreach(QString status_punct, status_puncts)
    {
        Status_string += status_punct+": " + status_bar_info[status_punct]+"   |   ";
    }
    ui->StatusLabel->clear();
    ui->StatusLabel->setText(Status_string);
}

// Завершение процесса
void taskmgr::on_TerminateProcessButton_clicked()
{
    if(SelectRow == -1) return;
    QString PID;
    if(query == "")
        PID = model->index(SelectRow, 1).data(Qt::DisplayRole).toString();
    else
        PID = searchModel->index(SelectRow, 1).data(Qt::DisplayRole).toString();
    qDebug() << PID;
    qDebug() << "Вызываю функцию для завершения процесса";
    Killer::kill_process(PID);
    refresh_proc_table();
}

taskmgr::~taskmgr()
{
    timer.stop();
    disconnect(this,SLOT(timer_slot()));
    delete model;
    delete procInfo;
    delete statusInfo;
    delete ui;
}


void taskmgr::selectionClicked(int column)
{
    selectColumn = column;


    if (strategy == Qt::SortOrder::AscendingOrder)
       strategy = Qt::SortOrder::DescendingOrder;
    else strategy = Qt::SortOrder::AscendingOrder;


    refresh_proc_table();
}


void taskmgr::on_search_textChanged(const QString &arg1)
{
    query = arg1;
    search();
}


void taskmgr::search()
{
    int rowCount = searchModel->rowCount();
    if(query != "")
    {
        int k = 0, l;
        for (int i = 0; i < RowCount; i++)
        {
            l = 0;
            bool flag = true;
            QStandardItem *item;
            for (int j = 0; j < horizontalHeader.size(); j++)
            {
                if(model->item(i, 0)->text().contains(query))
                {
                    item = new QStandardItem(model->item(i, j)->text());
                    item->setEditable(false);
                    searchModel->setItem(k, l, item);
                    l++;
                }
                else
                {
                    flag = false;
                    continue;
                }
            }
            if (flag) k++;
        }
        if (k < rowCount)
        {
            for(int row = searchModel->rowCount() - 1; row != k - 1; row--)
                searchModel->removeRow(row);

        }
        ui->ProcTable->setModel(searchModel);

    }
    else ui->ProcTable->setModel(model);

}

void taskmgr::sorting()
{

    if(query == "")
    {
       if (SelectRow != -1 && model->rowCount() != 0)
       {
           model->sort(selectColumn, strategy);
           ui->ProcTable->selectionModel()->clear();
           QModelIndex index = model->item(SelectRow, SelectColumn)->index();
           ui->ProcTable->selectionModel()->select(index, QItemSelectionModel::Select);
       }

   }
   else
   {
        if (SelectRowSearch != -1 && searchModel->rowCount() != 0)
        {
            searchModel->sort(selectColumn, strategy);
            ui->ProcTable->selectionModel()->clear();
            QModelIndex index = searchModel->item(SelectRowSearch, SelectColumnSearch)->index();
            ui->ProcTable->selectionModel()->select(index, QItemSelectionModel::Select);
        }
   }
}

