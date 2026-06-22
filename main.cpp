#include "DataStores.h"
#include "algo.cpp"
#include "crudOps.cpp"
#include<iostream>
using namespace std;

void printMatches(vector<Match>& match) {
    for (const auto& m : match) {
        cout << "[Match ID: " << m.id << " | Result: " << m.result << "] ";
    }
    cout << "\n";
}

void printTeamsTable() {
    for (const auto& team : teams) {
        cout << team.name << " (Points: " << team.points << ")\n";
    }
}

void printActiveTeams() {
    for (const auto& team : teams) {
        cout << team.name << " | Losses: " << team.losses 
                  << " | Eliminated: " << (team.eliminated ? "Yes" : "No") << "\n";
    }
}

int main(){

    // Add match result: Match 1, Team 1 vs Team 2 (Score: 3 - 1)
    addMatchResult(1, 1, 2, 3, 1);
    
    // Add match result: Match 2, Team 2 vs Team 3 (Score: 2 - 2)
    addMatchResult(2, 2, 3, 2, 2);

    cout << "--- Add Match Results ---\n";
    cout << "Team 1 Points: " << points[1] << " | Goals: " << goals[1] << "\n"; // Expected: 3 pts, 3 goals
    cout << "Team 2 Points: " << points[2] << " | Goals: " << goals[2] << "\n"; // Expected: 1 pt, 3 goals
    cout << "Team 3 Points: " << points[3] << " | Goals: " << goals[3] << "\n"; // Expected: 1 pt, 2 goals

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

    mergeSortTeams(teams, 0, teams.size() - 1);

    cout << "\n--- Sorted Leaderboard (Merge Sort) ---\n";
    printTeamsTable();

    teams.clear();
    // Points equal (12), but GD differs
    teams.push_back({1, "Chelsea", 12, 8, 6, 4, 0, 2, false});          // GD = +2
    teams.push_back({2, "Man United", 12, 10, 4, 4, 0, 2, false});        // GD = +6
    teams.push_back({3, "Liverpool", 18, 15, 3, 6, 0, 0, false});         // Clear Leader
    teams.push_back({4, "Arsenal", 6, 5, 9, 2, 0, 4, false});

    assignRanks(teams);

    teams.clear();
    // Add teams out of order by ID
    teams.push_back({45, "Arsenal", 10, 0, 0, 0, 0, 0, false});
    teams.push_back({12, "Chelsea", 14, 0, 0, 0, 0, 0, false});
    teams.push_back({89, "Man City", 18, 0, 0, 0, 0, 0, false});
    teams.push_back({23, "Liverpool", 7, 0, 0, 0, 0, 0, false});

    int search_id = 23;
    int index = findTeamById(teams, search_id);

    cout << "--- Binary Search ID Lookup ---\n";
    if (index != -1) {
        cout << "Found Team! Name: " << teams[index].name 
                  << " | ID: " << teams[index].id 
                  << " | Points: " << teams[index].points << "\n";
    } else {
        cout << "Team with ID " << search_id << " not found.\n";
    }


    teams.clear();
    
    teams.push_back({1, "Invincibles FC", 10, 0, 0, 3, 1, 0, false}); // Unbeaten
    teams.push_back({2, "Relegation United", 2, 0, 0, 0, 2, 5, true}); // Eliminated
    teams.push_back({3, "Solid Crew FC", 6, 0, 0, 2, 0, 1, false});    // 1 Loss
    teams.push_back({4, "Lucky Drawers", 4, 0, 0, 0, 4, 0, false});   // Unbeaten

    cout << "\n--- Initial Team List ---\n";
    printActiveTeams();

    int unbeatenCount = countUnbeaten(teams);
    cout << "\n Total Unbeaten Teams: " << unbeatenCount <<endl;

    // Test Algorithm #14
    cout << "\n Removing Eliminated Teams...\n";
    removeEliminated(teams);

    cout << "\n--- Final Active Team List ---\n";
    printActiveTeams(); 

    teams.clear();
    
    teams.push_back({2, "Team Beta",  10, 20, 18, 0, 0, 0, false}); // GD = +2
    teams.push_back({1, "Team Alpha", 10, 15, 5, 0, 0, 0, false});  // GD = +10
    teams.push_back({3, "Team Gamma", 10, 5, 12, 0, 0, 0, false});  // GD = -7

    cout << "\n--- Before Goal Difference Sort ---\n";
    for (const auto& team : teams) {
        cout << team.name << " (GD: " << (team.goals_for - team.goals_against) << ")\n";
    }

    goalDifferenceSort(teams);

    cout << "\n--- After Goal Difference Sort ---\n";
    for (const auto& team : teams) {
        cout << team.name << " (GD: " << (team.goals_for - team.goals_against) << ")\n";
    }

    vector<pair<int, int>> match_slots = {{10, 12}, {11, 13}, {14, 15}, {9, 10}};

    cout << "\n--- Merging Match Schedule Slots ---\n";
    vector<pair<int, int>> clean_schedule = mergeIntervals(match_slots);

    for (const auto& slot : clean_schedule) {
        cout << "Occupied Broadcast Window: [" << slot.first << " -> " << slot.second << "]\n";
    }


    teams.clear();
    
    teams.push_back({1, "Real Madrid", 12, 14, 5, 4, 0, 1, false});
    teams.push_back({2, "Man City",    15, 22, 8, 5, 0, 0, false}); // Highest scorer
    teams.push_back({3, "Bayern",      9,  11, 9, 3, 0, 3, false});

    Team topScorer = highestGoalScorer(teams);

    cout << "\n--- Golden Boot Team Award ---\n";
    cout << "Highest Scoring Team: " << topScorer.name 
              << " with " << topScorer.goals_for << " goals scored!\n";

    return 0;
}



