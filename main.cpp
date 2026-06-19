#include "DataStores.h"
#include "algo.cpp"
#include<iostream>
using namespace std;

void printMatches(vector<Match>& match) {
    for (const auto& m : match) {
        cout << "[Match ID: " << m.id << " | Result: " << m.result << "] ";
    }
    cout << "\n";
}

int main(){
    teams.push_back({1, "Real Madrid", 15, 12, 4, 5, 0, 1, false});
    teams.push_back({2, "Barcelona",   12, 10, 6, 4, 0, 2, false});
    teams.push_back({3, "Man City",    18, 20, 5, 6, 0, 0, false});
    teams.push_back({4, "Bayern Munich", 9,  8, 9, 3, 0, 3, false});

    topKTeams(teams, 3);

    matches.push_back({101, 1, 2, 2, 1, 'W', 0, 90});  // Win
    matches.push_back({102, 3, 4, 1, 1, 'D', 0, 90});  // Draw
    matches.push_back({103, 5, 6, 0, 3, 'L', 0, 90});  // Loss
    matches.push_back({104, 2, 4, 3, 2, 'W', 0, 90});  // Win
    matches.push_back({105, 1, 5, 0, 0, 'D', 0, 90});  // Draw
    matches.push_back({106, 6, 2, 1, 4, 'L', 0, 90});  // Loss

    cout << "Before Dutch National Flag Sorting\n";
    printMatches(matches);

   
    dutchNF(matches);

    cout << "\nAfter Dutch National Flag Sorting\n";
    printMatches(matches);

    return 0;
}
