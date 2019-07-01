#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMouseEvent>
#include <Qtimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnMin_clicked();

    void on_btnClose_clicked();

    void on_btnOpenFile_clicked();

    void on_btnPlay_clicked();

    void on_btnPre_clicked();

    void on_btnNext_clicked();

    void on_btn_playBackMode_clicked();

    void updateSliderPosition(qint64);

    void updateDuration(qint64 duration);
//    void on_sliderPosition_sliderMoved(int position);

    void on_sliderPosition_sliderMoved(int position);

private:
    QMediaPlayer* musicPlayer;
    QMediaPlaylist* musicList;
    void lalala();
    Ui::Widget *ui;
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    QPoint last;
};


#endif // WIDGET_H
