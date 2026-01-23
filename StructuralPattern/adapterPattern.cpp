#include <bits/stdc++.h>
using namespace std;

class PaymentProcessor{
public:
   virtual void processPayment(double amount, string currency) = 0;
   virtual bool isPaymentSuccessful() = 0;
   virtual string getTransactionId() = 0;
   virtual ~PaymentProcessor() {}
};

class InHousePaymentProcessor : public PaymentProcessor {
    string transactionId;
    bool isPaymentSuccessfulFlag;

public:
    InHousePaymentProcessor() : isPaymentSuccessfulFlag(false){}
    void processPayment(double amount, string currency) override {
       cout << "InHousePaymentProcessor: Processing payment of " << amount << " " << currency << endl;
       auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
       transactionId = "TXN_" + to_string(now);
       isPaymentSuccessfulFlag = true;
       cout << "InHousePaymentProcessor: Payment successful. Txn ID: " << transactionId << endl;
   }

   bool isPaymentSuccessful() override {
       return isPaymentSuccessfulFlag;
   }

   string getTransactionId() override {
       return transactionId;
   }
};

class CheckoutService {
private:
   PaymentProcessor* paymentProcessor;

public:
   CheckoutService(PaymentProcessor* paymentProcessor) : paymentProcessor(paymentProcessor) {}

   void checkout(double amount, string currency) {
       cout << "CheckoutService: Attempting to process order for $" << amount << " " << currency << endl;
       paymentProcessor->processPayment(amount, currency);
       if (paymentProcessor->isPaymentSuccessful()) {
           cout << "CheckoutService: Order successful! Transaction ID: " << paymentProcessor->getTransactionId() << endl;
       } else {
           cout << "CheckoutService: Order failed. Payment was not successful." << endl;
       }
   }
};

class LegacyGateway {
private:
   long transactionReference;
   bool isPaymentSuccessfulFlag;

public:
   LegacyGateway() : transactionReference(0), isPaymentSuccessfulFlag(false) {}

   void executeTransaction(double totalAmount, string currency) {
       cout << "LegacyGateway: Executing transaction for " << currency << " " << totalAmount << endl;
       transactionReference = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
       isPaymentSuccessfulFlag = true;
       cout << "LegacyGateway: Transaction executed successfully. Txn ID: " << transactionReference << endl;
   }

   bool checkStatus(long transactionReference) {
       cout << "LegacyGateway: Checking status for ref: " << transactionReference << endl;
       return isPaymentSuccessfulFlag;
   }

   long getReferenceNumber() {
       return transactionReference;
   }
};

class LegacyGatewayAdapter : public PaymentProcessor {
private:
   LegacyGateway* legacyGateway;
   long currentRef;

public:
   LegacyGatewayAdapter(LegacyGateway* legacyGateway) : legacyGateway(legacyGateway), currentRef(0) {}

   void processPayment(double amount, string currency) override {
       cout << "Adapter: Translating processPayment() for " << amount << " " << currency << endl;
       legacyGateway->executeTransaction(amount, currency);
       currentRef = legacyGateway->getReferenceNumber();
   }

   bool isPaymentSuccessful() override {
       return legacyGateway->checkStatus(currentRef);
   }

   string getTransactionId() override {
       return "LEGACY_TXN_" + to_string(currentRef);
   }
};

class ECommerceAppV2 {
public:
   static void main() {
       // Modern processor
       InHousePaymentProcessor processor;
       CheckoutService modernCheckout(&processor);
       cout << "--- Using Modern Processor ---" << endl;
       modernCheckout.checkout(199.99, "USD");

       // Legacy gateway through adapter
       cout << "\n--- Using Legacy Gateway via Adapter ---" << endl;
       LegacyGateway legacy;
       LegacyGatewayAdapter adapter(&legacy);
       CheckoutService legacyCheckout(&adapter);
       legacyCheckout.checkout(75.50, "USD");
   }
};

int main() {
   ECommerceAppV2::main();
   return 0;
}