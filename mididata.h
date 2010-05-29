#ifndef MIDIDATA_H
#define MIDIDATA_H

#include <QObject>

class MIDIData : public QObject
{
    Q_OBJECT
public:
    MIDIData();

    void setByteData(QByteArray data);

private:
    QByteArray m_byteData;
    bool m_blnIsValid;
    int m_SMFFormatType;
    int m_intTrackCount;
    int m_intDeltaTime;

    bool validate(int index, int data);

    void init();
};

#endif // MIDIDATA_H
