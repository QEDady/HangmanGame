#ifndef CHOOSESTRING_H
#define CHOOSESTRING_H
#include<QString>
#include<QVector>
#include<QFile>
#include<QTextStream>



class ChooseString
{
public:
    ChooseString();

    //retrurns a randomly picked string
    QString getString();


private:
    QVector<QString> strings;
};

#endif // CHOOSESTRING_H
