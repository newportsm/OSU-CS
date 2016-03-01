#pragma once

#include <string>
#include <vector>
#include <iterator>

//Base class
class Character
{
public:
    Character();
    void set_name(std::string name);
    virtual ~Character() {}
    virtual int attack() = 0;
    virtual int defend(int enemy_attack) = 0;
    virtual int dice_roll(int number_rolls, int number_sides);
    void recover_strength();
    std::string get_name();
    int get_creature_type();
    int current_strength_points;
    int number_wins;
    int points;
    bool special_used();
    virtual void reset(){}
    int get_points();
    int get_number_wins();
    std::string random_name();
protected:
    int max_strength_points;
    std::string name;
    int armor;
    int creature_type;
    bool special_on;
    std::vector<std::string> used_names;
};

class Goblin : public Character
{
public:
    Goblin();
    int attack();
    int defend(int enemy_attack);
    void reset();
private:
    bool hamstring;
};

class Barbarian : public Character
{
public:
    Barbarian();
    int attack();
    int defend(int enemy_attack);
    void reset();
};

class Reptile_people : public Character
{
public:
    Reptile_people();
    int attack();
    int defend(int enemy_attack);
    void reset();
};

class Blue_men : public Character
{
public:
    Blue_men();
    int attack();
    int defend(int enemy_attack);
    void reset();
};

class Shadow : public Character
{
public:
    Shadow();
    int attack();
    int defend(int enemy_attack);
    bool warp;
    void reset();
};