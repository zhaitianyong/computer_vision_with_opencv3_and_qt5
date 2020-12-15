#ifndef EDGE_DETECTOR_PLUGIN_H
#define EDGE_DETECTOR_PLUGIN_H
#include <cvplugininterface.h>
#include "edge_detector_plugin_global.h"

namespace Ui {
    class PluginGui;
}

class EDGE_DETECTOR_PLUGINSHARED_EXPORT Edge_Detector_Plugin:
        public QObject, public CvPluginInterface
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
   Q_INTERFACES(CvPluginInterface)
public:
    Edge_Detector_Plugin();
    ~Edge_Detector_Plugin();
    QString title();
    QString version();
    QString description();
    QString help();
    void setupUi(QWidget *parent);
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);

signals:
    void updateNeeded();
    void errorMessage(QString msg);
    void infoMessage(QString msg);

private slots:
    void on_btnRun_clicked();

private:
    Ui::PluginGui *ui;
    QWidget *parent;
};

#endif // EDGE_DETECTOR_PLUGIN_H
