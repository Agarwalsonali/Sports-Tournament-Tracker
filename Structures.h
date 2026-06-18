#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Team{
    int id;
    string name;
    int points;
    int goals_for;
    int goals_against;
    int wins, draws, losses;
    bool eliminated;
};

struct Match{
    int id;
    int home_team_id;
    int away_team_id;
    int home_team_goals;
    int away_team_goals;
    char result;                                     // 'W','D','L'
    int start_time;
    int end_time;
};

#endif // STRUCTURES_H