#ifndef STACKS_ITERATORS_H_INCLUDED
#define STACKS_ITERATORS_H_INCLUDED
using namespace std;
#include <iostream>
#include <vector>


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
    vector<T> Items;
    size_t top;
public:
    Vector_stack() : top(0) {}
    void Add(T NewItem) {Items.push_back(NewItem);}
    T GetElement(size_t Index) {return Items[Index];}
    void Ret() {return Items.pop_back();}
};


template<typename T>
class Massive_Stack_Iterator : public Iterator<T>
{
    T* Massive_Stack; //Указатель на массив
    size_t Pos; //Текущее положение в массиве
    size_t mass_size; //Размер массива

public:
    Massive_Stack_Iterator(T* stak, size_t mass) : Massive_Stack(stak), Pos(0), mass_size(mass) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= mass_size); }
    T GetCurrent() const override { return Massive_Stack[Pos]; }
};
#endif // STACKS_ITERATORS_H_INCLUDED
