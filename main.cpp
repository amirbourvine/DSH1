#include <iostream>
#include "worldcup23a1.h"

using namespace std;

int main(){
    //*********************Unit Tests*******************************
    world_cup_t wct;
    int counter = 1;

    //****************************AddTeam & RemoveTeam*******************************
    cout << "*********************AddTeam & RemoveTeam*********************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(1, 0);
    wct.add_team(2, 2);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(2, 0);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(2, -1);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.remove_team(1);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.remove_team(3);
    wct.remove_team(-1);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(1, 0);
    wct.add_player(1, 1, 0, 0, 0, false);
    wct.remove_team(1);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.remove_player(1);
    wct.remove_team(1);
    wct.printTeams();

    //****************************AddPlayer & RemoverPlayer**************************
    cout << "*********************AddPlayer & RemoverPlayer*****************" << endl;
    cout << endl << "Test" << counter << endl;
    wct.add_team(1, 0);
    ++counter;
    int playersCount = 1;
    wct.add_player(playersCount, 1,1, 1, 1, true);
    ++playersCount;
    for(; playersCount <= 11; ++playersCount){
        wct.add_player(playersCount, 1,1, 1, 1, false);
    }
    wct.add_player(playersCount, 2,1, 1, 1, true);
    ++playersCount;
    for(; playersCount <= 22; ++playersCount){
        wct.add_player(playersCount, 2,1, 1, 1, false);
    }
    wct.printPlayer(1);
    cout << endl;
    wct.printPlayersByTeamId(1);
    cout << endl;
    wct.printAllPlayers();
    cout << endl;

    cout << endl << "Test" << counter << endl;
    ++counter;
    for(int i = 1; i <= 11; ++i){
        wct.remove_player(i);
    }
    wct.printPlayersByTeamId(1);
    playersCount = 1;
    wct.add_player(playersCount, 1,1, 1, 1, true);
    ++playersCount;
    for(; playersCount <= 11; ++playersCount){
        wct.add_player(playersCount, 1,1, 1, 1, false);
    }
    /*

wct.add_player(1, 1, 1, 1000, 0, true);
wct.add_player(12, 1, 1, 1, 0, false);

wct.printPlayersByTeamId(1);
wct.printPlayersByTeamScore(1);
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

wct.printValidTeams();

wct.remove_player(10);
cout<<"GERAT"<<endl;
wct.printValidTeams();

wct.add_player(10, 2, 1, 2, 0, true);

wct.printValidTeams();

if(wct.knockout_winner(1,2).status()==StatusType::SUCCESS)
    cout<<wct.knockout_winner(1,2).ans();
    */

   return 0;
}