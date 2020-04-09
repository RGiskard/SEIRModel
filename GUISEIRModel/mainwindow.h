#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "seirmodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint(double x,double y);
    void clearData();
    void plot();
    void plotAll(map<int,QVector<double>> results);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    SEIRModel *modelo;
    QVector<double> qv_x,qv_y;
    vector<double> getParametersByGUIDouble();
    vector<int> getParametersByGUIInt();
    void initParameters();
};
#endif // MAINWINDOW_H
