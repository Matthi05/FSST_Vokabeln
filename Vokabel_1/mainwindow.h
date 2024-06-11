#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_einlesen_btn_clicked();
    void on_reset_btn_clicked();
    void on_drehen_btn_clicked();
    void on_richtig_btn_clicked();
    void on_wiederholen_btn_clicked();
    void on_sprache_btn_clicked();
    void vokabel_print();
    void mischen();
};
#endif // MAINWINDOW_H
