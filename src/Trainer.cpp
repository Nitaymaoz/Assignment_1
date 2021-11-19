#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) {capacity=t_capacity; open=false;}

int Trainer::getCapacity() const {return capacity;}

void Trainer::addCustomer(Customer *customer) {
    customersList.insert(customersList.end(),customer) //currently holding a pointer to a RAM location - later on check if a new object is needed.
}

void Trainer::removeCustomer(int id) {
    bool deleted = false;
    for(int i=0;i<customersList.size()||deleted;++i){
        if (customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i);
            deleted= true;
        }
    }
}

Customer *Trainer::getCustomer(int id) {
    bool found= false;
    for (int i = 0; i < customersList.size() || found; ++i) {
        if (customersList[i]->getId()==id) return *customersList[i];
    }
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector <OrderPair> &Trainer::getOrders() {
    return orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector <Workout> &workout_options) {
    for(int id : workout_ids){
        for(Workout workout:workout_options){
            if (workout.getId()==id){
                orderList.push_back(std::make_pair(customer_id,workout));//check if works, there's a possibility we need to make a new object for workout
                break;
            }
        }
    }

}

void Trainer::openTrainer() {open= true;}

void Trainer::closeTrainer() {open= false;}

int Trainer::getSalary() {
    int salary = 0;
    for (int i = 0; i < orderList.size(); ++i) {
        salary = salary + orderList[i].first;
    }
    return salary;
}

bool Trainer::isOpen() {return open;}
