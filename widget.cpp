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

    // for debug only
    QFile file(":/field.mid");
    file.open(QIODevice::ReadOnly);
    MIDIData *midiData = new MIDIData(this, &file);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->insertTopLevelItems(0, midiData->items());
    file.close();

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
    // for debug only
    QFile file(":/field.mid");
    file.open(QIODevice::ReadOnly);
    QByteArray buf = file.readAll();
    showByteData(buf);
    file.close();

#if 0
    QString fileName = QFileDialog::getOpenFileName(this, "Open MIDI file", "", "MIDI file (*.mid *.smf)");

    if (fileName.size()){
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)){
//            QByteArray buf = file.readAll();
//            showByteData(buf);
            MIDIData *midiData = new MIDIData(this, &file);

            ui->treeWidget->insertTopLevelItems(0, midiData->items());

            /*
            ui->treeWidget->setColumnCount(1);
            QList<QTreeWidgetItem *> items;
            for (int i = 0; i < 10; ++i)
            {
                items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
                items[i]->addChild(new QTreeWidgetItem(items[i],QStringList(QString("hello"))));
            }

            ui->treeWidget->insertTopLevelItems(0, items);
            */

        }
    }
#endif
}
