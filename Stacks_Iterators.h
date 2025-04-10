#ifndef STACKS_ITERATORS_H_INCLUDED
#define STACKS_ITERATORS_H_INCLUDED
using namespace std;

enum class RaceType
{
    Bad_races = 1,
    Elves = 2,
    Humans = 0,
};
class Middle_Earth
{
protected:
    RaceType side;
public:
    string name;
    int year;
    string place;
    Middle_Earth(string n, int y, string p) : name(n), year(y), place(p) {}

    virtual Print() const = 0;
    virtual ~Middle_Earth() = 0;
    virtual RaceType GetSide() const {return side;}
};

class Elves : Middle_Earth
{
public:
    string kind_of_elves;
    int values;
    bool in_films;

    Elves(string n = "Elves", int y = 1000, string p = "West", string k = "Rivendel", int v = 10000, bool in = true)
     : Middle_Earth(n, y, p), kind_of_elves(k), values(v), in_films(in) {}
};

#endif // STACKS_ITERATORS_H_INCLUDED
