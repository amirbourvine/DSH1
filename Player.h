//
// Created by Elad on 25/11/2022.
//

#ifndef DS_WET1_PLAYER_H
#define DS_WET1_PLAYER_H
#include <memory>
#include <iostream>

class Team;

using namespace std;

class Player {
private:
    int playerId;
    int gamesPlayedWithoutTeam;
    int goals;
    int cards;
    bool goalKeeper;
    weak_ptr<Player> betterPlayer;
    weak_ptr<Player> worsePlayer;
    weak_ptr<Team> team;

public:
    Player(int playerId);
    Player(int playerId, int gamesPlayed, int goals, int cards, bool goalKeeper, shared_ptr<Team> team);
    Player(Player& other) = default;
    Player& operator=(const Player& other) = default;
    ~Player() = default;

    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend bool operator==(const Player&, const Player&);

    void setGamesPlayedWithoutTeam(int gamesPlayedWithoutTeam);
    void setGoals(int goals);
    void setCards(int cards);
    void setBetterPlayer(shared_ptr<Player>);
    void setWorsePlayer(shared_ptr<Player>);

    int getPlayerId() const;
    int getGamesPlayedWithoutTeam() const;
    int getGoals() const;
    int getCards() const;
    bool isGoalKeeper() const;
    shared_ptr<Team> getTeam() const;

    shared_ptr<Player> getBetterPlayer() const;
    shared_ptr<Player> getWorsePlayer() const;
    int getClosestPlayerId() const;

    int compare(Player& other) const;
};


#endif //DS_WET1_PLAYER_H
