#include "local.h"
#include "ui_local.h"

Local::Local(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Local)
{
    ui->setupUi(this);
    player=new QMediaPlayer();
    playlist=new QMediaPlaylist();
    isSliding=false;
    shuffleActivated=false;
    changeOnce=true;

    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(changePos(qint64)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(updateCurrentSong(int)));
}

Local::~Local()
{
    delete ui;
}

void Local::on_pushButton_clicked()
{
    QFileDialog f;
    QString filter=tr("Musiques (*.mp3)");
    filesList=f.getOpenFileNames(0,"Sélectionner des sons","",filter);
    foreach(QString file, filesList)
    {
        playlist->addMedia(QMediaContent(QUrl::fromLocalFile(file)));
        songsList<<file.split("/")[file.split("/").length()-1];
    }
    updatePlaylist();
    playlist->setCurrentIndex(0);

    on_play_clicked();
}
void Local::updatePlaylist()
{
    foreach(QString song, songsList)
    {
        ui->listWidget->addItem(song);
    }
    alignList();
}

void Local::alignList()
{
    for(int i=0;i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
    }
}

void Local::on_play_clicked()
{
    if(player->playlist()!=playlist)
        player->setPlaylist(playlist);
    if(player->state()!=QMediaPlayer::PlayingState)
        player->play();

    ui->listWidget->setCurrentRow(playlist->currentIndex());
}

void Local::on_pause_clicked()
{
    if(player->state()==QMediaPlayer::PlayingState)
        player->pause();
}

void Local::on_next_clicked()
{
    int index=(playlist->currentIndex()+1)%playlist->mediaCount();

    int currTemp=playlist->currentIndex();

    if(shuffleActivated)
    {
        do{
            index=rand()%playlist->mediaCount();
        }while(index== currTemp);
    }


    playlist->setCurrentIndex(index);
    ui->listWidget->setCurrentRow(playlist->currentIndex());
}

void Local::on_prev_clicked()
{
    int index=(playlist->mediaCount()+playlist->currentIndex()-1)%playlist->mediaCount();
    int currTemp=playlist->currentIndex();

    if(shuffleActivated)
    {
        do{
            index=rand()%playlist->mediaCount();
        }while(index== currTemp);
    }

    playlist->setCurrentIndex(index);
    ui->listWidget->setCurrentRow(playlist->currentIndex());
}

void Local::on_loop_clicked()
{
    QIcon *ico = new QIcon();

    QString loopOne,loopAll,noLoop;
    loopOne="://Icones/repeat_one_48px.png";
    loopAll="://Icones/return_48px.png";
    noLoop="://Icones/repeat_48px.png";

    QString currentIco=ui->loop->icon().themeName();

    if(currentIco==loopAll)
        currentIco=loopOne;
    else if(currentIco==loopOne)
        currentIco=noLoop;
    else
        currentIco=loopAll;

    ico->addPixmap(QPixmap(currentIco));
    ico->setThemeName(currentIco);
    ui->loop->setIcon(*ico);
}

void Local::on_pushButtstopon_8_clicked()
{
    if(player->state()!=QMediaPlayer::StoppedState)
        player->stop();
}

void Local::on_rand_clicked()
{
    shuffleActivated=!shuffleActivated;
    if(shuffleActivated)
        ui->rand->setStyleSheet(ui->rand->styleSheet()+"QPushButton{border : 2px solid deepskyblue; padding :5px}");
    else
        ui->rand->setStyleSheet(ui->rand->styleSheet().split("QPushButton{border : 2px solid deepskyblue; padding :5px}")[0]);
}
void Local::changePos(qint64 pos)
{
    if(player->duration()<=0 || isSliding)
        return;

    ui->horizontalSlider->setValue(pos*100/player->duration());
    if(pos>=player->duration()/2)
    {
        changeOnce=true;
    }
}

void Local::on_listWidget_clicked(const QModelIndex &index)
{
    playlist->setCurrentIndex(index.row());
}

void Local::on_horizontalSlider_valueChanged(int value)
{
}

void Local::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position*player->duration()/100);
}

void Local::on_horizontalSlider_sliderPressed()
{
    isSliding=true;
}

void Local::on_horizontalSlider_sliderReleased()
{
    isSliding=false;
}
void Local::updateCurrentSong(int i)
{
    if(i<0)
    {
        playlist->setCurrentIndex(0);
        ui->listWidget->setCurrentRow(0);
        return;
    }
    int index;
    if(shuffleActivated&&changeOnce)
    {
        index=rand()%playlist->mediaCount();
        playlist->setCurrentIndex(index);
        ui->listWidget->setCurrentRow(index);
        changeOnce=false;
        return;
    }


    if(ui->listWidget->currentRow()!=i)
        ui->listWidget->setCurrentRow(i);
}
