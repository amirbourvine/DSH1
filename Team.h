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
    weak_ptr<Team> prevValidTeam;
    weak_ptr<Team> nextValidTeam;

public:
    Team(int teamId, int points = 0);
    Team(Team& other) = delete;
    Team& operator=(const Team& other) = delete;
    ~Team() = default;

    friend std::ostream& operator<<(std::ostream&, const Team&);

    output_t<AVLNode<shared_ptr<Player>>*> findPlayerByID(int playerId) const;
    void inOrderPlayers(void (*pFunction)(shared_ptr<Player>& t));
    void inOrderPlayers(void (*pFunction)(shared_ptr<Player>& p, shared_ptr<Team>& t), shared_ptr<Team>& team);


    int getTeamId() const;
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

    shared_ptr<Team> getNextValidTeam() const;
    shared_ptr<Team> getPrevValidTeam() const;

    void setNextValidTeam(shared_ptr<Team>);
    void setPrevValidTeam(shared_ptr<Team>);

    StatusType add_player(const shared_ptr<Player> p);
    StatusType remove_player(const shared_ptr<Player> p);
    bool isValid() const;

    void mergeTeams(shared_ptr<Team> team1, shared_ptr<Team> team2);
    void playersIntoArr(shared_ptr<Player> **arr);

    void printPlayersById();
    void printPlayersByScore();
};

bool isLargerByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);
bool isEqualByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);
bool isLargerByScore(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);
bool isEqualByScore(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2);


#endif //DS_WET1_TEAM_H
