#ifndef MAIN_H
#define MAIN_H

#include <QCoreApplication>

enum ttype_vadcout
{
    _VADC_OUT_VOLTAGE,
    _VADC_OUT_CURRENT
};

#define VADC_START_BYTE 0xA3
#define _LP_RD_CONFIG_MODE_VIRT_ADC 0x22
#define VADC_CONTROL_REG 0x0154

enum _pc_get
{
    _LP_READ_EMPTY,
    _LP_RD_CH_SETTINGS,
    _LP_RD_DATE_TIME,
    _LP_RD_ACK,
    _LP_RD_GETLOG,
    _LP_RD_GETOSC,
    _LP_RD_CLR_LOG,
    _LP_RD_SET_MODE,
    _LP_RD_TEST_MV,
    _LP_RD_TEST_MURS,//MURS2
    _LP_RD_TEST_MC,  //MURS1
    _LP_RD_TEST_TERMINAL,
    _LP_RD_PUSK_LP,
    _LP_RD_RESET_INF,
    _LP_RD_VER_PO,
    _LP_RD_TEST_AK,
    _LP_RD_FACTORY_DEF,
    _LP_RD_CALIBR,
    _LP_RD_TEST_KANAL,
    _LP_RD_SOUND_SETT,
    _LP_RD_RANDOM_SETTINGS,
    _LP_RD_SEND_HF_DATA,
    _LP_RD_GETCOUNT_LOG,


    //******* ДФЗ
    _LP_RD_CONFIG_VIRT_ADC=0x20,
    _LP_RD_CALIBR_MDFZ_ADC,
    _LP_RD_WRITE_MDFZ_REG,
    //PC
    _LP_RD_GET_MDFZ_IZM,
    _LP_RD_GET_V4Z_STATE,
    _LP_RD_GET_HW_SETTINGS,
    _LP_RD_GET_TIME,
    _LP_RD_GET_DATE,
    _LP_RD_GET_LOG,
    _LP_RD_GET_LEDS,
    _LP_RD_GET_OSC_AK,
    _LP_RD_GET_MODULE_STATE,
    _LP_RD_GET_IZM,
    _LP_RD_GET_MODULES_FW,
    _LP_RD_GET_OMP,
    _LP_RD_GET_MU_HELTH,

    _LP_RD_VBUTTON = 0x30,
    _LP_RD_GET_STRING,
    _LP_RD_GET_GOOSE_STATE,
    _LP_RD_GETCOMPARATORS_STATE,
    _LP_RD_VADC_PARAM,

    _LP_RD_GET_FESTATE,

    _LP_RD_COUNT
};

enum _pc_rcv_ansv
{
    _LP_SET_EMPTY,
    _LP_SET_SETTINGS,
    _LP_SET_TIME,
    _LP_SET_DATE,
    _LP_SEND_AK_RES,
    _LP_SEND_RESET,
    _LP_SEND_EVENT,
    _LP_SEND_LOG,
    _LP_SEND_LEDSTATE,
    _LP_TRANSMIT,
    _LP_SEND_ACK,
    _LP_SEND_OSC,
    _LP_START_AK,
    _LP_SEND_PA,
    _LP_SEND_MODULES_STATE,
    _LP_SEND_IZM,
    _LP_GET_VER_PO,
    _LP_SEND_FW,
    _LP_SEND_CALIBR,
    _LP_SEND_TEST_KANAL,
    _LP_SEND_RANDOM_SETTINGS,
    _LP_SEND_FFT,
    _LP_SEND_PHASE,
    _LP_SEND_BUZZER,
    _LP_SEND_LOG_COUNT,
    _LP_SEND_MODULES_EXP_STATE,
    _LP_SEND_STRING,
    _LP_SEND_GOOSE_STATE,


    //ДФЗ
    _LP_SEND_V4Z_STATE = 0x20,
    _LP_SEND_V4Z_IZM,
    _LP_SEND_COMPARATORS_STATE,
    _LP_SEND_MDFZ_OSC,
    _LP_SEND_MDFZ_OMP,
    _LP_SEND_MU_HEALTH,
    _LP_SEND_MZ_STATE_REGS,
    _LP_SEND_VADC_PARAM,

    _LP_SEND_FESTATE,

    _LP_COM_COUNT
};


struct _vadc_params
{
    QString  ip = "192.168.3.33";
    quint16 port = 8888;

    bool en_VADC = false;
    bool syncUa  = false;
    bool kt_En = false;

    bool send_mode = false;
    bool read_mode = false;
    uint16_t read_reg = 0x0000;

    float Ua = 60.0f;
    qint16 degUa = 0;
    float Ub = 60.0f;
    qint16 degUb = 240;
    float Uc = 60.0f;
    qint16 degUc = 120;
    float U3U0 = 0.0f;
    qint16 deg3U0 = 0;

    float Ia = 1.0f;
    qint16 degIa = 0;
    float Ib = 1.0f;
    qint16 degIb = 240;
    float Ic = 1.0f;
    qint16 degIc = 120;
};

union tbits8
{
    unsigned char byte_data;
    struct {
        unsigned bit0:1;
        unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;
    } single_bits;
};

union tbits16
{
    unsigned short short_data;
    unsigned char byte_data[2];
    struct {
        unsigned bit0:1;
        unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;
        unsigned bit8:1;
        unsigned bit9:1;
        unsigned bit10:1;
        unsigned bit11:1;
        unsigned bit12:1;
        unsigned bit13:1;
        unsigned bit14:1;
        unsigned bit15:1;
    } single_bits;
};

union tconvert_short
{
    unsigned short short_val;
    unsigned char char_val[2];
};

union tconvert_int
{
    unsigned int int_val;
    unsigned short short_val[2];
    unsigned char  char_val[4];
};

union tconvert_int64
{
    uint64_t	int64_data;
    unsigned int   int32_data[2];
    unsigned short short_data[4];
    unsigned char  byte_data[8];
};

enum _tconvert_val
{
    _LOW,
    _HIGH,
    _LOW2,
    _HIGH2,
    _LOW3,
    _HIGH3,
    _LOW4,
    _HIGH4
};

#endif // MAIN_H
