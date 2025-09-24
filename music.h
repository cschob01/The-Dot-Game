#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QList>

class Music : public QObject
{
    Q_OBJECT

public:
    Music(QObject* parent = nullptr);
    ~Music();

    void playSong(int level);
    qreal vol();
    int loadingTime();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QTimer *fadeTimer;

    QList<QUrl> songs;

    qreal targetVolume = 0.8;
    qreal volumeStep = 0.05;

    //helpers
    void fadeIn(int durationMs);
    void fadeOut(int durationMs);

    int currentSong;

    static const int FADE_OUT_TIME = 2000;
    static const int FADE_IN_TIME = 1000;
    
};

#endif
