#ifndef TASKMGR_H
#define TASKMGR_H
#include <QMainWindow>
#include "procinfo.h"
#include "statusinfo.h"
#include "killer.h"
#include <QStandardItemModel>
#include <ui_taskmgr.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class taskmgr: public QMainWindow
{
    Q_OBJECT
public:
    taskmgr(QWidget *parent = nullptr);
    ~taskmgr();
private:
    Ui::taskmgr *ui;
    ProcInfo *procInfo;
    StatusInfo *statusInfo;
    QList<QString> active_features;
    QList<QString> status_puncts;
    QStandardItemModel *model;
    QStandardItemModel *searchModel;
    int SelectRow;
    int SelectRowSearch;
    int selectColumn;
    int SelectColumn;
    int SelectColumnSearch;
    QTimer timer;
    QList<QString> horizontalHeader;
    int RowCount;
    QString query;
    Qt::SortOrder strategy;

    void fill_proc_table();
    void fill_status_bar();
    void refresh_status_bar();
    void refresh_proc_table();
    void search();
    void sorting();


private slots:
    void timer_slot();
    void on_ProcTable_clicked(const QModelIndex &index);
    void on_TerminateProcessButton_clicked();
    void selectionClicked(int column);
    void on_search_textChanged(const QString &arg1);
};

#endif // TASKMGR_H
