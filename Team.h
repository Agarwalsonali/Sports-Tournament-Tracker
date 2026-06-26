#ifndef TEAM_H
#define TEAM_H

#include <string>
using namespace std;

class Team {
private:
    int id;
    string name;
    int points;
    int goals_for;
    int goals_against;
    int wins;
    int draws;
    int losses;
    bool eliminated;

public:
    Team() 
        : id(-1), name(""), points(0), goals_for(0), goals_against(0), 
          wins(0), draws(0), losses(0), eliminated(false) {}

    Team(int id, string name) 
        : id(id), name(name), points(0), goals_for(0), goals_against(0), 
          wins(0), draws(0), losses(0), eliminated(false) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getPoints() const { return points; }
    int getGoalsFor() const { return goals_for; }
    int getGoalsAgainst() const { return goals_against; }
    int getGoalDifference() const { return goals_for - goals_against; }
    int getWins() const { return wins; }
    int getDraws() const { return draws; }
    int getLosses() const { return losses; }
    bool isEliminated() const { return eliminated; }

    // Mutators
    void updateStats(int g_for, int g_against, char result) {
        goals_for += g_for;
        goals_against += g_against;
        if (result == 'W') { wins++; points += 3; }
        else if (result == 'D') { draws++; points += 1; }
        else if (result == 'L') { losses++; }
    }

    void setEliminated(bool status) { eliminated = status; }
};

#endif