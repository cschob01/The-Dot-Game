#ifndef CREDITSPAGE_H
#define CREDITSPAGE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QLabel>

class CreditsPage : public QWidget
{
    Q_OBJECT

public:
    explicit CreditsPage(QWidget *parent = nullptr);
    ~CreditsPage();

signals:
    void changePage(int index);

private:
    QPushButton * to_TittlePage;
};

#endif
