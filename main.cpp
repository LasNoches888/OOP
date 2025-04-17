#include <iostream>
#include "Stacks_Iterators.h"
#include <vector>
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

    virtual void Print() const = 0;
    ~Middle_Earth() {}
    virtual RaceType GetSide() const {return side;}
};

class Elves : public Middle_Earth
{
public:
    string kind_of_elves;
    int values;
    bool in_films;

    Elves(string n = "Elves", int y = 1000, string p = "West", string k = "Rivendel", int v = 10000, bool in = true)
     : Middle_Earth(n, y, p), kind_of_elves(k), values(v), in_films(in) {}
     void Print() const override
     {
         cout<<"One of races: "<<name<<endl;
     }
};


class Bad_races : public Middle_Earth
{
public:
    string kind_of_evil;
    int howmany;
    bool win_or_not;

    Bad_races(string n = "Orcs", int y = 1500, string p = "Mordor", string koe = "Mordor's orcs", int h = 50000, bool w = false )
     : Middle_Earth(n, y, p), kind_of_evil(koe), howmany(h), win_or_not(w) {}
    void Print() const override
     {
         cout<<"One of races: "<<name<<endl;
     }


};

class Human : public Middle_Earth
{
public:
    string Parents_side;
    int value_of_Arnors_sons;


    Human(string n = "Humans", int y = 2000, string p = "Gondor", string p_side = "With good mans", int val_arnor = 1 )
     : Middle_Earth(n, y, p), Parents_side(p_side), value_of_Arnors_sons(val_arnor) {}
        void Print() const override
     {
         cout<<"One of races: "<<name<<endl;
     }

};

Middle_Earth *CreateRace(RaceType type)
{
    Middle_Earth *new_warrior = nullptr;

    if(type == RaceType::Humans)
    {
        new_warrior = new Human;
    }
    else if(type == RaceType::Elves)
    {
        new_warrior = new Elves;
    }
    else
    {
        new_warrior = new Bad_races;
    }
    return new_warrior;
}


void CommonPrint(Iterator<Middle_Earth*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Middle_Earth* current_race = it->GetCurrent();
        current_race->Print();
    }
}

int main()
{
    cout<<"Enter the value of orcs: ";
    int orc_value;
    cin>>orc_value;
    cout<<"Enter the value of elves and humans: ";
    int good_value;
    cin>>good_value;
    cout<<endl;
    cout<<"Enter type of object(0,1 or 2): ";
    int type_1;
    cin>>type_1;
    cout<<endl;
    cout<<"Enter next type of object(0,1 or 2): ";
    int type_2;
    cin>>type_2;
    cout<<endl;
    RaceType type_1_ob = static_cast<RaceType>(type_1);
    RaceType type_2_ob = static_cast<RaceType>(type_2);

    Massive_Stack<Middle_Earth*> Bad_stack;
    for(size_t i = 0; i!=orc_value; i++)
    {
        Middle_Earth *new_bad = CreateRace(type_1_ob);
        Bad_stack.Push(new_bad);
    }
    Iterator<Middle_Earth*> *it = new Massive_Stack_Iterator<Middle_Earth*>(&Bad_stack);
    CommonPrint(it);
    delete it;


    Vector_stack<Middle_Earth*> Good_stack;
    for(size_t i = 0; i!=orc_value; i++)
    {
        Middle_Earth *new_good = CreateRace(type_2_ob);
        Good_stack.Add(new_good);
    }

}





