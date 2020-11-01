#include "choosestring.h"

ChooseString::ChooseString()
{
    //stringsinput is a file that contain the data base of strings
    QFile file("stringsinput.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    //reading strings from the file to the vector
    QString s;
    while(!stream.atEnd()){
        stream>>s;
        strings.append(s);
    }

}

QString ChooseString::getString()
{
    //picking a random string from the vector
    srand(time(NULL));
    int index=rand() % strings.size();
    return strings[index];

}
