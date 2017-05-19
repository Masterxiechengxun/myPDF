#ifndef PDFVIEW_H
#define PDFVIEW_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QPalette>
#include <QResizeEvent>
#include <pdfutils.h>

class PdfView : public QWidget
{
    Q_OBJECT
public:
    explicit PdfView(QWidget *parent = 0);
    ~PdfView();
    void resizeEvent(QResizeEvent* e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void setMaxCachedNum(int maxCachedNum);
    bool setPath(QString pdfPath);
    bool setPage(int pageNumber);
    int getNumPages();
    float getScaledRatio();
    bool showClipImage(int pageNumber, int x, int y, int w, int h);
    void cancelClip();
    QSize pdfActualSize;
    QSize getPageSize();
signals:
    void pageChanged(int currentPage);
private:
    PdfUtils* pdfUtils;
    QString pdfPath;
    int maxCachedNum;
    QMap<int, QImage> cachedImageMap;
    //    QQueue<int> cachedPageQueue;
    int currentPage;
    int numPages;
    bool isMouseDown;
    int lastMouseY;
    QImage image;
    int imageX;
    int imageY;
    int imageMinY;
    bool isClip;
    bool getPdfImage(int pageNumber);
    void reachTop();
    void reachBottom();
    //判断是否需要发送重定位签名框的信号
    void needLocateSignArea();
};

#endif
