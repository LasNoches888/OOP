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
    virtual T GetCurrent() const = 0;
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
    size_t SizeStack() const {return Top;}

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
    Massive_Stack<T>* stak; //Указатель на массив
    size_t Pos; //Текущее положение в массиве
    size_t mass_size; //Размер массива

public:
    Massive_Stack_Iterator(Massive_Stack<T>* stak)
    : stak(stak) {}


    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= mass_size); }
    T GetCurrent() const override { return stak->GetElementByIndex(Pos); }

};

template<typename T>
class Vector_Iterator : public Iterator<T>
{
    T* Vector_stack;
    size_t pos;
    size_t vector_size;
public:
    void First() override { pos = 0; }
    void Next() override { pos++; }
    bool IsDone() const override { return (pos >= vector_size); }
    T GetCurrent() const override { return Vector_stack[pos]; }
};
#endif // STACKS_ITERATORS_H_INCLUDED
