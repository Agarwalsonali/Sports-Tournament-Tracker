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

    // Helper for Algorithm #2: Merge process 
    void merge(vector<Team>& arr, int l, int m, int r) {
        vector<Team> left(arr.begin() + l, arr.begin() + m + 1);
        vector<Team> right(arr.begin() + m + 1, arr.begin() + r + 1);
        size_t i = 0, j = 0;
        int k = l;
        while (i < left.size() && j < right.size()) {
            if (left[i].getPoints() >= right[j].getPoints()) arr[k++] = left[i++];
            else arr[k++] = right[j++];
        }
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }

    // Helper for Algorithm #2: Recursive Divide & Conquer
    void mergeSort(vector<Team>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    // Custom comparators
    static bool tieBreakerCompare(const Team& a, const Team& b) {
        if (a.getPoints() != b.getPoints()) return a.getPoints() > b.getPoints();
        return a.getGoalDifference() > b.getGoalDifference();
    }

    static bool compareByTeamId(const Team& a, const Team& b) {
        return a.getId() < b.getId();
    }

    static bool compareByGoalDifference(const Team& a, const Team& b) {
        return a.getGoalDifference() > b.getGoalDifference();
    }

public:
    void addTeam(int id, const string& name) {
        // Ensure vector is large enough to hold team at index id
        if (id >= teams.size()) {
            teams.resize(id + 1);
        }
        teams[id] = Team(id, name);
    }

    // Algorithm #1: Add Match Result — O(1) Updates using Direct Array Indexing
    void addMatchResult(int home_id, int away_id, int home_goals, int away_goals, int start = 0, int end = 0) {
        int match_id = matches.size();
        Match newMatch(match_id, home_id, away_id, home_goals, away_goals, start, end);
        char res = newMatch.getResult();

        // O(1) direct array indexing
        teams[home_id].updateStats(home_goals, away_goals, res);
        char awayRes = (res == 'W') ? 'L' : (res == 'L' ? 'W' : 'D');
        teams[away_id].updateStats(away_goals, home_goals, awayRes);

        matches.push_back(newMatch);
    }

    // Algorithm #2: Merge Sort from Scratch — O(n log n) 
    void sortStandings() {
        if (!teams.empty()) mergeSort(teams, 0, teams.size() - 1);
    }

    // Algorithm #3: Rank Assignment + Tie-Breaking using stable_sort — O(n log² n) 
    void assignRanksWithTieBreak() {
        stable_sort(teams.begin(), teams.end(), tieBreakerCompare);
    }

    // Algorithm #4: Top-K Teams via Max-Heap (priority_queue) — O(n log k) 
    void printTopK(int k) const {
        priority_queue<pair<int, string>> pq;
        for (const auto& team : teams) pq.push({team.getPoints(), team.getName()});

        cout << "\n🏆 Top " << k << " Teams Leaderboard:\n";
        int count = 0;
        while (!pq.empty() && count < k) {
            cout << count + 1 << ". " << pq.top().second << " - " << pq.top().first << " pts\n";
            pq.pop();
            count++;
        }
    }

    // Algorithm #5: Dutch National Flag — O(n) One Pass Result Category Partitioning
    void categorizeMatchResults() {
        int lo = 0, mid = 0, hi = matches.size() - 1;
        while (mid <= hi) {
            if (matches[mid].getResult() == 'W') swap(matches[lo++], matches[mid++]);
            else if (matches[mid].getResult() == 'D') mid++;
            else swap(matches[mid], matches[hi--]);
        }
    }

    // Algorithm #6: Binary Search (Operates on Local Copy to avoid breaking standings display) — O(log n) 
    int findTeamIndexById(int target_id) const {
        vector<Team> sorted_copy = teams;
        sort(sorted_copy.begin(), sorted_copy.end(), compareByTeamId);

        int low = 0, high = sorted_copy.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (sorted_copy[mid].getId() == target_id) {
                return target_id; // Direct indexing: team_id = vector index
            }
            if (sorted_copy[mid].getId() < target_id) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    // Algorithm #7: Prefix Sum Array — O(n) Build, O(1) Range Queries
    vector<int> buildGoalsPrefixSum() const {
        vector<int> prefix(matches.size() + 1, 0);
        for (size_t i = 0; i < matches.size(); ++i) {
            prefix[i + 1] = prefix[i] + (matches[i].getHomeGoals() + matches[i].getAwayGoals());
        }
        return prefix;
    }

    // Algorithm #8: Kadane's Algorithm for Maximum Goals Window — O(n) 
    int maxGoalsWindow() const {
        if (matches.empty()) return 0;
        int max_sum = matches[0].getHomeGoals() + matches[0].getAwayGoals();
        int curr_sum = max_sum;

        for (size_t i = 1; i < matches.size(); i++) {
            int current_goals = matches[i].getHomeGoals() + matches[i].getAwayGoals();
            curr_sum = max(current_goals, curr_sum + current_goals);
            max_sum = max(max_sum, curr_sum);
        }
        return max_sum;
    }

    // Algorithm #9: Sliding Window Rolling Form Engine — O(n) 
    void printRollingForm(const vector<int>& points_history, int k) const {
        if (points_history.size() < static_cast<size_t>(k)) return;
        int window_sum = 0;
        for (int i = 0; i < k; i++) window_sum += points_history[i];
        cout << "Form [0-" << k-1 << "]: " << window_sum << " pts\n";

        for (size_t i = k; i < points_history.size(); i++) {
            window_sum += points_history[i] - points_history[i - k];
            cout << "Form [" << i-k+1 << "-" << i << "]: " << window_sum << " pts\n";
        }
    }

    // Algorithm #10: Interval Merging for Scheduling Conflicts — O(n log n) 
    vector<pair<int, int>> mergeMatchSchedules() const {
        if (matches.empty()) return {};
        vector<pair<int, int>> slots;
        for (const auto& m : matches) slots.push_back({m.getStartTime(), m.getEndTime()});
        
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

    // Algorithm #11: Count Unbeaten Teams (count_if) — O(n) 
    int countUnbeatenTeams() const {
        return count_if(teams.begin(), teams.end(), [](const Team& t) {
            return t.getLosses() == 0;
        });
    }

    // Algorithm #12: Goal Difference Sort with Custom Comparator — O(n log n)
    void sortByGoalDifference() {
        sort(teams.begin(), teams.end(), compareByGoalDifference);
    }

    // Algorithm #13: Highest Goal-Scorer extraction via max_element — O(n)
    Team highestGoalScorer() const {
        if (teams.empty()) return Team(-1, "None");
        auto it = max_element(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
            return a.getGoalsFor() < b.getGoalsFor();
        });
        return *it;
    }

    // Algorithm #14: Remove Eliminated Teams (remove_if + erase) — O(n)
    void flagTeamElimination(int team_id, bool status) {
        // O(1) direct array indexing
        teams[team_id].setEliminated(status);
    }

    void purgeEliminatedTeams() {
        teams.erase(
            remove_if(teams.begin(), teams.end(), [](const Team& t) { return t.isEliminated(); }),
            teams.end()
        );
    }

    // Algorithm #15: Two-Pointer for Goal Targets — O(n log n + n)
    void findPairsWithGoalTarget(int target_goals) const {
        vector<int> team_goals;
        for (const auto& t : teams) team_goals.push_back(t.getGoalsFor());
        sort(team_goals.begin(), team_goals.end());

        int left = 0, right = team_goals.size() - 1;
        cout << "\nTeam pairs matching total target (" << target_goals << "):\n";
        while (left < right) {
            int current = team_goals[left] + team_goals[right];
            if (current == target_goals) {
                cout << "Pair: " << team_goals[left] << " & " << team_goals[right] << "\n";
                left++; right--;
            } else if (current < target_goals) left++;
            else right--;
        }
    }

    // System Utilities
    vector<Team>& getTeams() { return teams; }
    vector<Match>& getMatches() { return matches; }
};

#endif