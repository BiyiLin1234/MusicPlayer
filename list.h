#ifndef LIST_H
#define LIST_H

#include <QWidget>

namespace Ui {
class list;
}

class list : public QWidget
{
    Q_OBJECT

public:
    explicit list(QWidget *parent = 0);
    ~list();

private:
    Ui::list *ui;
};

#endif // LIST_H
