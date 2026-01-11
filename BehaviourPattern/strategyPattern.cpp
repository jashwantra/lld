#include<bits/stdc++.h>
using namespace std;

class Order{
    private:
    int value;
    int weight;
    string destinationZone;
    public:
    Order(int value_, int weight_, string destinationZone_) : value(value_) , weight(weight_), destinationZone(destinationZone_) {}
    int getWeight(){
        return this->weight;
    }

    string getDestinationZone(){
        return this->destinationZone;
    }

    int getOrderValue(){
        return this->value;
    }
};
class ShippingStrategy{
    public:
    virtual ~ShippingStrategy(){}
    virtual double calculateCost( Order & order) = 0;
};

class FlatRateShipping : public ShippingStrategy{
    double rate;
    public:
    FlatRateShipping(double rate_) : rate(rate_) {}
    double calculateCost( Order & order) override{
        cout<<"Shipping calculation FlatRateShipping "<< rate <<"\n";
        return rate;
    }
};

class WeightBasedShipping : public ShippingStrategy{
    private:
    int ratePerKg;
    public:
    WeightBasedShipping(int ratePerKg_) : ratePerKg(ratePerKg_) {}
    double calculateCost( Order & order) override{
        double cost = order.getWeight()*ratePerKg;
        cout<<"Shipping calculation WeightBasedShipping "<< cost <<"\n";
        return cost;
    }
};

class DistanceBasedShipping : public ShippingStrategy{
    private:
    int ratePerKm;
    public:
    DistanceBasedShipping(int ratePerKm_) : ratePerKm(ratePerKm_) {}
    double calculateCost( Order & order) override{
        double cost ;
        
        if (order.getDestinationZone() == "ZoneA") {
            cost = ratePerKm * 5.0;
        } else if (order.getDestinationZone() == "ZoneB") {
            cost = ratePerKm * 7.0;
        } else {
            cost = ratePerKm * 10.0;
        }

        cout<<"Shipping calculation DistanceBasedShipping "<< cost <<"\n";
        return cost;
    }
};

class ThirdPartyApiShipping : public ShippingStrategy{
    private:
    double baseFee;
    double percentageFee;
    public:
    ThirdPartyApiShipping(double baseFee_, double percentageFee_) : baseFee(baseFee_), percentageFee(percentageFee_) {}
    double calculateCost( Order & order) override{
        double cost = baseFee + order.getOrderValue()*percentageFee ;
        cout<<"Shipping calculation ThirdPartyApiShipping "<< cost <<"\n";
        return cost;
    }
};

class ShippingCostService{
    private:
    ShippingStrategy *strategy;
    public:
    ShippingCostService(ShippingStrategy * strategy_):strategy(strategy_){}
    void setStrategy(ShippingStrategy * newStrategy){
        cout<<"Shipping strategy changed\n";
        strategy = newStrategy ;
    }
    double calculateShippingCost( Order & order){
        if (strategy == nullptr) {
            throw invalid_argument("Shipping strategy not set.");
        }
        return strategy->calculateCost(order);
    }
};

int main(){
    Order order1(12,2,"ZoneA");

    FlatRateShipping flatRate(10.0);
    WeightBasedShipping weightBased(2.5);
    DistanceBasedShipping distanceBased(5.0);
    ThirdPartyApiShipping thirdParty(7.5, 0.02);

    ShippingCostService shippingService(&flatRate);
    
    cout << "--- Order 1: Using Flat Rate (initial) ---" << endl;
    shippingService.calculateShippingCost(order1);
    
    cout << "\n--- Order 1: Changing to Weight-Based ---" << endl;
    shippingService.setStrategy(&weightBased);
    shippingService.calculateShippingCost(order1);
    
    cout << "\n--- Order 1: Changing to Distance-Based ---" << endl;
    shippingService.setStrategy(&distanceBased);
    shippingService.calculateShippingCost(order1);
    
    cout << "\n--- Order 1: Changing to Third-Party API ---" << endl;
    shippingService.setStrategy(&thirdParty);
    shippingService.calculateShippingCost(order1);

    return 0;
}