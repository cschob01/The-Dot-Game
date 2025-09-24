#include "tittlepage.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>



TittlePage::TittlePage(QWidget *parent)
    : QWidget(parent)
    , tittle(new QLabel("The Dot Game", this))
    , to_LevelSelect(new QPushButton("Play Game", this))
    , to_CreditsPage(new QPushButton("Credits", this))
    , to_SettingsPage(new QPushButton("Settings", this))
    , to_TutorialPage(new QPushButton("Tutorial", this))
    , to_ExitGame(new QPushButton("Exit Game", this))
{

    QVBoxLayout *layout = new QVBoxLayout(this);

    //Adjusting the tittle
    tittle->setMinimumSize(100, 50);
    QFont font = tittle->font();
    font.setPointSize(80);
    tittle->setFont(font); 
    layout->addWidget(tittle, 0, Qt::AlignCenter);

    //Setting buttons
    layout->addWidget(to_LevelSelect);
    connect(to_LevelSelect, &QPushButton::clicked, this, [this]() {
        emit changePage(1);
    });
    layout->addWidget(to_TutorialPage);
    connect(to_TutorialPage, &QPushButton::clicked, this, [this]() {
        emit changePage(2);
    });
    layout->addWidget(to_SettingsPage);
    connect(to_SettingsPage, &QPushButton::clicked, this, [this]() {
        emit changePage(3);
    });
    layout->addWidget(to_CreditsPage);
    connect(to_CreditsPage, &QPushButton::clicked, this, [this]() {
        emit changePage(4);
    });
    layout->addWidget(to_ExitGame);
    connect(to_ExitGame, &QPushButton::clicked, this, [this]() {
        emit changePage(5);
    });

    setLayout(layout);

}

TittlePage::~TittlePage()
{
}
