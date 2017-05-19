#ifndef PDFUTILS_H
#define PDFUTILS_H

#include <QObject>
#include <QImage>
#include <QSize>
#include <QDebug>

#include "poppler-qt5.h"

class PdfUtils
{
public:
    explicit PdfUtils(QString filePath);
    ~PdfUtils();
    QImage getPdfImage(int pageNumber);
    int getNumPages();
    QSize getPageSize();
private:
    QString filePath;
    int numPages;
    QSize pageSize;
    void getPdfInfo();
};

#endif
