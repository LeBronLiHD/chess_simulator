#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QDeclarativeEngine>
//#include <QDeclarativeView>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlProperty>
#include <QQuickView>
#include <QWidget>
#include <QList>
#include <QDebug>
#include <iostream>
#include <QTimer>

#include "coordinate.h"
#include "SGeoPoint.h"
#include "Qml_Connection.h"
#include "global.h"
#include "Test/TestChessMove.h"

#include "Step.h"
#include "singleGame.h"
#include "Navigation.h"

#include <vision_thread.h>

#include <QFontDatabase>
#include <QFont>
#include <QMessageBox>
#include <QtGui>
//#include <QtSingleApplication>

QObject* object;
vision_thread *vision = NULL;           // USB Camera
int ** Main_chessBoard = NULL;          // Chess Board
bool __curTurn;                         // true for red and false for black
static const int CHESS_PLAY_MODE = Menu::Mode::Human_Human;
static const int BACKGROUND_MODE = Menu::Background::ChristmasTree;
int STRATEGY_MODE = Menu::Manual::inValidHaHa;
int SEARCH_DEPTH = PARAM::START_DEPTH;  // init search depth of alpha-beta purning
static const bool TEST_MODE = false;    // is Test Mode or not
static const bool START_GUI = true;     // show the init ui or not
bool Is_CIMC_EndGame = CHESS_PLAY_MODE == Menu::Mode::Human_AI_CIMC_EndGame;
void LetUsPlayChess();

int main(int argc, char *argv[]) {

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml_files/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QList<QObject*> objList = engine.rootObjects();
    std::cout << "objList.length() = " << objList.length() << std::endl; // 1: only main.qml
    vision = new vision_thread;
    vision->name = "vision";
    vision->start();
    // PythonMudule *python_vision = new PythonMudule("vision");
    // python_vision->start(QThread::HighPriority);

    QObject *objectTemp(0); // initialization
    if(!objList.empty()) objectTemp = *objList.begin();
    else qDebug() << "object list is empty!";
    object = objectTemp->findChild<QObject*>("field_root");
    if(object) std::cout << "field_root loaded successfully!" << std::endl;
    else qDebug() << "field_root loading failed!";
    GlobalEnvirIn::Instance()->__refreshBoard();

    LetUsPlayChess(); // real play API
    return app.exec();
}

/* * * * * * * * * * * * * * * * * * * * *
*   File:     main.cpp
*   Author:   Haodong LI
*   Usage:    UsageOfFile
*   Time:     2021-06-05
* * * * * * * * * * * * * * * * * * * * * */

void LetUsPlayChess() {
    if(BACKGROUND_MODE == 0) {
        object->setProperty(QString("isBackgroundSet").toLatin1(), false);
    }
    else {
        object->setProperty(QString("isBackgroundSet").toLatin1(), true);
        object->setProperty(QString("background_source").toLatin1(), Menu::BackgroundUrl.at(BACKGROUND_MODE).toLatin1());
    }
    if(TEST_MODE)
        TestChessMoveIn::Instance()->testMultiProcess();
    else
        switch (CHESS_PLAY_MODE) {
        case 0: singleGameIn::Instance()->normalPlay(PARAM::NINE_NINE_NINE); break;
        case 1: singleGameIn::Instance()->normalPlay_HumanVSAI(PARAM::NINE_NINE_NINE); break;
        case 2: singleGameIn::Instance()->normalPlay_HumanVSHuman(PARAM::NINE_NINE_NINE); break;
        case 3: singleGameIn::Instance()->normalPlay_HumanVSAI_CIMC(PARAM::NINE_NINE_NINE); break;
        case 4: singleGameIn::Instance()->normalPlay_HumanVSAI_CIMC_EndGame(PARAM::NINE_NINE_NINE); break;
        case 5: singleGameIn::Instance()->normalPlay_EndGame(PARAM::NINE_NINE_NINE); break;
        case 6: singleGameIn::Instance()->normalPlay_HumanVSAI_EndGame(PARAM::NINE_NINE_NINE); break;
        case 7: singleGameIn::Instance()->normalPlay_HumanVSHuman_EndGame(PARAM::NINE_NINE_NINE); break;
        default: qDebug() << "main.cpp line:79 CHESS_PLAY_MODE inValid!!! (see Navigation.h)"; break;
        }
}

/*
*  1. global vision   ->
*  2. image process   ->
*  3. chess identify  ->
*  4. matrix generate -> game decision algorithm ->
*  5. chess move      ->
*  6. avg robot move  ->
*  7. (next loop)     -> global vision
*
* board info:
*   _redNum
*   _BlackNum
*
* chess info:
*   _isAlive
*   _col
*   _row
*   _canMove
*   _canMovePos
*   _canKill
*   _canKillWho
*/
