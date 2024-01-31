/*
The program allows for a simple simulation of a football
league or a football match based on dice rolling.
The user can choose from multiple simulations of a single match,
simulation of an existing league or simulation custom league.

Each team is assigned a rating, the higher it is, the stronger the team is.

Match simulation: based on the difference in the rating of two teams,
they are assigned odds and a number of dice. The more chances and
fewer dice, the greater the chance of scoring a goal and winning the match.
*/

#include "functions.h"

// vector containing data for playing matches
// data order:
//    - match rating,
//    - number of dice of the better team,
//    - number of dice of the worse team,
//    - number of chances of the better team,
//    - number of chances of the worse team
std::vector <match_ratings> match_numbers {
    {0, 5, 5, 5, 5},
    {1, 5, 5, 6, 5},
    {2, 5, 6, 6, 5},
    {3, 4, 6, 6, 5},
    {4, 4, 6, 6, 4},
    {5, 4, 7, 6, 4},
    {6, 4, 7, 7, 4},
    {7, 3, 7, 7, 4},
    {8, 3, 7, 8, 4},
    {9, 3, 9, 8, 4},
    {10, 3, 9, 9, 4},
    {11, 3, 9, 9, 3},
    {12, 3, 10, 10, 3},
    {13, 3, 11, 11, 3},
    {14, 3, 12, 12, 3},
    {15, 3, 14, 14, 3},
    {16, 3, 16, 16, 3},
    {17, 3, 18, 18, 3},
    {18, 3, 20, 20, 3},
    {19, 3, 22, 22, 3},
    {20, 2, 22, 22, 2},
    {21, 2, 25, 25, 2},
    {22, 2, 30, 30, 2},
    {23, 2, 35, 35, 2},
    {24, 2, 45, 45, 2},
};


// A function that changes the match rating if the difference in team
// ratings is greater than 9. Subsequent match rating values are assigned
// every five points of difference between teams.

int real_rating(int rat1, int rat2)
{
    int rating = abs(rat1 - rat2);

    if(rating > 9 && rating < 15) { rating = 10; }
    else if(rating > 14 && rating < 20) { rating = 11; }
    else if(rating > 19 && rating < 25) { rating = 12; }
    else if(rating > 24 && rating < 30) { rating = 13; }
    else if(rating > 29 && rating < 35) { rating = 14; }
    else if(rating > 34 && rating < 40) { rating = 15; }
    else if(rating > 39 && rating < 45) { rating = 16; }
    else if(rating > 44 && rating < 50) { rating = 17; }
    else if(rating > 49 && rating < 55) { rating = 18; }
    else if(rating > 54 && rating < 60) { rating = 19; }
    else if(rating > 59 && rating < 65) { rating = 20; }
    else if(rating > 64 && rating < 70) { rating = 21; }
    else if(rating > 69 && rating < 80) { rating = 22; }
    else if(rating > 79 && rating < 90) { rating = 23; }
    else if(rating > 89) { rating = 24; }

    return rating;
}


// Descriptions of all functions are included in the functions.cpp file

std::vector <Country> countries;

std::vector <League> leagues;

std::vector <Team> teams;

std::vector <Participant> participants;

std::vector <Match> matches;

void loadCountries(std::vector <Country> &list_countries);

void loadLeagues(std::vector <League> &list_leagues);

void loadTeams(std::vector <Team> &list_teams);

bool hasLeague (int country_id);

int oneTier (int country_id);

void wrong_input();

void schedule(std::vector <Participant> &list_teams, std::vector <Match> &matches, int legs);

int goals(int dices, int rolls);



int main()
{
    loadLeagues(leagues); // loading league data
    loadCountries(countries); // loading countries data
    loadTeams(teams); // loading teams data

    char again {'Y'}; // at the end, the user can start from the beginning

    while(again == 'Y' || again == 'y')
    {
        // variables for navigating the menu
        int menu_level {1}, menu1 {-1}, menu2 {-1}, menu3 {-1}, menu4 {-1}, menu5 {-1}, menu6 {-1};

        int teams_number {2}; // variable to holds
        int legs {1}; // a variable that determines how many times teams face each other
        int single_match {0}; // with the single match option, the user can choose the number of simulations
        std::vector <int> options {}; // a vector that saves the available options in the menu
        char confirm; // at the end, the user must confirm his choice

        do
        {
            confirm = 'N';


            if(menu_level == 1)
            {
                // vector cleaning
                participants.clear();
                matches.clear();
                menu3=-1;

                system("CLS"); //clearing screen

                //menu
                std::cout << "1. Match\n2. Preset league\n3. Custom league\n0. Quit\n\nChoice: ";
                std::cin >> menu1;

                options = {0, 1, 2, 3}; // vector of possible options to choose


                if(std::cin.fail() || !std::count(options.begin(), options.end(), menu1))
                {
                    wrong_input();
                    menu1 = -1;
                }
                else if(menu1 > 0) { menu_level++; }
                else if(menu1 == 0) { return 0; }


                // if the user selects a single match, user must
                // input how many simulations program have to perform
                if(menu1 == 1)
                {
                    bool pass {true};
                    do
                    {
                        teams_number = 2;
                        std::cout << "\nHow many simulations (1-1000): ";
                        std::cin >> single_match;

                        if(std::cin.fail() || (single_match < 1 || single_match > 1000))
                        {
                            wrong_input();
                            pass = false;
                        }
                        else pass = true;
                    } while(!pass);
                }

                // if the user selects a custom league, user must
                // input how many teams will be in league
                if(menu1 == 3)
                {
                    bool pass {true};

                    do
                    {
                        std::cout << "\nHow many teams (3-24): ";
                        std::cin >> teams_number;

                        if(std::cin.fail() || (teams_number < 3 || teams_number > 24))
                        {
                            wrong_input();
                            pass = false;
                        }
                        else pass = true;

                        if(pass)
                        {
                            std::cout << "How many legs (1-6): ";
                            std::cin >> legs;

                            if(std::cin.fail() || (legs < 1 || legs > 6))
                            {
                                wrong_input();
                                pass = false;
                            }
                            else pass = true;
                        }

                    } while(!pass);
                }
            }

            // in menu level 2, the user selects national teams or clubs
            else if(menu_level == 2)
            {
                menu4 = -1; menu5 = -1; menu6 = -1; // resetting menu options if the user returns from higher menu levels

                if(menu1 != 2)
                {
                    do
                    {
                        system("CLS"); // cleaning screen

                        std::cout << "1. National teams\n2. Club teams\n0. Go back\n\nChoice: ";
                        std::cin >> menu2;

                        options = {0, 1, 2 }; // vector of possible options to choose

                        //checking input
                        if(std::cin.fail() || !std::count(options.begin(), options.end(), menu2))
                        {
                            wrong_input();
                            menu2 = -1;
                        }
                        else if(menu2 > 0) { menu_level++; }
                        else if(menu2 == 0) { menu_level--; }
                    } while(menu_level == 2);
                }
                // if a preset league is selected, menu level 2 will be skipped
                // because preset league applies only to clubs
                else if(menu1 == 2 && menu3 != 0)
                {
                    menu2 = 2;
                    menu_level++;
                }
                else if(menu1 == 2 && menu3 == 0)
                {
                    menu_level--;
                    menu3 = -1;
                }
            }

            // on the 3rd level of the menu, the user selects the continent from which he wants to select a team
            else if(menu_level == 3)
            {
                do
                {
                    system("CLS"); // cleaning screen
                    menu4 = -1; menu5 = -1; menu6 = -1; // resetting menu options if the user returns from higher menu levels

                    std::cout << "1. Europe\n2. South America\n3. North America\n4. Africa\n5. Asia\n6. Oceania\n0. Go back\n\nChoice: ";
                    std::cin >> menu3;

                    options = { 0, 1, 2, 3, 4, 5, 6 }; // vector of possible options to choose

                    if(std::cin.fail() || !std::count(options.begin(), options.end(), menu3))
                    {
                        wrong_input();
                        menu3 = -1;
                    }
                    //changing menu level
                    else if(menu3 > 0) { menu_level++; }
                    else if(menu3 == 0) { menu_level--; }
                } while(menu_level == 3);
            }

            // on the 4th level of the menu, user selects the country
            else if(menu_level == 4)
            {
                do
                {
                    menu6 = -1;
                    if(menu2 != 1)
                    {
                        menu5 = -1; menu6 = -1; // resetting menu options
                        system("CLS"); // cleaning screen

                        options = {0}; // vector of possible options to choose

                        // displaying nations from selected continent in menu level 3
                        // if they have league in database
                        for(auto nation : countries)
                        {
                            if(nation.confed == menu3 && hasLeague(nation.id))
                            {
                                std::cout << std::setw(4) << nation.id << ". " << nation.name << std::endl;
                                options.push_back(nation.id); // adding option to choose to options vector
                            }
                        }

                        std::cout << "   0. Go back\n\n";

                        std::cout << "Choice: ";
                        std::cin >> menu4;

                        // checking input
                        if(std::cin.fail() || !std::count(options.begin(), options.end(), menu4))
                        {
                            wrong_input();
                            menu4 = -1;
                        }
                        else if(menu4 > 0) { menu_level++; }
                        else if(menu4 == 0) { menu_level--; }
                    }

                    // skipping this menu level if user selected national teams
                    else if(menu2 == 1 && menu5 != 0)
                    {
                        menu_level++;
                    }
                    else if(menu2 == 1 && menu5 == 0)
                    {
                        menu_level--;
                    }

                } while(menu_level == 4);
            }

            // on the 5th level of the menu, user selects league from selected country
            else if(menu_level == 5)
            {

                do
                {
                    if(menu4 != -1)
                    {
                        system("CLS"); // cleaning screen

                        options = {0}; // vector of possible options to choose

                        // checking whether a given country has more then one  in the database
                        // if don't, this level will be skipped
                        if(oneTier(menu4) > 0 && menu6 != 0)
                        {
                            menu5 = oneTier(menu4);
                            menu_level++;
                        }
                        else if(oneTier(menu4) > 0 && menu6 == 0)
                        {
                            menu_level--;
                        }
                        // displaying all leagues from selected country
                        else
                        {
                            for(auto comp : leagues)
                            {
                                if(comp.country == menu4)
                                {
                                    std::cout << std::setw(4) << comp.id << ". " << comp.name << "\n";
                                    options.push_back(comp.id); // adding option to choose to options vector
                                }
                            }

                            std::cout << "   0. Go back\n\n";
                            std::cout << "Choice: ";
                            std::cin >> menu5;

                            if(std::cin.fail() || !std::count(options.begin(), options.end(), menu5))
                            {
                                wrong_input();
                            }
                            else if(menu5 > 0) { menu_level++; }
                            else if(menu5 == 0) { menu_level--; }
                        }
                    }
                    // skipping this menu level if user select national teams
                    else if(menu4 == -1 && menu6 != 0)
                    {
                        menu_level++;
                    }
                    else if(menu2 == 1 && menu6 == 0)
                    {
                        menu5 = 0;
                        menu_level--;
                    }

                } while(menu_level == 5);
            }

            // on the 6th level of the menu, user selects teams
            else if(menu_level == 6)
            {
                std::vector <int> options {0};

                if(menu1 == 1 || menu1 == 3)
                {
                    do
                    {
                        system("CLS"); // cleaning screen

                        options = {0}; // vector of possible options to choose

                        // displaying teams
                        for(auto team : teams)
                        {

                            // for national teams
                            if(menu2 == 1)
                            {
                                if(team.country == menu3 && team.type == menu2)
                                {
                                    std::cout << std::setw(4) << team.id << ". " << team.name << "\n";
                                    options.push_back(team.id);
                                }
                            }

                            // for clubs
                            else if((menu1 == 1 && menu2 == 2) || menu1 == 3)
                            {
                                if(team.league == menu5)
                                {
                                    std::cout << std::setw(4) << team.id << ". " << team.name << "\n";
                                    options.push_back(team.id);
                                }
                            }
                        }

                        std::cout << "   0. Go back\n\n";

                        // displaying selected teams
                        std::cout << "Participants: " << participants.size() << "/" << teams_number << "\n";

                        for(auto chosen : participants)
                        {
                            std::cout << std::setw(4) << chosen.team << ". " << teams[chosen.team].name << "\n";
                        }

                        if(participants.size() > 0)
                        {
                            std::cout << "*enter team number to remove it*\n";
                        }

                        std::cout << "\nChoice: ";
                        std::cin >> menu6;

                        bool check {false};
                        int del {0};

                        // deleted selected team from participants list
                        for(unsigned r = 0; r < participants.size(); r++)
                        {
                            if(participants[r].team == menu6)
                            {
                                check = true;
                                del = r;
                            }
                        }

                        // wrong input information
                        if((std::cin.fail() || !std::count(options.begin(), options.end(), menu6)) && !check)
                        {
                            wrong_input();
                        }
                        // adding selected team to participants list
                        else if(std::count(options.begin(), options.end(), menu6) && menu6 > 0 && !check)
                        {
                            Participant chosenTeam(menu6, 0, 0, 0, 0, 0, 0, 0);
                            participants.push_back(chosenTeam);
                        }
                        // deleting selected team from participants list
                        else if(check)
                        {
                            participants.erase (participants.begin()+del);
                        }
                        // decreasing menu level
                        else if(menu6 == 0) { menu_level--; }

                        // confirming selection
                        if(participants.size() == (unsigned)teams_number)
                        {
                            system("CLS"); // cleaning screen

                            // displaying selected teams
                            for(auto chosen : participants)
                            {
                                std::cout << teams[chosen.team].name << "\n";
                            }

                            std::cout << "\nDo you confirm list of participants?\n";
                            std::cout << "If don't, last team from a list will be deleted.\n\n";
                            std::cout << "Confirm? Enter Y or y to progress: ";
                            std::cin >> confirm;

                            // if the user confirms his choice, the program will exit the menu loop
                            if(confirm == 'y' || confirm == 'Y')
                            {
                                menu_level = 0;
                            }
                            else participants.pop_back();
                        }

                    } while(menu_level == 6);
                }

                // if preset league is selected, teams from selected league will be added automatically
                // and the user will not select teams
                else if(menu1 == 2)
                {
                    system("CLS"); // cleaning screen
                    teams_number = leagues[menu5-1].teams; // checking the number of teams in the selected league
                    legs = leagues[menu5-1].legs; // checking the number of legs in the selected league

                    // adding teams to the list of participants
                    for(auto team : teams)
                    {
                        if(team.league == menu5)
                        {
                            Participant chosenTeam(team.id, 0, 0, 0, 0, 0, 0, 0);
                            participants.push_back(chosenTeam);
                        }
                    }

                    // when the number of teams matches, the program will exit the menu loop
                    if(participants.size() == (unsigned)teams_number)
                    {
                        menu_level = 0;
                    }
                }
            }

        } while (menu_level != 0);

        system("CLS"); // cleaning screen

        char save {'x'}; // variable for asking about saving data to a file

        if(menu1 == 1)
        {
            std::cout << "Single match\n\n";

            // variables for statistics
            int team1_roll, team2_roll, team1_dice, team2_dice;
            int home_win {0}, away_win {0}, draw {0}, home_goals {0}, away_goals {0};

            // match rating calculation
            int match_rating = real_rating(teams[participants[0].team].rating, teams[participants[1].team].rating);

            // assigning dice and chances to teams according to the "match_numbers" vector
            for(auto dicerolls : match_numbers)
            {
                if(dicerolls.match_rating == match_rating)
                {
                    if(teams[participants[0].team].rating - teams[participants[1].team].rating >= 0)
                    {
                        team1_dice = dicerolls.dices_t1;
                        team2_dice = dicerolls.dices_t2;
                        team1_roll = dicerolls.rolls_t1;
                        team2_roll = dicerolls.rolls_t2;
                    }
                    else
                    {
                        team1_dice = dicerolls.dices_t2;
                        team2_dice = dicerolls.dices_t1;
                        team1_roll = dicerolls.rolls_t2;
                        team2_roll = dicerolls.rolls_t1;
                    }
                }
            }

            for(int m = 1; m <= single_match; m++)
            {
                int goal1 = goals(team1_dice, team1_roll); // rolling dice for home team
                int goal2 = goals(team2_dice, team2_roll); // rolling dice for away team

                // displaying results
                std::cout << std::setw(4) << m << ": " << teams[participants[0].team].name << " - " << teams[participants[1].team].name
                << " " << goal1 << ":" << goal2 << "\n";

                // counting statistics
                home_goals += goal1;
                away_goals += goal2;
                if(goal1 > goal2) { home_win++; }
                else if(goal1 < goal2) { away_win++; }
                else { draw++; }

            }

            // displaying statistics from all simulations
            std::cout << "\n" << teams[participants[0].team].name << ": " << home_win << "\n";
            std::cout << teams[participants[1].team].name << ": " << away_win << "\n";
            std::cout << "Draws: " << draw << "\n";
            std::cout << "Goals: " << home_goals << ":" << away_goals << "\n";
            std::cout << "Goal difference: " << home_goals - away_goals << "\n";
        }
        else if (menu1 != 1)
        {
            // displaying league name
            if(menu1 == 2)
            {
                std::cout << countries[menu4-1].name << " | " << leagues[menu5-1].name << "\n";
            }
            else if (menu1 == 3)
            {
                std::cout << "Custom League" << "\n";
            }

            schedule(participants, matches, legs); // creating schedule

            // calculating how many rounds will be played
            int gameweeks = (participants.size() - 1) * legs;

            for(int r = 1; r <= gameweeks; r++)
            {
                std::cout << "\n== MATCHDAY " << r << " ==\n";
                for(auto& game : matches)
                {
                    if(game.round == r)
                    {
                        int match_rat;
                        int team1_roll, team2_roll, team1_dice, team2_dice;

                        // match rating calculation
                        match_rat = real_rating(teams[game.home].rating, teams[game.away].rating);

                        // assigning dice and chances to teams according to the "match_numbers" vector
                        for(auto dicerolls : match_numbers)
                        {
                            if(dicerolls.match_rating == match_rat)
                            {
                                if(teams[game.home].rating - teams[game.away].rating >= 0)
                                {
                                    team1_dice = dicerolls.dices_t1;
                                    team2_dice = dicerolls.dices_t2;
                                    team1_roll = dicerolls.rolls_t1;
                                    team2_roll = dicerolls.rolls_t2;
                                }
                                else
                                {
                                    team1_dice = dicerolls.dices_t2;
                                    team2_dice = dicerolls.dices_t1;
                                    team1_roll = dicerolls.rolls_t2;
                                    team2_roll = dicerolls.rolls_t1;
                                }
                            }
                        }

                        game.goal1 = goals(team1_dice, team1_roll); // rolling dice for home team
                        game.goal2 = goals(team2_dice, team2_roll); // rolling dice for away team

                        for(auto& chosen : participants)
                        {
                            //adding points and goals for home team
                            if(game.home == chosen.team)
                            {
                                if(game.goal1 > game.goal2)
                                {
                                    chosen.wins++;
                                    chosen.points += 3;
                                }
                                else if(game.goal1 == game.goal2)
                                {
                                    chosen.draw++;
                                    chosen.points++;
                                }
                                else chosen.loss++;

                                chosen.gf += game.goal1;
                                chosen.ga += game.goal2;
                                chosen.gd += game.goal1 - game.goal2;
                            }

                            //adding points and goals for away team
                            if(game.away == chosen.team)
                            {
                                if(game.goal2 > game.goal1)
                                {
                                    chosen.wins++;
                                    chosen.points += 3;
                                }
                                else if(game.goal1 == game.goal2)
                                {
                                    chosen.draw++;
                                    chosen.points++;
                                }
                                else chosen.loss++;

                                chosen.gf += game.goal2;
                                chosen.ga += game.goal1;
                                chosen.gd += game.goal2 - game.goal1;
                            }

                        }

                        // for better text formatting
                        std::string home_name = teams[game.home].name;
                        int name_lenght = 47 - home_name.size();

                        // displaying result
                        std::cout << teams[game.home].name << " - " << std::setw(name_lenght) << std::left
                        << teams[game.away].name << game.goal1 << ":" << game.goal2 << "\n";
                    }
                }
            }

            // league table sorting
            sort(participants.begin(), participants.end(), sortTable());

            // league table display
            std::cout << "\n=== STANDINGS ===         MP   W   D   L   GOALS    GD  Pts\n";

            int place {1};
            for(auto chosen : participants)
            {
                if(chosen.team != 0)
                {
                    std::cout << std::setw(2) << std::right << place << ". ";
                    std::cout << std::setw(20) << std::left << teams[chosen.team].name;
                    std::cout << std::setw(4) << std::right << chosen.wins + chosen.draw + chosen.loss;
                    std::cout << std::setw(4) << chosen.wins;
                    std::cout << std::setw(4) << chosen.draw;
                    std::cout << std::setw(4) << chosen.loss;
                    std::cout << std::setw(5) << chosen.gf << ":";
                    std::cout << std::setw(4) << std::left << chosen.ga;
                    std::cout << std::setw(4) << std::right << chosen.gd;
                    std::cout << std::setw(5) << chosen.points << "\n";
                    place++;
                }
            }
        }

        // in custom or preset league, the user has the option of saving data to a text file
        if(menu1 != 1)
        {
            std::cout << "\nSave results to a txt file?\nInput 'Y' or 'y' to save: ";
            std::cin >> save;

            if(save == 'Y' || save == 'y')
            {
                std::ofstream saveFile;
                std::string filename;

                // naming file
                std::cout << "\nName the file? ";
                std::cin.clear(); std::cin.sync();
                getline(std::cin, filename);

                filename.append(".txt");

                saveFile.open(filename);

                // the upper part of the file with the name of the league
                std::string compName = leagues[menu5-1].name;
                std::transform(compName.begin(), compName.end(), compName.begin(), ::toupper);

                std::string countryName = countries[menu4-1].name;
                std::transform(countryName.begin(), countryName.end(), countryName.begin(), ::toupper);

                if(menu1 == 2)
                {
                    saveFile << countryName << " | " << compName << "\n";
                } else saveFile << "CUSTOM LEAGUE\n";

                int gameweeks = participants[0].wins + participants[0].draw + participants[0].loss;

                // saving match results
                for(int g = 1; g <= gameweeks; g++)
                {
                    saveFile << "\n=== MATCHDAY " << g << " ===\n";

                    for(auto game : matches)
                    {
                        if(game.round == g)
                        {
                        std::string home_name = teams[game.home].name;
                        int name_lenght = 47 - home_name.size();

                        saveFile << teams[game.home].name << " - " << std::setw(name_lenght) << std::left
                        << teams[game.away].name << game.goal1 << ":" << game.goal2 << "\n";
                        }
                    }
                }

                // saving league table
                saveFile << "\n=== STANDINGS ===         MP   W   D   L   GOALS    GD  Pts\n";

                int place {1};
                for(auto chosen : participants)
                {
                    if(chosen.team != 0)
                    {
                        saveFile << std::setw(2) << std::right << place << ". ";
                        saveFile << std::setw(20) << std::left << teams[chosen.team].name;
                        saveFile << std::setw(4) << std::right << gameweeks;
                        saveFile << std::setw(4) << chosen.wins;
                        saveFile << std::setw(4) << chosen.draw;
                        saveFile << std::setw(4) << chosen.loss;
                        saveFile << std::setw(5) << chosen.gf << ":";
                        saveFile << std::setw(4) << std::left << chosen.ga;
                        saveFile << std::setw(4) << std::right << chosen.gd;
                        saveFile << std::setw(5) << chosen.points << "\n";
                        place++;
                    }
                }

                // information about saving data to text file
                if(saveFile)
                {
                    std::cout << "Saved succesfully!\n";
                } else std::cout << "Error!\n";

                saveFile.close();
            }
        }

        // question about going back to the beginning
        std::cout << "\nAgain?\nInput 'Y' or 'y' to start again: ";
        std::cin >> again;
    }
    return 0;
}
