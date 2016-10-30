#include "mainwindow.h"
#include "ui_mainwindow.h"
int mode=1,spd=1,z=0;
#define roll 1
#define pause 2
#define spdup 3
#define spddown 4
#define up 5
#define down 6
#define mode1 7
#define mode2 8


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->start(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(Nav()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}
void MainWindow::Nav() //this function must be called after checking if the joystick is connected
{
    char x,y,manX,manY,cam,r;
    sf::Joystick::update();
    if(sf::Joystick::isConnected(0)){
       // qDebug()<<"in NAV";
    if(sf::Joystick::isButtonPressed(0, mode1) && !states[mode1])
    {   mode=1;
        states[mode1]=true;
        qDebug()<<"mode 1 activated";

    }
    else if(sf::Joystick::isButtonPressed(0, mode2) && !states[mode2])
    {   mode=2;
        states[mode2]=true;
        qDebug()<<"mode 2 activated";

    }
    if(sf::Joystick::isButtonPressed(0, pause) && !states[pause]) states[pause]=true;
    if(sf::Joystick::isButtonPressed(0, roll) && !states[roll]) states[roll]=true;
    //while (!sf::Joystick::isButtonPressed(0, pause) /*&& !states[pause]*/ && !sf::Joystick::isButtonPressed(0, roll) && !states[roll])
    //{
        if (mode=1)
        {
            x=sf::Joystick::getAxisPosition(0,sf::Joystick::X);
            y=sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
            manX=sf::Joystick::getAxisPosition(0,sf::Joystick::PovX);
            manY=sf::Joystick::getAxisPosition(0,sf::Joystick::PovY);
            cam=sf::Joystick::getAxisPosition(0,sf::Joystick::Z);
        }
        else if(mode=2)
        {
            manX=sf::Joystick::getAxisPosition(0,sf::Joystick::X);
            manY=sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
            x=sf::Joystick::getAxisPosition(0,sf::Joystick::PovX);
            y=sf::Joystick::getAxisPosition(0,sf::Joystick::PovY);
            cam=sf::Joystick::getAxisPosition(0,sf::Joystick::Z);
        }

    //}
    while(sf::Joystick::isButtonPressed(0, roll) && states[roll])
    {
       r=sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
    }
    if (sf::Joystick::isButtonPressed(0, up) && !states[up])
       { z=15; states[up]=true;}
    else if(sf::Joystick::isButtonPressed(0,down) && !states[down])
       {z=15; states[down]=true;}
    else if (sf::Joystick::isButtonPressed(0, spdup) && !states[spdup])
        { spd*=2; states[spdup]=true;}
    else if (sf::Joystick::isButtonPressed(0, spddown) && !states[spddown])
        { spd*=0.5; states[spddown]=true;}
    for (int i = 0; i < 8; i++)
    {
        if (!sf::Joystick::isButtonPressed(0, i) && states[i]) {
                        states[i] = false;
        }
    }
    qDebug()<<"x= "<<x<<"y= "<<(y);
    }
    else{
        qDebug()<<"NOT CONNECTED";
    }
}
