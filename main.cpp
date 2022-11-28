#include <iostream>
//#include "world_cup_t.h"
#include "world_cup_t.h"

using namespace std;
bool isLarger(const int& n, const int& m){
    return n>m;
}
bool isEqual(const int& n, const int& m){
    return n==m;
}
int main(){
    world_cup_t wct;
/*
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

    wct.update_player_stats(1, 1, 1000, 0);
    if(wct.play_match(1, 2) == StatusType::SUCCESS)
        cout << "Success" << endl;

    wct.add_player(220, 2, 1, 1, 0, false);
    if(wct.get_num_played_games(220).status() == StatusType::SUCCESS)
        cout << wct.get_num_played_games(220).ans() << endl;

    if(wct.get_team_points(1).status() == StatusType::SUCCESS)
        cout << "team 1 points: " << wct.get_team_points(1).ans() << endl;

    if(wct.get_top_scorer(2).status() == StatusType::SUCCESS)
        cout << wct.get_top_scorer(2).ans() << endl;

    if(wct.get_top_scorer(-1).status() == StatusType::SUCCESS)
        cout << wct.get_top_scorer(-1).ans() << endl;

    if(wct.get_all_players_count(2).status() == StatusType::SUCCESS)
        cout << wct.get_all_players_count(2).ans() << endl;

    if(wct.get_all_players_count(-1).status() == StatusType::SUCCESS)
        cout << wct.get_all_players_count(-1).ans() << endl;

    wct.remove_team(2);
*/
    wct.add_team(3, 0);
    wct.add_player(30, 3, 1, 200, 10, false);
    wct.add_player(31, 3, 1, 2, 2, false);
    //wct.add_player(32, 3, 1, 2, 4, false);
    //wct.add_player(33, 3, 1, 3, 10, false);

    cout << wct.get_closest_player(30, 3).ans() << endl;
    cout << wct.get_closest_player(31, 3).ans() << endl;
    //cout << wct.get_closest_player(32, 3).ans() << endl;
    //cout << wct.get_closest_player(33, 3).ans() << endl;
/*
    //Test unites teams
    wct.add_team(4, 0);
    wct.add_player(34, 4, 1, 200, 10, true);
    wct.add_player(35, 4, 1, 2, 2, false);
    wct.add_player(36, 4, 1, 2, 4, false);
    wct.add_player(37, 4, 1, 3, 10, false);
    wct.add_player(38, 4, 1, 200, 10, false);
    wct.add_player(39, 4, 1, 2, 2, false);
    wct.add_player(40, 4, 1, 2, 4, false);
    wct.add_player(41, 4, 1, 3, 10, false);


    if(wct.unite_teams(3, 4, 34) == StatusType::SUCCESS)
        cout << "Success but this time a great one " << endl;
    wct.printPlayersByTeamId(34);

     //Tests for get all players
    int output[12];
    wct.get_all_players(34, output);
    for(int i = 0; i < 12; ++i)
        cout << output[i] << " ";
    cout << endl;


    //Test knockout
    cout << wct.knockout_winner(1, 5).ans();
*/
    return 0;
}