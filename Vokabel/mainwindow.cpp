#include "mainwindow.h"
#include <QFileDialog>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}

QStringList Restart_Vokabel;
QStringList Vokabel;
QStringList Nochmal;
bool sprache = 0; // 0 = Deutsch, 1 = Englisch
bool sprache_vok = 0;
int vok_num = 0;
bool fertig = 0;

void MainWindow::vokabel_print()
{
    plainTextEdit->clear();
    if(fertig) plainTextEdit->appendPlainText("Fertig!!!");
    else if(Vokabel.length()) plainTextEdit->appendPlainText(Vokabel[vok_num].split("|")[sprache_vok]);
    else plainTextEdit->appendPlainText("Keine Vokabel");
}

void MainWindow::mischen()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(Vokabel.begin(), Vokabel.end(), g);
}

void MainWindow::on_einlesen_btn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this, "Titel", "." );

    QFile file( fileName );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    on_reset_btn_clicked();
    Vokabel.clear();
    while (!file.atEnd()) {
        Vokabel += file.readLine();
    }
    Restart_Vokabel = Vokabel;

    mischen();
    vokabel_print();
}


void MainWindow::on_drehen_btn_clicked()
{
    sprache_vok = !sprache_vok;
    vokabel_print();
}


void MainWindow::on_richtig_btn_clicked()
{
    sprache_vok = sprache;
    vok_num += 1;
    if(vok_num >= Vokabel.length()){
        vok_num = 0;
        if(Nochmal.length() != 0){
            Vokabel = Nochmal;
            //mischen();
            Nochmal.clear();
        }
        else fertig = 1;
    }
    vokabel_print();
}


void MainWindow::on_widerholen_btn_clicked()
{
    Nochmal += Vokabel[vok_num];
    on_richtig_btn_clicked();
}


void MainWindow::on_sprache_btn_clicked()
{
    sprache = !sprache;
    if(sprache)sprache_btn->setText("Deutsch");
    else sprache_btn->setText("Englisch");
}


void MainWindow::on_reset_btn_clicked()
{
    Vokabel = Restart_Vokabel;
    Nochmal.clear();
    vok_num = 0;
    fertig = 0;
    sprache_vok = sprache;
    vokabel_print();
}

