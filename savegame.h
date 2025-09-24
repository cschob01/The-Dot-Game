#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>
#include <utility>
#include <QStandardPaths>
#include <QDir>

#include "settings.h"
#include "levelmap.h"

#ifndef SAVEGAME_H
#define SAVEGAME_H

class SaveGame : public QWidget
{
public:
    SaveGame();
    ~SaveGame();

    QString getSaveFilePath();

    void saveGame(Settings settings, LevelMap levelMap);
    std::pair<Settings, LevelMap> getSaveGame();
};

#endif
