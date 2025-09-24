#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <QVector>
#include <QWidget>
#include <QPointF>
#include <utility>
#include <QtMath>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QVector2D>
#include <bitset>

class LevelMap
{
public:
    LevelMap();
    ~LevelMap();

    int static const STAGES = 5;
    int static const LPS = 5;

    void levelCompleted(std::pair<int, int> level);
    bool isUnlocked(std::pair<int, int> level);
    bool isCompleted(std::pair<int, int> level);

    std::pair<QString, QString> binaryForm();
    void setLevelMap(QString binary1, QString binary2, bool f_unlo, bool f_comp);

private:

    bool unlocked[STAGES][LPS];
    bool completed[STAGES][LPS];
    bool finalUnlocked;
    bool finalCompleted;

    void updateFinalLevel();
    
};

#endif
