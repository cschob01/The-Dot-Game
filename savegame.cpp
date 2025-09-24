#include "savegame.h"

QString SaveGame::getSaveFilePath() {
    // Get the writable app data location
    QString saveDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Make sure the directory exists
    QDir().mkpath(saveDir);

    // Return full path to savefile.json
    return saveDir + "/savefile.json";
}

void SaveGame::saveGame(Settings settings, LevelMap levelMap) {

    // Create a JSON object to store the data
    QJsonObject saveData;
    saveData["unlocked"] = levelMap.binaryForm().first;
    saveData["completed"] = levelMap.binaryForm().second;
    saveData["pov_h"] = settings.pov_h;
    saveData["pov_v"] = settings.pov_v;
    saveData["columns"] = settings.columns;
    saveData["rows"] = settings.rows;
    saveData["render"] = settings.render;
    saveData["height"] = settings.height;
    saveData["sensitivityH"] = settings.sensitivityH;
    saveData["sensitivityV"] = settings.sensitivityV;
    saveData["f_unlo"] = levelMap.isUnlocked(std::make_pair(5, 1));
    saveData["f_comp"] = levelMap.isCompleted(std::make_pair(5, 1));

    // Create a JSON document from the object
    QJsonDocument doc(saveData);

    QString path = getSaveFilePath();
    QFile saveFile(path);

    if (saveFile.open(QIODevice::WriteOnly)) {
        saveFile.write(doc.toJson());
        saveFile.close();
        qDebug() << "Game saved at:" << path;
    } else {
        qDebug() << "Failed to save game at:" << path;
    }
}

std::pair<Settings, LevelMap> SaveGame::getSaveGame() {
    
    QString path = getSaveFilePath();
    QFile saveFile(path);

    LevelMap levelMap;
    Settings settings;

    // Check if the file exists and open it
    if (saveFile.exists() && saveFile.open(QIODevice::ReadOnly)) {
        QByteArray saveData = saveFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if (loadDoc.isObject()) {
            QJsonObject saveDataObject = loadDoc.object();
            
            levelMap.setLevelMap(saveDataObject["unlocked"].toString(), saveDataObject["completed"].toString()
                                , saveDataObject["f_unlo"].toBool(), saveDataObject["f_comp"].toBool());
            settings.pov_h = saveDataObject["pov_h"].toInt();
            settings.pov_v = saveDataObject["pov_v"].toInt();
            settings.columns = saveDataObject["columns"].toInt();
            settings.rows = saveDataObject["rows"].toInt();
            settings.render = saveDataObject["render"].toInt();
            settings.height = saveDataObject["height"].toInt();
            settings.sensitivityH = saveDataObject["sensitivityH"].toInt();
            settings.sensitivityV = saveDataObject["sensitivityV"].toInt();

            saveFile.close();
            qDebug() << "Game loaded from:" << path;
        } else {
            qDebug() << "Failed to parse the save file!";
        }
    } else {
        qDebug() << "Save file does not exist. Starting fresh!";
    }

    return std::make_pair(settings, levelMap);

}

SaveGame::SaveGame(){

}

SaveGame::~SaveGame(){

}
