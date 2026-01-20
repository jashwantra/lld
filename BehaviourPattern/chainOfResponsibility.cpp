#include<bits/stdc++.h>
using namespace std;

class Request{
    public:
    string user;
    string userRole;
    int requestCount;
    string payload;

    Request(string user_, string userRole_, int requestCount_, string payload_) 
    : user(user_), userRole(userRole_), requestCount(requestCount_), payload(payload_){} 
};

class RequestHandlerInterface{
    public:
    virtual void setNext(RequestHandlerInterface *) = 0 ;
    virtual void handle(Request request) = 0 ;
    virtual ~RequestHandlerInterface() {}
};

class BaseHandler : public RequestHandlerInterface {
    protected:
    RequestHandlerInterface * next;
    public:
    BaseHandler() : next(NULL) {}
    void setNext(RequestHandlerInterface * next_) override {
        this->next = next_;
    }
    protected:
    void forward(Request request){
        if(next != NULL){
            next->handle(request);
        }
    }
};

class AuthHandler : public BaseHandler {
    public:
    void handle(Request request){
        if (request.user.empty()) {
           cout << "AuthHandler: User not authenticated." << endl;
           return; 
       }
       cout << "AuthHandler: Authenticated." << endl;
       forward(request);
    }
};

class AuthorizationHandler : public BaseHandler {
public:
   void handle(Request request) override {
       if (request.userRole != "ADMIN") {
           cout << "AuthorizationHandler: Access denied." << endl;
           return;
       }
       cout << "AuthorizationHandler: Authorized." << endl;
       forward(request);
   }
};

class RateLimitHandler : public BaseHandler {
public:
   void handle(Request request) override {
       if (request.requestCount >= 100) {
           cout << "RateLimitHandler: Rate limit exceeded." << endl;
           return;
       }
       cout << "RateLimitHandler: Within rate limit." << endl;
       forward(request);
   }
};

class ValidationHandler : public BaseHandler {
public:
   void handle(Request request) override {
       if (request.payload.empty()) {
           cout << "ValidationHandler: Invalid payload." << endl;
           return;
       }
       cout << "ValidationHandler: Payload valid." << endl;
       forward(request);
   }
};

class BusinessLogicHandler : public BaseHandler {
public:
   void handle(Request request) override {
       cout << "BusinessLogicHandler: Processing request..." << endl;
       // Core application logic goes here
   }
};

class RequestHandlerApp {
public:
   static void main() {

       RequestHandlerInterface* auth = new AuthHandler();
       RequestHandlerInterface* authorization = new AuthorizationHandler();
       RequestHandlerInterface* rateLimit = new RateLimitHandler();
       RequestHandlerInterface* validation = new ValidationHandler();
       RequestHandlerInterface* businessLogic = new BusinessLogicHandler();

       auth->setNext(authorization);
       authorization->setNext(rateLimit);
       rateLimit->setNext(validation);
       validation->setNext(businessLogic);

       Request request("john", "ADMIN", 10, "{ \"data\": \"valid\" }");
       auth->handle(request);

       cout << "\n--- Trying an invalid request ---" << endl;
       Request badRequest("", "USER", 150, "");
       auth->handle(badRequest);

       delete auth;
       delete authorization;
       delete rateLimit;
       delete validation;
       delete businessLogic;
   }
};


int main(){
    RequestHandlerApp::main();
    return 0;
}