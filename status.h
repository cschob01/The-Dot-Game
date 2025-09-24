#ifndef STATUS_H
#define STATUS_H

struct Status {

    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;

    bool up = false;
    bool down = false;
    bool l = false;
    bool r = false;

    bool m = false;

    bool shift = false;

    bool t = false; //Testing
    int count = 0;

    Status() = default;

};

#endif