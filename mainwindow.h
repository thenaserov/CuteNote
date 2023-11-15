#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    bool Save(QKeyEvent *event);

public slots:
    void saveSlot();
    void setDark();
    void setLight();
};
#endif // MAINWINDOW_H
