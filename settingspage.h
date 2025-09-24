#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "settings.h"

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();
    Settings getSettings();

    void setup(Settings settings);

signals:
    void changePage(int index);

private:
    QPushButton * to_TittlePage;
    Settings settings;

    QLabel *pov_h_c;
    QLabel *pov_v_c;
    QLabel *col_c;
    QLabel *row_c;
    QLabel *render_c;
    QLabel *sensitivityH_c;
    QLabel *sensitivityV_c;
    QPushButton *roofs_c;

    //helpers
    void updateLabels();

};

#endif
