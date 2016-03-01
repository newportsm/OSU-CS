#include "characters.h"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <iterator>


Character::Character(){}

std::string Character::random_name()
{
    const char *names[] = { "Cyne", "Nieles", "Dela", "GewyHany", "Anserth", "Siwiu", "Wulfa", "Beorhtio", "Sige", "Sunna", "Lene", "Hone", "Wlfrida", "Phelia", "Elin", "Aehis", "Eneth", "Kypwe",
        "Elell", "Eaded", "Azog", "Gorbul", "Muzga", "Gorkil", "Gashur", "Rishnakh", "Baga", "Snaga", "Orbak", "Lagdush", "Agakh", "Olfil", "Mega", "Orcog", "Bulug", "Bolga", "Lugduf", "Lukil",
        "Lagduf", "Golfimb", "Maraie", "Akshar", "Agos", "Aton", "Vacal", "Loculs", "Napha", "Kima", "Agar", "Surgo", "Juan", "Nicole", "Bob", "Timmy", "Danny", "Paul", "Kenny", "Han Solo",
        "Luke Skywalker", "Hwan Solo", "Bill", "Honem", "Malaph", "Pyraz", "Ryanem", "Paha", "Samua", "Achiel", "Zelah", "Arman", "Azah", "Elincim", "Renc", "Ta", "Coulo", "Lamees", "Flal",
        "Torak", "Shoalli", "Ilarac", "Inetos", "Kea", "Lancol", "Shell", "Sem", "Jeassoe", "Naxelus", "Jilla", "Faer", "Isoma", "Shouk Wes Maclachlan", "Clifford Angelico", "Alfred Toguchi", "Hadley",
        "Francesco Guiggey", "Merrill", "Lesley", "Joe Pellegren", "Lenard Bloyd", "Rolando", "Jospeh Canizares", "Cournoyer", "Barrett Fremming","Robt Lacy Stallard", "Haywood Supplee", "Octavio Legere",
        "Darin Haustein", "Rene Campoverde", "Lon Manasse", "Sydney Hanstine Gisela", "Sherita Fritz", "Emma Toussaint", "Chelsie", "Gisela", "Ping Agonoy", "Myrtie Casilla Mersch", "Conchita Janett Woolems",
        "Lamonica Raden", "Myrle Burgard", "Mellisa Arevalo", "Tessa", "Clementina Daloia", "Erminia Johna", "Giammarino", "Keeley Delahay", "Gertude Jenista", "Gilma Tony Rain","Cassie Plautz",
        "Josephine Zachariah Boone" };
    std::vector<std::string> random_names(names, names + 130);
    int randomIndex = rand() % random_names.size();
    if (used_names.size() >= 120) //just in case the users decides to make a huge tournament, names will then have to be reused.
    {
        used_names.clear();
    }
    return random_names[randomIndex];
}

void Character::set_name(std::string team_name)
{
    bool valid_name = false;
    bool name_used = false;
    std::string randomized_name;
    while (!valid_name)
    {
        randomized_name = random_name();
        for (size_t i = 0; i < used_names.size(); i++)
        {
            if (randomized_name == used_names[i])
            {
                name_used = true;
            }
        }
        if (!name_used)
        {
            valid_name = true;
        }
    }
    used_names.push_back(randomized_name);
    name.insert(0, " the ");
    name.insert(0, randomized_name);
    name += " (";
    name += team_name;
    name += ")";
}

int Character::dice_roll(int number_rolls, int number_sides)
{
    int result = 0;
    for (int i = 0; i < number_rolls; i++)
    {
        result += (rand() % number_sides) + 1;
    }
    return result;
}

std::string Character::get_name()
{
    return name;
}

int Character::get_creature_type()
{
    return creature_type;
}

bool Character::special_used()
{
    return special_on;
}

void Character::recover_strength()
{
    int coin_flip = rand() % 2; //50% chance of either 0 or 1
    int recover_points = ((max_strength_points - current_strength_points) / 2);
    if (coin_flip == 0)
    {
        current_strength_points += recover_points; //character recovers about 50% of the damage he lost
    }
    current_strength_points += 1; //This is always happens for any character that wins a match.
}

int Character::get_points()
{
    return points;
}

int Character::get_number_wins()
{
    return number_wins;
}

Goblin::Goblin() : Character()
{
    name = "Goblin";
    armor = 3;
    max_strength_points = 8;
    current_strength_points = 8;
    creature_type = 1; //flag to alert combat_sim() this is a goblin
    special_on = false;
    number_wins = 0;
    points = 0;
}

int Goblin::attack()
{
    int attack = dice_roll(2, 6); //two rolls of 6-sided dice
    if (attack == 12)
    {
        special_on = true;
    }
    return attack;
}

int Goblin::defend(int enemy_attack)
{
    int defense = dice_roll(1, 6); // one roll of 6-sided dice
    return ((enemy_attack - defense) - armor);
}

void Goblin::reset()
{
    armor = 3;
    max_strength_points = 8;
    current_strength_points = 8;
    creature_type = 1; //flag to alert combat_sim() this is a goblin
    special_on = false;
    number_wins = 0;
    points = 0;
}

Barbarian::Barbarian() : Character()
{
    name = "Barbarian";
    armor = 0;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

int Barbarian::attack()
{
    return dice_roll(2, 6); //two rolls of 6-sided dice
}

int Barbarian::defend(int enemy_attack)
{
    int defense = dice_roll(2, 6); // two rolls of 6-sided dice
    return ((enemy_attack - defense) - armor);
}

void Barbarian::reset()
{
    armor = 0;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

Reptile_people::Reptile_people() : Character()
{
    name = "Reptilian";
    armor = 7;
    max_strength_points = 18;
    current_strength_points = 18;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

int Reptile_people::attack()
{
    return dice_roll(3, 6); //three rolls of 6-sided dice
}

int Reptile_people::defend(int enemy_attack)
{
    int defense = dice_roll(1, 6); // one roll of 6-sided dice
    return ((enemy_attack - defense) - armor);
}

void Reptile_people::reset()
{
    armor = 7;
    max_strength_points = 18;
    current_strength_points = 18;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

Blue_men::Blue_men() : Character()
{
    name = "Blue men";
    armor = 3;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

int Blue_men::attack()
{
    return dice_roll(2, 10); //two rolls of 10-sided dice
}

int Blue_men::defend(int enemy_attack)
{
    int defense = dice_roll(3, 6); // three rolls of 6-sided dice
    return ((enemy_attack - defense) - armor);
}

void Blue_men::reset()
{
    armor = 3;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 0;
    special_on = false;
    number_wins = 0;
    points = 0;
}

Shadow::Shadow() : Character()
{
    name = "Shadow";
    armor = 0;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 2; //flag to alert combat_sim() this is a shadow
    special_on = false;
    number_wins = 0;
    points = 0;
}

int Shadow::attack()
{
    return dice_roll(2, 10); //two rolls of 10-sided dice
}

int Shadow::defend(int enemy_attack)
{
    int shadow_warp = rand() % 2; //50% chance of either 0 or 1
    if (shadow_warp == 0)
    {
        special_on = true;
        return 0; //No damage done
    }
    else
    {
        int defense = dice_roll(1, 6); // one roll of 6-sided dice
        special_on = false;
        return ((enemy_attack - defense) - armor);
    }
}

void Shadow::reset()
{
    armor = 0;
    max_strength_points = 12;
    current_strength_points = 12;
    creature_type = 2; //flag to alert combaat_sim() this is a shadow
    special_on = false;
    number_wins = 0;
    points = 0;
}