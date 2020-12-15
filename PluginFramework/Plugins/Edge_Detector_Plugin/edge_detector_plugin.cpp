#include "edge_detector_plugin.h"
#include "ui_plugin.h"
#include <QMessageBox>
#include <QtDebug>
Edge_Detector_Plugin::Edge_Detector_Plugin()
{
}

Edge_Detector_Plugin::~Edge_Detector_Plugin(){

}
QString Edge_Detector_Plugin::title()
{
    return this->metaObject()->className();
}

QString Edge_Detector_Plugin::version()
{
    return "1.0.0";
}

QString Edge_Detector_Plugin::description()
{
    return "A <b>edge detector</b> plugin";
}

QString Edge_Detector_Plugin::help()
{
    return "This is a <b>edge detector</b> plugin. Clone and use it to create new plugins.";
}

void Edge_Detector_Plugin::setupUi(QWidget *parent)
{
    this->parent = parent;
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    // Connect signals for GUI elemnts manually here since they won't be connected by name in a plugin
    connect(ui->btnRun, &QPushButton::clicked, this, &Edge_Detector_Plugin::on_btnRun_clicked);
    // emit updateNeeded(); should be added whenever parameters on the plugin GUI change

}

void Edge_Detector_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    try {
        cv::Mat grayImage, blurImage;
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2BGRA);
        cv::GaussianBlur(grayImage, blurImage, cv::Size(5, 5), 1.);
        cv::Canny(blurImage, outputImage,
                  ui->txtThreshold1->value(),
                  ui->txtThreshold2->value(),
                  ui->txtApertureSize->value());

    } catch (...) {
        emit errorMessage("process image error");
    }
}

void Edge_Detector_Plugin::on_btnRun_clicked()
{
    emit updateNeeded();
}
