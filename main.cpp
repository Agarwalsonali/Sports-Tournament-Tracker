#include "TournamentTracker.h"
#include <iostream>
#include <vector>
using namespace std;

void printLeaderboardState(const vector<Team>& teams) {
    for (const auto& team : teams) {
        cout << team.getName() << " (Points: " << team.getPoints() 
                  << ", GD: " << team.getGoalDifference() 
                  << ", Goals Scored: " << team.getGoalsFor() << ")\n";
    }
}

int main() {
    TournamentTracker tracker;

    // Seed Data Configurations
    tracker.addTeam(0, "Real Madrid");
    tracker.addTeam(1, "Barcelona");
    tracker.addTeam(2, "Liverpool");
    tracker.addTeam(3, "Man City");

    // Algorithm #1: Add Match Results
    tracker.addMatchResult(0, 1, 3, 1, 10, 12); 
    tracker.addMatchResult(2, 3, 2, 2, 11, 13); 
    tracker.addMatchResult(0, 2, 1, 0, 14, 15); 
    tracker.addMatchResult(3, 1, 4, 2, 16, 18); 

    cout << "--- Initial Seeding Standings ---\n";
    printLeaderboardState(tracker.getTeams());

    // Algorithm #2: Manual Merge Sort Execution
    cout << "\n--- Algorithm #2: Manual Merge Sort Execution ---\n";
    tracker.sortStandings();
    printLeaderboardState(tracker.getTeams());

    // Algorithm #3: Stable Sort Tie-Breaking
    cout << "\n--- Algorithm #3: Stable Sort Tie-Breaking ---\n";
    tracker.assignRanksWithTieBreak();
    printLeaderboardState(tracker.getTeams());

    // Algorithm #4: Top-K Teams via Max-Heap
    cout << "\n--- Algorithm #4: Top-K Teams via Max-Heap ---\n";
    tracker.printTopK(2);

    // Algorithm #5: Dutch National Flag
    cout << "\n--- Algorithm #5: Dutch National Flag ---\n";
    tracker.categorizeMatchResults();

    // Algorithm #6: Binary Search
    cout << "\n--- Algorithm #6: Binary Search Check (Targeting Team ID 2) ---\n";
    int targetIdx = tracker.findTeamIndexById(2);
    if (targetIdx != -1) {
        cout << "Located structural data position index: " << targetIdx << "\n";
    }

    // Algorithm #7: Prefix Sum Array
    cout << "\n--- Algorithm #7: Cumulative Goals Prefix Sum Array ---\n";
    auto sumArray = tracker.buildGoalsPrefixSum();
    for (int value : sumArray) cout << value << " ";
    cout << "\n";

    // Algorithm #8: Kadane's Maximum Goals Window
    cout << "\n--- Algorithm #8: Kadane's Maximum Goals Window ---\n";
    cout << "Maximum sequential match window goals: " << tracker.maxGoalsWindow() << "\n";

    // Algorithm #9: Sliding Window Rolling Form
    cout << "\n--- Algorithm #9: Sliding Window Rolling Form ---\n";
    vector<int> historicalFormPoints = {3, 1, 3, 0, 3, 1, 0};
    tracker.printRollingForm(historicalFormPoints, 3);

    // Algorithm #10: Interval Merging
    cout << "\n--- Algorithm #10: Interval Merging ---\n";
    auto uniqueBlocks = tracker.mergeMatchSchedules();
    for (const auto& block : uniqueBlocks) {
        cout << "[" << block.first << " -> " << block.second << "] ";
    }
    cout << "\n";

    // Algorithm #11: Count Unbeaten Teams
    cout << "\n--- Algorithm #11: Count Unbeaten Teams ---\n";
    cout << "Total Unbeaten Teams remaining: " << tracker.countUnbeatenTeams() << "\n";

    // Algorithm #12: Goal Difference Sort
    cout << "\n--- Algorithm #12: Goal Difference Sort ---\n";
    tracker.sortByGoalDifference();
    printLeaderboardState(tracker.getTeams());

    // Algorithm #13: Highest Goal Scorer
    cout << "\n--- Algorithm #13: Highest Goal Scorer ---\n";
    Team championScorer = tracker.highestGoalScorer();
    cout << "Most clinical group: " << championScorer.getName() << "\n";

    // Algorithm #14: Remove Eliminated Teams
    cout << "\n--- Algorithm #14: Remove Eliminated Teams ---\n";
    tracker.flagTeamElimination(1, true);
    tracker.purgeEliminatedTeams();
    printLeaderboardState(tracker.getTeams());

    // Algorithm #15: Two-Pointer Goal Pairs
    cout << "\n--- Algorithm #15: Two-Pointer Goal Pairs ---\n";
    tracker.findPairsWithGoalTarget(5);

    return 0;
}