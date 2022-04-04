#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "all.h"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private:
    Ui::Home *ui;
};

#endif // HOME_H
