#include "hangman.h"
#include "ui_hangman.h"
#include <QGraphicsLineItem>
#include <qpainter.h>
#include "choosestring.h"

#include <QGraphicsTextItem>
Hangman::Hangman(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hangman)
{

    given="";
    count=1;
    programended=false;

    ui->setupUi(this);
    scene= new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    scene->setSceneRect(-400,-400,600,600);

    QLineF TopLine (scene->sceneRect().topLeft(),scene->sceneRect().topRight());
    QLineF LeftLine (scene->sceneRect().topLeft(),scene->sceneRect().bottomLeft());
    QLineF BottomLine (scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());
    QLineF RightLine (scene->sceneRect().topRight(),scene->sceneRect().bottomRight());

   pen.setColor("black");

    scene->addLine(TopLine,pen);
    scene->addLine(LeftLine,pen);
    scene->addLine(BottomLine,pen);
    scene->addLine(RightLine,pen);



    pen.setWidth(10);

    scene->addLine(-300,-300,-300,100,pen);//long vertical line
    scene->addLine(-350,100,-250,100,pen);//bottom line
    scene->addLine(-300,-300,-150,-300,pen);//top line
    scene->addLine(-150,-300,-150,-225,pen);//short vertical line



    // font type, size, and bold
   font = new QFont("Times", 15, QFont::Bold);
   bigfont= new QFont("Times", 50, QFont::Bold);



    worditem=new QGraphicsTextItem();
    worditem->setFont(*font);
    worditem->setPlainText("press a letter");
    worditem->setPos(-10,-100);
    scene->addItem(worditem);



    backgroundmusic= new QMediaPlayer;
    connect(backgroundmusic, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

    backgroundmusic->setMedia(QUrl::fromLocalFile("Y:/projects/HangmanGame/HangManGame/backgroundmusic.mp3"));
    backgroundmusic->play();




    //choosing a string and working with it
    ChooseString x;

    chosen=x.getString();
   //Setting all bools with false
    successful=new bool[chosen.size()];
      for(int i =0; i < chosen.size() ;i++)
           successful[i] = false;

      //setting the map of characters with their indices
      for(int i=0;i<chosen.size();i++){
          charactars[chosen.at(i)].append(i);
      }


}

Hangman::~Hangman()
{
    delete ui;
    delete scene;
    delete finishscene;
    delete worditem;

}

void Hangman::keyPressEvent(QKeyEvent *event)
{
    given= event->text();

    // if the program didn't end, we process the given letter
    if(!programended){
        process(checkletter());
        //check if user lost or won
         winOrLose();
    }

}
bool Hangman::checkletter(){


    if(charactars.count(given[0])){
       for(int ind: charactars[given[0]]){
           worditem=new QGraphicsTextItem();
           worditem->setFont(*font);
           worditem->setPlainText(given.toUpper());
           worditem->setPos(20*ind-30,-50);
           scene->addItem(worditem);

           successful[ind]=true;
       }
       return true;

    }

    return false;



}


void Hangman::process(bool CorrectLetter){


    pen.setColor("blue");
    pen.setWidth(5);


    if(!CorrectLetter){

                if(count==1)
                {
                 ellipse=scene->addEllipse(-187.5,-220,75,75,pen); // face
                 count++;
                }
                else if(count==2)
                {
                    scene->addLine(-150,-145,-150,-20,pen); //body
                    count++;
                }
                else if(count==3)
                {
                   scene->addLine(-150,-20,-90,60,pen); //right leg (my right)
                   count++;
                }
                else if(count==4)
                {
                    scene->addLine(-150,-20,-210,60,pen); //left leg (my left)
                    count++;
                }
                else if(count==5)
                {
                   scene->addLine(-150,-90,-90,-140,pen); //right arm (my right)
                   count++;
                }
                else if(count==6)
                {
                    scene->addLine(-150,-90,-210,-140,pen); //left arm (my left)
                    count++;
                }
        }
    }






void Hangman::winOrLose()
{
    bool Allcorrect=true;
        for(int i=0;i<chosen.size();i++)
        {
            if(successful[i] == false)
            {
                Allcorrect = false;
                break;
            }

        }
        if(Allcorrect){
            finishscene= new QGraphicsScene;
            ui->graphicsView->setScene(finishscene);
            worditem->setPlainText("Congratulations, you won!");
            worditem->setPos(-100, 200);
            worditem->setFont(*bigfont);
            finishscene->addItem(worditem);
            programended=true;

        }
        else if(count == 7)
        {

            finishscene= new QGraphicsScene;
            ui->graphicsView->setScene(finishscene);



           worditem->setPlainText("You failed!");
           worditem->setPos(-100, 200);
           worditem->setFont(*bigfont);
            finishscene->addItem(worditem);

              programended=true;

        }


}

