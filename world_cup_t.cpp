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
        playersByScore(new AVLTree<shared_ptr<Player>>(&isLargerByScore, &isEqualByID)),
        top_scorer(nullptr),
        playersCount(0){}

StatusType world_cup_t::add_team(int teamId, int points){
    if(teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Team> t(new Team(teamId, points));
    if(teams->find(t).status() != StatusType::FAILURE)
        return StatusType::FAILURE;

    try {
        if(teams->insert(t) != StatusType::SUCCESS)
            return StatusType::SUCCESS;
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
    if(out.status() != StatusType::SUCCESS)
        return out.status();

    team = *(out.ans()->getKey().ans());
    try {
        shared_ptr<Player> p(new Player (playerId, gamesPlayed - team->getGamesPlayedAsTeam(), goals, cards, goalKeeper, &*team));

        if (players->insert(shared_ptr<Player>(p)) != StatusType::SUCCESS)
            return players->insert(shared_ptr<Player>(p));

        if (playersByScore->insert(shared_ptr<Player>(p)) != StatusType::SUCCESS)
            return playersByScore->insert(shared_ptr<Player>(p));

        ++playersCount;

        bool validBeforePlayer = team->isValid();

        if(team->add_player(p) != StatusType::SUCCESS)
            return team->add_player(p);

        if(team->isValid() && !validBeforePlayer){
            if(validTeams->insert(team) != StatusType::SUCCESS)
                return validTeams->insert(shared_ptr<Team>(team));
        }

        if(top_scorer == nullptr || top_scorer->compare(*p) == p->getPlayerId())
            top_scorer = shared_ptr<Player>(p);

        if(playersByScore->findAbove(p).ans() != nullptr) {
            p->setBetterPlayer(&**(playersByScore->findAbove(p).ans()->getKey().ans()));
            if(p->getBetterPlayer() != nullptr)
                p->getBetterPlayer()->setWorsePlayer(&*p);
        }

        if(playersByScore->findUnder(p).ans() != nullptr){
            p->setWorsePlayer(&**(playersByScore->findUnder(p).ans()->getKey().ans()));
            if(p->getWorsePlayer() != nullptr)
                p->getWorsePlayer()->setBetterPlayer(&*p);
        }
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
    if(out.status() != StatusType::SUCCESS)
        return StatusType::SUCCESS;

    player = *(out.ans()->getKey().ans());

    if(players->remove(player) != StatusType::SUCCESS)
        return players->remove(player);

    if(playersByScore->remove(player) != StatusType::SUCCESS)
        return playersByScore->remove(player);

    bool validBeforePlayer = player->getTeam()->isValid();

    if (player->getTeam()->remove_player(player) != StatusType::SUCCESS)
        return player->getTeam()->remove_player(player);

    if(!player->getTeam()->isValid() && validBeforePlayer){
        //teams->print2D();
        shared_ptr<Team> team = shared_ptr<Team>(player->getTeam());
        if(validTeams->remove(team) != StatusType::SUCCESS)
            return validTeams->remove(team);
    }
    //teams->print2D();


    --playersCount;

    if(playersCount == 0)
        top_scorer = nullptr;
    else if(top_scorer->getPlayerId() == playerId){
        top_scorer = *(playersByScore->findMax()->getKey().ans());
    }

    if(player->getBetterPlayer() != nullptr)
        player->getBetterPlayer()->setWorsePlayer(player->getWorsePlayer());
    if(player->getWorsePlayer() != nullptr)
        player->getWorsePlayer()->setBetterPlayer(player->getBetterPlayer());

    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived){
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player(new Player(playerId));
    output_t<AVLNode<shared_ptr<Player>>*> out = players->find(player);
    if(out.status() != StatusType::SUCCESS)
        return out.status();

    player = *(out.ans()->getKey().ans());

    if(remove_player(player->getPlayerId()) != StatusType::SUCCESS)
        return remove_player(player->getPlayerId());

    if(add_player(player->getPlayerId(), player->getTeam()->getTeamId(),
                  player->getGamesPlayedWithoutTeam(),
                  player->getGoals(), player->getCards(),
                  player->isGoalKeeper()) != StatusType::SUCCESS)
        return add_player(player->getPlayerId(), player->getTeam()->getTeamId(),
                          player->getGamesPlayedWithoutTeam() + gamesPlayed,
                          player->getGoals() + scoredGoals, player->getCards() + cardsReceived,
                          player->isGoalKeeper());

    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    shared_ptr<Team> team1(new Team(teamId1));
    output_t<AVLNode<shared_ptr<Team>>*> out1 = validTeams->find(team1);
    if(out1.status() != StatusType::SUCCESS) {
        return out1.status();
    }

    team1 = *(out1.ans()->getKey().ans());

    shared_ptr<Team> team2(new Team(teamId2));
    output_t<AVLNode<shared_ptr<Team>>*> out2 = validTeams->find(team2);

    if(out2.status() != StatusType::SUCCESS) {
        return out2.status();
    }

    team2 = *(out2.ans()->getKey().ans());

    if(team1->getWinningRate() > team2->getWinningRate())
        team1->setPoints(team1->getPoints() + 3);
    else if(team1->getWinningRate() < team2->getWinningRate())
        team2->setPoints(team2->getPoints() + 3);
    else {
        team1->setPoints(team1->getPoints() + 1);
        team2->setPoints(team2->getPoints() + 1);
    }

    team1->setGamesPlayedAsTeam(team1->getGamesPlayedAsTeam() + 1);
    team2->setGamesPlayedAsTeam(team2->getGamesPlayedAsTeam() + 1);

    return StatusType::SUCCESS;
}

output_t <int> world_cup_t::get_num_played_games(int playerId){
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player(new Player(playerId));
    output_t<AVLNode<shared_ptr<Player>>*> out = players->find(player);
    if(out.status() != StatusType::SUCCESS)
        return out.status();

    player = *(out.ans()->getKey().ans());

    return player->getGamesPlayedWithoutTeam() + player->getTeam()->getGamesPlayedAsTeam();
}

output_t<int> world_cup_t::get_team_points(int teamId){
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Team> team(new Team(teamId));
    output_t<AVLNode<shared_ptr<Team>>*> out1 = teams->find(team);
    if(out1.status() != StatusType::SUCCESS) {
        return out1.status();
    }

    team = *(out1.ans()->getKey().ans());

    return team->getPoints();
}

output_t<int> world_cup_t::get_top_scorer(int teamId){
    if(teamId == 0)
        return StatusType::INVALID_INPUT;

    if(teamId > 0){
        shared_ptr<Team> team(new Team(teamId));
        output_t<AVLNode<shared_ptr<Team>>*> out1 = teams->find(team);
        if(out1.status() != StatusType::SUCCESS) {
            return out1.status();
        }

        team = *(out1.ans()->getKey().ans());

        if(team->getPlayersCount() == 0)
            return StatusType::FAILURE;

        return team->getTopScorer()->getPlayerId();
    }

    if(playersCount == 0)
        return StatusType::FAILURE;

    return top_scorer->getPlayerId();
}

output_t<int> world_cup_t::get_all_players_count(int teamId){
    if(teamId == 0)
        return StatusType::INVALID_INPUT;

    if(teamId > 0){
        shared_ptr<Team> team(new Team(teamId));
        output_t<AVLNode<shared_ptr<Team>>*> out1 = teams->find(team);
        if(out1.status() != StatusType::SUCCESS) {
            return out1.status();
        }

        team = *(out1.ans()->getKey().ans());

        if(team->getPlayersCount() == 0)
            return StatusType::FAILURE;

        return team->getPlayersCount();
    }

    if(playersCount == 0)
        return StatusType::FAILURE;

    return playersCount;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId){
    if(playerId <= 0 || teamId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Team> team(new Team(teamId));
    output_t<AVLNode<shared_ptr<Team>>*> out1 = teams->find(team);
    if(out1.status() != StatusType::SUCCESS) {
        return out1.status();
    }

    team = *(out1.ans()->getKey().ans());


    output_t<AVLNode<shared_ptr<Player>>*> out2 = team->findPlayerByID(playerId);
    if(out2.status() != StatusType::SUCCESS) {
        return out2.status();
    }

    shared_ptr<Player> player = *(out2.ans()->getKey().ans());

    return player->getClosestPlayerId();
}

void addGamesToPlayer(const shared_ptr<Player>& p){
    p->setGamesPlayedWithoutTeam(p->getGamesPlayedWithoutTeam() + p->getTeam()->getGamesPlayedAsTeam());
}
StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId){
    if(teamId1 <= 0 || teamId2 <= 0 || newTeamId <=0 || teamId1 == teamId2)
        return StatusType::FAILURE;

    shared_ptr<Team> team1(new Team(teamId1));
    output_t<AVLNode<shared_ptr<Team>>*> out1 = validTeams->find(team1);
    if(out1.status() != StatusType::SUCCESS) {
        return out1.status();
    }

    team1 = *(out1.ans()->getKey().ans());

    shared_ptr<Team> team2(new Team(teamId2));
    output_t<AVLNode<shared_ptr<Team>>*> out2 = validTeams->find(team2);

    if(out2.status() != StatusType::SUCCESS) {
        return out2.status();
    }

    team2 = *(out2.ans()->getKey().ans());

    shared_ptr<Team> newTeam(new Team(newTeamId, team1->getPoints() + team2->getPoints()));
    if(teams->find(newTeam).status() != StatusType::FAILURE)
        return StatusType::FAILURE;

    if(team1->isValid()){
        if(validTeams->remove(team1) != StatusType::SUCCESS)
            return validTeams->remove(team1);
    }

    if(team2->isValid()){
        if(validTeams->remove(team2) != StatusType::SUCCESS)
            return validTeams->remove(team2);
    }

    if(teams->remove(team1) != StatusType::SUCCESS)
        return validTeams->remove(team1);

    if(teams->remove(team2) != StatusType::SUCCESS)
        return validTeams->remove(team2);

    newTeam->setGoalKeepersAmount(team1->getGoalKeepersAmount() + team2->getGoalKeepersAmount());

    newTeam->setGamesPlayedAsTeam(0);
    team1->inOrderPlayers(&addGamesToPlayer);
    team2->inOrderPlayers(&addGamesToPlayer);

    newTeam->setTopScorer((team1->getTopScorer()->compare(*team2->getTopScorer())
                           == team1->getTopScorer()->getPlayerId()) ? team1->getTopScorer() : team2->getTopScorer());

    newTeam->mergeTeams(team1, team2);

    if(newTeam->isValid()) {
        if(validTeams->insert(newTeam) != StatusType::SUCCESS)
            return validTeams->insert(newTeam);
    }

    if(teams->insert(newTeam) != StatusType::SUCCESS)
        return teams->insert(newTeam);

    return StatusType::SUCCESS;
}

StatusType world_cup_t::get_all_players(int teamId, int* const output){
    if(teamId == 0 || output == NULL){
        return StatusType::INVALID_INPUT;
    }

    if(teamId > 0){
        shared_ptr<Team> team(new Team(teamId));
        output_t<AVLNode<shared_ptr<Team>>*> out1 = teams->find(team);
        if(out1.status() != StatusType::SUCCESS) {
            return out1.status();
        }

        team = *(out1.ans()->getKey().ans());

        if(team->getPlayersCount() == 0)
            return StatusType::FAILURE;

        shared_ptr<Player>* arr[team->getPlayersCount()];
        team->playersIntoArr(arr);
        for(int i = 0; i < team->getPlayersCount(); ++i)
            output[i] = (*arr[i])->getPlayerId();

        return StatusType::SUCCESS;
    }

    if(playersCount == 0)
        return StatusType::FAILURE;

    shared_ptr<Player>* arr[playersCount];
    playersByScore->inorderToArr(arr, playersCount);
    for(int i = 0; i < playersCount; ++i)
        output[i] = (*arr[i])->getPlayerId();

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId){
    if(minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId)
        return StatusType::INVALID_INPUT;

    int validTeamsAmount = validTeams->getSize();
    shared_ptr<Team>* teamsPlaying[validTeamsAmount];
    for(int i = 0; i < validTeamsAmount; ++i)
        teamsPlaying[i] = nullptr;

    //Find teamsPlaying with a return value of its size

    return StatusType::SUCCESS;
}











