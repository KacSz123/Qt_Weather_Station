#include "connect_window.h"
#include "ui_connect_window.h"
#include <QList>
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
Connect_window::Connect_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect_window)
{
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->device =new QSerialPort;
    DF=new DataFrame;


}

Connect_window::~Connect_window()
{
    delete ui;
    delete device;
}

void Connect_window::on_pushButtonSearch_clicked()
{


    this->addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++)
    {
        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBoxDevices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }/* */
}


void Connect_window::addToLogs(QString msg)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->Logs->append(currentDateTime + "\t" + msg);
}


void Connect_window::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString comboBoxQString = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxQString.split("\t");
    QString portName = portList.first();

    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen())
    {
        if(device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            // CONNECT:
            connect(this->device, SIGNAL(readyRead()),
                    this, SLOT(readFromPort()));

            this->addToLogs("Otwarto port szeregowy.");
        }
        else
        {
            this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    }
    else
    {
        this->addToLogs("Port już jest otwarty!");
        return;
    }
}

void Connect_window::on_pushButtonDisc_clicked()
{
    if(this->device->isOpen()) {
        this->device->close();
        this->addToLogs("Zamknięto połączenie.");
    } else {
        this->addToLogs("Port nie jest otwarty!");
        return;
    }}
void Connect_window::readFromPort() {
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        //qDebug() << line.left(pos);
        this->addToLogs(line.left(pos));

        this->DF->ParseData(line.toStdString());
        //DF->display_DataFrame();
        sendData();
        sendDataToPlot();
    }
}

void Connect_window::sendMessageToDevice(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->addToLogs("Wysyłam informacje do urządzenia " + message);
        this->device->write(message.toStdString().c_str());
    } else {
        this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
    }
}
