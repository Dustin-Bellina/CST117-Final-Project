#include <iostream>
#include <random>
using namespace std;

class Enemy
{
    protected: 
        int health, damage;
        string name;
        char symbol;
    public:

        Enemy(int incomingHealth, int incomingDamage, string incomingName, char incomingSymbol)
{
        health = incomingHealth;
        damage = incomingDamage;
        name = incomingName;
        symbol = incomingSymbol;

}

        void setHealth(int incomingHealth)
        {
            health = incomingHealth;
        }

         int getHealth()
        {
             return health;
         }

        void setDamage(int incomingDamage)
        {
            damage = incomingDamage;
        }

         int getDamage()
        {
             return damage;
        }


        string getName()
        {
            return name;
        }

        char getSymbol()
        {
            return symbol;
        }

        void takeDamage(int amt)
        {
            health -= amt;
        }
        bool isAlive()
        {
            return health > 0;
        }

};

class Bat : public Enemy
{
    public:
        Bat() : Enemy ( 25, 5, "Bat", 'B'){}

};

class Centipede : public Enemy 
{
    public:
        Centipede() : Enemy(10, 3, "Centipede", 'C'){}

};

class Elf : public Enemy 
{
    public:
        Elf() : Enemy( 25, 10, "Elf", 'E'){}

};

class Goblin : public Enemy 
{
    public:
        Goblin() : Enemy(10, 3, "Goblin", 'G'){}

};

class Hobgoblin : public Enemy 
{
    public:
        Hobgoblin() : Enemy(10, 3, "Hobgoblin", 'H'){}

};

class Locust : public Enemy 
{
    public:
        Locust() : Enemy(10, 3, "Locust", 'L'){}

};

class Monkey : public Enemy 
{
    public:
        Monkey() : Enemy(10, 3, "Monkey", 'M'){}

};


class Orc : public Enemy 
{
    public:
        Orc() : Enemy(10, 3, "Orc", 'O'){}

};



class Rat : public Enemy 
{
    public:
        Rat() : Enemy(10, 3, "Rat", 'R'){}

};


class Slime : public Enemy 
{
    public:
        Slime() : Enemy(10, 3, "Slime", 'S'){}

};


class Vampire : public Enemy 
{
    public:
        Vampire() : Enemy(10, 3, "Vampire", 'V'){}

};


class Wolf : public Enemy 
{
    public:
        Wolf() : Enemy(10, 3, "Wolf", 'W'){}

};
    class Boss : public Enemy
{
    //enemy stuff
};

int main(){

//add each enemy type
//add random so enemy can be randomly put in map
    // enemy.health == 15;
    // enemy.damage -= 5;
    
        
    return 0;
}