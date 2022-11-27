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
        cout << "Success" << endl;

    // threrefore removed from validTeams and then also from teams
    // line 141 world_cup_t.cpp

    wct.update_player_stats(1, 1, 1000, 0);
    if(wct.play_match(1, 2) == StatusType::SUCCESS)
        cout << "Success" << endl;

    wct.add_player(220, 2, 1, 1, 0, false);

    if(wct.get_num_played_games(220).status() == StatusType::SUCCESS)
        cout << wct.get_num_played_games(220).ans() << endl;

    if(wct.get_team_points(1).status() == StatusType::SUCCESS)
        cout << wct.get_team_points(1).ans() << endl;

    if(wct.get_top_scorer(2).status() == StatusType::SUCCESS)
        cout << wct.get_top_scorer(2).ans() << endl;

    if(wct.get_top_scorer(-1).status() == StatusType::SUCCESS)
        cout << wct.get_top_scorer(-1).ans() << endl;

    if(wct.get_all_players_count(2).status() == StatusType::SUCCESS)
        cout << wct.get_all_players_count(2).ans() << endl;

    if(wct.get_all_players_count(-1).status() == StatusType::SUCCESS)
        cout << wct.get_all_players_count(-1).ans() << endl;

    wct.remove_team(2);

    wct.add_team(3, 0);
    wct.add_player(30, 3, 1, 200, 10, false);
    wct.add_player(31, 3, 1, 2, 2, false);
    wct.add_player(32, 3, 1, 2, 4, false);
    wct.add_player(33, 3, 1, 3, 10, false);

    /*
    cout << wct.get_closest_player(30, 3).ans() << endl;
    cout << wct.get_closest_player(31, 3).ans() << endl;
    cout << wct.get_closest_player(32, 3).ans() << endl;
    cout << wct.get_closest_player(33, 3).ans() << endl;
     */

    //Test unite teams


     //Tests for get all players
    int output[4];
    wct.get_all_players(3, output);
    for(int i = 0; i < 4; ++i)
        cout << output[i] << " ";
    cout << endl;

    //Test knockout


    return 0;
}