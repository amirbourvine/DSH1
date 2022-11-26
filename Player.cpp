//
// Created by Elad on 25/11/2022.
//

#include "Player.h"

using namespace std;

Player::Player(int playerId) : playerId(playerId) {}

Player::Player(int playerId, int gamesPlayed, int goals, int cards, bool goalKeeper, Team* team):
        playerId(playerId),
        gamesPlayedWithoutTeam(gamesPlayed),
        goals(goals),
        cards(cards),
        goalKeeper(goalKeeper),
        betterPlayer(nullptr),
        worsePlayer(nullptr),
        team(team){
}

int Player::getPlayerId() const {
    return playerId;
}

int Player::getGamesPlayedWithoutTeam() const {
    return gamesPlayedWithoutTeam;
}

int Player::getGoals() const {
    return goals;
}

int Player::getCards() const {
    return cards;
}

bool Player::isGoalKeeper() const {
    return goalKeeper;
}

shared_ptr<Player> Player::getBetterPlayer() const {
    return betterPlayer;
}

shared_ptr<Player> Player::getWorsePlayer() const {
    return worsePlayer;
}

void Player::setGamesPlayedWithoutTeam(int gamesPlayedWithoutTeam) {
    Player::gamesPlayedWithoutTeam = gamesPlayedWithoutTeam;
}

void Player::setGoals(int goals) {
    Player::goals = goals;
}

void Player::setCards(int cards) {
    Player::cards = cards;
}

void Player::setGoalKeeper(bool goalKeeper) {
    Player::goalKeeper = goalKeeper;
}

void Player::setBetterPlayer(shared_ptr<Player> betterPlayer) {
    Player::betterPlayer = betterPlayer;
}

void Player::setWorsePlayer(shared_ptr<Player> WorsePlayer) {
    Player::worsePlayer = worsePlayer;
}

Team* Player::getTeam() const {
    return team;
}

void Player::setTeam(Team* team) {
    Player::team = team;
}

int Player::compare(Player& other) const{
    if(this->goals > other.goals)
        return this->playerId;

    if(this->goals < other.goals)
        return other.playerId;

    if(this->cards < other.cards)
        return this->playerId ;

    if(this->cards > other.cards)
        return other.playerId;

    return (this->playerId > other.playerId) ? this->playerId : other.playerId;
}

std::ostream& operator<<(std::ostream& os, const Player& p){
    /*
    return os << "playerId: " << p.playerId << ", gamesPlayedWithoutTeam: " << p.gamesPlayedWithoutTeam
              << ", goals: " << p.goals << ", cards: " << p.cards << ", goalKeeper: " << p.goalKeeper
              << ", teamId: " << p.teamId << std::endl;
              */
    return os << "playerId: " << p.playerId << std::endl;
}

bool operator==(const Player& p1, const Player& p2){
    return p1.playerId == p2.playerId;
}
