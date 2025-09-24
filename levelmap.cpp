
#include "levelmap.h"

LevelMap::LevelMap(){

    for(int i = 0; i < STAGES; i++){
        for(int j = 0; j < LPS; j++){
            unlocked[i][j] = false;
        }
    }
    unlocked[0][0] = true;
    finalCompleted = false;
    finalUnlocked = false;

}

LevelMap::~LevelMap(){

}

void LevelMap::levelCompleted(std::pair<int, int> level){
    if(level.first == 5){
        finalCompleted = true;
        qDebug() << "GAME COMPLETED";
    }
    else{
        completed[level.first][level.second] = true;
        if(level.second != LPS - 1){
            unlocked[level.first][level.second + 1] = true;
        }
        if((level.second == 2) && (level.first != STAGES - 1)){
            unlocked[level.first + 1][0] = true;
        }
    }
    updateFinalLevel();
}

void LevelMap::updateFinalLevel(){

    for(int i = 0; i < STAGES; i++){
        for(int j = 0; j < LPS; j++){
            if(!completed[i][j]){
                return;
            }
        }
    }
    finalUnlocked = true;

}

bool LevelMap::isUnlocked(std::pair<int, int> level){
    if(level.first == 5){
        return finalUnlocked;
    }
    return unlocked[level.first][level.second];
}

bool LevelMap::isCompleted(std::pair<int, int> level){
    if(level.first == 5){
        return finalCompleted;
    }
    return completed[level.first][level.second];
}

std::pair<QString, QString> LevelMap::binaryForm(){
    QString binary1;
    QString binary2;
    for(int i = 0; i < STAGES; i++){
        for(int j = 0; j < LPS; j++){
            binary1 = binary1 + "0";
            binary2 = binary2 + "0";
        }
    }
    for(int i = 0; i < STAGES; i++){
        for(int j = 0; j < LPS; j++){
            binary1[i * 5 + j] = static_cast<char>(unlocked[i][j]);
            binary2[i * 5 + j] = static_cast<char>(completed[i][j]);
        }
    }
    return std::make_pair(binary1, binary2);
}

void LevelMap::setLevelMap(QString binary1, QString binary2, bool f_unlo, bool f_comp){
    for(int i = 0; i < STAGES; i++){
        for(int j = 0; j < LPS; j++){
            if(binary1[i * 5 + j] == QChar(0x0000)) unlocked[i][j] = 0;
            if(binary1[i * 5 + j] == QChar(0x0001)) unlocked[i][j] = 1;
            if(binary2[i * 5 + j] == QChar(0x0000)) completed[i][j] = 0;
            if(binary2[i * 5 + j] == QChar(0x0001)) completed[i][j] = 1;
        }
    }
    unlocked[0][0] = 1;
    finalCompleted = f_comp;
    finalUnlocked = f_unlo;
}
