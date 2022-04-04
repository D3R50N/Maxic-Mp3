#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    container=new QVBoxLayout;
    ui->container->setLayout(container);
    ui->container->layout()->setMargin(1);
    currentBtn=0;
    currentWidget=0;


    menuHome=new Home();
    menuLocal=NULL;
    menuRecord=NULL;
    menuSettings=NULL;

    changeWidget(menuHome);
}

MainMenu::~MainMenu()
{
    delete ui;
}
void MainMenu::changeWidget(QWidget *newWidget, QPushButton *curr)
{
    clearContainer();
    currentWidget=newWidget;

    ui->container->layout()->addWidget(currentWidget);
    if(currentWidget->isHidden())
        currentWidget->show();
    if(curr!=0)
    {
        if(currentBtn!=0)
        {
            currentBtn->setStyleSheet(currentBtnStyleSheet);
        }
        currentBtn=curr;
        changeCurrentBtn();
    }
}

void MainMenu::clearContainer()
{
    for(int i=0;i<container->count();i++)
        container->removeItem(container->itemAt(i));

    if(currentWidget!=0)
        currentWidget->hide();
}
void MainMenu::on_label_clicked()
{
    changeWidget(menuHome);
    currentBtn->setStyleSheet(currentBtnStyleSheet);
    currentBtn=0;
}
void MainMenu::changeCurrentBtn()
{
    currentBtn->setStyleSheet(currentBtnStyleSheet+"QPushButton{border-left : 5px solid deepskyblue;}\n QPushButton::hover{border-left : 5px solid white;}");
}
void MainMenu::autoChangeWidget(QWidget *wdg)
{
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    if(currentBtn==0)
        currentBtnStyleSheet=btn->styleSheet();
    changeWidget(wdg,btn);
}

void MainMenu::on_local_clicked()
{
    if(menuLocal==NULL)
        menuLocal=new Local();

    autoChangeWidget(menuLocal);
}

void MainMenu::on_record_clicked()
{
    if(menuRecord==NULL)
        menuRecord=new Record();

    autoChangeWidget(menuRecord);
}

void MainMenu::on_online_clicked()
{
    autoChangeWidget(menuHome);
}

void MainMenu::on_settings_clicked()
{
    if(menuSettings==NULL)
        menuSettings=new Settings();

    autoChangeWidget(menuSettings);
}
