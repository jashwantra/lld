#include<bits/stdc++.h>
using namespace std;

class Notification{
    public:
    virtual void send(const string & msg) = 0;
    virtual ~Notification() {}
};

class EmailNotification : public Notification{
    public:
    void send(const string & msg) override {
        cout<<"Sending Email Notification with msg:: " << msg <<"\n";
    }
};

class SmsNotification : public Notification {
    public:
    void send(const string & msg) override {
        cout<<"Sending SMS Notification with msg:: " << msg <<"\n";
    }
};

class PushNotification : public Notification {
    public:
    void send(const string & msg) override {
        cout<<"Sending Push Notification with msg:: " << msg <<"\n";
    }
};

class SlackNotification : public Notification {
    public:
    void send(const string & msg) override {
        cout<<"Sending Slack Notification with msg:: " << msg <<"\n";
    }
};

class NotificationCreator{
    public:
    virtual Notification* createNotification() = 0;
    void send(const string & msg){
        Notification * notification = createNotification();
        notification->send(msg);
        delete notification ;
    }
    virtual ~NotificationCreator() {}
};

class EmailNotificationCreator : public NotificationCreator{
    public:
    Notification* createNotification(){
        return new EmailNotification ();
    }
};

class SmsNotificationCreator : public NotificationCreator{
    public:
    Notification* createNotification(){
        return new SmsNotification ();
    }
};

class PushNotificationCreator : public NotificationCreator{
    public:
    Notification* createNotification(){
        return new PushNotification ();
    }
};


int main(){
    NotificationCreator* creator;

    // Send Email
    creator = new EmailNotificationCreator();
    creator->send("Welcome to our platform!");
    delete creator;

    // Send SMS
    creator = new SmsNotificationCreator();
    creator->send("Your OTP is 123456");
    delete creator;

    // Send Push Notification
    creator = new PushNotificationCreator();
    creator->send("You have a new follower!");
    delete creator;

    return 0;
}