#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {

    int pov_h = 100;
    int pov_v = 70;
    int columns = 220;
    int rows = 150;
    int render = 200;
    int height = 10;
    double sensitivityH = 6;
    double sensitivityV = 3;

    bool roofs = true;
    bool map = true;

    Settings() = default;

};

#endif