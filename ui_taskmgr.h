/********************************************************************************
** Form generated from reading UI file 'taskmgr.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMGR_H
#define UI_TASKMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_taskmgr
{
public:
    QAction *actionNew_task;
    QAction *actionTerminate_task;
    QAction *actionView;
    QAction *actionSet_priory;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *search;
    QGridLayout *gridLayout;
    QFrame *line;
    QTableView *ProcTable;
    QLabel *StatusLabel;
    QPushButton *TerminateProcessButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *taskmgr)
    {
        if (taskmgr->objectName().isEmpty())
            taskmgr->setObjectName(QString::fromUtf8("taskmgr"));
        taskmgr->resize(631, 453);
        actionNew_task = new QAction(taskmgr);
        actionNew_task->setObjectName(QString::fromUtf8("actionNew_task"));
        actionTerminate_task = new QAction(taskmgr);
        actionTerminate_task->setObjectName(QString::fromUtf8("actionTerminate_task"));
        actionView = new QAction(taskmgr);
        actionView->setObjectName(QString::fromUtf8("actionView"));
        actionSet_priory = new QAction(taskmgr);
        actionSet_priory->setObjectName(QString::fromUtf8("actionSet_priory"));
        centralWidget = new QWidget(taskmgr);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        search = new QLineEdit(centralWidget);
        search->setObjectName(QString::fromUtf8("search"));

        verticalLayout->addWidget(search);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 2);

        ProcTable = new QTableView(centralWidget);
        ProcTable->setObjectName(QString::fromUtf8("ProcTable"));
        ProcTable->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ProcTable->sizePolicy().hasHeightForWidth());
        ProcTable->setSizePolicy(sizePolicy1);
        ProcTable->setMaximumSize(QSize(1000000, 16777215));

        gridLayout->addWidget(ProcTable, 1, 0, 1, 2);

        StatusLabel = new QLabel(centralWidget);
        StatusLabel->setObjectName(QString::fromUtf8("StatusLabel"));
        StatusLabel->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(StatusLabel, 5, 0, 1, 2);

        TerminateProcessButton = new QPushButton(centralWidget);
        TerminateProcessButton->setObjectName(QString::fromUtf8("TerminateProcessButton"));

        gridLayout->addWidget(TerminateProcessButton, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        taskmgr->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(taskmgr);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 22));
        taskmgr->setMenuBar(menuBar);
        mainToolBar = new QToolBar(taskmgr);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        taskmgr->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(taskmgr);

        QMetaObject::connectSlotsByName(taskmgr);
    } // setupUi

    void retranslateUi(QMainWindow *taskmgr)
    {
        taskmgr->setWindowTitle(QCoreApplication::translate("taskmgr", "\320\234\320\265\320\275\320\265\320\264\320\266\320\265\321\200 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\320\262", nullptr));
        actionNew_task->setText(QCoreApplication::translate("taskmgr", "New ", nullptr));
        actionTerminate_task->setText(QCoreApplication::translate("taskmgr", "Terminate ", nullptr));
        actionView->setText(QCoreApplication::translate("taskmgr", "View", nullptr));
        actionSet_priory->setText(QCoreApplication::translate("taskmgr", "Set priory", nullptr));
        StatusLabel->setText(QString());
        TerminateProcessButton->setText(QCoreApplication::translate("taskmgr", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class taskmgr: public Ui_taskmgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMGR_H
