#include "filter_plugin.h"
#include "ui_plugin.h"

Filter_Plugin::Filter_Plugin()
{
}

Filter_Plugin::~Filter_Plugin(){

}

QString Filter_Plugin::title()
{
    return this->metaObject()->className();
}

QString Filter_Plugin::version()
{
    return "1.0.0";
}

QString Filter_Plugin::description()
{
    return "A <b>Filter</b> plugin";
}

QString Filter_Plugin::help()
{
    return "This is a <b>Filter</b> plugin. Clone and use it to create new plugins.";
}

void Filter_Plugin::setupUi(QWidget *parent)
{

    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    // Connect signals for GUI elemnts manually here since they won't be connected by name in a plugin

    connect(ui->btnBilateralFilter, &QPushButton::clicked, this, &Filter_Plugin::on_btnBilateralFilter_clicked);
    connect(ui->btnBlur, &QPushButton::clicked, this, &Filter_Plugin::on_btnBlur_clicked);
    connect(ui->btnGaussiBlur, &QPushButton::clicked, this, &Filter_Plugin::on_btnGaussiBlur_clicked);
    connect(ui->btnMedianBlur, &QPushButton::clicked, this, &Filter_Plugin::on_btnMedianBlur_clicked);
    // emit updateNeeded(); should be added whenever parameters on the plugin GUI change
}

void Filter_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    switch (m_filterType) {
    case FilterType::Blur:
    {
      int ksize = ui->blurKernelSizeSpinBox->value();
      cv::blur(inputImage, outputImage, cv::Size(ksize, ksize));
      break;
    }
    case FilterType::BilateralFilter:
    {
        cv::bilateralFilter(inputImage, outputImage,
                            ui->spinBoxDiameter->value(),
                            ui->spinBoxSigmaSpace->value(),
                            ui->spinBoxSigmaColor->value());
        break;
    }
    case FilterType::GaussianBlur:
    {
         int ksize = ui->gaussiBlurKernelSizeSpinBox->value();

        cv::GaussianBlur(inputImage, outputImage, cv::Size(ksize,ksize),
                         ui->gaussiBlurSigmaXSpin->value(),
                         ui->gaussiBlurSigmaYSpin->value());
        break;
    }
    case FilterType::MedianBlur:
    {
        int ksize = ui->medianBlurKernelSizeSpinBox->value();
        cv::medianBlur(inputImage, outputImage, ksize);
        break;
    }
    default:
    {
        emit errorMessage("process image error!");
        break;
    }

    }

}


void Filter_Plugin::on_btnBilateralFilter_clicked()
{

    m_filterType = FilterType::BilateralFilter;

    emit updateNeeded();
}

void Filter_Plugin::on_btnBlur_clicked()
{
    m_filterType = FilterType::Blur;
    emit updateNeeded();

}

void Filter_Plugin::on_btnGaussiBlur_clicked()
{
    m_filterType = FilterType::GaussianBlur;
    emit updateNeeded();
}

void Filter_Plugin::on_btnMedianBlur_clicked()
{
    m_filterType = FilterType::MedianBlur;
    emit updateNeeded();
}
