#include <bits/stdc++.h>
using namespace std;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void on() {
        cout << "Light turned ON" << endl;
    }

    void off() {
        cout << "Light turned OFF" << endl;
    }
};

class Thermostat {
private:
    int currentTemperature = 20; // default

public:
    void setTemperature(int temp) {
        cout << "Thermostat set to " << temp << "°C" << endl;
        currentTemperature = temp;
    }

    int getCurrentTemperature() {
        return currentTemperature;
    }
};

class LightOnCommand : public Command {
private:
    Light* light;

public:
    LightOnCommand(Light* light) : light(light) {}

    void execute() override {
        light->on();
    }

    void undo() override {
        light->off();
    }
};

class LightOffCommand : public Command {
private:
    Light* light;

public:
    LightOffCommand(Light* light) : light(light) {}

    void execute() override {
        light->off();
    }

    void undo() override {
        light->on();
    }
};

class SetTemperatureCommand : public Command {
private:
    Thermostat* thermostat;
    int newTemperature;
    int previousTemperature;

public:
    SetTemperatureCommand(Thermostat* thermostat, int temperature) 
        : thermostat(thermostat), newTemperature(temperature), previousTemperature(0) {}

    void execute() override {
        previousTemperature = thermostat->getCurrentTemperature();
        thermostat->setTemperature(newTemperature);
    }

    void undo() override {
        thermostat->setTemperature(previousTemperature);
    }
};

class SmartButton {
private:
    Command* currentCommand;
    vector<Command*> history;

public:
    SmartButton() : currentCommand(nullptr) {}

    void setCommand(Command* command) {
        currentCommand = command;
    }

    void press() {
        if (currentCommand != nullptr) {
            currentCommand->execute();
            history.push_back(currentCommand);
        } else {
            cout << "No command assigned." << endl;
        }
    }

    void undoLast() {
        if (!history.empty()) {
            Command* lastCommand = history.back();
            history.pop_back();
            lastCommand->undo();
        } else {
            cout << "Nothing to undo." << endl;
        }
    }
};

int main() {
    // Receivers
    Light* light = new Light();
    Thermostat* thermostat = new Thermostat();

    // Commands
    Command* lightOn = new LightOnCommand(light);
    Command* lightOff = new LightOffCommand(light);
    Command* setTemp22 = new SetTemperatureCommand(thermostat, 22);

    // Invoker
    SmartButton* button = new SmartButton();

    // Simulate usage
    cout << "→ Pressing Light ON" << endl;
    button->setCommand(lightOn);
    button->press();

    cout << "→ Pressing Set Temp to 22°C" << endl;
    button->setCommand(setTemp22);
    button->press();

    cout << "→ Pressing Light OFF" << endl;
    button->setCommand(lightOff);
    button->press();

    // Undo sequence
    cout << "\n↶ Undo Last Action" << endl;
    button->undoLast();  // undo Light OFF

    cout << "↶ Undo Previous Action" << endl;
    button->undoLast();  // undo Set Temp

    cout << "↶ Undo Again" << endl;
    button->undoLast();  // undo Light ON

    delete light;
    delete thermostat;
    delete lightOn;
    delete lightOff;
    delete setTemp22;
    delete button;

    return 0;
}