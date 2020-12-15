#ifndef FILTER_PLUGIN_H
#define FILTER_PLUGIN_H

#include "filter_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}


class FILTER_PLUGINSHARED_EXPORT Filter_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)

public:
    Filter_Plugin();
    ~ Filter_Plugin();

    QString title();
    QString version();
    QString description();
    QString help();
    void setupUi(QWidget *parent);
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);


    enum FilterType{
        Blur,
        GaussianBlur,
        MedianBlur,
        BilateralFilter
    };

signals:
    void updateNeeded();
    void errorMessage(QString msg);
    void infoMessage(QString msg);

private slots:
    void on_btnBilateralFilter_clicked();

    void on_btnBlur_clicked();

    void on_btnGaussiBlur_clicked();

    void on_btnMedianBlur_clicked();

private:
    Ui::PluginGui *ui;

    FilterType m_filterType;

};

#endif // FILTER_PLUGIN_H
