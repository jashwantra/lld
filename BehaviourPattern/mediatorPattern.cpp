#include <bits/stdc++.h>
using namespace std;

class UIComponent;

class UIMediator {
public:
   virtual void componentChanged(UIComponent* component) = 0;
   virtual ~UIMediator() {}
};

class UIComponent {
protected:
   UIMediator* mediator;

public:
   UIComponent(UIMediator* mediator) : mediator(mediator) {}

   void notifyMediator() {
       mediator->componentChanged(this);
   }

   virtual ~UIComponent() {}
};

class TextField : public UIComponent {
private:
   string text;

public:
   TextField(UIMediator* mediator) : UIComponent(mediator), text("") {}

   void setText(string newText) {
       text = newText;
       cout << "TextField updated: " << newText << endl;
       notifyMediator();
   }

   string getText() {
       return text;
   }
};

class Button : public UIComponent {
private:
   bool enabled;

public:
   Button(UIMediator* mediator) : UIComponent(mediator), enabled(false) {}

   void click() {
       if (enabled) {
           cout << "Login Button clicked!" << endl;
           notifyMediator(); // Will trigger login attempt
       } else {
           cout << "Login Button is disabled." << endl;
       }
   }

   void setEnabled(bool value) {
       enabled = value;
       cout << "Login Button is now " << (enabled ? "ENABLED" : "DISABLED") << endl;
   }
};

class Label : public UIComponent {
private:
   string text;

public:
   Label(UIMediator* mediator) : UIComponent(mediator) {}

   void setText(string message) {
       text = message;
       cout << "Status: " << text << endl;
   }
};

class FormMediator : public UIMediator {
private:
   TextField* usernameField;
   TextField* passwordField;
   Button* loginButton;
   Label* statusLabel;

public:
   FormMediator() : usernameField(nullptr), passwordField(nullptr), 
                    loginButton(nullptr), statusLabel(nullptr) {}

   void setUsernameField(TextField* usernameField) {
       this->usernameField = usernameField;
   }

   void setPasswordField(TextField* passwordField) {
       this->passwordField = passwordField;
   }

   void setLoginButton(Button* loginButton) {
       this->loginButton = loginButton;
   }

   void setStatusLabel(Label* statusLabel) {
       this->statusLabel = statusLabel;
   }

   void componentChanged(UIComponent* component) override {
       if (component == usernameField || component == passwordField) {
           bool enableButton = !usernameField->getText().empty() &&
               !passwordField->getText().empty();
           loginButton->setEnabled(enableButton);
       } else if (component == loginButton) {
           string username = usernameField->getText();
           string password = passwordField->getText();

           if (username == "admin" && password == "1234") {
               statusLabel->setText("✅ Login successful!");
           } else {
               statusLabel->setText("❌ Invalid credentials.");
           }
       }
   }
};

class MediatorApp {
public:
   static void main() {
       FormMediator mediator;

       TextField usernameField(&mediator);
       TextField passwordField(&mediator);
       Button loginButton(&mediator);
       Label statusLabel(&mediator);

       mediator.setUsernameField(&usernameField);
       mediator.setPasswordField(&passwordField);
       mediator.setLoginButton(&loginButton);
       mediator.setStatusLabel(&statusLabel);

       // Simulate user interaction
       usernameField.setText("admin");
       passwordField.setText("1234");
       loginButton.click(); // Should succeed

       cout << "\n--- New Attempt with Wrong Password ---" << endl;
       passwordField.setText("wrong");
       loginButton.click(); // Should fail
   }
};

int main() {
   MediatorApp::main();
   return 0;
}