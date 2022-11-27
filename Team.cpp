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

output_t<AVLNode<shared_ptr<Player>>*> Team::findPlayerByID(int playerId) const{
    shared_ptr<Player> player(new Player(playerId));
    return teamPlayersByID->find(player);
}

void Team::inOrderPlayers(void (*pFunction)(shared_ptr<Player>& t)){
    teamPlayersByID->inorder(pFunction);
}

int Team::getTeamId() const {
    return teamId;
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

    ++playersCount;

    if(top_scorer == nullptr || top_scorer->compare(*p) == p->getPlayerId())
        top_scorer = shared_ptr<Player>(p);

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

    --playersCount;

    if(playersCount == 0)
        top_scorer = nullptr;
    else if(top_scorer->getPlayerId() == p->getPlayerId()){
        top_scorer = *(teamPlayersByScore->findMax()->getKey().ans());
    }

    return StatusType::SUCCESS;
}

void Team::mergeTeams(shared_ptr<Team> team1, shared_ptr<Team> team2){
    playersCount = team1->playersCount + team2->playersCount;

    teamPlayersByID->unite(&*(team1->teamPlayersByID));
    teamPlayersByID->unite(&*(team2->teamPlayersByID));

    teamPlayersByScore->unite(&*(team1->teamPlayersByScore));
    teamPlayersByScore->unite(&*(team2->teamPlayersByScore));
}

void Team::playersIntoArr(shared_ptr<Player> **arr){
    teamPlayersByScore->inorderToArr(arr, playersCount);
}

void Team::printPlayersById(){
    teamPlayersByID->print2D();
}


