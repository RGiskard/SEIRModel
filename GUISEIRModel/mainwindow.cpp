#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modelo=new SEIRModel();
    ui->plotCustom->xAxis->setLabel("Tiempo (Días)");
    ui->plotCustom->yAxis->setLabel("Población");
    ui->plotCustom->xAxis->setRange(0, 20);
    ui->plotCustom->yAxis->setRange(0, 25);
    Qt::GlobalColor colors[]={Qt::red,Qt::green,Qt::yellow,Qt::blue};
    QString labels[]={"S","E","I","R"};
    for(int i=0;i<4;i++)
    {
        ui->plotCustom->addGraph();
        ui->plotCustom->graph(i)->setPen(QPen(colors[i]));
        ui->plotCustom->graph(i)->setName(labels[i]);
    }
    //ui->plotCustom->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    //ui->plotCustom->graph(0)->setLineStyle(QCPGraph::lsNone);
    initParameters();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete modelo;
}

void MainWindow::plot()
{
    ui->plotCustom->graph(0)->setData(qv_x,qv_y);
    ui->plotCustom->replot();
    ui->plotCustom->update();
}
void MainWindow::plotAll(map<int,QVector<double>> results)
{
    ui->plotCustom->graph(0)->setData(results[0],results[1]);
    ui->plotCustom->replot();
    ui->plotCustom->update();
    for(int i=1;i<4;i++)
    {
        ui->plotCustom->graph(i)->setData(results[0],results[i+1]);
        ui->plotCustom->replot();
        ui->plotCustom->update();
    }
    ui->plotCustom->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}



void MainWindow::on_pushButton_clicked()
{
    modelo->InitParametersByVectorDouble(getParametersByGUIDouble());
    modelo->InitParametersByVectorInt(getParametersByGUIInt());
    for(int i=0;i<4;i++)
    {
        ui->plotCustom->graph(i)->data()->clear();
    }
    ui->plotCustom->replot();
    modelo->Execute();
    map<int,QVector<double>> results=modelo->getResultados();
    plotAll(results);
}

vector<double> MainWindow::getParametersByGUIDouble()
{
    vector<double> valuesByGUI;
    valuesByGUI.push_back(ui->spBoxBeta->value());
    valuesByGUI.push_back(ui->spBoxGamma->value());
    valuesByGUI.push_back(ui->spBoxSigma->value());
    valuesByGUI.push_back(ui->spBoxMu->value());
    valuesByGUI.push_back(ui->spBoxNu->value());
    return valuesByGUI;
}
vector<int> MainWindow::getParametersByGUIInt()
{
    vector<int> valuesByGUI;
    valuesByGUI.push_back(ui->spBoxSusceptible->value());
    valuesByGUI.push_back(ui->spBoxExposed->value());
    valuesByGUI.push_back(ui->spBoxInfected->value());
    valuesByGUI.push_back(ui->spBoxRecovered->value());
    valuesByGUI.push_back(ui->spBoxDays->value());
    return valuesByGUI;
}

void MainWindow::initParameters()
{

    ui->spBoxBeta->setSingleStep(0.1);
    ui->spBoxBeta->setValue(0.9);
    ui->spBoxGamma->setSingleStep(0.1);
    ui->spBoxGamma->setValue(0.2);
    ui->spBoxSigma->setSingleStep(0.1);
    ui->spBoxSigma->setValue(0.5);
    /*Segundo bloco*/
    ui->spBoxSusceptible->setValue(10);
    ui->spBoxExposed->setValue(1);
    ui->spBoxInfected->setValue(12);
    ui->spBoxRecovered->setValue(0);
    ui->spBoxDays->setValue(15);
}

void MainWindow::on_pushButton_2_clicked()
{
    //initParameters();
}
