#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGenerateClicked()
{
    bool okMin, okMax;
    int min = ui->minEdit->text().toInt(&okMin);
    int max = ui->maxEdit->text().toInt(&okMax);

    if(!okMin || !okMax) {
        ui->resultLabel->setText("<font color='red'>Введите числа!</font>");
        return;
    }

    if(min >= max) {
        ui->resultLabel->setText("<font color='red'>Min должен быть меньше Max!</font>");
        return;
    }

    int randomNumber = QRandomGenerator::global()->bounded(min, max + 1);
    ui->resultLabel->setText(QString::number(randomNumber));
}
