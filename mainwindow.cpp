#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    setWindowTitle("Cute Note - by TheNaserov");
    this->setStyleSheet("background-color: white;");
    ui->plainTextEdit->setUndoRedoEnabled(1);

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(setDark()));
    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(setLight()));
    connect(ui->actionundo, SIGNAL(triggered()), ui->plainTextEdit, SLOT(undo()));
    connect(ui->actionredo, SIGNAL(triggered()), ui->plainTextEdit, SLOT(redo()));
    connect(ui->actionOpen, SIGNAL(triggered()), ui->plainTextEdit, SLOT(open()));
    connect(ui->actionNew, SIGNAL(triggered()), ui->plainTextEdit, SLOT(newDoc()));
    shortcutPlus = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus), this);
    connect(shortcutPlus, &QShortcut::activated, this, &MainWindow::zoomIn);
    shortcutMinus = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), this);
    connect(shortcutMinus, &QShortcut::activated, this, &MainWindow::zoomOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier | event->modifiers() == Qt::KeypadModifier)
    {
        switch (event->key())
        {
            case Qt::Key_S:{
                save();
                break;
            }
            case Qt::Key_W:{
                this->~MainWindow();
                break;
            }
            case Qt::Key_P:{
                print();
            }
        }
    }
}

void MainWindow::save()
{
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

void MainWindow::zoomIn()
{
    ui->plainTextEdit->zoomIn();
}

void MainWindow::zoomOut()
{
    ui->plainTextEdit->zoomOut();
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "failed to open! : " + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}

void MainWindow::newDoc()
{
    currentFile.clear();
    ui->plainTextEdit->setPlainText("");
}

void MainWindow::print()
{

}
