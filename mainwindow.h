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
    void on_equationEdit_returnPressed();
    void mouseMoveEvent(QMouseEvent *event);
    void mouseWheelEvent();
    void on_actionOpen_triggered();
    void on_treeWgt_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWgt_customContextMenuRequested();
    void delItemInTree();
    void addItemInTree();

    void on_actionContext_help_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_as_triggered();

private:
    void convertPolynom(QString& error);
    void painter();
    void showCurve();
    void setInvariant(double delta, double D, double I, double B);
    void setCurveType(int type);
    void loadBasicFile(const QString& fileName);

    Ui::MainWindow *ui;
    Polynom polynom;
};

#endif // MAINWINDOW_H
