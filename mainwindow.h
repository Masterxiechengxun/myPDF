#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QScrollBar>
#include <QHBoxLayout>
#include <pdfview.h>
#include "connservice.h"

#define SCROLLBAR_WIDTH 30

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent* e);
    bool setPdfPath(QString path);
    //void resizeView();
    void setWidgetVisible(bool pdfCanvasVisible, bool scrollbarVisible);
    void openFile();
public slots:
    void onPageChange(int currentPage);
    void onScrollBarValueChange();
private:
    QWidget *mainEdit;
    QAction *openAction;
    PdfView *view;
    QScrollBar *scrollbar;
};

#endif
