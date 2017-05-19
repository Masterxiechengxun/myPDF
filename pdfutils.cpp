#include "pdfutils.h"

PdfUtils::PdfUtils(QString filePath)
{
    this->filePath = filePath;
    getPdfInfo();
}
PdfUtils::~PdfUtils() {
}
QImage PdfUtils::getPdfImage(int pageNumber) {
    QImage image;
    Poppler::Document* document = Poppler::Document::load(filePath);
    if (!document || document->isLocked()) {
        delete document;
        return image;
    }
    Poppler::Page* pdfPage = document->page(pageNumber);
    document->setRenderHint(Poppler::Document::TextAntialiasing);
    if (pdfPage == 0) {
        return image;
    }
    image = pdfPage->renderToImage(150,150, -1, -1, -1, -1);
    if (image.isNull()) {
        return image;
    }
    delete pdfPage;
    delete document;
    return image;
}
int PdfUtils::getNumPages() {
    return numPages;
}
QSize PdfUtils::getPageSize() {
    return pageSize;
}
void PdfUtils::getPdfInfo() {
    numPages = 0;
    Poppler::Document* document = Poppler::Document::load(filePath);
    if (!document || document->isLocked()) {
        delete document;
        return;
    }
    numPages = document->numPages();
    Poppler::Page* pdfPage = document->page(0);
    pageSize = pdfPage->pageSize();
    qDebug()<<pageSize;
    delete pdfPage;
    delete document;
}
