#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_button_scan_clicked();

    void on_button_setup_clicked();

    void on_button_check_for_connection_clicked();

    void on_button_exit_clicked();

    void on_button_back_clicked();

    void on_button_back_2_clicked();

    void update_paintEvent();

    void send_command(QString);

    void on_lineEdit_command_returnPressed();

    void read_serial();

private:
    Ui::MainWindow *ui;
    std::vector<float> points;
    void init_port();

    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString port_name;
    bool port_available;

    QString serialBuffer;
    QByteArray serialData;

    QSerialPort *port;
    double angle;
    int numberOfPoints;
    int centerX;
    int centerY;

    bool showRadar;
    double timePassed;
    QTimer *timer;


protected:
    void paintEvent(QPaintEvent *e);

};

#endif // MAINWINDOW_H
