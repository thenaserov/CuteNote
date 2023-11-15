#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Cute Note - by TheNaserov");
    this->setStyleSheet("background-color: white;");

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveSlot()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(setDark()));
    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(setLight()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Save(event);
}

bool MainWindow::Save(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        switch (event->key())
        {
        case Qt::Key_S:
            QMessageBox msgBox;
             msgBox.setText("The document has been modified.");
             msgBox.setInformativeText("Do you want to save your changes?");
             msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
             msgBox.setDefaultButton(QMessageBox::Save);
             int ret = msgBox.exec();
             switch (ret) {
                   case QMessageBox::Save:{
                       // Save was clicked
                     QString fileName = QFileDialog::getSaveFileName(this, tr("Save Text File"), "./", tr("Text Files (*.txt)"));
                     if (fileName != "")
                     {
                         QFile file(QFileInfo(fileName).absoluteFilePath());
                         if (file.open(QIODevice::WriteOnly))
                         {
                             QString text = ui->plainTextEdit->toPlainText();
                             QTextStream out(&file);
                             out << text;
                             file.close();
                         }
                         else
                         {
                             //TODO: Error message
                         }
                       break;
                   }
             }

                   case QMessageBox::Discard:{
                       // Don't Save was clicked
                       break;
                   }
                   case QMessageBox::Cancel:{
                       // Cancel was clicked
                       break;
                   }
                   default:{
                       // should never be reached
                       break;
                   }
             }
            break;
        }
    }
}

void MainWindow::saveSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Text File"), "./", tr("Text Files (*.txt)"));
    if (fileName != "")
    {
        QFile file(QFileInfo(fileName).absoluteFilePath());
        if (file.open(QIODevice::WriteOnly))
        {
            QString text = ui->plainTextEdit->toPlainText();
            QTextStream out(&file);
            out << text;
            file.close();
        }
        else
        {
            //TODO: Error message
        }
    }
}

void MainWindow::setDark()
{
    this->setStyleSheet("background-color: #1E0532;"
                        "color : white;");
}

void MainWindow::setLight()
{
    this->setStyleSheet("background-color: white;");
}
