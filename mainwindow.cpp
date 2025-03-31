#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QSequentialAnimationGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация анимации кнопки
    buttonAnimation = new QPropertyAnimation(ui->generateButton, "geometry", this);
    buttonAnimation->setDuration(150);
    buttonAnimation->setEasingCurve(QEasingCurve::OutQuad);

    // Стилизация приложения
    this->setStyleSheet(
        "QMainWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a2e, stop:1 #16213e);"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4e54c8, stop:1 #8f94fb);"
        "   color: white;"
        "   border: none;"
        "   padding: 15px 30px;"
        "   font-size: 16px;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "   box-shadow: 0 4px 6px rgba(0, 0, 0, 0.3);"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5b5fcc, stop:1 #9a9efc);"
        "   transform: translateY(-1px);"
        "   box-shadow: 0 6px 8px rgba(0, 0, 0, 0.4);"
        "}"
        "QPushButton:pressed {"
        "   box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);"
        "}"
        "QLineEdit {"
        "   background: rgba(255, 255, 255, 0.9);"
        "   border: 2px solid #4e54c8;"
        "   border-radius: 6px;"
        "   padding: 8px;"
        "   font-size: 14px;"
        "   color: #1a1a2e;"
        "}"
        "QLabel {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   color: white;"
        "   qproperty-alignment: AlignCenter;"
        "   text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);"
        "}"
    );

    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGenerateClicked()
{
    // Анимация кнопки
    QRect originalGeometry = ui->generateButton->geometry();
    buttonAnimation->setStartValue(QRect(originalGeometry.x() + 5, originalGeometry.y() + 5,
                                      originalGeometry.width() - 10, originalGeometry.height() - 10));
    buttonAnimation->setEndValue(originalGeometry);
    buttonAnimation->start();

    // Генерация случайного числа
    bool okMin, okMax;
    int min = ui->minEdit->text().toInt(&okMin);
    int max = ui->maxEdit->text().toInt(&okMax);

    if(!okMin || !okMax) {
        ui->resultLabel->setText("<font color='#ff4444'>Введите числа!</font>");
        return;
    }

    if(min >= max) {
        ui->resultLabel->setText("<font color='#ff4444'>Min должен быть меньше Max!</font>");
        return;
    }

    int randomNumber = QRandomGenerator::global()->bounded(min, max + 1);
    ui->resultLabel->setText(QString::number(randomNumber));
}
