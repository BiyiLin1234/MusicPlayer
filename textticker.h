#ifndef TEXTTICKER_H
#define TEXTTICKER_H

#include <QLabel>
class TextTicker : public QLabel
{
    Q_OBJECT
public:
    TextTicker(QWidget* parent);
    void showScrollText(QString text);
    void changeLabelState();
private:
    int stepWidth;
    int stepTime;
    int curIndex;
    QString showText;
    QTimer *scrollTimer;

private slots:
    void updateIndex();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // TEXTTICKER_H
