#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTreeWidgetItem>
#include "polynom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeWgt_itemClicked(QTreeWidgetItem *item);
    void on_treeWgt_customContextMenuRequested();
    void on_actionContext_help_triggered();
    void mouseMoveEvent(QMouseEvent *event);
    void on_equationEdit_returnPressed();
    void on_actionOpen_as_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void mouseWheelEvent();
    void delItemInTree();
    void addItemInTree();

private:
    void setInvariant(double delta, double D, double I, double B);
    void loadBasicFile(const QString& fileName);
    void convertPolynom(QString& error);
    void setCurveType(int type);
    void setSimplified();
    void showCurve();
    void painter();

    Ui::MainWindow *ui;
    Polynom polynom;
};

#endif // MAINWINDOW_H
