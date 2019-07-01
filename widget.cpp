#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMediaMetaData>
#include <QMessageBox>
#include <QListWidget>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //去除标题
    this->setWindowFlags(Qt::FramelessWindowHint);
    //实例化指针
    musicPlayer = new QMediaPlayer(this);
    musicList = new QMediaPlaylist(this);
    musicPlayer->setPlaylist(musicList);
    //loop play
    musicList->setPlaybackMode(QMediaPlaylist::Loop);
//    this->set

//    connect(musicPlayer, QOverload<>::of(&QMediaObject::metaDataChanged),
    connect(musicPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(musicPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(updateSliderPosition(qint64)));
    connect(musicPlayer, QOverload<>::of(&QMediaObject::metaDataChanged),
         this, [=](){
        QString song=musicPlayer->metaData("Title").toString();
        QString singer=musicPlayer->metaData("Author").toString();
        QString album=musicPlayer->metaData("AlbumTitle").toString();
//            ui->label_1->setText((song.isEmpty()?"":song) + (singer.isEmpty()?"":("-"+singer)) + (album.isEmpty()?"":("-"+album))); /* ... */
        ui->label_1->showScrollText((song.isEmpty()?"":song) + (singer.isEmpty()?"":("-"+singer)) + (album.isEmpty()?"":("-"+album)));
        qDebug() <<(song.isEmpty()?"":song) + (singer.isEmpty()?"":("-"+singer)) + (album.isEmpty()?"":("-"+album));
        QFont ft;
        ft.setPointSize(29);
        ui->label_1->setFont(ft);
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnMin_clicked()
{
    this->showMinimized();
}

void Widget::on_btnClose_clicked()
{
    close();
    exit(0);
}

void Widget::on_btnOpenFile_clicked()
{
    static QString path = "C:/";//打开的时候默认路径
    QStringList fileList_new = QFileDialog::getOpenFileNames(this,"choose musics",path,QString("mp3,wma(*.mp3 *.wma)"));
    if(fileList_new.isEmpty()){
        return;
    }
    else{
        foreach (QString filename, fileList_new) {
            QMediaContent media = QMediaContent(QUrl::fromLocalFile(filename));
            this->musicList->addMedia(media);
        }
        QMessageBox::information(this,"tip","添加成功");
    }
    //musicList = fileList_new + musicList;
}

void Widget::on_btnPlay_clicked()
{
    if(musicList->isEmpty()){
        on_btnOpenFile_clicked();
    }
    else if(musicPlayer->state() == QMediaPlayer::PlayingState){
        musicPlayer->pause();
        ui->btnPlay->setStyleSheet("image: url(:/image/zangting.png)");
    }
    else {
        musicPlayer->play();
        ui->btnPlay->setStyleSheet("image: url(:/image/zt13.png)");
    }
    ui->label_1->changeLabelState();
}

void Widget::on_btnPre_clicked()
{
    if(musicList->isEmpty()){
        return;
    }
    else {
        musicPlayer->playlist()->previous();
    }
}

void Widget::on_btnNext_clicked()
{
    if(musicList->isEmpty()){
        return;
    }
    else {
        musicPlayer->playlist()->next();
    }
}


void Widget::mousePressEvent(QMouseEvent* ev){
    last = ev->globalPos();;;
}

void Widget::mouseMoveEvent(QMouseEvent* ev){

    move(x()+ev->globalX() - last.x(), y()+ev->globalY() - last.y());
    last = ev->globalPos();

}

void Widget::mouseReleaseEvent(QMouseEvent*){

}


void Widget::on_btn_playBackMode_clicked()
{
    if(musicList->playbackMode() == QMediaPlaylist::Loop){
        musicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//单曲循环
        ui->btn_playBackMode->setStyleSheet("image: url(:/image/image/loop-one.png)");
    }
    else{
        musicList->setPlaybackMode(QMediaPlaylist::Loop);
        ui->btn_playBackMode->setStyleSheet("image: url(:/image/image/loop-list.png)");
    }
}

void Widget::updateSliderPosition(qint64 position)
{
    ui->sliderPosition->setValue(position);
}

void Widget::updateDuration(qint64 duration){
    ui->sliderPosition->setRange(0,duration);
    ui->sliderPosition->setEnabled(duration>0);
    ui->sliderPosition->setPageStep(duration/10);
}

//void Widget::on_sliderPosition_sliderMoved(int position)
//{
//        ui->sliderPosition->setValue(position);
//}

void Widget::on_sliderPosition_sliderMoved(int position)
{
    musicPlayer->setPosition(position);
}
