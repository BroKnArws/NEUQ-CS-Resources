#include "mymessagebox.h"
#include "ui_mymessagebox.h"
#include <QPixmap>
//阴影类包含头文件
#include <QGraphicsDropShadowEffect>

MyMessageBox::MyMessageBox(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
    this->setProperty("canMove",true);

    this->initUi();
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

void MyMessageBox::initUi()
{
    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(16);
    //给嵌套QDialog设置阴影
    ui->w_bg->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->lay_bg->setMargin(12);
}

void MyMessageBox::setIcon(QString type)
{
    if(type == "error") {
        QPixmap logo(":/icons/error.png");
        ui->lab_mbox_icon->setPixmap(logo);
    }else if(type == "warn") {
        QPixmap logo(":/icons/warn.png");
        ui->lab_mbox_icon->setPixmap(logo);
    }else if(type == "check") {
        QPixmap logo(":/icons/check.png");
        ui->lab_mbox_icon->setPixmap(logo);
    }else {
        QPixmap logo(":/icons/question.png");
        ui->lab_mbox_icon->setPixmap(logo);
    }
}

void MyMessageBox::setBodyText(QString text)
{
    ui->lab_mess_body->setText(text);
}

void MyMessageBox::setButtonText(QString text1, QString text2)
{
    ui->btn_mbox_btn01->show();
    ui->btn_mbox_btn01->setText(text1);
    ui->btn_mbox_btn02->setText(text2);
}

void MyMessageBox::setButtonText(QString text)
{
    ui->btn_mbox_btn01->hide();
    ui->btn_mbox_btn02->setText(text);

}

void MyMessageBox::on_btn_system_close_clicked()
{
    //发送信号
    btnchicked(0);
    //关闭窗口
    close();
}

void MyMessageBox::on_btn_mbox_btn01_clicked()
{
    //发送信号
    btnchicked(1);
    //关闭窗口
    close();
}

void MyMessageBox::on_btn_mbox_btn02_clicked()
{
    //发送信号
    btnchicked(2);
    //关闭窗口
    close();
}
