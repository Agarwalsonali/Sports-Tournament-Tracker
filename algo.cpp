#include "DataStores.h"
#include<iostream>
#include<queue>
#include<string>
#include<utility>
#include<algorithm>
using namespace std;


//Algorithm #4: Top K Teams based on points
void topKTeams(vector<Team>& team, int k) {
    priority_queue<pair<int, string>> pq;

    for (const auto& t : team) {
        pq.push({t.points, t.name});
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




//Algorithm #5: Dutch National Flag
void dutchNF(vector<Match>& matches) {
    int l=0, h=matches.size()-1;                        //Win, Draw, Loss - l,m,h
    int m=0;

    while(m<=h){
        if(matches[m].result == 'W'){
            swap(matches[l], matches[m]);
            l++;
            m++;
        }
        else if(matches[m].result == 'D'){
            m++;
        }
        else{
            swap(matches[m], matches[h]);
            h--;
        }
    }
}




//Algorithm #10: Interval Merging - Match Schedule
vector<pair<int, int>> mergeIntervals(vector<pair<int, int>>& slots) {
    if (slots.empty()) return {};

    // Sort intervals by start time
    sort(slots.begin(), slots.end());
    
    vector<pair<int, int>> merged;
    merged.push_back(slots[0]);

    for (int i = 1; i < slots.size(); i++) {
      
        if (slots[i].first <= merged.back().second) {
            merged.back().second = max(merged.back().second, slots[i].second);
        } else {
            merged.push_back(slots[i]);
        }
    }
    return merged; 
}




//Algiorithm #11: Count Unbeaten Teams
int countUnbeaten(const vector<Team>& t) {
    return count_if(t.begin(), t.end(), [](const Team& team) {
        return team.losses == 0;
    });
}




// Custom comparator
bool compareByGoalDifference(const Team& a, const Team& b) {
    int gdA = a.goals_for - a.goals_against;
    int gdB = b.goals_for - b.goals_against;
    return gdA > gdB; // Descending order of Goal Difference
}

// Algorithm #12: Goal Difference Sort
void goalDifferenceSort(vector<Team>& t) {
    sort(t.begin(), t.end(), compareByGoalDifference);
}




// Algorithm #13: Highest Goal-Scorer
Team highestGoalScorer(const vector<Team>& t) {
    if (t.empty()) {
        return Team{-1, "None", 0, 0, 0, 0, 0, 0, false};
    }

    auto it = max_element(t.begin(), t.end(), [](const Team& a, const Team& b) {
        return a.goals_for < b.goals_for;
    });

    return *it;
}




//Algorithm #14: Remove Eliminated Teams
void removeEliminated(vector<Team>& t) {
    // Move all eliminated teams to the end of the vector
    auto it = remove_if(t.begin(), t.end(), [](const Team& team) {
        return team.eliminated;
    });
    
    // Erase those elements from the vector permanently
    t.erase(it, t.end());
}


//Algorithm #7: Prefix Sum - Cumulative Goals
vector<int> buildPrefixGoals(vector<Match>& matches){
    vector<int> prefix;
    int sum = 0;

    for(auto m : matches){
        int totalGoals = m.home_team_goals + m.away_team_goals;
        sum += totalGoals;
        prefix.push_back(sum);
    }

    return prefix;
}


//Algorithm #8: Maximum Goals Window (Kadane)
int maxGoalWindow(vector<Match>& matches){
    int maxSum = 0;
    int currSum = 0;

    for(auto m : matches){
        int totalGoals = m.home_team_goals + m.away_team_goals;

        currSum += totalGoals;

        if(currSum > maxSum)
            maxSum = currSum;

        if(currSum < 0)
            currSum = 0;
    }

    return maxSum;
}


//Algorithm #9: Sliding Window - Rolling Form
int rollingForm(vector<int>& formPoints, int k){
    if(formPoints.size() < k)
        return -1;

    int sum = 0;

    for(int i=0; i<k; i++){
        sum += formPoints[i];
    }

    int maxForm = sum;

    for(int i=k; i<formPoints.size(); i++){
        sum = sum - formPoints[i-k] + formPoints[i];

        if(sum > maxForm)
            maxForm = sum;
    }

    return maxForm;
}


//Algorithm #15: Two Pointer - Match Goal Pairs
void findGoalPairs(vector<int>& goals, int target){
    sort(goals.begin(), goals.end());

    int left = 0;
    int right = goals.size() - 1;

    cout << "\nPairs with sum " << target << ":\n";

    while(left < right){
        int sum = goals[left] + goals[right];

        if(sum == target){
            cout << goals[left] << " + "
                 << goals[right] << endl;

            left++;
            right--;
        }
        else if(sum < target){
            left++;
        }
        else{
            right--;
        }
    }
}
