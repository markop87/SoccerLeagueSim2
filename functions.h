#ifndef CUSTOM
#define CUSTOM

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <iomanip>

struct League {
    int id;
    std::string name;
    int country;
    int tier;
    int teams;
    int legs;

    League (int league_id, std::string league_name, int league_country, int league_tier, int league_teams, int league_legs);
};

struct Country {
    int id;
    std::string name;
    int confed;

    Country (int country_id, std::string country_name, int confederation);
};

struct Team {
    int id;
    std::string name;
    int type;
    int country;
    int league;
    int rating;

    Team (int team_id, std::string team_name, int team_type, int team_country, int team_league, int team_rating);
};

struct Participant {
    int team;
    int wins;
    int draw;
    int loss;
    int gf;
    int ga;
    int gd;
    int points;

    Participant (int t, int w, int d, int l, int goal_for, int goal_against, int goal_dif, int pts);
};

// sorting league table by points, goal difference and goals scored
struct sortTable
{
    inline bool operator() (const Participant& struct1, const Participant& struct2)
    {
        if(struct1.points != struct2.points)
        {
            return (struct1.points > struct2.points);
        }
        else if(struct1.gd != struct2.gd)
        {
            return (struct1.gd > struct2.gd);
        }
        return struct1.gf > struct2.gf;
    }
};

struct Match {
    int round;
    int home;
    int away;
    int goal1;
    int goal2;

    Match(int match_round, int match_hometeam, int match_awayteam, int match_goalhome, int match_goalaway);
};

struct match_ratings
{
    int match_rating;
    int dices_t1;
    int dices_t2;
    int rolls_t1;
    int rolls_t2;
};


int oneTier (int country_id);

void loadCountries(std::vector <Country> &list_countries);

void wrong_input();

void schedule(std::vector <Participant> &list_teams, std::vector <Match> &matches, int legs);

int goals(int dices, int rolls);

#endif // CUSTOM

