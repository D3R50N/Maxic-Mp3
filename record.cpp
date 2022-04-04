#include "record.h"
#include "ui_record.h"



Record::Record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);

    recorder=new QAudioRecorder(this);
    connect(recorder,SIGNAL(stateChanged(QMediaRecorder::State)),this,SLOT(isRec(QMediaRecorder::State)) );

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(blink()));

    ui->text->setText(tr("<b style='color : grey'>Aucun enregistrement</b>"));
    m1=0;
    m2=0;
    s1=0;
    s2=0;
    counter=0;
}

Record::~Record()
{
    delete ui;
}

void Record::on_pushButton_clicked()
{
    if(recorder->state()==QAudioRecorder::RecordingState)
    {
        recorder->stop();
        return;
    }
    QDir dir;
    QString folder="Enregistrements/";
    if(!dir.exists(folder))
        dir.mkpath(folder);

    dir.setPath(folder);

    int count= dir.count()-2;
    QFileDialog *dialog=new QFileDialog(this);
    currentFileName="maxicRecord"+QString::number(count+1);

    QString filter=tr("Fichier wav(*.wav);; Fichier mp3 (*.mp3);; AMR (*.amr)");
    QString path=dialog->getSaveFileName(0,"Enregistrer sous ?",folder+currentFileName,filter);

    ext=path.split(".")[path.split(".").length()-1];

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/"+ext);
    audioSettings.setQuality(QMultimedia::HighQuality);

    recorder->setEncodingSettings(audioSettings);
    recorder->setOutputLocation(QUrl::fromLocalFile(path));
    timer->start(tictac);
    recorder->record();



}
void Record::isRec(QMediaRecorder::State state)
{
    if(state==QMediaRecorder::RecordingState)
    {
        ui->pushButton->setText("Arrêter");
        ui->text->setText(tr("Enregistrement de <i style='color : rgb(255, 175, 37)'>")+currentFileName+"."+ext+tr("</i><br><br> Périphérique d'entrée détecté : <span style='color:lightgreen'>")+recorder->audioInput()+tr("<span>"));
    }
    else
    {
        ui->pushButton->setText("Enregistrer");
        ui->text->setText(tr("<b style='color : grey'>Aucun enregistrement</b>"));
        m1=0;
        m2=0;
        s1=0;
        s2=0;
        ui->time->setText(QString::number(m1)+QString::number(m2)+":"+QString::number(s1)+QString::number(s2));
        timer->stop();
        ui->label->setVisible(!ui->label->isVisible());
    }

}
void Record::blink()
{
    ui->label->setVisible(!ui->label->isVisible());
    counter++;
    ui->time->setText(QString::number(m1)+QString::number(m2)+":"+QString::number(s1)+QString::number(s2));
    if(counter>1000/tictac)
    {
        s2++;
        counter=0;
    }
    if(s2>9)
    {
        s1++;
        s2=0;
    }
    if(s1>5)
    {
        m2++;
        s1=0;
    }
    if(m2>9)
    {
        m1++;
        m2=0;
    }

}
