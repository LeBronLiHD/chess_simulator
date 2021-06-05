#include "General.h"

General::General(int x, int y, QString name, bool camp, int number, bool isAlive):
    Chess(x, y, name, camp, number, isAlive)
{

}

double General::space_value() {
    if(!isAlive()) return 0;
    return 1.0; // is alive, return 100%
}

bool General::canChessMove() {
    bool retMove;
    if(GlobalEnvirIn::Instance()->__isOtherChessAround(GlobalEnvirIn::Instance()->__QStr2intName(GlobalEnvirIn::Instance()->__QString2SimpleName(chessName())),
                                                       chessNumber())) retMove = false;
    else retMove = true;
    return retMove;
}

void General::generateMove() {

}
