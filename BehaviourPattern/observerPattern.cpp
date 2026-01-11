#include<bits/stdc++.h>
using namespace std;

class FitnessData ;
class FitnessDataObserver{
    public:
    virtual ~FitnessDataObserver() = default;
    virtual void update(FitnessData * data) = 0;
};

class FitnessDataSubject{
    public:
    virtual ~FitnessDataSubject() = default;
    virtual void registerObserver(FitnessDataObserver *observer) = 0;
    virtual void removeObserver(FitnessDataObserver * observer) = 0;
    virtual void notifyObservers() = 0; 
};

class FitnessData : public FitnessDataSubject {
    int steps;
    int activeMinutes;
    int calories;
    vector<FitnessDataObserver * > observers;
    public:
    FitnessData() :steps(0), activeMinutes(0), calories(0){}
    void registerObserver (FitnessDataObserver * observer) override {
        observers.push_back(observer);
    }
    void removeObserver (FitnessDataObserver * observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers () override {
        for(FitnessDataObserver  * observer : observers){
            observer->update(this);
        }
    }
    void newFitnessDataPushed(int steps, int activeMinutes, int calories){
        this->steps = steps;
        this->activeMinutes = activeMinutes;
        this->calories = calories;
        cout << "\nFitnessData: New data received Steps: " << steps 
             << ", Active Minutes: " << activeMinutes << ", Calories: " << calories << endl;
        notifyObservers();
    }
    void dailyReset(){
        steps = 0;
        activeMinutes = 0;
        calories = 0;
        cout << "\nFitnessData: Daily reset performed." << endl;
        notifyObservers();
    }
    int getSteps(){
        return steps;
    }
    int getActiveMinutes(){
        return activeMinutes;
    }
    int getCalories(){
        return calories;    
    }
};

class LiveActivityDisplay : public FitnessDataObserver {
    public:
    void update (FitnessData * data) override {
        cout << "Live Display → Steps: " << data->getSteps() 
             << " | Active Minutes: " << data->getActiveMinutes() 
             << " | Calories: " << data->getCalories() << endl;
    }
};

class ProgressLogger : public FitnessDataObserver {
public:
    void update(FitnessData* data) override {
        cout << "Logger → Saving to DB: Steps=" << data->getSteps() 
             << ", ActiveMinutes=" << data->getActiveMinutes() 
             << ", Calories=" << data->getCalories() << endl;
    }
};

class GoalNotifier : public FitnessDataObserver {
private:
    int stepGoal;
    bool goalReached;

public:
    GoalNotifier() : stepGoal(10000), goalReached(false) {}
    
    void update(FitnessData* data) override {
        if (data->getSteps() >= stepGoal && !goalReached) {
            cout << "Notifier → 🎉 Goal Reached! You've hit " << stepGoal << " steps!" << endl;
            goalReached = true;
        }
    }
    
    void reset() {
        goalReached = false;
    }
};

int main(){
    cout << "\n\n=== Observer Pattern Approach ===" << endl;
    FitnessData fitnessData;
    
    LiveActivityDisplay display;
    ProgressLogger logger;
    GoalNotifier notifier;
    
    fitnessData.registerObserver(&display);
    fitnessData.registerObserver(&logger);
    fitnessData.registerObserver(&notifier);

    // Simulate updates
    fitnessData.newFitnessDataPushed(500, 5, 20);
    fitnessData.newFitnessDataPushed(9800, 85, 350);
    fitnessData.newFitnessDataPushed(10100, 90, 380); // Goal should trigger

    // Daily reset
    notifier.reset();
    fitnessData.dailyReset();

    return 0;
}