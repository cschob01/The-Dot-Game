#ifndef DOTFIELD_H
#define DOTFIELD_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QtMath>
#include <utility>
#include <QElapsedTimer>

#include <QPainter>
#include <QPaintEvent>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QScrollArea>
#include <QScrollBar>

#include "music.h"
#include "settings.h"
#include "status.h"

#include "map.h"
#include "map1.h"
#include "maps/mapsorter.h"

class DotField : public QWidget
{
    Q_OBJECT

public:
    explicit DotField(QWidget *parent = nullptr);
    ~DotField();

    void startLevel(std::pair<int, int> level, Settings settings);

signals:
    void exitingLevel(bool win);

private slots:
    void update();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:

    QLabel * you_lose;
    QLabel * you_win;
    QLabel * loading;
    QLabel * forced_settings;
    QVBoxLayout * layout;

    //Managing visible map
    static const int MAP_VISIBILITY_H = 300;
    static const int MAP_VISIBILITY_V = 300;
    QScrollArea* scrollArea;
    bool held_m;

    Music music;

    //Game management
    Settings settings;
    Status status;

    //External settings
    static const int MPF = 50;
    static constexpr double SPEED = 0.35;
    static constexpr double SPRINT_MULTIPLIER = 2;

    //Player/map state
    int max_vertical_look; //dependent setting
    Map * map;
    bool map_in_motion;
    bool end_called;
    QPointF pos;
    double angleV;
    double angleH;
    bool ** animation;

    //Game ticks
    QTimer *timer;

    //helpers
    void fadeOutWidget(QWidget *widget, int durationMs);
    void fadeInWidget(QWidget *widget, int durationMs);
    void endLevel(bool win);
    void setTimer(bool active);
    void moveThere(double step, double angle);
    void paintPixel(QPainter* painter, int i, int j, std::tuple<double, QString, std::vector<std::pair<double, QColor>>> dist);
    void setMapSettingsMusic(std::pair<int, int> level, Settings settings);

    //Adjusting display to mainWindow
    double maxSize_h;
    double maxSize_v;
    static const int BORDER_SPACE = 30;

    //Teleportation:
    bool teleported;

};

#endif
