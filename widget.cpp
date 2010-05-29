#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::showByteData(QByteArray buf)
{
    QString strwrk;

    for (int i = 0; i < buf.size(); i++){
        if (i % 0x10 == 0){
            if (i > 0){
                strwrk += "\n";
            }
            strwrk += QString().sprintf("%6x: ", i);
        }
        strwrk += QString().sprintf("%02x ", (uchar)buf.at(i));
    }

    ui->textBrowser->setPlainText(strwrk);
}


void Widget::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open MIDI file", "", "MIDI file (*.mid *.smf)");

    if (fileName.size()){
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)){
            QByteArray buf = file.readAll();
            showByteData(buf);
            m_MidiData.setByteData(buf);
        }
    }
}
