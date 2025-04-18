#include <iostream>
#include "Stacks_Iterators.h"
#include <vector>
#include <list>
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
    Middle_Earth(string n, int y, string p, RaceType s) : name(n), year(y), place(p), side(s) {}

    virtual void Print() const = 0;
    ~Middle_Earth() {}
    virtual RaceType GetSide() const {return side;}

    bool IsGood() const
    {
        return side == RaceType::Elves || side == RaceType::Humans;
    }

};

class Elves : public Middle_Earth
{
public:
    string kind_of_elves;
    int values;
    bool in_films;

    Elves(string n = "Elves", int y = 1000, string p = "West", string k = "Rivendel", int v = 10000, bool in = true)
     : Middle_Earth(n, y, p, RaceType::Elves), kind_of_elves(k), values(v), in_films(in) {}
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
     : Middle_Earth(n, y, p, RaceType::Bad_races), kind_of_evil(koe), howmany(h), win_or_not(w) {}
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
     : Middle_Earth(n, y, p, RaceType::Humans), Parents_side(p_side), value_of_Arnors_sons(val_arnor) {}
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


void RaceGood(Iterator<Middle_Earth*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Middle_Earth *current_race = it->GetCurrent();
        if(!current_race->IsGood()) continue;

        current_race->Print();
    }
}


class RaceGoodDecorator : public IteratorDecorator<Middle_Earth*>
{
private:
    bool TargetGood;

public:
    RaceGoodDecorator(Iterator<Middle_Earth*> *it, bool isGood)
        : IteratorDecorator<Middle_Earth*>(it), TargetGood(isGood) {}

    void First() override
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->IsGood() != TargetGood)
        {
            It->Next();
        }
    }

    void Next() override
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->IsGood() != TargetGood);
    }
};


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



    Vector_stack<Middle_Earth*> Good_stack;
    for(size_t i = 0; i!=good_value; i++)
    {
        Middle_Earth *new_good = CreateRace(type_2_ob);
        Good_stack.Add(new_good);
    }

    Iterator<Middle_Earth*> *it = new Massive_Stack_Iterator<Middle_Earth*>(&Bad_stack);
    CommonPrint(it);
    delete it;
    Iterator<Middle_Earth*> *it2 = new Vector_Iterator<Middle_Earth*>(&Good_stack);
    CommonPrint(it2);
    delete it2;


    Massive_Stack<Middle_Earth*> All_Races;
    for(size_t i=0; i<10; i++)
    {
        int rac_num1 = rand()%2+1; // Число от 1 до 3 (случайный фрукт)
        RaceType Race_type = static_cast<RaceType>(rac_num1);
        Middle_Earth *newrace1 = CreateRace(Race_type);
        All_Races.Push(newrace1);
    }


    cout << endl << "Show all good races with iterator:" << endl;
    Iterator<Middle_Earth*> *goodIt = new RaceGoodDecorator(All_Races.GetIterator(), true);
    RaceGood(goodIt);
    delete goodIt;


    list<Middle_Earth*> fruitVector; // а еще можно vector, forward_list, ...
    for(size_t i=0; i<10; i++)
    {
        int rac_num1 = rand()%2+1; // Число от 1 до 3 (случайный фрукт)
        RaceType Race_type = static_cast<RaceType>(rac_num1);
        Middle_Earth *newrace2 = CreateRace(Race_type);
        fruitVector.push_back(newrace2); // Добавить новый фрукт в конец списка
    }


    cout << "Eating all good orange using adapted iterator (another container):" << endl;
    Iterator<Middle_Earth*> *adaptedIt = new ConstIteratorAdapter<std::list<Middle_Earth*>, Middle_Earth*>(&fruitVector);
    Iterator<Middle_Earth*> *adaptedOrangeIt = new RaceGoodDecorator(adaptedIt, true);
    RaceGood(adaptedOrangeIt);
    delete adaptedOrangeIt;

}







