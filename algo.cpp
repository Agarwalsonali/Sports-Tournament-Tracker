#include "DataStores.h"
#include<iostream>
#include<queue>
#include<string>
#include<utility>
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