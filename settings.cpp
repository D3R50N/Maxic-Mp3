#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_comboBox_currentIndexChanged(int index)
{
    if(index==1)
    {
        ui->frame->setStyleSheet("background-color:white");
    }
}
