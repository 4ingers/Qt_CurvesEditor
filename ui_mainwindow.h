/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionContext_help;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionOpen_as;
    QWidget *wgtCentral;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vLayLeft;
    QTreeWidget *treeWgt;
    QLabel *labelInv;
    QGridLayout *invarLay;
    QLabel *labelDelta;
    QLabel *labelD;
    QLabel *labelB;
    QLabel *labelI;
    QVBoxLayout *vLayRight;
    QLabel *labelCurve;
    QCustomPlot *customPlot;
    QLineEdit *equationEdit;
    QSpacerItem *bottomSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setSizeIncrement(QSize(1, 1));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../GOG Games/Soldiers - Heroes of World War II/Soldiers.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral("background-color: white;"));
        MainWindow->setIconSize(QSize(24, 24));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QFont font;
        font.setFamily(QStringLiteral("Menlo"));
        actionOpen->setFont(font);
        actionContext_help = new QAction(MainWindow);
        actionContext_help->setObjectName(QStringLiteral("actionContext_help"));
        actionContext_help->setFont(font);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setFont(font);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setFont(font);
        actionOpen_as = new QAction(MainWindow);
        actionOpen_as->setObjectName(QStringLiteral("actionOpen_as"));
        actionOpen_as->setFont(font);
        wgtCentral = new QWidget(MainWindow);
        wgtCentral->setObjectName(QStringLiteral("wgtCentral"));
        horizontalLayout = new QHBoxLayout(wgtCentral);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        vLayLeft = new QVBoxLayout();
        vLayLeft->setSpacing(6);
        vLayLeft->setObjectName(QStringLiteral("vLayLeft"));
        treeWgt = new QTreeWidget(wgtCentral);
        treeWgt->setObjectName(QStringLiteral("treeWgt"));
        QFont font1;
        font1.setFamily(QStringLiteral("Menlo"));
        font1.setPointSize(10);
        treeWgt->setFont(font1);
        treeWgt->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWgt->setFrameShape(QFrame::NoFrame);
        treeWgt->setLineWidth(0);
        treeWgt->setEditTriggers(QAbstractItemView::DoubleClicked);
        treeWgt->setProperty("showDropIndicator", QVariant(false));
        treeWgt->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeWgt->setTextElideMode(Qt::ElideMiddle);
        treeWgt->setIndentation(20);
        treeWgt->setRootIsDecorated(true);
        treeWgt->setSortingEnabled(false);
        treeWgt->setAnimated(true);
        treeWgt->setWordWrap(false);
        treeWgt->setHeaderHidden(true);
        treeWgt->setColumnCount(1);
        treeWgt->header()->setVisible(false);

        vLayLeft->addWidget(treeWgt);

        labelInv = new QLabel(wgtCentral);
        labelInv->setObjectName(QStringLiteral("labelInv"));
        QFont font2;
        font2.setFamily(QStringLiteral("Menlo"));
        font2.setPointSize(14);
        labelInv->setFont(font2);
        labelInv->setAlignment(Qt::AlignCenter);

        vLayLeft->addWidget(labelInv);

        invarLay = new QGridLayout();
        invarLay->setSpacing(6);
        invarLay->setObjectName(QStringLiteral("invarLay"));
        labelDelta = new QLabel(wgtCentral);
        labelDelta->setObjectName(QStringLiteral("labelDelta"));
        labelDelta->setFont(font2);
        labelDelta->setAlignment(Qt::AlignCenter);

        invarLay->addWidget(labelDelta, 1, 0, 1, 1);

        labelD = new QLabel(wgtCentral);
        labelD->setObjectName(QStringLiteral("labelD"));
        labelD->setFont(font2);
        labelD->setAlignment(Qt::AlignCenter);

        invarLay->addWidget(labelD, 1, 1, 1, 1);

        labelB = new QLabel(wgtCentral);
        labelB->setObjectName(QStringLiteral("labelB"));
        labelB->setFont(font2);
        labelB->setAlignment(Qt::AlignCenter);

        invarLay->addWidget(labelB, 2, 0, 1, 1);

        labelI = new QLabel(wgtCentral);
        labelI->setObjectName(QStringLiteral("labelI"));
        labelI->setFont(font2);
        labelI->setAlignment(Qt::AlignCenter);

        invarLay->addWidget(labelI, 2, 1, 1, 1);


        vLayLeft->addLayout(invarLay);

        vLayLeft->setStretch(0, 5);
        vLayLeft->setStretch(1, 1);
        vLayLeft->setStretch(2, 4);

        horizontalLayout->addLayout(vLayLeft);

        vLayRight = new QVBoxLayout();
        vLayRight->setSpacing(6);
        vLayRight->setObjectName(QStringLiteral("vLayRight"));
        labelCurve = new QLabel(wgtCentral);
        labelCurve->setObjectName(QStringLiteral("labelCurve"));
        QFont font3;
        font3.setFamily(QStringLiteral("Menlo"));
        font3.setPointSize(18);
        font3.setKerning(false);
        labelCurve->setFont(font3);
        labelCurve->setLineWidth(4);
        labelCurve->setAlignment(Qt::AlignCenter);

        vLayRight->addWidget(labelCurve);

        customPlot = new QCustomPlot(wgtCentral);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);
        customPlot->setFont(font);

        vLayRight->addWidget(customPlot);

        equationEdit = new QLineEdit(wgtCentral);
        equationEdit->setObjectName(QStringLiteral("equationEdit"));
        equationEdit->setFont(font2);
        equationEdit->setCursor(QCursor(Qt::IBeamCursor));
        equationEdit->setMaxLength(36);
        equationEdit->setFrame(false);
        equationEdit->setAlignment(Qt::AlignCenter);
        equationEdit->setClearButtonEnabled(true);

        vLayRight->addWidget(equationEdit);

        bottomSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vLayRight->addItem(bottomSpacer);

        vLayRight->setStretch(0, 1);
        vLayRight->setStretch(1, 28);
        vLayRight->setStretch(2, 2);

        horizontalLayout->addLayout(vLayRight);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 8);
        MainWindow->setCentralWidget(wgtCentral);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 19));
        menuBar->setFont(font);
        menuBar->setDefaultUp(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_as);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionContext_help);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Black Quadratic Tuesday", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_STATUSTIP
        actionOpen->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionContext_help->setText(QApplication::translate("MainWindow", "Context help", nullptr));
#ifndef QT_NO_SHORTCUT
        actionContext_help->setShortcut(QApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen_as->setText(QApplication::translate("MainWindow", "Open as..", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", nullptr));
#endif // QT_NO_SHORTCUT
        QTreeWidgetItem *___qtreewidgetitem = treeWgt->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Projects", nullptr));
        labelInv->setText(QApplication::translate("MainWindow", "Invariants", nullptr));
        labelDelta->setText(QApplication::translate("MainWindow", "\316\224", nullptr));
        labelD->setText(QApplication::translate("MainWindow", "D", nullptr));
        labelB->setText(QApplication::translate("MainWindow", "B", nullptr));
        labelI->setText(QApplication::translate("MainWindow", "I", nullptr));
        labelCurve->setText(QApplication::translate("MainWindow", "Curve plotter", nullptr));
        equationEdit->setInputMask(QString());
        equationEdit->setText(QString());
        equationEdit->setPlaceholderText(QApplication::translate("MainWindow", " Enter an equation", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
