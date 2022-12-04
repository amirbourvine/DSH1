//
// Created by Elad on 25/11/2022.
//
#include <math.h>
#include "Player.h"

using namespace std;

Player::Player(int playerId) : playerId(playerId) {}

Player::Player(int playerId, int gamesPlayed, int goals, int cards, bool goalKeeper, shared_ptr<Team> team):
        playerId(playerId),
        gamesPlayedWithoutTeam(gamesPlayed),
        goals(goals),
        cards(cards),
        goalKeeper(goalKeeper),
        team(team){
    shared_ptr<Player> temp1(nullptr);
    this->betterPlayer = temp1;
    this->worsePlayer = temp1;
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
    return betterPlayer.lock();
}

shared_ptr<Player> Player::getWorsePlayer() const {
    return worsePlayer.lock();
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

void Player::setBetterPlayer(shared_ptr<Player> betterPlayer) {
    Player::betterPlayer = betterPlayer;
}

void Player::setWorsePlayer(shared_ptr<Player> WorsePlayer) {
    Player::worsePlayer = WorsePlayer;
}

int Player::getClosestPlayerId() const{
    if(worsePlayer.lock() == nullptr && betterPlayer.lock() == nullptr)
        return playerId;
    if(worsePlayer.lock() != nullptr && betterPlayer.lock() == nullptr)
        return worsePlayer.lock()->playerId;
    if(worsePlayer.lock() == nullptr && betterPlayer.lock() != nullptr){
        return betterPlayer.lock()->playerId;
    }

    if(abs(goals - worsePlayer.lock()->goals) < abs(goals - betterPlayer.lock()->goals))
        return worsePlayer.lock()->playerId;
    if(abs(goals - worsePlayer.lock()->goals) > abs(goals - betterPlayer.lock()->goals))
        return betterPlayer.lock()->playerId;

    if(abs(cards - worsePlayer.lock()->cards) < abs(cards - betterPlayer.lock()->cards))
        return worsePlayer.lock()->playerId;
    if(abs(cards - worsePlayer.lock()->cards) > abs(cards - betterPlayer.lock()->cards))
        return betterPlayer.lock()->playerId;

    if(abs(playerId - worsePlayer.lock()->playerId) > abs(playerId - betterPlayer.lock()->playerId))
        return worsePlayer.lock()->playerId;
    if(abs(playerId - worsePlayer.lock()->playerId) < abs(playerId - betterPlayer.lock()->playerId))
        return betterPlayer.lock()->playerId;

    return (worsePlayer.lock()->playerId > betterPlayer.lock()->playerId)
        ? worsePlayer.lock()->playerId : betterPlayer.lock()->playerId;
}

shared_ptr<Team> Player::getTeam() const {
    return team.lock();
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

    if(this->playerId > other.playerId){return this->playerId;}
    else{return other.playerId;}
}

std::ostream& operator<<(std::ostream& os, const Player& p){
    if(p.team.lock()== nullptr){
        os << "playerId: " << p.playerId << " TEAM PTR IS NULL" << std::endl;
    }
    return os << "playerId: " << p.playerId << ", gamesPlayedWithoutTeam: " << p.gamesPlayedWithoutTeam
              << ", goals: " << p.goals << ", cards: " << p.cards << ", goalKeeper: " << p.goalKeeper
               << std::endl;

    //return os << "playerId: " << p.playerId << std::endl;
}

bool operator==(const Player& p1, const Player& p2){
    return p1.playerId == p2.playerId;
}

void Player::setTeam(shared_ptr<Team> &team1) {
    this->team = team1;
}
