#ifndef MATCH_H
#define MATCH_H

class Match {
private:
    int id;
    int home_team_id;
    int away_team_id;
    int home_goals;
    int away_goals;
    char result; 
    int start_time;
    int end_time;

public:
    Match(int id, int home_id, int away_id, int h_goals, int a_goals, int start, int end)
        : id(id), home_team_id(home_id), away_team_id(away_id), 
          home_goals(h_goals), away_goals(a_goals), start_time(start), end_time(end) {
        if (home_goals > away_goals) result = 'W';
        else if (home_goals == away_goals) result = 'D';
        else result = 'L';
    }

    //Getters
    int getId() const { return id; }
    int getHomeTeamId() const { return home_team_id; }
    int getAwayTeamId() const { return away_team_id; }
    int getHomeGoals() const { return home_goals; }
    int getAwayGoals() const { return away_goals; }
    char getResult() const { return result; }
    int getStartTime() const { return start_time; }
    int getEndTime() const { return end_time; }
};

#endif