//
// Created by Elad on 25/11/2022.
//
#include <exception>
#include "world_cup_t.h"

using namespace std;

bool isLargerByID(const shared_ptr<Team>& t1, const shared_ptr<Team>& t2){
    return t1->getTeamId() > t2->getTeamId();
}
bool isEqualByID(const shared_ptr<Team>& t1, const shared_ptr<Team>& t2){
    return t1->getTeamId() == t2->getTeamId();
}

world_cup_t::world_cup_t():
        teams(new AVLTree<shared_ptr<Team>>(&isLargerByID, &isEqualByID)),
        validTeams(new AVLTree<shared_ptr<Team>>(&isLargerByID, &isEqualByID)),
        players(new AVLTree<shared_ptr<Player>>(&isLargerByID, &isEqualByID)),
        playersByScore(new AVLTree<shared_ptr<Player>>(&isLargerByID, &isEqualByID)),
        top_scorer(nullptr),
        playersCount(0){}

StatusType world_cup_t::add_team(int teamId, int points){
    if(teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;

    try {
        shared_ptr<Team> t(new Team(teamId, points));

        if(teams->insert(t) == StatusType::FAILURE)
            return StatusType::FAILURE;
    }
    catch(bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

#include <iostream>
StatusType world_cup_t::remove_team(int teamId){
    if(teamId <= 0)
        return StatusType::FAILURE;

    shared_ptr<Team> temp(new Team(teamId));
    output_t<AVLNode<shared_ptr<Team>>*> out = teams->find(temp);
    if(out.status() == StatusType::FAILURE)
        return StatusType::FAILURE;

    temp = *(out.ans()->getKey().ans());

    if(temp->getPlayersCount() > 0)
        return StatusType::FAILURE;

    StatusType status = teams->remove(temp);

    return status;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper){
    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 ||
       (gamesPlayed == 0 && (goals > 0 || cards > 0)))
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> temp_p(new Player(playerId));
    if(players->find(temp_p).status() != StatusType::FAILURE)
        return StatusType::FAILURE;

    shared_ptr<Team> team(new Team(teamId));
    output_t<AVLNode<shared_ptr<Team>>*> out = teams->find(team);
    if(out.status() == StatusType::FAILURE)
        return StatusType::FAILURE;

    team = *(out.ans()->getKey().ans());
    try {
        shared_ptr<Player> p(new Player (playerId, gamesPlayed - team->getGamesPlayedAsTeam(), goals, cards, goalKeeper, &*team));

        if (players->insert(shared_ptr<Player>(p)) == StatusType::FAILURE)
            return StatusType::FAILURE;

        if (playersByScore->insert(shared_ptr<Player>(p)) == StatusType::FAILURE)
            return StatusType::FAILURE;

        ++playersCount;

        bool validBeforePlayer = team->isValid();

        if(team->add_player(p) != StatusType::SUCCESS)
            return team->add_player(p);

        if(team->isValid() && !validBeforePlayer){
            if(validTeams->insert(team) == StatusType::FAILURE)
                return StatusType::FAILURE;
        }

        if(top_scorer == nullptr || top_scorer->compare(*p) == p->getPlayerId())
            top_scorer = shared_ptr<Player>(p);

        //ClosestPlayer
    }
    catch(bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId){
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player(new Player(playerId));
    output_t<AVLNode<shared_ptr<Player>>*> out = players->find(player);
    if(out.status() == StatusType::FAILURE)
        return StatusType::FAILURE;

    player = *(out.ans()->getKey().ans());

    if(players->remove(player) == StatusType::FAILURE)
        return StatusType::FAILURE;

    if(playersByScore->remove(player) == StatusType::FAILURE)
        return StatusType::FAILURE;

    --playersCount;

    bool validBeforePlayer = player->getTeam()->isValid();

    if (player->getTeam()->remove_player(player) != StatusType::SUCCESS)
        return player->getTeam()->remove_player(player);

    if(!player->getTeam()->isValid() && validBeforePlayer){
        shared_ptr<Team> temp;
        temp = static_cast<const shared_ptr<Team>>(player->getTeam());
        if(validTeams->remove(temp) == StatusType::FAILURE)
            return StatusType::FAILURE;
    }

    if(playersCount == 0)
        top_scorer = nullptr;
    else if(top_scorer->getPlayerId() == playerId){
        top_scorer = *(playersByScore->findMax()->getKey().ans());
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived){
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player(new Player(playerId));
    output_t<AVLNode<shared_ptr<Player>>*> out = players->find(player);
    if(out.status() == StatusType::FAILURE)
        return StatusType::FAILURE;

    player = *(out.ans()->getKey().ans());

    if(remove_player(player->getPlayerId()) != StatusType::SUCCESS)
        return remove_player(player->getPlayerId());

    if(add_player(player->getPlayerId(), player->getTeam()->getTeamId(), player->getGamesPlayedWithoutTeam(),
                  player->getGoals(), player->getCards(), player->isGoalKeeper()) != StatusType::SUCCESS)
        return add_player(player->getPlayerId(), player->getTeam()->getTeamId(),
                          player->getGamesPlayedWithoutTeam() + gamesPlayed,
                          player->getGoals() + scoredGoals, player->getCards() + cardsReceived, player->isGoalKeeper());

    return StatusType::SUCCESS;
}
