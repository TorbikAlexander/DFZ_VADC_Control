#include "main.h"
#include <QCoreApplication>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTextStream>
#include <QCommandLineParser>
#include "crc16.h"


static inline void PutShortToBuff(QByteArray *data_buff, quint16 sdata)
{
    union tconvert_short data;
    data.short_val = sdata;
    data_buff->push_back(data.char_val[_HIGH]);
    data_buff->push_back(data.char_val[_LOW]);
}

static inline void PutFloatToBuff(QByteArray *data_buff, float sdata)
{
    union tconvert_short data;
    data.short_val = static_cast<quint16>(sdata*100.0f);
    data_buff->push_back(data.char_val[_HIGH]);
    data_buff->push_back(data.char_val[_LOW]);
}

QByteArray VADC_SetMode( struct _vadc_params *VADC_Params)
{
    QByteArray data_buff;
    qint16 deg;
    quint16 vadc_en_param = 0;
    tconvert_short param;

    data_buff.clear();

    data_buff.push_back((quint8)VADC_START_BYTE);//
    data_buff.push_back((quint8)_LP_RD_CONFIG_MODE_VIRT_ADC);
    data_buff.push_back((quint8)0x00);
    data_buff.push_back((quint8)0x0A);

    if(VADC_Params->en_VADC) vadc_en_param = 1;
    if(VADC_Params->syncUa) vadc_en_param |= 0x10;
    if(VADC_Params->kt_En) vadc_en_param |= 0x04;

    param.short_val = VADC_CONTROL_REG;
    data_buff.push_back(param.char_val[_HIGH]);
    data_buff.push_back(param.char_val[_LOW]);

    param.short_val = vadc_en_param;
    data_buff.push_back(param.char_val[_HIGH]);
    data_buff.push_back(param.char_val[_LOW]);

    tconvert_short buff_crc;
    buff_crc.short_val = CRC16(&data_buff,data_buff.size());
    data_buff.append(buff_crc.char_val[_LOW]);
    data_buff.append(buff_crc.char_val[_HIGH]);

    return data_buff;

}


QByteArray VADC_SetU( struct _vadc_params *VADC_Params)
{
    QByteArray data_buff;
    qint16 deg;
    quint8 vadc_en_param = 0;

    data_buff.clear();

    data_buff.push_back((quint8)VADC_START_BYTE);//
    data_buff.push_back((quint8)_LP_RD_CONFIG_VIRT_ADC);
    data_buff.push_back((quint8)0x00);
    data_buff.push_back((quint8)0x18);

    // if(VADC_Params->en_VADC) vadc_en_param = 1;
    // if(VADC_Params->syncUa) vadc_en_param |= 0x10;
    // if(VADC_Params->kt_En) vadc_en_param |= 0x04;

    data_buff.push_back(vadc_en_param);
    data_buff.push_back(_VADC_OUT_VOLTAGE);

    PutFloatToBuff(&data_buff,VADC_Params->Ua);
    deg = VADC_Params->degUa;
    if(deg<0) deg = 360 + deg;
    PutShortToBuff(&data_buff, deg);

    deg = VADC_Params->degUb;
    if(deg<0) deg = 360 + deg;
    PutFloatToBuff(&data_buff,VADC_Params->Ub);
    PutShortToBuff(&data_buff,deg);

    deg = VADC_Params->degUc;
    if(deg<0) deg = 360 + deg;
    PutFloatToBuff(&data_buff,VADC_Params->Uc);
    PutShortToBuff(&data_buff,deg);

    deg = VADC_Params->deg3U0;
    if(deg<0) deg = 360 + deg;
    PutFloatToBuff(&data_buff,VADC_Params->U3U0);
    PutShortToBuff(&data_buff,deg);

    tconvert_short buff_crc;
    buff_crc.short_val = CRC16(&data_buff,data_buff.size());
    data_buff.append(buff_crc.char_val[_LOW]);
    data_buff.append(buff_crc.char_val[_HIGH]);

    return data_buff;

}

QByteArray VADC_SetI( struct _vadc_params *VADC_Params)
{
    QByteArray data_buff;
    qint16 deg;
    quint8 vadc_en_param = 0;

    data_buff.clear();

    data_buff.push_back((quint8)VADC_START_BYTE);
    data_buff.push_back((quint8)_LP_RD_CONFIG_VIRT_ADC);
    data_buff.push_back((quint8)0x00);
    data_buff.push_back((quint8)0x18);

    // if(VADC_Params->en_VADC) vadc_en_param = 1;
    // if(VADC_Params->syncUa) vadc_en_param |= 0x10;

    data_buff.push_back(vadc_en_param);
    data_buff.push_back(_VADC_OUT_CURRENT);

    PutFloatToBuff(&data_buff,VADC_Params->Ia);
    deg = VADC_Params->degIa;
    if(deg<0) deg = 360 + deg;
    PutShortToBuff(&data_buff,deg);

    PutFloatToBuff(&data_buff,VADC_Params->Ib);
    deg = VADC_Params->degIb;
    if(deg<0) deg = 360 + deg;
    PutShortToBuff(&data_buff,deg);

    PutFloatToBuff(&data_buff,VADC_Params->Ic);
    deg = VADC_Params->degIc;
    if(deg<0) deg = 360 + deg;
    PutShortToBuff(&data_buff,deg);

    PutFloatToBuff(&data_buff,0.0f);
    PutShortToBuff(&data_buff,0);

    tconvert_short buff_crc;
    buff_crc.short_val = CRC16(&data_buff,data_buff.size());
    data_buff.append(buff_crc.char_val[_LOW]);
    data_buff.append(buff_crc.char_val[_HIGH]);

    return data_buff;
}

QByteArray VADC_ReadReg( struct _vadc_params *VADC_Params)
{
    QByteArray data_buff;
    qint16 deg,data;
    quint8 vadc_en_param = 0;

    data_buff.clear();

    // data_buff.push_back((quint8)VADC_START_BYTE);
    // data_buff.push_back((quint8)_LP_RD_CONFIG_VIRT_ADC);
    // data_buff.push_back((quint8)0x00);
    // data_buff.push_back((quint8)0x0A);

    // data = VADC_Params->read_reg;
    // PutShortToBuff(&data_buff,data);

    // data_buff.push_back((quint8)0x01);
    // data_buff.push_back((quint8)0x00);

    // tconvert_short buff_crc;
    // buff_crc.short_val = CRC16(&data_buff,data_buff.size());
    // data_buff.append(buff_crc.char_val[_LOW]);
    // data_buff.append(buff_crc.char_val[_HIGH]);

    return data_buff;
}

void ProcessReadReg(QByteArray answer)
{
    //if(answer.at(1)==_LP_SEND_V4Z_STATE)
    {

    }
}

inline int SendToVADC(struct _vadc_params vadc_param)
{
    QTextStream err(stderr);
    QTcpSocket socket;
    QByteArray data_buff;


    socket.connectToHost(vadc_param.ip, vadc_param.port);
    if (!socket.waitForConnected(3000)) {
        err << "Connect failed: " << socket.errorString() << Qt::endl;
        return 1;
    }

    data_buff = VADC_SetU(&vadc_param);
    socket.write(data_buff);
    socket.waitForBytesWritten(100);
    socket.readAll();
    socket.waitForReadyRead(20);

    data_buff = VADC_SetI(&vadc_param);
    socket.write(data_buff);
    socket.waitForBytesWritten(100);
    socket.readAll();
    socket.waitForReadyRead(20);

    if(vadc_param.send_mode)
    {
        data_buff = VADC_SetMode(&vadc_param);
        socket.write(data_buff);
        socket.waitForBytesWritten(100);
        socket.readAll();
        socket.waitForReadyRead(20);
    }

    if(vadc_param.read_mode)
    {
        QByteArray answer;

        data_buff = VADC_ReadReg(&vadc_param);
        socket.write(data_buff);
        socket.waitForBytesWritten(100);
        socket.readAll();
        socket.waitForReadyRead(20);
        answer = socket.readAll();
        ProcessReadReg(answer);
    }

    socket.disconnectFromHost();
    if (socket.state() != QAbstractSocket::UnconnectedState) {
        socket.waitForDisconnected(3000);
    }

    return 0;
};

inline void ParseVADCParam(QCoreApplication *a,struct _vadc_params *vadc_params)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("Orion DFZ-110 VADC Control application");
    parser.addHelpOption();

    parser.addOption({"ip", "VADC IP address", "value"});
    parser.addOption({"En", "VADC Enable", "value"});
    parser.addOption({"SyncEn", "VADC Sync Enable", "value"});
    parser.addOption({"KTEn", "KT Enable", "value"});

    parser.addOption({"Ua", "Voltage A,V", "value"});
    parser.addOption({"Ub", "Voltage B,V", "value"});
    parser.addOption({"Uc", "Voltage C,V", "value"});
    parser.addOption({"degUa", "Deg UA,°", "value"});
    parser.addOption({"degUb", "Deg UB,°", "value"});
    parser.addOption({"degUc", "Deg UC,°", "value"});

    parser.addOption({"Ia", "Current A,A", "value"});
    parser.addOption({"Ib", "Current B,A", "value"});
    parser.addOption({"Ic", "Current C,A", "value"});
    parser.addOption({"degIa", "Deg IA,°", "value"});
    parser.addOption({"degIb", "Deg IB,°", "value"});
    parser.addOption({"degIc", "Deg IC,°", "value"});

    parser.addOption({"U3U0", "3U0,V", "value"});
    parser.addOption({"deg3U0", "Deg 3U0,°", "value"});

    parser.addOption({"getReg", "HexRegValue", "value"});

    parser.process(*a);

    if (parser.isSet("ip"))
    {
        vadc_params->ip = parser.value("ip");
    }

    if (parser.isSet("En"))
    {
        vadc_params->en_VADC = parser.value("En").toUInt() & 1;
        vadc_params->send_mode = true;
    }

    if (parser.isSet("SyncEn"))
    {
        vadc_params->syncUa = parser.value("SyncEn").toUInt() & 1;
        vadc_params->send_mode = true;
    }

    if (parser.isSet("KTEn"))
    {
        vadc_params->syncUa = parser.value("KTEn").toUInt() & 1;
        vadc_params->send_mode = true;
    }
    //Ua
    if (parser.isSet("Ua"))
    {
        vadc_params->Ua = parser.value("Ua").toFloat();
    }
    if (parser.isSet("degUa"))
    {
        vadc_params->degUa = parser.value("degUa").toInt();
    }
    //Ub
    if (parser.isSet("Ub"))
    {
        vadc_params->Ub = parser.value("Ub").toFloat();
    }
    if (parser.isSet("degUb"))
    {
        vadc_params->degUb = parser.value("degUb").toInt();
    }
    //Uc
    if (parser.isSet("Uc"))
    {
        vadc_params->Uc = parser.value("Uc").toFloat();
    }
    if (parser.isSet("degUc"))
    {
        vadc_params->degUc = parser.value("degUc").toInt();
    }
//
    //Ia
    if (parser.isSet("Ia"))
    {
        vadc_params->Ia = parser.value("Ia").toFloat();
    }
    if (parser.isSet("degIa"))
    {
        vadc_params->degIa = parser.value("degIa").toInt();
    }
    //Ib
    if (parser.isSet("Ib"))
    {
        vadc_params->Ib = parser.value("Ib").toFloat();
    }
    if (parser.isSet("degIb"))
    {
        vadc_params->degIb = parser.value("degIb").toInt();
    }
    //Ic
    if (parser.isSet("Ic"))
    {
        vadc_params->Ic = parser.value("Ic").toFloat();
    }
    if (parser.isSet("degIc"))
    {
        vadc_params->degIc = parser.value("degIc").toInt();
    }
    //3U0
    if (parser.isSet("U3U0"))
    {
        vadc_params->U3U0 = parser.value("U3U0").toFloat();
    }
    if (parser.isSet("deg3U0"))
    {
        vadc_params->deg3U0 = parser.value("deg3U0").toInt();
    } //parser.addOption({"getReg", "HexRegValue", "value"});

    //HexRegValue
    if (parser.isSet("getReg"))
    {
        vadc_params->read_reg = parser.value("getReg").toUInt();
        vadc_params->read_mode = true;
    }



}

int main(int argc, char *argv[])
{
    struct _vadc_params vadc_params;

    QCoreApplication a(argc, argv);

    ParseVADCParam(&a, &vadc_params);
    SendToVADC(vadc_params);

    return 0;
}
