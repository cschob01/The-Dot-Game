#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <utility>
#include <QWidget>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <stdexcept>
#include <QGraphicsOpacityEffect>

#include "levelmap.h"

class LevelSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();

    LevelMap getLevelMap();
    
    void setup(LevelMap levelMap);
    void levelCompleted(std::pair<int, int> level);

signals:
    void changePage(int index);
    void startLevel(std::pair<int, int> level);

private:
    LevelMap levelMap;
    QPushButton* to[5][5];
    QPushButton* finalLevel;

    //Helpers
    void updateLevels();
};

#endif
