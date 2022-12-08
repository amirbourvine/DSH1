#include <iostream>
#include "worldcup23a1.h"

using namespace std;

//
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
//

#include "worldcup23a1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_players(string cmd, world_cup_t *obj, int teamID);

int main()
{
    cin >> std::boolalpha;

    int d1, d2, d3, d4, d5;
    bool b1;

    // Init
    world_cup_t *obj = new world_cup_t();

    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("add_team")) {
            cin >> d1 >> d2;
            print(op, obj->add_team(d1, d2));
        } else if (!op.compare("remove_team")) {
            cin >> d1;
            print(op, obj->remove_team(d1));
        } else if (!op.compare("add_player")) {
            cin >> d1 >> d2 >> d3 >> d4 >> d5 >> b1;
            print(op, obj->add_player(d1, d2, d3, d4, d5, b1));
        } else if (!op.compare("remove_player")) {
            cin >> d1;
            print(op, obj->remove_player(d1));
        } else if (!op.compare("update_player_stats")) {
            cin >> d1 >> d2 >> d3 >> d4;
            print(op, obj->update_player_stats(d1, d2, d3, d4));
        } else if (!op.compare("play_match")) {
            cin >> d1 >> d2;
            print(op, obj->play_match(d1, d2));
        } else if (!op.compare("get_num_played_games")) {
            cin >> d1;
            print(op, obj->get_num_played_games(d1));
        } else if (!op.compare("get_team_points")) {
            cin >> d1;
            print(op, obj->get_team_points(d1));
        } else if (!op.compare("unite_teams")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->unite_teams(d1, d2, d3));
        } else if (!op.compare("get_top_scorer")) {
            cin >> d1;
            print(op, obj->get_top_scorer(d1));
        } else if (!op.compare("get_all_players_count")) {
            cin >> d1;
            print(op, obj->get_all_players_count(d1));
        } else if (!op.compare("get_all_players")) {
            cin >> d1;
            query_get_all_players(op, obj, d1);
        } else if (!op.compare("get_closest_player")) {
            cin >> d1 >> d2;
            print(op, obj->get_closest_player(d1, d2));
        } else if (!op.compare("knockout_winner")) {
            cin >> d1 >> d2;
            print(op, obj->knockout_winner(d1, d2));
        } else {
            obj->printPlayersByTeamId(1);
            cout << endl << endl << endl;
            obj->printPlayersByTeamId(18);

            //cout << "Unknown command: " << op << endl;
            //return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_players(string cmd, world_cup_t *obj, int teamID)
{
    output_t<int> count = obj->get_all_players_count(teamID);
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS && (count.ans() > 0)) {
        out_mem = new int[count.ans()];
        for (int i = 0; i < count.ans(); ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_players(teamID, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < count.ans(); ++i)
        {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}

    /*
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
    wct.add_player(playersCount, 1,1, 1, 1, true);
    for(int j = 0; j < 11; ++j){
        wct.add_player(playersCount, 1,1, 1, 1, false);
        ++playersCount;
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
    wct.update_player_stats(1, 0, 6, 1);
    wct.play_match(1, 2);
    wct.printTeams();

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.play_match(1, 1);
    wct.printTeams();

    //****************************getNumGamesPlayed***********************************
    cout << "*********************getNumGamesPlayed************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_player(playersCount, 1, 0, 0, 0, false);
    cout << wct.get_num_played_games(playersCount).ans() << endl;
    ++playersCount;
    wct.add_player(playersCount, 1, 1, 0, 0, false);
    cout << wct.get_num_played_games(playersCount).ans() << endl;
    ++playersCount;

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.play_match(1, 2);
    cout << wct.get_num_played_games(playersCount - 1).ans() << endl;

    //****************************getTeamPoints*************************************
    cout << "*********************getTeamPoints****************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    cout << wct.get_team_points(1).ans() << endl;
    cout << wct.get_team_points(2).ans() << endl;
    wct.printTeams();

    //****************************uniteTeams*****************************************
    cout << "*********************uniteTeams****************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.printTeams();

    wct.unite_teams(1, 2, 1);

    cout<<"*******************************UNITED**********************************"<<endl;
    wct.printTeams();
    wct.printValidTeams();
    wct.printPlayersByTeamId(1);
    wct.printPlayersByTeamScore(1);

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(4, 0);
    wct.add_player(playersCount, 4, 0, 0, 0, false);
    ++playersCount;
    wct.unite_teams(1, 4, 1);
    wct.printTeams();
    wct.printPlayersByTeamId(1);

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.add_team(2, 0);
    wct.add_player(playersCount, 2, 0, 0, 0, false);
    ++playersCount;
    wct.add_team(3, 0);
    wct.unite_teams(2, 3, 4);
    wct.printTeams();
    wct.printPlayersByTeamId(4);

    cout << endl << "Test" << counter << endl;
    ++counter;
    wct.unite_teams(1, 4, 1);
    wct.printTeams();
    wct.printPlayersByTeamId(1);

    //****************************knockout********************************************
    cout << "*********************knockout**********************************" << endl;
    cout << endl << "Test" << counter << endl;
    ++counter;
    for(int i = 10; i < 18; ++i){
        wct.add_team(i, 0);
        for(int j = 0; j < 11; ++j){
            wct.add_player(playersCount, i, 1, i, 0, true);
            ++playersCount;
        }
    }
    cout << wct.knockout_winner(10, 17).ans() << endl;

    cout << endl << "Test" << counter << endl;
    ++counter;
    cout << wct.knockout_winner(15, 17).ans() << endl;
    wct.remove_player(playersCount - 12);
    cout << wct.knockout_winner(15, 17).ans() << endl;
    */
    //return 0;
//}