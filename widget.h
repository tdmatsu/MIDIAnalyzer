#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "mididata.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;

    void showByteData(QByteArray buf);
    MIDIData m_MidiData;

private slots:
    void on_btnOpen_clicked();
};

#endif // WIDGET_H
