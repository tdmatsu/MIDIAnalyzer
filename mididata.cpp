#include "mididata.h"

#include <QDebug>

MIDIData::MIDIData()
{
}

void MIDIData::setByteData(QByteArray data)
{
    init();
    m_byteData = data;

    // it should be at least bigger than 14 bytes
    if(m_byteData.size() < 14){
        qDebug() << "ERROR: file size is less than 14 bytes";
        return;
    }

    if(!validate(0,0x4D) || !validate(1,0x54) || !validate(2,0x68) || !validate(3,0x64)) {
        qDebug() << "ERROR: Header is not 'MThd'";
        return;
    }

    if(!validate(4,0x00) || !validate(5,0x00) || !validate(6,0x00) || !validate(7,0x06)) {
        qDebug() << "ERROR: Invalid header chunk size";
        return;
    }

    if(!validate(8,0x00) || !(validate(9,0x00) || validate(9,0x01) || validate(9,0x02))) {
        qDebug() << "ERROR: Invalid SMF format type";
        return;
    } else {
        m_SMFFormatType = m_byteData[9];
        qDebug() << "SMF format type = " << m_SMFFormatType;
    }

    // number of tracks
    m_intTrackCount = m_byteData[10] * 0x100 + m_byteData[11];
    qDebug() << m_intTrackCount << " tracks";

    // delta time
    m_intDeltaTime = m_byteData[12] * 0x100 + m_byteData[13];
    qDebug() << "delta time = " << m_intDeltaTime;


    qDebug() << "done!!";

    m_blnIsValid = true;
}

void MIDIData::init()
{
    m_blnIsValid = false;
    m_SMFFormatType = 0;
    m_intTrackCount = 0;
    m_intDeltaTime = 0;
}

bool MIDIData::validate(int index ,int data)
{
    // index out of range
    if (index > m_byteData.size() - 1){
        qDebug() << "index out of range";
    }

    return (m_byteData.at(index) == data);
}
