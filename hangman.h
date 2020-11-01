#ifndef HANGMAN_H
#define HANGMAN_H
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPainter>
#include <QString>
#include <QGraphicsLineItem>
#include<QKeyEvent>
#include<QGraphicsTextItem>
#include<QFont>
#include<QMap>

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Hangman; }
QT_END_NAMESPACE

class Hangman : public QMainWindow
{
    Q_OBJECT

public:
    Hangman(QWidget *parent = nullptr);
    ~Hangman();
    //check if the given letter is correct or not. If correct, it prints it.
    bool checkletter();
    //Proces works if the letter is not correct, then it makes the next part of the HangMan apper
   void process(bool correctletter);

   //show the final result
   void winOrLose();

private:
    Ui::Hangman *ui;
    QGraphicsScene *scene;
    QGraphicsScene *finishscene;

    QGraphicsEllipseItem *ellipse;

    QString given;
    QString chosen;

    QMediaPlayer* backgroundmusic;
    QGraphicsTextItem* worditem;


    QPen pen;

    QFont* font;
    QFont* bigfont;


    QMap<QChar, QVector<int>> charactars;

    //integer to help us show different parts of the body
    int count;
    //boolean array to track the letters
    bool *successful;
    //bool to indicatr if the program ended
    bool programended;

private slots:
    //takes the given letter
    void keyPressEvent(QKeyEvent *event); //override()


};
#endif // HANGMAN_H
