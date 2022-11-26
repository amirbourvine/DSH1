#include <iostream>
//#include "world_cup_t.h"
#include "world_cup_t.h"

using namespace std;

int main(){
    world_cup_t wct;

    wct.add_team(1, 1);
    wct.add_team(2, 1);
    wct.add_player(79, 1, 0, 0, 0, false);
    wct.add_player(12, 1, 1, 1, 0, false);

    wct.remove_player(12);

    //wct.remove_team(2);

    return 0;
}