#ifndef MIDIDATA_H
#define MIDIDATA_H

#include <QObject>

class QIODevice;
class QTreeWidgetItem;

class MIDIData : public QObject
{
    Q_OBJECT
public:
    MIDIData(QObject* parent, QIODevice* data);
    QList<QTreeWidgetItem *>& items(){return m_items;}

private:
    QList<QTreeWidgetItem *> m_items;
    void setByteData(QIODevice *data);

    QTreeWidgetItem* createItem(QString key, QString value);
};

#endif // MIDIDATA_H
