#include "TournamentTracker.h"
#include<iostream>
using namespace std;

void printMatches(vector<Match>& match) {
    for (const auto& m : match) {
        cout << "[Match ID: " << m.getId() << " | Result: " << m.getResult() << "] ";
    }
    cout << "\n";
}

void printTeamsTable(vector<Team>& teams) {
    for (const auto& team : teams) {
        cout << team.getName() << " (Points: " << team.getPoints() << ")\n";
    }
}

void printActiveTeams(vector<Team>& teams) {
    for (const auto& team : teams) {
        cout << team.getName() << " | Losses: " << team.getLosses() 
                  << " | Eliminated: " << (team.isEliminated() ? "Yes" : "No") << "\n";
    }
}

int main(){
    TournamentTracker tracker;

    // Add teams first (indexed by ID)
    tracker.addTeam(0, "Team 1");
    tracker.addTeam(1, "Team 2");
    tracker.addTeam(2, "Team 3");

    // Add match result: Match 1, Team 1 vs Team 2 (Score: 3 - 1)
    tracker.addMatchResult(1, 0, 1, 3, 1);
    
    // Add match result: Match 2, Team 2 vs Team 3 (Score: 2 - 2)
    tracker.addMatchResult(2, 1, 2, 2, 2);

    cout << "--- Add Match Results ---\n";
    cout << "Match results added successfully\n";

    // Clear and add new teams for testing
    tracker.getTeams().clear();
    tracker.addTeam(1, "Real Madrid");
    tracker.addTeam(2, "Barcelona");
    tracker.addTeam(3, "Man City");
    tracker.addTeam(4, "Bayern Munich");

    // Manually set stats for these teams (since they start at 0)
    for (auto& t : tracker.getTeams()) {
        if (t.getId() == 1) t.updateStats(12, 4, 'W');
        if (t.getId() == 2) t.updateStats(10, 6, 'D');
        if (t.getId() == 3) t.updateStats(20, 5, 'W');
        if (t.getId() == 4) t.updateStats(8, 9, 'L');
    }

    tracker.topKTeams(3);

    tracker.getMatches().clear();
    tracker.getMatches().push_back(Match(101, 1, 2, 2, 1, 0, 90));  // Win
    tracker.getMatches().push_back(Match(102, 3, 4, 1, 1, 0, 90));  // Draw
    tracker.getMatches().push_back(Match(103, 5, 6, 0, 3, 0, 90));  // Loss
    tracker.getMatches().push_back(Match(104, 2, 4, 3, 2, 0, 90));  // Win
    tracker.getMatches().push_back(Match(105, 1, 5, 0, 0, 0, 90));  // Draw
    tracker.getMatches().push_back(Match(106, 6, 2, 1, 4, 0, 90));  // Loss

    cout << "Before Dutch National Flag Sorting\n";
    printMatches(tracker.getMatches());

    tracker.dutchNF();

    cout << "\nAfter Dutch National Flag Sorting\n";
    printMatches(tracker.getMatches());

    tracker.sortStandings();

    cout << "\n--- Sorted Leaderboard (Merge Sort) ---\n";
    printTeamsTable(tracker.getTeams());

    tracker.getTeams().clear();
    // Points equal (12), but GD differs
    tracker.addTeam(1, "Chelsea");
    tracker.addTeam(2, "Man United");
    tracker.addTeam(3, "Liverpool");
    tracker.addTeam(4, "Arsenal");

    // Manually set stats
    for (auto& t : tracker.getTeams()) {
        if (t.getId() == 1) t.updateStats(8, 6, 'W');
        if (t.getId() == 2) t.updateStats(10, 4, 'W');
        if (t.getId() == 3) t.updateStats(15, 3, 'W');
        if (t.getId() == 4) t.updateStats(5, 9, 'L');
    }

    tracker.assignRanks();

    tracker.getTeams().clear();
    // Add teams out of order by ID
    tracker.addTeam(45, "Arsenal");
    tracker.addTeam(12, "Chelsea");
    tracker.addTeam(89, "Man City");
    tracker.addTeam(23, "Liverpool");

    int search_id = 23;
    int index = tracker.findTeamById(search_id);

    cout << "--- Binary Search ID Lookup ---\n";
    if (index != -1) {
        cout << "Found Team! Name: " << tracker.getTeams()[index].getName() 
                  << " | ID: " << tracker.getTeams()[index].getId() 
                  << " | Points: " << tracker.getTeams()[index].getPoints() << "\n";
    } else {
        cout << "Team with ID " << search_id << " not found.\n";
    }

    tracker.getTeams().clear();
    
    tracker.addTeam(1, "Invincibles FC");
    tracker.addTeam(2, "Relegation United");
    tracker.addTeam(3, "Solid Crew FC");
    tracker.addTeam(4, "Lucky Drawers");

    // Set stats and elimination status
    for (auto& t : tracker.getTeams()) {
        if (t.getId() == 1) t.updateStats(10, 0, 'W');
        if (t.getId() == 2) { t.updateStats(0, 0, 'L'); t.setEliminated(true); }
        if (t.getId() == 3) t.updateStats(6, 0, 'W');
        if (t.getId() == 4) t.updateStats(4, 0, 'D');
    }

    cout << "\n--- Initial Team List ---\n";
    printActiveTeams(tracker.getTeams());

    int unbeatenCount = tracker.countUnbeaten();
    cout << "\n Total Unbeaten Teams: " << unbeatenCount << endl;

    // Test Algorithm #14
    cout << "\n Removing Eliminated Teams...\n";
    tracker.removeEliminated();

    cout << "\n--- Final Active Team List ---\n";
    printActiveTeams(tracker.getTeams()); 

    tracker.getTeams().clear();
    
    tracker.addTeam(2, "Team Beta");
    tracker.addTeam(1, "Team Alpha");
    tracker.addTeam(3, "Team Gamma");

    // Set stats
    for (auto& t : tracker.getTeams()) {
        if (t.getId() == 1) t.updateStats(15, 5, 'W');
        if (t.getId() == 2) t.updateStats(20, 18, 'W');
        if (t.getId() == 3) t.updateStats(5, 12, 'L');
    }

    cout << "\n--- Before Goal Difference Sort ---\n";
    for (const auto& team : tracker.getTeams()) {
        cout << team.getName() << " (GD: " << team.getGoalDifference() << ")\n";
    }

    tracker.goalDifferenceSort();

    cout << "\n--- After Goal Difference Sort ---\n";
    for (const auto& team : tracker.getTeams()) {
        cout << team.getName() << " (GD: " << team.getGoalDifference() << ")\n";
    }

    vector<pair<int, int>> match_slots = {{10, 12}, {11, 13}, {14, 15}, {9, 10}};

    cout << "\n--- Merging Match Schedule Slots ---\n";
    vector<pair<int, int>> clean_schedule = tracker.mergeIntervals(match_slots);

    for (const auto& slot : clean_schedule) {
        cout << "Occupied Broadcast Window: [" << slot.first << " -> " << slot.second << "]\n";
    }

    tracker.getTeams().clear();
    
    tracker.addTeam(1, "Real Madrid");
    tracker.addTeam(2, "Man City");
    tracker.addTeam(3, "Bayern");

    // Set stats
    for (auto& t : tracker.getTeams()) {
        if (t.getId() == 1) t.updateStats(14, 5, 'W');
        if (t.getId() == 2) t.updateStats(22, 8, 'W');
        if (t.getId() == 3) t.updateStats(11, 9, 'L');
    }

    Team topScorer = tracker.highestGoalScorer();

    cout << "\n--- Golden Boot Team Award ---\n";
    cout << "Highest Scoring Team: " << topScorer.getName() 
              << " with " << topScorer.getGoalsFor() << " goals scored!\n";

    cout << "\n--- Prefix Sum of Goals ---\n";
    vector<int> prefix = tracker.buildPrefixGoals();

    for(int x : prefix){
        cout << x << " ";
    }
    cout << endl;

    cout << "\n--- Maximum Goal Window (Kadane) ---\n";
    cout << "Maximum Goals = " << tracker.maxGoalWindow() << endl;

    cout << "\n--- Sliding Window Rolling Form ---\n";
    vector<int> formPoints = {3,3,1,0,3,1,3};

    cout << "Best Form = "
         << tracker.rollingForm(formPoints, 5)
         << endl;

    cout << "\n--- Two Pointer Goal Pairs ---\n";
    vector<int> goalArray = {1,2,3,4,5,6};

    tracker.findGoalPairs(goalArray, 8);
    
    return 0;
}



