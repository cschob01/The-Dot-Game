#ifndef MAPSORTER_H
#define MAPSORTER_H

#include <utility>

#include "map1_1.h"
#include "map1_2.h"
#include "map1_3.h"
#include "map1_4.h"
#include "map1_5.h"
#include "map2_1.h"
#include "map2_2.h"
#include "map2_3.h"
#include "map2_4.h"
#include "map2_5.h"
#include "map3_1.h"
#include "map3_2.h"
#include "map3_3.h"
#include "map3_4.h"
#include "map3_5.h"
#include "map4_1.h"
#include "map4_2.h"
#include "map4_3.h"
#include "map4_4.h"
#include "map4_5.h"
#include "map5_1.h"
#include "map5_2.h"
#include "map5_3.h"
#include "map5_4.h"
#include "map5_5.h"
#include "map6_1.h"

namespace MapSorter {
    inline Map * getMap(std::pair<int, int> level, int render){
        Map * map;
        if(level.first == 0){
            if(level.second == 0){
                map = new Map1_1();
            }
            if(level.second == 1){
                map = new Map1_2();
            }
            if(level.second == 2){
                map = new Map1_3();
            }
            if(level.second == 3){
                map = new Map1_4();
            }
            if(level.second == 4){
                map = new Map1_5();
            }
        }
        if(level.first == 1){
            if(level.second == 0){
                map = new Map2_1();
            }
            if(level.second == 1){
                map = new Map2_2();
            }
            if(level.second == 2){
                map = new Map2_3();
            }
            if(level.second == 3){
                map = new Map2_4();
            }
            if(level.second == 4){
                map = new Map2_5();
            }
        }
        if(level.first == 2){
            if(level.second == 0){
                map = new Map3_1();
            }
            if(level.second == 1){
                map = new Map3_2();
            }
            if(level.second == 2){
                map = new Map3_3();
            }
            if(level.second == 3){
                map = new Map3_4();
            }
            if(level.second == 4){
                map = new Map3_5();
            }
        }
        if(level.first == 3){
            if(level.second == 0){
                map = new Map4_1();
            }
            if(level.second == 1){
                map = new Map4_2();
            }
            if(level.second == 2){
                map = new Map4_3();
            }
            if(level.second == 3){
                map = new Map4_4();
            }
            if(level.second == 4){
                map = new Map4_5();
            }
        }
        if(level.first == 4){
            if(level.second == 0){
                map = new Map5_1();
            }
            if(level.second == 1){
                map = new Map5_2();
            }
            if(level.second == 2){
                map = new Map5_3();
            }
            if(level.second == 3){
                map = new Map5_4();
            }
            if(level.second == 4){
                map = new Map5_5();
            }
        }
        if(level.first == 5){
            map = new Map6_1();
        }
        map->optimize(render);
        return map;
    }
}

#endif
