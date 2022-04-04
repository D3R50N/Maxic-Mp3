#ifndef LOCAL_H
#define LOCAL_H

#include <QWidget>
#include "all.h"

namespace Ui {
class Local;
}

class Local : public QWidget
{
    Q_OBJECT

public:
    explicit Local(QWidget *parent = 0);
    ~Local();

private slots:
    void on_pushButton_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_next_clicked();

    void on_prev_clicked();

    void on_loop_clicked();

    void on_pushButtstopon_8_clicked();

    void on_rand_clicked();

    void changePos(qint64 pos);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_sliderReleased();

   void updateCurrentSong(int i);

private:
    Ui::Local *ui;
    QStringList filesList,songsList;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    bool isSliding;
    bool shuffleActivated;
    bool changeOnce;

    void updatePlaylist();
    void alignList();

};

#endif // LOCAL_H
