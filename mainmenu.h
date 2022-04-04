#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QtWidgets>

#include "home.h"
#include "local.h"
#include "record.h"
#include "settings.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_label_clicked();

    void on_local_clicked();

    void on_record_clicked();

    void on_online_clicked();

    void on_settings_clicked();

private:
    Ui::MainMenu *ui;
    QLayout *container;
    QPushButton *currentBtn;
    QString currentBtnStyleSheet;
    QWidget *currentWidget;

    void changeWidget(QWidget *newWidget,QPushButton *curr=0);
    void clearContainer();
    void changeCurrentBtn();
    void autoChangeWidget(QWidget *wdg);

    //Les widgets du menu
    Home *menuHome;
    Local *menuLocal;
    Record *menuRecord;
    Settings *menuSettings;
};

#endif // MAINMENU_H
