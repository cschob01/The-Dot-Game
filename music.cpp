#include "music.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>
#include <QObject>

Music::Music(QObject* parent)
    : QObject(parent)
    , player(new QMediaPlayer())      // Instantiate QMediaPlayer
    , audioOutput(new QAudioOutput()) // Instantiate QAudioOutput
    , fadeTimer(new QTimer())
{

    // Set QAudioOutput as the audio output for QMediaPlayer
    player->setAudioOutput(audioOutput);
    songs = {  QUrl("qrc:/resources/music/DotGame_BaseLine.mp3")   // Home
             , QUrl("qrc:/resources/music/DotGame_MeG+Meg.mp3")    // stage 1
             , QUrl("qrc:/resources/music/DotGame_Fai+Fri.mp3")    // stage 2
             , QUrl("qrc:/resources/music/DotGame_16T+Roc.mp3")    // stage 3
             , QUrl("qrc:/resources/music/DotGame_Ist+Jun.mp3")    // stage 4
             , QUrl("qrc:/resources/music/DotGame_Hit+Koo.mp3")    // stage 5
             , QUrl("qrc:/resources/music/DotGame_Son+Pir.mp3")    // secret Level
    };
    
    audioOutput->setVolume(0.0);
    player->setSource(songs[0]);
    fadeIn(1000);
    player->play();
    currentSong = 0;

    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            player->setPosition(0); // Go back to the beginning
            player->play();         // Start again
        }
    });

}

Music::~Music()
{
    delete player;
    delete audioOutput;
    delete fadeTimer;
}

void Music::playSong(int level){
    if((level < 0) || (level > 6)){
        throw std::runtime_error("Out-of-index song request");
    }
    fadeOut(FADE_OUT_TIME);
    QTimer::singleShot(FADE_OUT_TIME + 1000, [level, this]() {
        player->setSource(songs[level]);
        player->play();
        fadeIn(FADE_IN_TIME);
    });

}

void Music::fadeOut(int durationMs) {
    const qreal epsilon = 0.0001;
    if(std::abs(audioOutput->volume() - targetVolume) > epsilon){
        // throw std::runtime_error("fadeOut called early");
        qDebug() << "Fade out called early";
    }

    fadeTimer->stop();
    fadeTimer->disconnect();

    int interval = 100;  // ms between steps
    int steps = durationMs / interval;
    qreal currentVolume = audioOutput->volume();
    volumeStep = currentVolume / steps;

    connect(fadeTimer, &QTimer::timeout, this, [this]() {
        qreal vol = audioOutput->volume();
        vol -= volumeStep;
        if (vol <= 0.0) {
            vol = 0.0;
            fadeTimer->stop();
        }
        audioOutput->setVolume(vol);
    });
    fadeTimer->start(interval);
}

void Music::fadeIn(int durationMs) {
    if(audioOutput->volume() != 0){
        // throw std::runtime_error("fadeIn called early");
        qDebug() << "Fade in called early";
    }

    fadeTimer->stop();
    fadeTimer->disconnect();

    int interval = 100;  // ms between steps
    int steps = durationMs / interval;
    qreal startVolume = 0.0;
    volumeStep = targetVolume / steps;

    audioOutput->setVolume(0.0);

    connect(fadeTimer, &QTimer::timeout, this, [this]() {
        qreal vol = audioOutput->volume();
        vol += volumeStep;
        if (vol >= targetVolume) {
            vol = targetVolume;
            fadeTimer->stop();
        }
        audioOutput->setVolume(vol);
    });
    fadeTimer->start(interval);
}

qreal Music::vol(){
    return audioOutput->volume();
}

int Music::loadingTime(){
    return FADE_IN_TIME + FADE_OUT_TIME + 1000;
}
