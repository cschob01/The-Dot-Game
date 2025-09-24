#include "mainwindow.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , stackedWidget(new QStackedWidget(this))
    , tittlePage(new TittlePage(this))
    , tutorialPage(new TutorialPage(this))
    , creditsPage(new CreditsPage(this))
    , levelSelect(new LevelSelect(this))
    , settingsPage(new SettingsPage(this))
    , dotField(new DotField(this))
{

    this->setMinimumSize(800, 500);

    // Set up the central widget and layout
    QWidget *centralWidget = new QWidget(this);  // Create central widget
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);  // Create a layout
    layout->addWidget(stackedWidget);
    stackedWidget->addWidget(tittlePage);
    stackedWidget->addWidget(creditsPage);
    stackedWidget->addWidget(tutorialPage);
    stackedWidget->addWidget(levelSelect);
    stackedWidget->addWidget(settingsPage);
    stackedWidget->addWidget(dotField);
    stackedWidget->setCurrentWidget(tittlePage);

    connect(tittlePage, &TittlePage::changePage, this, &MainWindow::onPageChange);
    connect(tutorialPage, &TutorialPage::changePage, this, &MainWindow::onPageChange);
    connect(creditsPage, &CreditsPage::changePage, this, &MainWindow::onPageChange);
    connect(settingsPage, &SettingsPage::changePage, this, &MainWindow::onPageChange);
    connect(levelSelect, &LevelSelect::changePage, this, &MainWindow::onPageChange);

    connect(levelSelect, &LevelSelect::startLevel, this, &MainWindow::onStartLevel);

    connect(dotField, &DotField::exitingLevel, this, &MainWindow::onExitingLevel);

    QTimer::singleShot(100, [this]() {
        std::pair<Settings, LevelMap> save = saveGame.getSaveGame();
        settingsPage->setup(save.first);
        levelSelect->setup(save.second);
    });

}

void MainWindow::onStartLevel(std::pair<int, int> level){
    currentLevel = level;
    dotField->startLevel(level, settingsPage->getSettings());
    stackedWidget->setCurrentWidget(dotField);
}

void MainWindow::onPageChange(int index) {
    switch (index) {
        case 0: stackedWidget->setCurrentWidget(tittlePage); break;
        case 1: stackedWidget->setCurrentWidget(levelSelect); break;
        case 2: stackedWidget->setCurrentWidget(tutorialPage); break;
        case 3: stackedWidget->setCurrentWidget(settingsPage); break;
        case 4: stackedWidget->setCurrentWidget(creditsPage); break;
        case 5: close(); break;
    }
}

void MainWindow::onExitingLevel(bool win){
    if(win){
        levelSelect->levelCompleted(currentLevel);
    }
    stackedWidget->setCurrentWidget(levelSelect);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event){
    saveGame.saveGame(settingsPage->getSettings(), levelSelect->getLevelMap());
}
