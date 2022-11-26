//
// Created by Elad on 25/11/2022.
//

#ifndef DS_WET1_WORLD_CUP_T_H
#define DS_WET1_WORLD_CUP_T_H

#include <memory>
#include "Team.h"

class world_cup_t {
private:
    unique_ptr<AVLTree<shared_ptr<Team>>> teams;
    unique_ptr<AVLTree<shared_ptr<Team>>> validTeams;
    unique_ptr<AVLTree<shared_ptr<Player>>> players;
    unique_ptr<AVLTree<shared_ptr<Player>>> playersByScore;
    shared_ptr<Player> top_scorer;

    int playersCount;

public:
    world_cup_t();
    world_cup_t(world_cup_t& other) = delete;
    world_cup_t& operator=(const world_cup_t& other) = delete;
    virtual ~world_cup_t() = default;

    StatusType add_team(int teamId, int points);
    StatusType remove_team(int teamId);

    StatusType add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    StatusType remove_player(int playerId);
    StatusType update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived);
};

bool isLargerByID(const shared_ptr<Team>&, const shared_ptr<Team>&);
bool isEqualByID(const shared_ptr<Team>&, const shared_ptr<Team>&);

#endif //DS_WET1_WORLD_CUP_T_H
