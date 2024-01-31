#include "functions.h"

// constructors for structs from functions.h file

League::League (int league_id, std::string league_name, int league_country, int league_tier, int league_teams, int league_legs)
{
    id = league_id;
    name = league_name;
    country = league_country;
    tier = league_tier;
    teams = league_teams;
    legs = league_legs;
};

Country::Country (int country_id, std::string country_name, int confederation)
{
    id = country_id;
    name = country_name;
    confed = confederation;
};

Team::Team (int team_id, std::string team_name, int team_type, int team_country, int team_league, int team_rating)
{
    id = team_id;
    name = team_name;
    type = team_type;
    country = team_country;
    league = team_league;
    rating = team_rating;
};

Participant::Participant (int t, int w, int d, int l, int goal_for, int goal_against, int goal_dif, int pts)
{
    team = t;
    wins = w;
    draw = d;
    loss = l;
    gf = goal_for;
    ga = goal_against;
    gd = goal_dif;
    points = pts;
};

Match::Match(int match_round, int match_hometeam, int match_awayteam, int match_goalhome, int match_goalaway)
{
    round = match_round;
    home = match_hometeam;
    away = match_awayteam;
    goal1 = match_goalhome;
    goal2 = match_goalaway;
};

extern std::vector <Country> countries;

extern std::vector <League> leagues;

extern std::vector <Team> teams;

extern std::vector <Participant> participants;

extern std::vector <Match> matches;


// function to check if selected country has a league in database
bool hasLeague (int country_id)
{
    bool league_exist {false};

    for(auto comp : leagues)
    {
        if(comp.country == country_id)
        {
            league_exist = true;
        }
    }

    return league_exist;
};

// function to check if selected country has a more than one tier in database
int oneTier (int country_id)
{
    int counter {0};

    for(auto comp : leagues)
    {
        if(comp.country == country_id)
        {
            counter++;
        }
    }

    if(counter == 1)
    {
        for(auto comp : leagues)
        {
            if(comp.country == country_id)
            {
                return comp.id;
            }
        }

    }
    return 0;
}

//loading country from csv file to countries vector
void loadCountries(std::vector <Country> &list_countries) {

    std::ifstream inputFile;
    inputFile.open("countries.csv");

    std::string line = "";

    while(getline(inputFile, line)) {

        int id;
        std::string name;
        int confed;
        std::string tempString;

        std::stringstream inputString(line);

        getline(inputString, tempString, ';');
        id = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, name, ';');

        getline(inputString, tempString, ';');
        confed = atoi(tempString.c_str());
        tempString = "";

        Country newCountry(id, name, confed);
        countries.push_back(newCountry);

        line = "";
    }

    inputFile.close();
}

//loading leagues from csv file to leagues vector
void loadLeagues(std::vector <League> &list_leagues) {

    std::ifstream inputFile;
    inputFile.open("leagues.csv");

    std::string line = "";

    while(getline(inputFile, line)) {

        int id;
        std::string name;
        int country;
        int tier;
        int teams;
        int legs;
        std::string tempString;

        std::stringstream inputString(line);

        getline(inputString, tempString, ';');
        id = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, name, ';');

        getline(inputString, tempString, ';');
        country = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        tier = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        teams = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        legs = atoi(tempString.c_str());
        tempString = "";

        League newLeague(id, name, country, tier, teams, legs);
        leagues.push_back(newLeague);

        line = "";
    }

    inputFile.close();
}

//loading teams from csv file to teams vector
void loadTeams(std::vector <Team> &list_teams) {

    std::ifstream inputFile;
    inputFile.open("teams.csv");

    std::string line = "";

    while(getline(inputFile, line)) {

        int id;
        std::string name;
        int type;
        int country;
        int league;
        int rating;
        std::string tempString;

        std::stringstream inputString(line);

        getline(inputString, tempString, ';');
        id = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, name, ';');

        getline(inputString, tempString, ';');
        type = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        country = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        league = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ';');
        rating = atoi(tempString.c_str());
        tempString = "";

        Team newTeam(id, name, type, country, league, rating);
        teams.push_back(newTeam);

        line = "";
    }

    inputFile.close();
}

// a function that informs about a bad entry and prepares the program to accept the next entry
void wrong_input()
{
    std::cout << "Wrong input!";
    std::cin.clear();
    std::cin.ignore(256,'\n');
    Sleep(1000);
}

// function for creating a match schedule
void schedule(std::vector <Participant> &list_teams, std::vector <Match> &matches, int legs)
{
    int number_of_teams, gameweek = 1;
    int match_count = 0; //to count number of all added games
    int tie = 0; //to count number of added games in one gameweek

    //counting number of games in a league
    int games = (float)list_teams.size() / 2 * (list_teams.size() - 1) * legs;

    // shuffling the team list
    std::random_shuffle(list_teams.begin(), list_teams.end());

    //checking if the number of teams is even, if not, one empty participant is added
    if(list_teams.size() % 2 != 0)
    {
        Participant newTeam(0, 0, 0, 0, 0, 0, 0, 0);
        list_teams.push_back(newTeam);
    }

    number_of_teams = list_teams.size();

    while(match_count < games)
    {
        if(list_teams[tie].team != 0 && list_teams[number_of_teams-1-tie].team != 0) //to avoid empty participant
        {
            //changing the order of teams every two gameweeks for teams to have home and away games
            if(gameweek % 2 != 0)
            {
                Match nextMatch(gameweek, list_teams[tie].team, list_teams[number_of_teams-1-tie].team, 0, 0);
                matches.push_back(nextMatch);
            }
            else {
                Match nextMatch(gameweek, list_teams[number_of_teams-1-tie].team, list_teams[tie].team, 0, 0);
                matches.push_back(nextMatch);
            }

            match_count++;
        }
        tie++;

        //if all games of one gameweek were added, changing the order of teams on list
        if(tie == number_of_teams / 2)
        {
            int temp = list_teams[number_of_teams-1].team;

            for(int k=number_of_teams-1; k > 1; k--)
            {
                list_teams[k].team = list_teams[k-1].team;
            }

            list_teams[1].team = temp;
            gameweek++;

            tie = 0;
        }
    }
}

int goals(int dices, int rolls)
{
    static std::mt19937 gen(time(nullptr));; // seed the generator
    std::uniform_int_distribution<> distr(1, 6); //range

        int goals {0}, dice_roll;

        for(int r = 0; r < rolls; r++)
        {
            dice_roll = 0;

            //throwing dice and adding value
            for (int i = 0; i < dices; i++)
            {
                dice_roll += distr(gen);
            }

            //if the result of rolling is higher than 2/3 of the maximum result of rolling, the goal is added
            if(dice_roll > dices * 4)
            {
                goals++;
            }
        }

    return goals;
};
