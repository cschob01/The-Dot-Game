#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QLabel>

class TutorialPage : public QWidget
{
    Q_OBJECT

public:
    explicit TutorialPage(QWidget *parent = nullptr);
    ~TutorialPage();

signals:
    void changePage(int index);

private:
    QPushButton * to_TittlePage;
};

#endif
