#include "../include/Trainer.h"
#include "../include/Customer.h"

<<<<<<< HEAD
Trainer::Trainer(int t_capacity) {capacity=t_capacity; original_capacity=t_capacity; open=false;}
=======
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
>>>>>>> bae136f8e37df30582c4bddf5d7120d4c97431f1

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
<<<<<<< HEAD
    capacity=capacity-1;
    customersList.insert(customersList.end(),customer) //currently holding a pointer to a RAM location - later on check if a new object is needed.
=======
    capacity = capacity - 1;
    customersList.insert(customersList.end(),
                         customer) //Currently holding a pointer to a RAM location - later on check if a new object is needed.
    //add salary here?
>>>>>>> bae136f8e37df30582c4bddf5d7120d4c97431f1
}

void Trainer::removeCustomer(int id) {
    bool deleted = false;
    for (int i = 0; i < customersList.size() || deleted; ++i) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin() + i);
            deleted = true;
        }
    }
<<<<<<< HEAD
    capacity = capacity+1;
=======
    capacity = capacity + 1;
    //minus salary here?
>>>>>>> bae136f8e37df30582c4bddf5d7120d4c97431f1
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
=======
    <<<<<<< HEAD
            == == == =

    >>>>>>> 4a06992405069b337a46a66a0c45a5fa099767d3
>>>>>>> bae136f8e37df30582c4bddf5d7120d4c97431f1
}

void Trainer::openTrainer() { open = true; }

<<<<<<< HEAD
void Trainer::closeTrainer() {
    open= false;
    capacity=original_capacity;
    for(Customer* customer: customersList){
        removeCustomer(customer->getId());
    }
}
=======
void Trainer::closeTrainer() { open = false; }
>>>>>>> bae136f8e37df30582c4bddf5d7120d4c97431f1

int Trainer::getSalary() {
    for (int i = 0; i < orderList.size(); ++i) {
        salary = salary + orderList[i].first;
    }
    return salary;
}

bool Trainer::isOpen() { return open; }
