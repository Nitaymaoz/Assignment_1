#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) {t_capacity=capacity;}

int Trainer::getCapacity() const {return capacity;}

void Trainer::addCustomer(Customer *customer) {
    customersList.insert(customersList.begin(),customer) //currently holding a pointer to a RAM location - later on check if a new object is needed.
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

}

std::vector <OrderPair> &Trainer::getOrders() {

}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector <Workout> &workout_options) {

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
