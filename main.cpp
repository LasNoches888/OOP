#include <iostream>
#include "Stacks_Iterators.h"
#include <vector>
#include <list>
using namespace std;

enum class RaceWar : int
{
    Shred,
    ShootBow,
    Chop
};

enum class RaceType : int
{
    Bad_races = 1,
    Elves = 2,
    Humans = 0,
};


class Middle_Earth
{
protected:
    RaceType side;
    HowToFigthing* WarManner;
    void DoHowToWar() {
    if (WarManner == nullptr) {
        cout << "Do nothing!";
        return;
    }
    else
    {
        WarManner->War();
    }
    }
public:
    string name;
    int year;
    string place;
    Middle_Earth(string n, int y, string p, RaceType s) : name(n), year(y), place(p), side(s) {}

    virtual void Prepare() const = 0;
    virtual void Print() const = 0;
    ~Middle_Earth() {}
    virtual RaceType GetSide() const {return side;}

    bool IsGood() const
    {
        return side == RaceType::Elves || side == RaceType::Humans;
    }
    void SetHowToWar(HowToFigthing* warmanner) {
    WarManner = warmanner;
    }


    //Функция с реализацией
    void Fight()
    {
        Prepare();
        DoHowToWar();
        cout << endl;
    }

};




HowToFigthing* CreateWarStrategy(RaceWar type)
{
    switch(type) {
    case RaceWar::Shred:
        return new Orc_figthing;
    case RaceWar::ShootBow:
        return new Elves_figthing;
    case RaceWar::Chop:
        return new Human_figthing;
    default:
        return nullptr;
    }
}

class Elves : public Middle_Earth
{
public:
    string kind_of_elves;
    int values;
    bool in_films;

    Elves(string n = "Elves", int y = 1000, string p = "West", string k = "Rivendel", int v = 10000, bool in = true)
     : Middle_Earth(n, y, p, RaceType::Elves), kind_of_elves(k), values(v), in_films(in)
     {
        SetHowToWar(CreateWarStrategy(RaceWar::ShootBow));
     }
     void Prepare() const override
     {
         cout<<"Pulling the bowstring...";
     }
     void Print() const override
     {
         cout<<name<<"--";
     }
};


class Bad_races : public Middle_Earth
{
public:
    string kind_of_evil;
    int howmany;
    bool win_or_not;

    Bad_races(string n = "Orcs", int y = 1500, string p = "Mordor", string koe = "Mordor's orcs", int h = 50000, bool w = false )
     : Middle_Earth(n, y, p, RaceType::Bad_races), kind_of_evil(koe), howmany(h), win_or_not(w)
     {
        SetHowToWar(CreateWarStrategy(RaceWar::Shred));
     }
     void Prepare() const override
     {
         cout<<"Sharpennig rusty weapons...";
     }
     void Print() const override
     {
         cout<<name<<"--";
     }

};

class Human : public Middle_Earth
{
public:
    string Parents_side;
    int value_of_Arnors_sons;


    Human(string n = "Humans", int y = 2000, string p = "Gondor", string p_side = "With good mans", int val_arnor = 1 )
     : Middle_Earth(n, y, p, RaceType::Humans), Parents_side(p_side), value_of_Arnors_sons(val_arnor)
     {
        SetHowToWar(CreateWarStrategy(RaceWar::Chop));
     }
     void Prepare() const override
     {
         cout<<"Putting the swords in order...";
     }
     void Print() const override
     {
         cout<<name<<"--";
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







//void CommonPrint(Iterator<Middle_Earth*> *it)
//{
//    for(it->First(); !it->IsDone(); it->Next())
//    {
//        Middle_Earth* current_race = it->GetCurrent();
//        current_race->Print();
//    }
//}


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
    cout<<"Enter the value for stack_for_all: ";
    int value_for_all;
    cin>>value_for_all;
    cout<<endl;

    RaceType type_1_ob = static_cast<RaceType>(type_1);
    RaceType type_2_ob = static_cast<RaceType>(type_2);

    cout<<"Stack only for bad races: "<<endl;
    Massive_Stack<Middle_Earth*> Bad_stack;
    for(size_t i = 0; i!=orc_value; i++)
    {
        Middle_Earth *new_bad = CreateRace(type_1_ob);
        Bad_stack.Push(new_bad);
        new_bad->Fight();
    }


    cout<<"Stack only for good races: "<<endl;
    Vector_stack<Middle_Earth*> Good_stack;
    for(size_t i = 0; i!=good_value; i++)
    {
        Middle_Earth *new_good = CreateRace(type_2_ob);
        Good_stack.Add(new_good);
        new_good->Fight();
    }

//    Iterator<Middle_Earth*> *it = new Massive_Stack_Iterator<Middle_Earth*>(&Bad_stack);
//    CommonPrint(it);
//    delete it;
//    Iterator<Middle_Earth*> *it2 = new Vector_Iterator<Middle_Earth*>(&Good_stack);
//    CommonPrint(it2);
//    delete it2;


//    Massive_Stack<Middle_Earth*> All_Races;
//    for(size_t i=0; i<10; i++)
//    {
//        int rac_num1 = rand()%2+1; // Число от 1 до 3 (случайный фрукт)
//        RaceType Race_type = static_cast<RaceType>(rac_num1);
//        Middle_Earth *newrace1 = CreateRace(Race_type);
//        All_Races.Push(newrace1);
//    }

    cout<<endl;
    cout<<endl;
//    cout << endl << "Show all good races with iterator:" << endl;
//    Iterator<Middle_Earth*> *goodIt = new RaceGoodDecorator(All_Races.GetIterator(), true);
//    RaceGood(goodIt);
//    delete goodIt;

    cout<<"Stack for all races: "<<endl;
    list<Middle_Earth*> RaceVector;
    for(size_t i=0; i<value_for_all; i++)
    {
        int rac_num1 = rand()%2+1;
        RaceType Race_type = static_cast<RaceType>(rac_num1);
        Middle_Earth *newrace2 = CreateRace(Race_type);
        newrace2->Fight();
        RaceVector.push_back(newrace2); //
    }


    cout << "Filtering all races to good using adapted iterator:" << endl;
    Iterator<Middle_Earth*> *adaptedIt = new ConstIteratorAdapter<std::list<Middle_Earth*>, Middle_Earth*>(&RaceVector);
    Iterator<Middle_Earth*> *adaptedOrangeIt = new RaceGoodDecorator(adaptedIt, true);
    RaceGood(adaptedOrangeIt);
    delete adaptedOrangeIt;


}







