#ifndef MAP5_5_H
#define MAP5_5_H

#include "../map.h"

class Map5_5 : public Map
{
    Q_OBJECT

public:
    explicit Map5_5(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int box_w = 100;
        int box_h = 100;
        int gap_size = 20;
        int w = 100 + box_w;
        int h = 100 + box_h;
        int start_w = (w - box_w) / 2;
        int start_h = (h - box_h) / 2;
        setMapSize(w + 10, h + 10, true);

        //Set starting data
        starting_coords = QPointF(start_w + box_w / 2, start_h + box_h / 2);
        starting_angle = 0.0;
        loading_text = "5:5\nFinal Straw";

        //Set up randomizer
        std::random_device rd;
        std::mt19937 gen(rd());

        //Initialize table of set portals <- exclude middle
        bool port_table[box_w / gap_size][box_h / gap_size];
        for(int i = 0; i < box_w / gap_size; i++){
            for(int j = 0; j < box_h / gap_size; j++){
                port_table[i][j] = false;
            }
        }
        port_table[box_w / gap_size / 2][box_h / gap_size / 2] = true;
        int open = (box_h / gap_size) * (box_w / gap_size) - 1;

        //Add walls/obstacles/finish
        for(int i = 0; i < (box_h / gap_size) * (box_w / gap_size) / 2; i++){

            //Assignment
            std::uniform_int_distribution<> distr1(0, open - 1);
            int rn1 = distr1(gen);
            std::uniform_int_distribution<> distr2(0, open - 2);
            open -= 2;
            int rn2 = distr2(gen);

            //Color assignment
            std::uniform_int_distribution<> distr3(1, 5);
            int rn3 = distr3(gen);
            QColor color;
            if(rn3 == 1) color = QColor("orange");
            if(rn3 == 2) color = QColor("white");
            if(rn3 == 3) color = QColor("purple");
            if(rn3 == 4) color = QColor("teal");
            if(rn3 == 5) color = QColor("yellow");

            //Get locations on port_table
            bool done = false;
            int count = 0;
            int loc1;
            int loc2;
            while(!done){
                if(!port_table[count % (box_w / gap_size)][count / (box_w / gap_size)]){
                    if(rn1 == 0){
                        loc1 = count;
                        done = true;
                        port_table[count % (box_w / gap_size)][count / (box_w / gap_size)] = true;
                    }
                    else{
                        rn1--;
                    }
                }
                count++;
            }
            done = false;
            count = 0; // Reset for second portal
            while(!done){
                if(!port_table[count % (box_w / gap_size)][count / (box_w / gap_size)]){
                    if(rn2 == 0){
                        loc2 = count;
                        done = true;
                        port_table[count % (box_w / gap_size)][count / (box_w / gap_size)] = true;
                    }
                    else{
                        rn2--;
                    }
                }
                count++;
            }

            // Make the portal now
            makePortal(start_w + 10 + gap_size * (loc1 % (box_w / gap_size)), start_h + 10 + gap_size * (loc1 / (box_w / gap_size)), 
                        start_w + 10 + gap_size * (loc2 % (box_w / gap_size)), start_h + 10 + gap_size * (loc2 / (box_w / gap_size)),
                        10, 10, color);
        }

        double speed = 1.75;
        std::uniform_int_distribution<> distr2(500 * speed, 2000 * speed);
        std::uniform_int_distribution<> distr3(-15, 15);

        //Top-down
        makeMovingBeamObst(1, 0, 0, 0, 0, h + 10, 4000 * speed);
        makeMovingBeamObst(1, 0, distr3(gen), 0, 0, h + 10, distr2(gen));

        //Bottom-up
        makeMovingBeamObst(w + 9, h + 9, 180, 0, 0, -h - 10, 4000 * speed);
        makeMovingBeamObst(w + 9, h + 9, 180 +  distr3(gen), 0, 0, -h - 10, distr2(gen));

        //Left-Right
        makeMovingBeamObst(1, 1, 90, 0, w + 10, 0, 4000 * speed);
        makeMovingBeamObst(1, 1, 90 +  distr3(gen), 0, w + 10, 0, distr2(gen));

        //Right-Left
        makeMovingBeamObst(w + 9, h + 9, 90 + 180, 0, -w - 10, 0, 4000 * speed);
        makeMovingBeamObst(w + 9, h + 9, 270 +  distr3(gen), 0, -w - 10, 0, distr2(gen));

        //Finish Line
        int time = 17000;
        makeMovingBeamObst(w + 5, h + 9, 90 + 180, 0, -w - 10, 0, time);
        makeMovingBeamFin(w + 9, h + 9, 90 + 180, 0, -w - 10, 0, time);

        //Borders (FOR RENDER)
        // int space = 10;
        // makeBeamObst(start_w - space, 1, 90, 0);
        // makeBeamObst(start_w + box_w + space, 1, 90, 0);
        // makeBeamObst(1, start_h - space, 0, 0);
        // makeBeamObst(1, start_h + box_h + space, 0, 0);

        forced_settings.render = 100;

        // makeMovingBeamObst(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete = true);
        
    }
    ~Map5_5(){}
};

#endif
