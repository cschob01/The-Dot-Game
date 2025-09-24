#include "dotfield.h"

DotField::DotField(QWidget *parent)
    : QWidget(parent)
    , timer(new QTimer(this))
    , scrollArea(new QScrollArea(this))
{

    teleported = false;
    setFocusPolicy(Qt::NoFocus);

    scrollArea->setStyleSheet("QScrollArea {"
        "border: 2px solid white;"
        "border-radius: 5px;"
        "padding: 0px;"
        "}");

    loading = new QLabel("Loading...", this);
    loading->setFont(QFont("", 80)); 
    loading->hide();    
    you_lose = new QLabel("You Died", this);
    you_lose->setFont(QFont("", 80)); 
    you_lose->hide();
    you_win = new QLabel("You Survived", this);
    you_win->setFont(QFont("", 80)); 
    you_win->hide();
    forced_settings = new QLabel("", this);
    forced_settings->setFont(QFont("", 10)); 
    forced_settings->hide();

    layout = new QVBoxLayout(this);
    setLayout(layout);

    connect(timer, &QTimer::timeout, this, &DotField::update);
    
}

DotField::~DotField()
{
}

void DotField::setMapSettingsMusic(std::pair<int, int> level, Settings settings){

    if((level.first < 0) || (level.first > 5) || (level.second < 0) || (level.second > 4)){
        throw std::runtime_error("Out-of-index map request");
    }

    delete map;
    map = MapSorter::getMap(level, settings.render);
    map->setParent(this);

    scrollArea->setFixedSize(MAP_VISIBILITY_H, MAP_VISIBILITY_V);
    scrollArea->setWidget(map);
    scrollArea->setWidgetResizable(true);
    scrollArea->hide();

    this->settings = map->forcedSettings(settings);
    // this->settings.height = this->settings.render/10.0;
    max_vertical_look = 85 - settings.sensitivityV - settings.pov_v / 2;

    music.playSong(level.first + 1);

    pos = map->startingCoords();
    angleV = 0;
    angleH = map->startingAngle();
}

void DotField::startLevel(std::pair<int, int> level, Settings settings){
    end_called = false;
    setMapSettingsMusic(level, settings);

    map->startAnimation(settings.columns, settings.rows, music.loadingTime() / 1.333);

    layout->addWidget(loading, 0, Qt::AlignCenter);
    layout->addWidget(forced_settings, 0, Qt::AlignCenter);

    loading->setGraphicsEffect(nullptr);
    forced_settings->setGraphicsEffect(nullptr);
    loading->setText(map->loadingText());
    forced_settings->setText(map->forcedSettingsText());
    loading->setAlignment(Qt::AlignCenter);
    forced_settings->setAlignment(Qt::AlignCenter);
    loading->show();
    forced_settings->show();

    map_in_motion = false;
    setTimer(true);

    QTimer::singleShot(music.loadingTime() / 2, [level, this]() {
        fadeOutWidget(loading, music.loadingTime() / 2);
        fadeOutWidget(forced_settings, music.loadingTime() / 2);
    });
    QTimer::singleShot(music.loadingTime(), [level, this]() {
        layout->removeWidget(loading);
        layout->removeWidget(forced_settings);
        layout->addWidget(scrollArea, 0, Qt::AlignCenter);
        status = Status();
        map_in_motion = true;
        setFocus();
    });

}

void DotField::endLevel(bool win){
    scrollArea->hide();
    end_called = true;
    music.playSong(0);
    clearFocus();
    status = Status();
    layout->removeWidget(map);
    if(win){
        layout->addWidget(you_win, 0, Qt::AlignCenter);
        fadeInWidget(you_win, music.loadingTime() / 2);
        QTimer::singleShot(music.loadingTime(), [this]() {
            layout->removeWidget(you_win);
            you_win->hide();
            map_in_motion = false;
            setTimer(false);
            emit exitingLevel(true);
        });
    }
    else{
        layout->addWidget(you_lose, 0, Qt::AlignCenter);
        fadeInWidget(you_lose, music.loadingTime() / 2);
        QTimer::singleShot(music.loadingTime(), [this]() {
            layout->removeWidget(you_lose);
            you_lose->hide();
            map_in_motion = false;
            setTimer(false);
            emit exitingLevel(false);
        });
    }
}

void DotField::fadeOutWidget(QWidget *widget, int durationMs) {
    auto *effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);

    auto *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(durationMs);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    QObject::connect(animation, &QPropertyAnimation::finished, widget, [widget]() {
        widget->hide();
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DotField::fadeInWidget(QWidget *widget, int durationMs) {
    auto *effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    effect->setOpacity(0.0);

    auto *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(durationMs);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    widget->show();
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
