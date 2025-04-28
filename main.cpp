#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"

using namespace std;

// Тип напитка
enum class DrinkType : int
{
    MilkChocolate,
    DarkChocolate,
    CaffeinatedChocolate,
    Unknown
};

// Реализация паттерна "Стратегия" для напитков

enum class DrinkingMannerEnum : int
{
    Sip,
    DrinkInOneGo,
    Stir,

    None
};

class DrinkingStrategy
{
public:
  virtual ~DrinkingStrategy() {}
  virtual void Drink() = 0;
};

class SipDrinkingStrategy : public DrinkingStrategy
{
  void Drink() { cout << "Sip slowly..."; }
};

class DrinkInOneGoStrategy : public DrinkingStrategy
{
  void Drink() { cout << "Drink it all in one go..."; }
};

class StirStrategy : public DrinkingStrategy
{
  void Drink() { cout << "Stir and then drink..."; }
};

// Фабричный метод для создания стратегий
DrinkingStrategy *CreateDrinkingStrategy(DrinkingMannerEnum drinkingManner)
{
  switch(drinkingManner)
  {
    case DrinkingMannerEnum::Sip: return new SipDrinkingStrategy;
    case DrinkingMannerEnum::DrinkInOneGo: return new DrinkInOneGoStrategy;
    case DrinkingMannerEnum::Stir: return new StirStrategy;

    default: return nullptr;
  }
}

class Drink // Родительский (базовый) класс "Напиток"
{
private:
    DrinkType Type;
    double Volume;

    DrinkingStrategy *DrinkingManner;

    void DoDrinkUsingStrategy()
    {
      if(DrinkingManner == nullptr)
      {
        cout << "Do nothing!";
        return;
      }
      else
      {
        DrinkingManner->Drink();
      }
    }

protected:
    bool DrinkIsGood;

public:
    Drink(DrinkType type) : Type(type), Volume(0.0), DrinkIsGood(false), DrinkingManner(nullptr)
    {
        DrinkIsGood = static_cast<bool>(rand()%2);
    }

    virtual ~Drink()
    {
      if(DrinkingManner != nullptr) delete DrinkingManner;
    }

    bool IsGood() const { return DrinkIsGood; }
    DrinkType GetType() const { return Type; }
    double GetVolume() const { return Volume; }

    virtual void PrintType() = 0;

    virtual void Prepare() = 0;

    void DrinkIt()
    {
        PrintType();
        cout << " : ";

        if(IsGood()) cout << "GOOD";
        else cout << "BAD";

        cout << " : ";

        Prepare();
        cout << " : ";

        DoDrinkUsingStrategy();

        cout << endl;
    }

    void SetDrinkingManner(DrinkingStrategy *drinkingManner) { DrinkingManner = drinkingManner; }
};

class MilkChocolate : public Drink
{
public:
    MilkChocolate() : Drink(DrinkType::MilkChocolate)
    {
        SetDrinkingManner(CreateDrinkingStrategy(DrinkingMannerEnum::Sip));
    }

    ~MilkChocolate() {}

    void PrintType() { cout << "Milk Chocolate"; }
    void Prepare() { cout << "Warm up and add milk"; }
};

class DarkChocolate : public Drink
{
public:
    DarkChocolate() : Drink(DrinkType::DarkChocolate)
    {
        SetDrinkingManner(CreateDrinkingStrategy(DrinkingMannerEnum::Stir));
    }

    ~DarkChocolate() {}

    void PrintType() { cout << "Dark Chocolate"; }
    void Prepare() { cout << "Heat and stir"; }
};

class CaffeinatedChocolate : public Drink
{
public:
    CaffeinatedChocolate() : Drink(DrinkType::CaffeinatedChocolate)
    {
        SetDrinkingManner(CreateDrinkingStrategy(DrinkingMannerEnum::DrinkInOneGo));
    }

    ~CaffeinatedChocolate() {}

    void PrintType() { cout << "Caffeinated Chocolate"; }
    void Prepare() { cout << "Mix with coffee and heat"; }
};

// Фабричный метод для создания напитков
Drink *CreateDrink(DrinkType type)
{
    Drink *newDrink = nullptr;

    if(type == DrinkType::MilkChocolate)
    {
        newDrink = new MilkChocolate;
    }
    else if(type == DrinkType::DarkChocolate)
    {
        newDrink = new DarkChocolate;
    }
    else if(type == DrinkType::CaffeinatedChocolate)
    {
        newDrink = new CaffeinatedChocolate;
    }

    return newDrink;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t N = 30;

    vector<Drink*> drinkArray;
    for(size_t i=0; i<N; i++)
    {
        int drink_num = rand()%3+1; // Число от 1 до 3 (случайный напиток)
        DrinkType drink_type = static_cast<DrinkType>(drink_num);
        Drink *newDrink = CreateDrink(drink_type);

        drinkArray.push_back(newDrink);
    }

    cout << "Размер массива напитков: " << drinkArray.size() << endl;

    // Обход всех напитков
    cout << endl << "Drinking all in a simple loop:" << endl;
    for(size_t i=0; i<drinkArray.size(); i++)
    {
        Drink *currentDrink = drinkArray[i];
        currentDrink->DrinkIt();
    }

    return 0;
}

