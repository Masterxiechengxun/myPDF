#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,600);
    //setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("MyPDFviewer"));
    setWindowIcon(QIcon(":/images/mdragon"));
    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file-> addAction(openAction);
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar-> addAction(openAction);
    mainEdit = new QWidget(this);
    setCentralWidget(mainEdit);
    view = new PdfView(mainEdit);
    view->setFixedSize(650,500);
    scrollbar = new QScrollBar(Qt::Vertical, mainEdit);
    //scrollbar->setGeometry(this->width()-SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, this->height());
    setWidgetVisible(false, false);
    connect(view, SIGNAL(pageChanged(int)), this, SLOT(onPageChange(int)));
    connect(scrollbar, SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChange()));
}
MainWindow::~MainWindow()
{
    if(view)
        delete view;
    if(mainEdit)
        delete mainEdit;
}
void MainWindow::resizeEvent(QResizeEvent *e) {
}
bool MainWindow::setPdfPath(QString path) {
    bool result = view->setPath(path);
    if(result) {
        //view->setGeometry(view->rect());
        int numPages = view->getNumPages();
        if(numPages>1) {
            scrollbar->setMaximum(numPages-1);
            scrollbar->setValue(0);
        }
        view->setPage(0);
    }
    int numPages = view->getNumPages();
    if(numPages == 1)
        setWidgetVisible(true, false);
    else if(numPages > 1)
        setWidgetVisible(true, true);
    return result;
}
//void MainWindow::resizeView() {
//    int numPages = view->getNumPages();
//    if(numPages == 1) {
//        //view->setGeometry(view->rect());
//        //view->setGeometry(this->rect());
//        //view->setGeometry(0, 0, this->width()-SCROLLBAR_WIDTH, this->height());
//        //scrollbar->setGeometry(this->width()-SCROLLBAR_WIDTH, 0, this->width()-SCROLLBAR_WIDTH, this->height());
//        setWidgetVisible(true, false);
//    } else if(numPages > 1) {
//        //view->setGeometry(view->rect());
//        //view->setGeometry(0, 0, this->width()-SCROLLBAR_WIDTH, this->height());
//        //scrollbar->setGeometry(this->width()-SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, this->height());
//        setWidgetVisible(true, true);
//    } else {
//        setWidgetVisible(false, false);
//    }
//}
void MainWindow::setWidgetVisible(bool viewVisible, bool scrollbarVisible)
{
    view->setVisible(viewVisible);
    scrollbar->setVisible(scrollbarVisible);

}
void MainWindow::onPageChange(int currentPage) {
    view->setPage(currentPage);
}
void MainWindow::onScrollBarValueChange() {
    view->setPage(scrollbar->value());
}
void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("PDF Files(*.pdf)"));
       if(!path.isEmpty()) {
           setPdfPath(path);
       } else {
           QMessageBox::warning(this, tr("Path"),
                                tr("You did not select any file."));
       }
}
