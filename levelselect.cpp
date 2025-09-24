#include "levelselect.h"

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout(this);

    for(int i = 0; i < 5; i++){
        QHBoxLayout *layout1 = new QHBoxLayout();
        QLabel *stage1 = new QLabel("Stage " + QString::number(i + 1) + ":");
        stage1->setAlignment(Qt::AlignCenter);
        layout1->addWidget(stage1);
        for(int j = 0; j < 5; j++){
            to[i][j] = new QPushButton("Level " + QString::number(j + 1));
            to[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(to[i][j], &QPushButton::clicked, this, [this, i, j]() {
                emit startLevel(qMakePair(i, j));
            });
            layout1->addWidget(to[i][j]);
        }
        layout->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
        layout->addLayout(layout1);
    }

    QHBoxLayout *layout2 = new QHBoxLayout();
    finalLevel = new QPushButton("Final Level");
    finalLevel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(finalLevel, &QPushButton::clicked, this, [this]() {
        emit startLevel(qMakePair(5, 0));
    });
    layout2->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout2->addWidget(finalLevel);
    layout2->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addLayout(layout2);
    
    layout->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    QPushButton * to_TittlePage = new QPushButton("Back");
    connect(to_TittlePage, &QPushButton::clicked, this, [this]() {
        emit changePage(0);
    });
    layout->addWidget(to_TittlePage);
}

LevelSelect::~LevelSelect()
{
}

LevelMap LevelSelect::getLevelMap(){
    return levelMap;
}

void LevelSelect::setup(LevelMap levelMap){
    this->levelMap = levelMap;
    updateLevels();
}

void LevelSelect::updateLevels(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(levelMap.isUnlocked(qMakePair(i, j))){
                QGraphicsOpacityEffect* existingEffect = qobject_cast<QGraphicsOpacityEffect*>(to[i][j]->graphicsEffect());
                if (existingEffect) {
                    delete existingEffect;
                }
                QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(to[i][j]);
                to[i][j]->setGraphicsEffect(opacityEffect);
                opacityEffect->setOpacity(qreal(1));
                to[i][j]->setEnabled(true);
            }
            else{
                QGraphicsOpacityEffect* existingEffect = qobject_cast<QGraphicsOpacityEffect*>(to[i][j]->graphicsEffect());
                if (existingEffect) {
                    delete existingEffect;
                }
                QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(to[i][j]);
                to[i][j]->setGraphicsEffect(opacityEffect);
                opacityEffect->setOpacity(qreal(.5));
                to[i][j]->setEnabled(false);
            }

            if (levelMap.isCompleted(qMakePair(i, j))) {
                to[i][j]->setStyleSheet("background-color: #88cc88;");
            } else {
                to[i][j]->setStyleSheet("background-color: grey; color: white;");
            }
        }
    }

    if(levelMap.isUnlocked(qMakePair(5, 0))){
        QGraphicsOpacityEffect* existingEffect = qobject_cast<QGraphicsOpacityEffect*>(finalLevel->graphicsEffect());
        if (existingEffect) {
            delete existingEffect;
        }
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(finalLevel);
        finalLevel->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(qreal(1));
        finalLevel->setEnabled(true);
    }
    else{
        QGraphicsOpacityEffect* existingEffect = qobject_cast<QGraphicsOpacityEffect*>(finalLevel->graphicsEffect());
        if (existingEffect) {
            delete existingEffect;
        }
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(finalLevel);
        finalLevel->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(qreal(.5));
        finalLevel->setEnabled(false);
    }

    if (levelMap.isCompleted(qMakePair(5, 0))) {
        finalLevel->setStyleSheet("background-color: #88cc88;");
    } else {
        finalLevel->setStyleSheet("background-color: grey; color: white;");
    }

}

void LevelSelect::levelCompleted(std::pair<int, int> level){
    levelMap.levelCompleted(level);
    updateLevels();
}
