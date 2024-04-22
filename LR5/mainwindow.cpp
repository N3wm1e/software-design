#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    connectButtons();
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QMainWindow::resizeEvent(event);
}
void MainWindow::connectButtons(){

    QList<QPushButton*> buttons = ui->centralWidget->findChildren<QPushButton*>();
    for (auto button : buttons) {
        PaintScene::FigureTypes figureType = static_cast<PaintScene::FigureTypes>(button->property("FigureType").toInt());
        connect(button, &QPushButton::clicked, this, [this, figureType]() {
            scene->setTypeFigure(figureType);
        });
    }
}

