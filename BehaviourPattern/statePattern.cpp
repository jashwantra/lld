#include <bits/stdc++.h>
using namespace std;

class VendingMachine;

class MachineState {
public:
    virtual ~MachineState() = default;
    virtual void selectItem(VendingMachine* context, string itemCode) = 0;
    virtual void insertCoin(VendingMachine* context, double amount) = 0;
    virtual void dispenseItem(VendingMachine* context) = 0;
};

class IdleState : public MachineState {
public:
    void selectItem(VendingMachine* context, string itemCode) override ;
    void insertCoin(VendingMachine* context, double amount) override ;
    void dispenseItem(VendingMachine* context) override ;
};

class ItemSelectedState : public MachineState {
public:
    void selectItem(VendingMachine* context, string itemCode) override ;
    void insertCoin(VendingMachine* context, double amount) override ;
    void dispenseItem(VendingMachine* context) override ;
};

class HasMoneyState : public MachineState {
public:
    void selectItem(VendingMachine* context, string itemCode) override ;
    void insertCoin(VendingMachine* context, double amount) override ;
    void dispenseItem(VendingMachine* context) override ;
};

class DispensingState : public MachineState {
public:
    void selectItem(VendingMachine* context, string itemCode) override ;
    void insertCoin(VendingMachine* context, double amount) override ;
    void dispenseItem(VendingMachine* context) override ;
};

class VendingMachine {
private:
    MachineState* currentState;
    string selectedItem;
    double insertedAmount;

public:
    VendingMachine() : selectedItem(""), insertedAmount(0.0) {
        currentState = new IdleState();
    }

    ~VendingMachine() {
        delete currentState;
    }

    void setState(MachineState* newState) {
        delete currentState;
        currentState = newState;
    }

    void setSelectedItem(string itemCode) {
        selectedItem = itemCode;
    }

    void setInsertedAmount(double amount) {
        insertedAmount = amount;
    }

    string getSelectedItem() {
        return selectedItem;
    }

    void selectItem(string itemCode) {
        currentState->selectItem(this, itemCode);
    }

    void insertCoin(double amount) {
        currentState->insertCoin(this, amount);
    }

    void dispenseItem() {
        currentState->dispenseItem(this);
    }

    void reset() {
        selectedItem = "";
        insertedAmount = 0.0;
        setState(new IdleState());
    }
};

void IdleState::selectItem(VendingMachine* context, string itemCode)  {
        cout << "Item selected: " << itemCode << endl;
        context->setSelectedItem(itemCode);
        context->setState(new ItemSelectedState());
    }

void IdleState::insertCoin(VendingMachine* context, double amount)  {
        cout << "Please select an item before inserting coins." << endl;
    }

void IdleState :: dispenseItem(VendingMachine* context)  {
        cout << "No item selected. Nothing to dispense." << endl;
    }

void ItemSelectedState::selectItem(VendingMachine* context, string itemCode) {
      cout << "Item already selected: " << context->getSelectedItem() << endl;
    }

void ItemSelectedState::insertCoin(VendingMachine* context, double amount)  {
      cout << "Inserted $" << amount << " for item: " << context->getSelectedItem() << endl;
      context->setInsertedAmount(amount);
      context->setState(new HasMoneyState());
    }

void ItemSelectedState::dispenseItem(VendingMachine* context)  {
      cout << "Insert coin before dispensing." << endl;
    }

void HasMoneyState::selectItem(VendingMachine* context, string itemCode)  {
        cout << "Cannot change item after inserting money." << endl;
    }

void HasMoneyState::insertCoin(VendingMachine* context, double amount)  {
        cout << "Money already inserted." << endl;
    }

void HasMoneyState::dispenseItem(VendingMachine* context)  {
        cout << "Dispensing item: " << context->getSelectedItem() << endl;
        context->setState(new DispensingState());

        // Simulate dispensing
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Item dispensed successfully." << endl;
        context->reset();
    }

void DispensingState::selectItem(VendingMachine* context, string itemCode)  {
        cout << "Please wait, dispensing in progress." << endl;
    }

void DispensingState::insertCoin(VendingMachine* context, double amount)  {
        cout << "Please wait, dispensing in progress." << endl;
    }

void DispensingState::dispenseItem(VendingMachine* context)  {
        cout << "Already dispensing. Please wait." << endl;
    }

int main() {
    VendingMachine* vm = new VendingMachine();

    vm->insertCoin(1.0); // Invalid in IdleState
    vm->selectItem("A1");
    vm->insertCoin(1.5);
    vm->dispenseItem();

    cout << "\n--- Second Transaction ---" << endl;
    vm->selectItem("B2");
    vm->insertCoin(2.0);
    vm->dispenseItem();

    delete vm;
    return 0;
}