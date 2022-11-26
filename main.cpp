#include <iostream>
//#include "world_cup_t.h"
#include "world_cup_t.h"

using namespace std;

int main(){
    world_cup_t wct;

    wct.add_team(1, 0);
    wct.add_team(2, 0);

    wct.add_player(1, 1, 1, 1, 0, true);
    wct.add_player(12, 1, 1, 1, 0, false);
    wct.add_player(13, 1, 1, 1, 0, false);
    wct.add_player(14, 1, 1, 1, 0, false);
    wct.add_player(15, 1, 1, 1, 0, false);
    wct.add_player(16, 1, 1, 1, 0, false);
    wct.add_player(17, 1, 1, 1, 0, false);
    wct.add_player(18, 1, 1, 1, 0, false);
    wct.add_player(19, 1, 1, 1, 0, false);
    wct.add_player(20, 1, 1, 1, 0, false);
    wct.add_player(21, 1, 1, 1, 0, false);

    wct.add_player(10, 2, 1, 2, 0, true);
    wct.add_player(120, 2, 1, 1, 0, false);
    wct.add_player(130, 2, 1, 1, 0, false);
    wct.add_player(140, 2, 1, 1, 0, false);
    wct.add_player(150, 2, 1, 1, 0, false);
    wct.add_player(160, 2, 1, 1, 0, false);
    wct.add_player(170, 2, 1, 1, 0, false);
    wct.add_player(180, 2, 1, 1, 0, false);
    wct.add_player(190, 2, 1, 1, 0, false);
    wct.add_player(200, 2, 1, 1, 0, false);
    wct.add_player(210, 2, 1, 1, 0, false);

    if(wct.play_match(1, 2) == StatusType::SUCCESS)
        cout << "Success";

    return 0;
}