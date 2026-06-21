#include "DataStores.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Algorithm #1: Add Match Result 
void addMatchResult(int match_id, int home_id, int away_id, int home_goals, int away_goals) {
    Match newMatch;
    newMatch.id = match_id;
    newMatch.home_team_id = home_id;
    newMatch.away_team_id = away_id;
    newMatch.home_team_goals = home_goals;
    newMatch.away_team_goals = away_goals;

    if (home_goals > away_goals) {
        newMatch.result = 'W';
        points[home_id] += 3; // 3 Points for a win
        points[away_id] += 0; // 0 Points for a loss
    } else if (home_goals == away_goals) {
        newMatch.result = 'D';
        points[home_id] += 1;
        points[away_id] += 1; // 1 Point each for a draw
    } else {
        newMatch.result = 'L';
        points[away_id] += 3;
        points[home_id] += 0; 
    }

    goals[home_id] += home_goals;
    goals[away_id] += away_goals;

    matches.push_back(newMatch);
}




//Algorithm #2: Merge Sort for Teams based on Points
void mergeTeams(vector<Team>& arr, int l, int m, int r) {
    
    vector<Team> left(arr.begin() + l, arr.begin() + m + 1);
    vector<Team> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {
        if (left[i].points >= right[j].points) {                                //Descending order based on points
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

// Main Merge Sort function 
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




// Algorithm #3: Rank Assignment + Tie-Breaking
bool tieBreakerCompare(const Team& a, const Team& b) {
    if (a.points != b.points) {
        return a.points > b.points; // Higher points wins
    }
    // Tie-breaker: Higher Goal Difference (Goals For - Goals Against)
    int gdA = a.goals_for - a.goals_against;
    int gdB = b.goals_for - b.goals_against;
    return gdA > gdB;
}

void assignRanks(vector<Team>& t) {
    if (t.empty()) return;

    // Use stable_sort to keep order of perfectly identical teams preserved
    stable_sort(t.begin(), t.end(), tieBreakerCompare);

    cout << "\n Official Ranked Standings Table \n";
    cout << "-------------------------------------------\n";
    
    // Assign ranks cleanly
    for (int i = 0; i < t.size(); i++) {
        int current_rank = i + 1;
        cout << "Rank " << current_rank << ": " << t[i].name 
                  << " | Points: " << t[i].points 
                  << " | GD: " << (t[i].goals_for - t[i].goals_against) << "\n";
    }
}




// Algorithm #6: Binary Search for Team by ID
bool compareByTeamId(const Team& a, const Team& b) {
    return a.id < b.id;
}

int findTeamById(vector<Team>& t, int target_id) {
    //sorted by ID first
    sort(t.begin(), t.end(), compareByTeamId);

    int low = 0;
    int high = t.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (t[mid].id == target_id) {
            return mid;
        }
        if (t[mid].id < target_id) {
            low = mid + 1; 
        } else {
            high = mid - 1; 
        }
    }

    return -1; // Target team ID not found
}