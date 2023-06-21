#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QProcess>
#include <QPlainTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QProcess process;
    void console();

private slots:
    void on_text_edit_textChanged();

    void on_open_button_clicked();

    void on_run_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

