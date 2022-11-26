//
// Created by Elad on 25/11/2022.
//
#include <exception>
#include <memory>
#include "AVLTree.h"
#include "wet1util.h"
#include "Team.h"

using namespace std;

bool isLargerByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2){
    if(p1 == nullptr || p2 == nullptr)
        throw invalid_argument("Comparison with nullptr");

    return p1->getPlayerId() > p2->getPlayerId();
}

bool isEqualByID(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2){
    if(p1 == nullptr || p2 == nullptr)
        throw invalid_argument("Comparison with nullptr");

    return p1->getPlayerId() == p2->getPlayerId();
}

bool isLargerByScore(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2){
    if(p1 == nullptr || p2 == nullptr)
        throw invalid_argument("Comparison with nullptr");

    return p1->compare(*p2) == p1->getPlayerId();
}

Team::Team(int teamId, int points) :
    teamId(teamId),
    points(points),
    GoalKeepersAmount(0),
    gamesPlayedAsTeam(0),
    winningRate(points),
    teamPlayersByID(new AVLTree<shared_ptr<Player>>(&isLargerByID, &isEqualByID)),
    teamPlayersByScore(new AVLTree<shared_ptr<Player>>(&isLargerByScore, &isEqualByID)),
    playersCount(0),
    top_scorer(nullptr)
{}

std::ostream& operator<<(std::ostream& os, const Team& t){
    return os << "TeamId: " << t.teamId << std::endl;
}

int Team::getTeamId() const {
    return teamId;
}

void Team::setTeamId(int teamId) {
    Team::teamId = teamId;
}

int Team::getPoints() const {
    return points;
}

void Team::setPoints(int points) {
    Team::points = points;
}

int Team::getGoalKeepersAmount() const {
    return GoalKeepersAmount;
}

void Team::setGoalKeepersAmount(int goalKeepersAmount) {
    GoalKeepersAmount = goalKeepersAmount;
}

int Team::getGamesPlayedAsTeam() const {
    return gamesPlayedAsTeam;
}

void Team::setGamesPlayedAsTeam(int gamesPlayedAsTeam) {
    Team::gamesPlayedAsTeam = gamesPlayedAsTeam;
}

int Team::getWinningRate() const {
    return winningRate;
}

void Team::setWinningRate(int winningRate) {
    Team::winningRate = winningRate;
}

int Team::getPlayersCount() const {
    return playersCount;
}

void Team::setPlayersCount(int playersCount) {
    Team::playersCount = playersCount;
}

const shared_ptr<Player> &Team::getTopScorer() const {
    return top_scorer;
}

void Team::setTopScorer(const shared_ptr<Player> &topScorer) {
    top_scorer = topScorer;
}

StatusType Team::add_player(const shared_ptr<Player> p) {
    if(teamPlayersByID->insert(shared_ptr<Player>(p)) == StatusType::FAILURE)
        return StatusType::FAILURE;

    if(teamPlayersByScore->insert(shared_ptr<Player>(p)) == StatusType::FAILURE)
        return StatusType::FAILURE;

    winningRate += p->getGoals() - p->getCards();
    GoalKeepersAmount += p->isGoalKeeper();

    if(top_scorer == nullptr || top_scorer->compare(*p) == p->getPlayerId())
        top_scorer = shared_ptr<Player>(p);

    ++playersCount;

    //Closest Player

    return StatusType::SUCCESS;
}

bool Team::isValid() const{
    return (this->GoalKeepersAmount > 0 && this->playersCount >= 11);
}

StatusType Team::remove_player(const shared_ptr<Player> p){
    if(teamPlayersByID->remove(p) == StatusType::FAILURE)
        return StatusType::FAILURE;

    if(teamPlayersByScore->remove(p) == StatusType::FAILURE)
        return StatusType::FAILURE;

    winningRate -= p->getGoals() - p->getCards();
    GoalKeepersAmount -= p->isGoalKeeper();

    if(playersCount == 0)
        top_scorer = nullptr;
    else if(top_scorer->getPlayerId() == p->getPlayerId()){
        top_scorer = *(teamPlayersByScore->findMax()->getKey().ans());
    }

    --playersCount;

    //Closest Player

    return StatusType::SUCCESS;
}