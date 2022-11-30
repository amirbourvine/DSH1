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

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.update_player_stats(2, 0, 1, 0);
    wct.update_player_stats(3, 0, 1, 1);
    wct.printPlayersByTeamScore(1);

    //****************************Valid Team******************************************
    cout << "*********************Valid Team********************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.printValidTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.remove_player(1);
    wct.printValidTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_player(1, 1, 1, 1, 1, false);
    wct.printValidTeams();
    wct.remove_player(1);
    wct.add_player(1, 1, 1, 1, 1, true);

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_player(100, 1, 1, 1, 1, true);
    wct.add_player(200, 1, 1, 1, 1, true);
    wct.remove_player(100);
    wct.remove_player(200);

    wct.printValidTeams();

    //****************************play match******************************************
    cout << "*********************play match********************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.play_match(1, 2);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.update_player_stats(1, 0, 5, 1);
    wct.play_match(1, 2);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.play_match(1, 1);
    wct.printTeams();

    //****************************knockout********************************************
    cout << "*********************knockout**********************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    for(int i = 10; i < 18; ++i){
        wct.add_team(i, 0);
        for(int j = i * 100; j < i * 100 + 11; ++j)
            wct.add_player(j, i, 1, i, 0, true);
    }
    cout << wct.knockout_winner(10, 17).ans() << endl;

    cout << endl << "Test" << counter << endl;
    ++counter;
    cout << wct.knockout_winner(10, 12).ans() << endl;
    wct.remove_player(1100);
    cout << wct.knockout_winner(10, 12).ans() << endl;

   return 0;
}