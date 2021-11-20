#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) {
    capacity = t_capacity;
    open = false;
}

// Rule of 5
//Destructor
virtual Trainer::~Trainer(){

    if (customersList){
        for(Customer *customer: customersList){
            if(*customer != nullptr){
                delete *customer;
                *customer = nullptr;
            }
        }
    }

    if (orderList) {
        for(OrderPair pair: orderList){
            if(pair != nullptr){
                delete pair;
                pair = nullptr;
            }
        }
    }
    customersList.clear()
    orderList.clear()
}

// Copy Constructor
Trainer::Trainer(const Trainer &other) {
    capacity = other.capacity;
    open = other.open;
    customersList = new std::vector<Customer *>;
    orderList = new std::vector<OrderPair>;
    for (int i = 0; i < other.customersList.size(); ++i) {
        customersList.push_back(new Customer(other.customersList[i]));
    }
    for (int i = 0; i < other.orderList.size(); ++i) {
        orderList.push_back(new OrderPair(other.orderList[i]));
    }
}

//Copy Assignment Operator
Trainer &Trainer::operator=(const Trainer &other) {

    if (this != &other) {

        if (customersList) customersList.clear();
        if (orderList) orderList.clear();
        capacity = other.capacity;
        open = other.open;
        for (Customer *customer: other.customersList) {
            customersList.push_back(new Customer(customer->getName(),customer->getId()));
        }
        for (OrderPair pair: other.orderList) {
            orderList.push_back(new OrderPair (pair.first,pair.second));
        }
    }
    return *this;
}




int Trainer::getCapacity() const { return capacity; }

void Trainer::addCustomer(Customer *customer) {
    capacity = capacity - 1;
    customersList.insert(customersList.end(),
                         customer) //Currently holding a pointer to a RAM location - later on check if a new object is needed.
    //add salary here?
}

void Trainer::removeCustomer(int id) {
    bool deleted = false;
    for (int i = 0; i < customersList.size() || deleted; ++i) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin() + i);
            deleted = true;
        }
    }
    capacity = capacity + 1;
    //minus salary here?
}

Customer *Trainer::getCustomer(int id) {
    Customer *customer;
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList[i]->getId() == id) {
            customer = customersList[i];
            break;
        }
    }
    return customer;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector <OrderPair> &Trainer::getOrders() {
    return orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector <Workout> &workout_options) {
    for (int id: workout_ids) {
        for (Workout workout: workout_options) {
            if (workout.getId() == id) {
                orderList.push_back(std::make_pair(customer_id,
                                                   workout));//check if works, there's a possibility we need to make a new object for workout
                break;
            }
        }
    }
    <<<<<<< HEAD
            == == == =

    >>>>>>> 4a06992405069b337a46a66a0c45a5fa099767d3
}

void Trainer::openTrainer() { open = true; }

void Trainer::closeTrainer() { open = false; }

int Trainer::getSalary() {
    int salary = 0;
    for (int i = 0; i < orderList.size(); ++i) {
        salary = salary + orderList[i].first;
    }
    return salary;
}

bool Trainer::isOpen() { return open; }
