#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QString>
#include <QDir>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
//    Mat img=cv::imread("D:/libs/opencv3.4.1/opencv-3.4.1/samples/data/chessboard.png");
//    imshow("image",img);
//    waitKey();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Loading image file
void MainWindow::on_inputPushButton_clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this,
                                                   "Open Input Image",
                                                   QDir::currentPath(),
                                                   "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName)){
        ui->inputLineEdit->setText(fileName);
    }
}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Select Output Image",
                                                    QDir::currentPath(),
                                                    "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty()){
        ui->outputLineEdit->setText(fileName);
        Mat inImg, outImg;
        inImg = imread(ui->inputLineEdit->text().toStdString());
        if(ui->medianBlurRadioButton->isChecked())
            cv::medianBlur(inImg,outImg,5);
        else if(ui->gaussianBlurRradioButton->isChecked())
            cv::GaussianBlur(inImg,outImg,Size(5, 5), 1.25);
        imwrite(fileName.toStdString(), outImg);
        if(ui->displayImageCheckBox->isChecked())
        {
            imshow("Output Image", outImg);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this,
                                      "Exit",
                                      "Are you sure you want to close this program?",
                                      QMessageBox::Yes,
                                      QMessageBox::No);
    if(result == QMessageBox::Yes){
        saveSettings();
        event->accept();
    }else{
        event->ignore();
    }


    QSettings settings("Packt",
                       "Hello_OpenCV_Qt",
                       this);
}

void MainWindow::loadSettings()
{
    QSettings settings("Packt",
                       "Hello_OpenCV_Qt",
                       this);
    ui->inputLineEdit->setText(settings.value("inputLineEdit","").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit","").toString());
    ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton",true).toBool());
    ui->gaussianBlurRradioButton->setChecked(settings.value("gaussianBlurRradioButton",false).toBool());
    ui->displayImageCheckBox->setChecked(settings.value("displayImageCheckBox",false).toBool());
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt",
                       "Hello_OpenCV_Qt",
                       this);
    settings.value("inputLineEdit",ui->inputLineEdit->text());
    settings.value("outputLineEdit",ui->outputLineEdit->text());
    settings.value("medianBlurRadioButton",ui->medianBlurRadioButton->isChecked());
    settings.value("gaussianBlurRradioButton",ui->gaussianBlurRradioButton->isChecked());
    settings.value("displayImageCheckBox",ui->displayImageCheckBox->isChecked());
}
