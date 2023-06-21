#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <fileoperator.h>
#include <QProcess>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <QMessageBox>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QProcess process;
    process.start("cmd");
    process.closeWriteChannel();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_text_edit_textChanged()
{
    std::string text = ui->text_edit->toPlainText().toStdString();
    write_file(text, ui->path_view->text().toStdString());
}


void MainWindow::on_open_button_clicked()
{
    std::string path = ui->path_view->text().toStdString();
    auto text = read_file(path);
    ui->text_edit->setText(QString::fromStdString(text));
    std::stringstream ss;
    ss << "cd " << path;
    std::string* s = new std::string(ss.str());
    system(s->c_str());
}


void MainWindow::on_run_button_clicked(){
    const char* command = ui->console_view->toPlainText().toStdString().c_str();
    QProcess process;
    process.start(command);
    QByteArray * arr = new QByteArray;
    *arr = process.readAllStandardOutput();
    //std::cout << arr->data();
    ui->console_out->setPlainText(arr->data());
    ui->console_view->setPlainText(QString(""));
}


