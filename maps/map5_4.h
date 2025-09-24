#ifndef MAP5_4_H
#define MAP5_4_H

#include "../map.h"

class Map5_4 : public Map
{
    Q_OBJECT

public:
    explicit Map5_4(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int w  = 1500;
        int h = 20;
        setMapSize(w + 40, h, true);

        //Set starting data
        starting_coords = QPointF(20, 13);
        starting_angle = 270.0;
        loading_text = "5:4\nSSSP";

        //Add walls/obstacles/finish
        for(int i = 0; i < w / 60; i++){
            makePortal(20 + i * 60, 0, 80 + i * 60, h - 5, 10, 5, QColor("purple").lighter(100 + 10 * i));
            if(i != w / 60 - 1){ //Ignore last one
                makePortal(10 + i * 60, h - 5, 70 + i * 60, 0, 10, 5, QColor("teal").darker(100 + 10 * i));
            }
        }
        makeFin(w + 10, 0, 20, 5);

        int count = 7;
        for(int i = 0; i < count; i++){
            makeMovingObst(40, 0, 20, h, w - 60, 0, 900, (1.0 / count) * i);
        }
    }
    ~Map5_4(){}
};

#endif
