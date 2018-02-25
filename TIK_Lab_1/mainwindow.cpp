#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->str = ui->lineEdit->text();
    this->tmppair = this->calc_complex(this->str);
    if(this->tmppair.first == "Error"){ // processing errors
        if(this->tmppair.second == "Empty")
            ui->textEdit->setPlainText("Error, you enter blank string!!");
    }
    else{ // without errors
        this->tmppair.first.truncate(this->tmppair.first.size()-1);
        QString exhaust;
        exhaust = "ПІБ: " + this->str + "; N=" + QString::number(this->str.size()) + '\n'
                + "Ансамбль джерела: A = {" + this->tmppair.first + "}" + '\n'
                + "Кількість різних повідомлень: K = " + QString::number((this->tmppair.first.size()+1)/2) + '\n'
                + '\n'
                + '\t' + "Ai" + '\t' + "Ni" + '\t' +  "Pi" + '\t' + '\t' + "I(Ai)" + '\n';
        int tmp = 1;
        for(int i = 0; i < this->tmppair.first.size()+1; i = i+2){
            QString tmpstr2;
            tmpstr2.push_back(this->tmppair.second[i]);
            exhaust.push_back("'" + this->tmppair.first[i] + "'" + '\t' + QString::number(tmp) + '\t' + this->tmppair.second[i]
                              + '\t' + QString::number(tmpstr2.toDouble()/(double)this->str.size(),'f',4) + '\t' + '\t'
                              + QString::number(std::log2(1/(tmpstr2.toDouble()/(double)this->str.size())),'f',4));
            exhaust.push_back('\n');
            tmp++;
        }
        exhaust.push_back('\n');
        exhaust.push_back('\n');
        exhaust.push_back("Ентропія джерела H(A) = ");
        double entropy = 0;
        for(int i = 0; i < this->tmppair.first.size()+1; i = i+2){
            QString tmpstr2;
            tmpstr2.push_back(this->tmppair.second[i]);
            entropy = entropy - tmpstr2.toDouble()/(double)this->str.size() * std::log2(tmpstr2.toDouble()/(double)this->str.size());
        }
        exhaust.push_back(QString::number(entropy, 'f', 4) + '\n');
        exhaust.push_back("Продуктивність джерела V(A) = ");
        this->t = t/(tmp-1);
        exhaust.push_back(QString::number(entropy/t, 'f', 4));
        this->t = 1;
        ui->textEdit->setPlainText(exhaust);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->textEdit->clear();
}

QPair <QString, QString> MainWindow::calc_complex(QString string)
{
    QPair <QString, QString> exhaust;
    if(string.isEmpty()){

        exhaust.first = "Error";
        exhaust.second = "Empty";
        return exhaust;
    }
    for( int i = 0; i < string.size(); i++)
    {
        int howmach = 0;
        if(!exhaust.first.contains(string[i]))
        {
            exhaust.first.push_back(string[i]);
            exhaust.first.push_back(",");
            howmach++;
            for(int j = i+1; j < string.size(); j++)
            {
                if(string[i] == string[j])
                    howmach++;
            }
            exhaust.second.push_back(QString::number(howmach));
            exhaust.second.push_back(",");
        }
    }
    return exhaust;
}
