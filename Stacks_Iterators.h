#ifndef STACKS_ITERATORS_H_INCLUDED
#define STACKS_ITERATORS_H_INCLUDED
using namespace std;
#include <iostream>
#include <vector>
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

template<typename T>
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual void First() = 0;
    virtual T GetCurrent() = 0;
};


const size_t MaxSize = 100;

template<typename T>
class Massive_Stack
{
private:
    T* Things = new T[MaxSize];  // Создание массива, который будет содержать данные типа T
    size_t Top; //Индекс элемента стека, следующего за верхним

public:
    Massive_Stack() : Top(0) {}
    T Pop() {return Things[--Top];}
    bool IsEmpty() const  {return (Top == 0);}


    void Push(T NewThing) {Things[Top++] = NewThing;} //Добавление элемента
    T GetElementByIndex(size_t index) { return Things[index];} //Получение элемента по индексу
    ~Massive_Stack() { delete [] Things;} //Декструктор, чтобы чистить память
};


template<typename T>
class Vector_stack
{
private:
    vector<T> Items[MaxSize];
    size_t top;
public:
    Vector_stack() : top(0) {}
    void Add(T NewItem) {Items.push_back(NewItem);}
    T GetElement(size_t Index) {return Items[Index];}
    void Ret() {return Items.pop_back();}
};

#endif // STACKS_ITERATORS_H_INCLUDED
