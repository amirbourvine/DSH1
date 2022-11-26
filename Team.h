//
// Created by Elad on 25/11/2022.
//

#ifndef DS_WET1_TEAM_H
#define DS_WET1_TEAM_H

#include <memory>
#include "AVLTree.h"
#include "Player.h"

using namespace std;

class Team {
private:
    int teamId;
    int points;
    int GoalKeepersAmount;
    int gamesPlayedAsTeam;
    int winningRate;
    unique_ptr<AVLTree<shared_ptr<Player>>> teamPlayersByID;
    unique_ptr<AVLTree<shared_ptr<Player>>> teamPlayersByScore;
    int playersCount;
    shared_ptr<Player> top_scorer;

public:
    Team(int teamId, int points = 0);
    Team(Team& other) = delete;
    Team& operator=(const Team& other) = delete;
    ~Team() = default;

    friend std::ostream& operator<<(std::ostream&, const Team&);

    int getTeamId() const;
    void setTeamId(int teamId);
    int getPoints() const;
    void setPoints(int points);
    int getGoalKeepersAmount() const;
    void setGoalKeepersAmount(int goalKeepersAmount);
    int getGamesPlayedAsTeam() const;
    void setGamesPlayedAsTeam(int gamesPlayedAsTeam);
    int getWinningRate() const;
    void setWinningRate(int winningRate);
    int getPlayersCount() const;
    void setPlayersCount(int playersCount);
    const shared_ptr<Player> &getTopScorer() const;
    void setTopScorer(const shared_ptr<Player> &topScorer);

    StatusType add_player(const shared_ptr<Player> p);
    StatusType remove_player(const shared_ptr<Player> p);
    bool isValid() const;
};

bool isLargerByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);
bool isEqualByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);
bool isLargerByScore(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);


#endif //DS_WET1_TEAM_H