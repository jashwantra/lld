#include <bits/stdc++.h>

using namespace std;

class EnemyPrototype{
    virtual EnemyPrototype* clone() = 0;
    virtual ~EnemyPrototype(){}
};

class Enemy{
private:
    string type;
    int health;
    double speed;
    bool armored;
    string weapon;

public:
    Enemy(string type_, int health_, double speed_, bool armored_, string weapon_)
    : type(type_), health(health_), speed(speed_), armored(armored_), weapon(weapon_){}

    Enemy* clone(){
        return new Enemy(type, health, speed, armored, weapon);
    }

    void setHealth(int health_){
        health = health_;
    }

    void printStats() {
        cout << type << " [Health: " << health 
            << ", Speed: " << speed 
            << ", Armored: " << (armored ? "true" : "false")
            << ", Weapon: " << weapon << "]" << endl;
    }

};

class EnemyRegistry {
private:
   map<string, Enemy*> prototypes;

public:
   void registerPrototype(string key, Enemy* prototype) {
       prototypes[key] = prototype;
   }

   Enemy* get(string key) {
       auto it = prototypes.find(key);
       if (it != prototypes.end()) {
           return it->second->clone();
       }
       throw invalid_argument("No prototype registered for: " + key);
   }

   ~EnemyRegistry() {
       for (auto& pair : prototypes) {
           delete pair.second;
       }
   }
};

class Game {
public:
   static void main() {
       EnemyRegistry registry;

       // Register prototype enemies
       registry.registerPrototype("flying", new Enemy("FlyingEnemy", 100, 12.0, false, "Laser"));
       registry.registerPrototype("armored", new Enemy("ArmoredEnemy", 300, 6.0, true, "Cannon"));

       // Clone from registry
       Enemy* e1 = registry.get("flying");
       Enemy* e2 = registry.get("flying");
       e2->setHealth(80); // maybe this one was spawned with less HP

       Enemy* e3 = registry.get("armored");

       // Print stats to verify
       e1->printStats();
       e2->printStats();
       e3->printStats();

       // Clean up
       delete e1;
       delete e2;
       delete e3;
   }
};

int main(){
    Game::main();
    return 0;
}