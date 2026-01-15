#include<bits/stdc++.h>
using namespace std;

class Button{
    public:
    virtual void paint() = 0;
    virtual void onClick() = 0;
    virtual ~Button() {}
};

class Checkbox{
    public:
    virtual void paint() = 0;
    virtual void onSelect() = 0;
    virtual ~Checkbox(){}
};

class WindowsButton : public Button{
    public:
    void paint() override {
        cout<<"Painting a windows style button.\n";
    }
    void onClick() override{
        cout<<"Windows button clicked.\n";
    }
};

class WindowsCheckbox : public Checkbox {
    public:
    void paint() override{
        cout<<"Painting a windows checkbox.\n";
    }
    void onSelect() override{
        cout<<"Windows checkbox selected.\n";
    }
};

class MacOsButton : public Button{
    public:
    void paint() override{
        cout<<"Painting a mac button.\n";
    }
    void onClick() override{
        cout<<"Mac button clicked.\n";
    }
};

class MacOsCheckbox : public Checkbox{
    public:
    void paint() override{
        cout<<"Painting a Mac checkbox.\n";
    }
    void onSelect() override{
        cout<<"Mac checkbox selected.\n";
    }
};

class GuiFactory{
    public:
    virtual Button * createButton() = 0;
    virtual Checkbox * createCheckbox() = 0;
    virtual ~GuiFactory(){}
};

class WindowsFactory : public GuiFactory {
    public:
    Button * createButton() override{
        return new WindowsButton();
    }
    Checkbox * createCheckbox() override{
        return new WindowsCheckbox();
    }
};

class MacOsFactory : public GuiFactory{
    public:
    Button* createButton() override{
        return new MacOsButton();
    }
    Checkbox* createCheckbox() override{
        return new MacOsCheckbox();
    }
};

class Application{
    private:
    Button * button = NULL;
    Checkbox * checkbox = NULL;

    public:
    Application(GuiFactory * factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    ~Application(){
        delete button;
        delete checkbox;
    }

    void renderUi(){
        button->paint();
        checkbox->paint();
    }
};

int main(){
    string os;
    cout<<"Enter OS (windows/mac)\n";
    cin>>os;

    GuiFactory* factory = NULL;

    transform(os.begin(), os.end(), os.begin(), ::tolower);

    if (os.find("windows") != string::npos) {
        factory = new WindowsFactory();
    } else {
        factory = new MacOsFactory();
    }

    Application app(factory);
    app.renderUi();

    delete factory;

    return 0;
}