#ifndef TITTLEPAGE_H
#define TITTLEPAGE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QFont>

class TittlePage : public QWidget
{
    Q_OBJECT

public:
    explicit TittlePage(QWidget *parent = nullptr);
    ~TittlePage();

signals:
    void changePage(int index);

private:
    QLabel * tittle;
    QPushButton * to_LevelSelect;
    QPushButton * to_CreditsPage;
    QPushButton * to_SettingsPage;
    QPushButton * to_TutorialPage;
    QPushButton * to_ExitGame;
};

#endif
