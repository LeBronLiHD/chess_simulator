#include "Qml_Connection.h"

/*****************************************************************
*   File:     Qml_Connection.cpp
*   Author:   Haodong LI
*   Usage:    TheUsageOfFile
*   Time:     2021-05-31 -> 20:29:48
*****************************************************************/

Qml_Connection::Qml_Connection()
{

}

void Qml_Connection::changeChessPos(int chessName, int number, bool camp, SGeoPoint *Pos) {
    // number already contain the infomation of camp
    QString name = GlobalEnvirIn::Instance()->__int2QStrName(chessName) + QString::number(number);
    if(name.isEmpty()) {
        qDebug() << "ERROR! Qml_Connection.cpp changeChessPos() line: 17";
        return;
    }
    object->setProperty((name + QString("_posX")).toLatin1(), coordinateIn::Instance()->tranRealPosX(Pos->getPosX()));
    object->setProperty((name + QString("_posY")).toLatin1(), coordinateIn::Instance()->tranRealPosY(Pos->getPosY()));
}

void Qml_Connection::changeChessPos(QString chessName, int number, bool camp, SGeoPoint *Pos) {
    int chessNameInt = GlobalEnvirIn::Instance()->__QStr2intName(chessName);
    if(chessNameInt == -1) {
        qDebug() << "ERROR! Qml_Connection.cpp changeChessPos() line: 27";
        return;
    }
    changeChessPos(chessNameInt, number, camp, Pos); // call other function
}

void Qml_Connection::changeChessPos(int chessName, int number, bool camp, int deltaX, int deltaY) { //TODO
    QString name = GlobalEnvirIn::Instance()->__int2QStrName(chessName) + QString::number(number);
    if(name.isEmpty()) {
        qDebug() << "ERROR! Qml_Connection.cpp changeChessPos() line: 36";
        return;
    }
}

void Qml_Connection::changeChessPos(QString chessName, int number, bool camp, int deltaX, int deltaY) {
    int chessNameInt = GlobalEnvirIn::Instance()->__QStr2intName(chessName);
    if(chessNameInt == -1) {
        qDebug() << "ERROR! Qml_Connection.cpp changeChessPos() line: 44";
        return;
    }
    changeChessPos(chessNameInt, number, camp, deltaX ,deltaY); // call other function
}
