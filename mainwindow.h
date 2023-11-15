#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::MainWindow *ui;
    QString currentFile { "" };
    QShortcut *shortcutPlus = nullptr;
    QShortcut *shortcutMinus = nullptr;
    QKeyEvent *event = nullptr;

public slots:
    void save();
    void open();
    void newDoc();
    void print();
    void zoomIn();
    void zoomOut();
    void setDark();
    void setLight();

};
#endif // MAINWINDOW_H
