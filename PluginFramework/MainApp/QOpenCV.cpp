#include "QOpenCV.hpp"

namespace QOpenCV {

static bool s_greyTableInit = false;
static QVector<QRgb> s_greyTable;
QImage wrapImage( const cv::Mat& cvmat)
{
    int height = cvmat.rows;
    int width = cvmat.cols;

    if (cvmat.depth() == CV_8U && cvmat.channels() == 3) {
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if (cvmat.depth() == CV_8U && cvmat.channels() == 1) {
        if (!s_greyTableInit) {
            for (int i = 0; i < 256; i++){
                s_greyTable.push_back(qRgb(i, i, i));
            }
        }
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_Indexed8);
        img.setColorTable(s_greyTable);
        return img;
    } else {
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}

cv::Rect grow( const cv::Rect& rect, double scale )
{
    cv::Size size = rect.size();

    size.width = (scale * size.width);
    size.height = (scale * size.height);

    cv::Point offset = size - rect.size();
    offset.x /= 2;
    offset.y /= 2;

    return cv::Rect( rect.tl() - offset, size );
}
cv::Mat qImageToMat(QImage &image)
{
    image = image.convertToFormat(QImage::Format_RGB888).rgbSwapped();
    return cv::Mat(image.height(),
        image.width(),
        CV_8UC3,
        image.bits(),
        image.bytesPerLine());
}

QImage matToQImage(cv::Mat &image)
{
    return QImage(image.data,
        image.cols,
        image.rows,
        image.step,
        QImage::Format_RGB888);
}

}
