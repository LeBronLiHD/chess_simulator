#ifndef QML_CONNECTION_H
#define QML_CONNECTION_H

/*****************************************************************
*   File:     Qml_Connection.h
*   Author:   Haodong LI
*   Usage:    connect with qml file to change the position of chesses,
*             change the position and info of all chess board and update
*   Time:     2021-05-31 -> 13:59:25
*****************************************************************/

//#include "singleton.h"
//#include "Params.h"
#include "global.h"
#include "coordinate.h"

class Qml_Connection
{
public:
    Qml_Connection();
    virtual void changeChessPos(int chessName,     int number, bool camp, SGeoPoint* Pos);
    virtual void changeChessPos(QString chessName, int number, bool camp, SGeoPoint* Pos);
    virtual void changeChessPos(int chessName,     int number, bool camp, int deltaX, int deltaY);
    virtual void changeChessPos(QString chessName, int number, bool camp, int deltaX, int deltaY);

private:
    // static SGeoPoint* pTest;
};

// SGeoPoint* Qml_Connection::pTest = new SGeoPoint(0, 0);

typedef NormalSingleton< Qml_Connection > QmlConnectIn;

#endif // QML_CONNECTION_H
