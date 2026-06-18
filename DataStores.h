#ifndef DATASTORES_H
#define DATASTORES_H

#include "Structures.h"
#include<iostream>
#include<vector>
using namespace std;

vector<Team> teams;
vector<Match> matches;

int points[100] = {0};                  //let 100 be the maximum number of teams for both points and goals
int goals[100] = {0}; 

#endif // DATASTORES_H