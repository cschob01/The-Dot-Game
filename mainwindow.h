#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include <utility>

#include <QTimer>

#include "tittlepage.h"
#include "tutorialpage.h"
#include "creditspage.h"
#include "levelselect.h"
#include "settingspage.h"
#include "dotfield.h"
#include "settings.h"
#include "savegame.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPageChange(int index);
    void onStartLevel(std::pair<int, int> level);
    void onExitingLevel(bool win);

protected:
    void closeEvent(QCloseEvent *event) override;

private:

    QStackedWidget *stackedWidget;

    TittlePage * tittlePage;
    TutorialPage * tutorialPage;
    CreditsPage * creditsPage;
    LevelSelect * levelSelect;
    SettingsPage * settingsPage;
    DotField * dotField;

    SaveGame saveGame;

    std::pair<int, int> currentLevel;


};

#endif
