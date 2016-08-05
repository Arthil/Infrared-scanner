#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    srand (time(NULL));

    //draw background
    QPixmap bkgnd("/Users/chrisunkone/Downloads/tutka.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->lineEdit_command->hide();

    serialBuffer = "";

    //numberOfPoints = 250;
    centerX = 640;
    centerY = 357;
    showRadar = false;
    timePassed = 0;
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(update_paintEvent()));
    timer->start(10);

    port_name = "";
    port_available = false;
    port = new QSerialPort;

    //Get all the available ports

    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier())
        {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier())
        {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)
            {
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id)
                {
                    port_name = serialPortInfo.portName();
                    port_available = true;
                }
            }
        }
    }


    init_port();
}

//Initializes the properties of a port, also shows a warning if no port was found
void MainWindow::init_port()
{

    if(port_available == true)
    {
        port->setPortName(port_name);
        port->open(QSerialPort::ReadWrite);
        qDebug() << port->setBaudRate(QSerialPort::Baud9600);
        qDebug() << port->setDataBits(QSerialPort::Data8);
        qDebug() << port->setParity(QSerialPort::NoParity);
        qDebug() << port->setStopBits(QSerialPort::OneStop);
        qDebug() << port->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(port,SIGNAL(readyRead()),this,SLOT(read_serial()));
        qDebug() << "Connection succesful!";
    }
    else
    {
        QMessageBox::warning(this,"Port Error","Couldn't find port.");
    }

}

MainWindow::~MainWindow()
{
    if(port->isOpen())port->close();

    delete port;
    delete ui;
}

//Function used for custom commands inside application which is used to communicate with the arduino device
void MainWindow::send_command(QString command)
{
    if(port->isWritable())
    {
        port->write(command.toStdString().c_str());
    }
    else
    {
        qDebug() << "Couldn't wirte to serial!";
    }
}


void MainWindow::read_serial()
{
    //Read the data from a serialport and parse it
    serialData = port->readLine(1024);
    serialBuffer = QString::fromStdString(serialData.toStdString());
    QStringList bufferSplit = serialBuffer.split(",");

    foreach(QString str,bufferSplit)
    {
        int i = str.toInt();
        if(i != 0)
        {
         i = (600-i)/3;
        }

        qDebug() << i;

    //if the point is viable, push it to the points vector
        if(i >= 25 && i < 500)
        {
            points.push_back(i);
        }


    }

    serialBuffer = "";

}

//Send the scanning command to the arduino device
void MainWindow::on_button_scan_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    //Calculate random points
    /*
    for(int i = 0; i < numberOfPoints; i++ )
    {
        points.push_back((rand() % 10 + 1)*5 + 100);
    }
    */

    send_command("scan");


    //Scan completed
    //Setting painter on
    showRadar = true;

}

void MainWindow::on_button_setup_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_check_for_connection_clicked()
{
    //send_command("test");
    ui->lineEdit_command->show();
}

void MainWindow::on_button_exit_clicked()
{
    this->close();
}

void MainWindow::on_button_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    points.clear();
    showRadar = false;
}

void MainWindow::on_button_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    points.clear();
    showRadar = false;
}


//This function paints the scanner itself
//One part is the rotating scanner which is just doing a circle
//Second part draws the data found from points vector to the screen
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pointpen(Qt::green);

    //Draw the circle and the scale
    QPen outlinepen(Qt::white);
    outlinepen.setWidth(1);
    painter.setPen(outlinepen);
    QPoint pt;
    pt.setX(centerX);
    pt.setY(centerY);

    //draw the white circles in the center
    painter.drawEllipse(pt, 220, 220);
    painter.drawEllipse(pt, 170, 170);
    painter.drawEllipse(pt, 120, 120);
    painter.drawEllipse(pt, 70, 70);

    //draw the white lines in the center
    painter.drawLine(410,357,870,357);
    painter.drawLine(640,137,640,577);

    painter.drawLine(centerX-125,centerY-125,centerX+125,centerY+125);
    painter.drawLine(centerX+125,centerY-125,centerX-125,centerY+125);

    QColor radarGreen(0,255,0);
    QPen radarpen(radarGreen);
    painter.setPen(radarpen);
    radarpen.setWidth(1);
    double timestep = 3.14/360;
    timePassed += timestep;





    pointpen.setWidth(5);
    painter.setPen(pointpen);

    //Draw the radar points if showRadar == true
    //Draw the data from points vector
    if(showRadar == true)
    {
        for(int i = 0; i < points.size() ;i++)
        {
            qDebug() << points.size();
            if(points[i] < 150)
            {
                angle = 3.14/100*(-i);
                QPoint pt;
                pt.setX(centerX + points[i]*cos(angle));
                pt.setY(centerY + points[i]*sin(angle));
                painter.drawPoint(pt);
            }
        }

        for(int i = 0;i < 100;i++)
        {
            radarGreen.setAlpha(255-i*2.5);
            radarpen.setColor(radarGreen);
            painter.setPen(radarpen);
            painter.drawLine(centerX,centerY,centerX + 220*cos(timePassed-timestep*i),centerY + 220*sin(timePassed-timestep*i));
        }
    }
}

void MainWindow::update_paintEvent()
{
    this->repaint();
}

void MainWindow::on_lineEdit_command_returnPressed()
{
    send_command(ui->lineEdit_command->text());
    ui->lineEdit_command->clear();
}
