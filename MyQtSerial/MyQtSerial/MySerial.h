#ifndef MYSERIAL_H
#define MYSERIAL_H


class MySerial
{
public:
    MySerial();
    ~MySerial();

    void open();
     serial = new QSerialPort(this);
};

#endif // MYSERIAL_H
