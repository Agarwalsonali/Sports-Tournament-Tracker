#ifndef TOURNAMENT_TRACKER_H
#define TOURNAMENT_TRACKER_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>
#include <utility>
using namespace std;

#include "Team.h"
#include "Match.h"

class TournamentTracker {
private:
    vector<Team> teams;
    vector<Match> matches;


    // Helper for Algorithm #2: Merge Teams based on Points
    void mergeTeams(vector<Team>& arr, int l, int m, int r) {
        vector<Team> left(arr.begin() + l, arr.begin() + m + 1);
        vector<Team> right(arr.begin() + m + 1, arr.begin() + r + 1);

        int i = 0, j = 0, k = l;

        while (i < left.size() && j < right.size()) {
            if (left[i].getPoints() >= right[j].getPoints()) { // Descending order based on points
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }

        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }

    // Helper comparator for Algorithm #3
    static bool tieBreakerCompare(const Team& a, const Team& b) {
        if (a.getPoints() != b.getPoints()) {
            return a.getPoints() > b.getPoints(); // Higher points wins
        }
        // Tie-breaker: Higher Goal Difference
        return a.getGoalDifference() > b.getGoalDifference();
    }

    // Helper comparator for Algorithm #6
    static bool compareByTeamId(const Team& a, const Team& b) {
        return a.getId() < b.getId();
    }

    // Helper comparator for Algorithm #12
    static bool compareByGoalDifference(const Team& a, const Team& b) {
        return a.getGoalDifference() > b.getGoalDifference(); // Descending order of Goal Difference
    }

public:
    // Setup helper to populate internal database
    void addTeam(int id, const string& name) {
        teams.push_back(Team(id, name));
    }

    // Algorithm #1: Add Match Result (O(1) index optimization)
    void addMatchResult(int match_id, int home_id, int away_id, int home_goals, int away_goals) {
        Match newMatch(match_id, home_id, away_id, home_goals, away_goals, 0, 90);

        char result = newMatch.getResult();
        teams[home_id].updateStats(home_goals, away_goals, result);
        teams[away_id].updateStats(away_goals, home_goals, result);

        matches.push_back(newMatch);
    }

    // Algorithm #2: Merge Sort for Teams based on Points
    void mergeSortTeams(vector<Team>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            
            // Divide and conquer
            mergeSortTeams(arr, l, m);
            mergeSortTeams(arr, m + 1, r);
            
            // Combine 
            mergeTeams(arr, l, m, r);
        }
    }

    // Facade wrapper to sort internal standings seamlessly
    void sortStandings() {
        if (!teams.empty()) {
            mergeSortTeams(teams, 0, teams.size() - 1);
        }
    }

    // Algorithm #3: Rank Assignment + Tie-Breaking
    void assignRanks() {
        if (teams.empty()) return;

        // Use stable_sort to keep order of perfectly identical teams preserved
        stable_sort(teams.begin(), teams.end(), tieBreakerCompare);

        cout << "\n Official Ranked Standings Table \n";
        cout << "-------------------------------------------\n";
        
        // Assign ranks cleanly
        for (size_t i = 0; i < teams.size(); i++) {
            int current_rank = i + 1;
            cout << "Rank " << current_rank << ": " << teams[i].getName() 
                      << " | Points: " << teams[i].getPoints() 
                      << " | GD: " << teams[i].getGoalDifference() << "\n";
        }
    }

    // Algorithm #4: Top K Teams based on points via Max-Heap
    void topKTeams(int k) {
        priority_queue<pair<int, string>> pq;

        for (const auto& t : teams) {
            pq.push({t.getPoints(), t.getName()});
        }

        cout << "\n Top " << k << " Teams Leaderboard \n";
        cout << "-----------------------------------\n";

        int count = 0;
        while (!pq.empty() && count < k) {
            cout << count + 1 << ". " << pq.top().second 
                      << " - " << pq.top().first << " pts\n";
            pq.pop();
            count++;
        }
    }

    // Algorithm #5: Dutch National Flag
    void dutchNF() {
        int l = 0, h = matches.size() - 1; // Win, Draw, Loss - l, m, h
        int m = 0;

        while (m <= h) {
            if (matches[m].getResult() == 'W') {
                swap(matches[l], matches[m]);
                l++;
                m++;
            } else if (matches[m].getResult() == 'D') {
                m++;
            } else {
                swap(matches[m], matches[h]);
                h--;
            }
        }
    }

    // Algorithm #6: Binary Search for Team by ID
    int findTeamById(int target_id) {
        // sorted by ID first
        sort(teams.begin(), teams.end(), compareByTeamId);

        int low = 0;
        int high = teams.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (teams[mid].getId() == target_id) {
                return mid;
            }
            if (teams[mid].getId() < target_id) {
                low = mid + 1; 
            } else {
                high = mid - 1; 
            }
        }
        return -1; // Target team ID not found
    }

    // Algorithm #7: Prefix Sum - Cumulative Goals
    vector<int> buildPrefixGoals() {
        vector<int> prefix;
        int sum = 0;

        for (auto m : matches) {
            int totalGoals = m.getHomeGoals() + m.getAwayGoals();
            sum += totalGoals;
            prefix.push_back(sum);
        }
        return prefix;
    }

    // Algorithm #8: Maximum Goals Window (Kadane)
    int maxGoalWindow() {
        int maxSum = 0;
        int currSum = 0;

        for (auto m : matches) {
            int totalGoals = m.getHomeGoals() + m.getAwayGoals();
            currSum += totalGoals;

            if (currSum > maxSum)
                maxSum = currSum;

            if (currSum < 0)
                currSum = 0;
        }
        return maxSum;
    }

    // Algorithm #9: Sliding Window - Rolling Form
    int rollingForm(vector<int>& formPoints, int k) {
        if (formPoints.size() < k)
            return -1;

        int sum = 0;

        for (int i = 0; i < k; i++) {
            sum += formPoints[i];
        }

        int maxForm = sum;

        for (size_t i = k; i < formPoints.size(); i++) {
            sum = sum - formPoints[i - k] + formPoints[i];

            if (sum > maxForm)
                maxForm = sum;
        }
        return maxForm;
    }

    // Algorithm #10: Interval Merging - Match Schedule
    vector<pair<int, int>> mergeIntervals(vector<pair<int, int>>& slots) {
        if (slots.empty()) return {};

        // Sort intervals by start time
        sort(slots.begin(), slots.end());
        
        vector<pair<int, int>> merged;
        merged.push_back(slots[0]);

        for (size_t i = 1; i < slots.size(); i++) {
            if (slots[i].first <= merged.back().second) {
                merged.back().second = max(merged.back().second, slots[i].second);
            } else {
                merged.push_back(slots[i]);
            }
        }
        return merged; 
    }

    // Algorithm #11: Count Unbeaten Teams
    int countUnbeaten() {
        return count_if(teams.begin(), teams.end(), [](const Team& team) {
            return team.getLosses() == 0;
        });
    }

    // Manual setter to flag teams externally before structural purging
    void flagTeamElimination(int id, bool state) {
        for (auto& t : teams) {
            if (t.getId() == id) t.setEliminated(state);
        }
    }

    // Algorithm #12: Goal Difference Sort
    void goalDifferenceSort() {
        sort(teams.begin(), teams.end(), compareByGoalDifference);
    }

    // Algorithm #13: Highest Goal-Scorer
    Team highestGoalScorer() {
        if (teams.empty()) {
            return Team(-1, "None");
        }

        auto it = max_element(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
            return a.getGoalsFor() < b.getGoalsFor();
        });

        return *it;
    }

    // Algorithm #14: Remove Eliminated Teams
    void removeEliminated() {
        // Move all eliminated teams to the end of the vector
        auto it = remove_if(teams.begin(), teams.end(), [](const Team& team) {
            return team.isEliminated();
        });
        
        // Erase those elements from the vector permanently
        teams.erase(it, teams.end());
    }

    // Algorithm #15: Two Pointer - Match Goal Pairs
    void findGoalPairs(vector<int>& goals, int target) {
        sort(goals.begin(), goals.end());

        int left = 0;
        int right = goals.size() - 1;

        cout << "\nPairs with sum " << target << ":\n";

        while (left < right) {
            int sum = goals[left] + goals[right];

            if (sum == target) {
                cout << goals[left] << " + "
                          << goals[right] << endl;

                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    // Expose reference arrays explicitly to let team modules interact safely with tests
    vector<Team>& getTeams() { return teams; }
    vector<Match>& getMatches() { return matches; }
};

#endif