#include "mididata.h"

#include <QDebug>
#include <QTreeWidgetItem>

#define READ2BYTES(buf,i) buf.at(i)*0x100+buf.at(i+1)
//#define READ4BYTES(buf,i)

inline int readBytes(QByteArray &buf, int index, int len)
{
    if (len > 4)
        return 0; //max size is int

    int ret = buf.at(index);
    for (int i = 1; i < len; i++){
        ret <<= 8;
        ret += (uchar)buf.at(index+i);
    }
    return ret;
}

MIDIData::MIDIData(QObject*parent, QIODevice *data)
    : QObject(parent)
{
    setByteData(data);
}

QTreeWidgetItem* MIDIData::createItem(QString key, QString value)
{
    QStringList list;
    list << key << value;
    return new QTreeWidgetItem(list);
}

void MIDIData::setByteData(QIODevice *data)
{
    m_items.clear();

    //read chunk header
    QByteArray buf;

    while(!data->atEnd())
    {
        buf.resize(8);
        if (data->read(buf.data(),8) == -1){
            qDebug() << "Failed to read data type!";
            return;
        }

        QString strType = buf.left(4);
        int intLen = readBytes(buf,4,4);

        buf.clear();
        buf.resize(intLen);
        if (data->read(buf.data(), intLen) == -1){
            qDebug() << "Failed to read data!";
            qDebug() << "    strType = " + strType;
            qDebug() << "    intLen = " + QString::number(intLen,10);
            return;
        }

        if (strType != "MThd" && strType != "MTrk"){
            qDebug() << "Invalid chunk header!!";
            qDebug() << "    strType = " + strType;
            return;
        }

        m_items.append(new QTreeWidgetItem(QStringList(strType)));
        m_items.last()->addChild(createItem("Chunk size", QString::number(intLen, 10)));

        if (strType == "MThd"){
            if(intLen != 6){
                qDebug() << "Invalid header chunk size!!";
                qDebug() << "    intLen = " + QString::number(intLen,10) << " (expected 6)";
                return;
            }
            int typ = readBytes(buf, 0, 2);
            m_items.last()->addChild(createItem("SMF type", QString::number(typ,10)));

            int trk = readBytes(buf, 2, 2);
            m_items.last()->addChild(createItem("Number of tracks", QString::number(trk,10)));

            int tim = readBytes(buf, 4, 2);
            m_items.last()->addChild(createItem("Delta time", QString::number(tim,10)));
        }else if(strType == "MTrk"){

        }
    }
}
