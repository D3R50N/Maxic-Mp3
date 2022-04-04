#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include "QAudioRecorder"
#include "QUrl"
#include "QDir"
#include "QFileDialog"
#include "QTimer"

namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = 0);
    ~Record();

private slots:
    void on_pushButton_clicked();
    void isRec(QMediaRecorder::State state);
    void blink();

private:
    Ui::Record *ui;
    QAudioRecorder *recorder;
    QString currentFileName;
    QString ext;
    QTimer *timer;

    int m1,m2,s1,s2,counter,tictac=250;
};

#endif // RECORD_H
