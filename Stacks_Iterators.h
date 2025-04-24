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


template <typename T> class Massive_Stack_Iterator; //Forwarding declaration - заранее обьявляем итератор для массива
template <typename T> class Vector_Iterator; //То же самое, что и выше, только для вектора

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
    Iterator<T>* GetIterator()
    {
        return new Massive_Stack_Iterator<T>(this);
    }

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
    size_t Size() const { return Items.size(); }

    Iterator<T>* GetIterator()
    {
        return new Vector_stack<T>(Items, top);
    }

};


template<typename T>
class Massive_Stack_Iterator : public Iterator<T>
{
    Massive_Stack<T>* stak; //Указатель на массив
    size_t Pos; //Текущее положение в массиве
    size_t mass_size; //Размер массива

public:
    Massive_Stack_Iterator(Massive_Stack<T>* stak)
    : stak(stak), Pos(0), mass_size(stak->SizeStack()) {}


    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= mass_size); }
    T GetCurrent() const override { return stak->GetElementByIndex(Pos); }

};

template<typename T>
class Vector_Iterator : public Iterator<T>
{
    Vector_stack<T>* data;
    size_t pos;
    size_t vector_size;
public:
    Vector_Iterator(Vector_stack<T>* data) : data(data), pos(0), vector_size(data->Size()) {}
    void First() override { pos = 0; }
    void Next() override { pos++; }
    bool IsDone() const override { return (pos >= vector_size); }
    T GetCurrent() const override { return data->GetElement(pos); }
};

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;
public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};

class HowToFigthing
{
public:
    virtual void War() = 0;
    virtual ~HowToFigthing() {}
};

class Orc_figthing : public HowToFigthing
{
    void War() override {cout<<"Orcs using old weapons and dead people...";}
};

class Elves_figthing : public HowToFigthing
{
    void War() override {cout<<" Elves using skillful weapon and help of Ents...";}
};

class Human_figthing : public HowToFigthing
{
    void War() override {cout<<"Human using iron weapons and catapults...";}
};



#endif // STACKS_ITERATORS_H_INCLUDED
