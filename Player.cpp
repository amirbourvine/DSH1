//
// Created by Elad on 25/11/2022.
//
#include <math.h>
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

Player* Player::getBetterPlayer() const {
    return betterPlayer;
}

Player* Player::getWorsePlayer() const {
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

void Player::setBetterPlayer(Player* betterPlayer) {
    Player::betterPlayer = betterPlayer;
}

void Player::setWorsePlayer(Player* WorsePlayer) {
    Player::worsePlayer = worsePlayer;
}

int Player::getClosestPlayerId() const{
    if(worsePlayer == nullptr && betterPlayer == nullptr)
        return playerId;
    if(worsePlayer != nullptr && betterPlayer == nullptr)
        return worsePlayer->playerId;
    if(worsePlayer == nullptr && betterPlayer != nullptr)
        return betterPlayer->playerId;

    if(abs(goals - worsePlayer->goals) < abs(goals - betterPlayer->goals))
        return worsePlayer->playerId;
    if(abs(goals - worsePlayer->goals) > abs(goals - betterPlayer->goals))
        return betterPlayer->playerId;

    if(abs(cards - worsePlayer->cards) < abs(cards - betterPlayer->cards))
        return worsePlayer->playerId;
    if(abs(cards - worsePlayer->cards) > abs(cards - betterPlayer->cards))
        return betterPlayer->playerId;

    if(abs(playerId - worsePlayer->playerId) > abs(playerId - betterPlayer->playerId))
        return worsePlayer->playerId;
    if(abs(playerId - worsePlayer->playerId) < abs(playerId - betterPlayer->playerId))
        return betterPlayer->playerId;

    return (worsePlayer->playerId > betterPlayer->playerId) ? worsePlayer->playerId : betterPlayer->playerId;
}

Team* Player::getTeam() const {
    return team;
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
