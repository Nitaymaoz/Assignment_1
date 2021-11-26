#include "../include/Trainer.h"
#include "../include/Customer.h"


Trainer::Trainer(int t_capacity) : capacity(t_capacity), original_capacity(t_capacity), open(false), customersList(),
                                   orderList() {}


// Rule of 5
//Destructor
Trainer::~Trainer() {

    if (!customersList.empty()) {
        for (Customer *customer: customersList) {
            if (customer != nullptr) {
                delete customer;
                customer = nullptr;
            }
        }
    }

    customersList.clear();
    orderList.clear();
}

// Copy Constructor
Trainer::Trainer(const Trainer &other) : capacity(other.capacity), original_capacity(other.original_capacity),
                                         open(other.open), customersList(), orderList(), salary(other.salary) {
//    for(OrderPair pair: orderList){      //maybe needed
//        orderList.push_back(pair);
//    }
    orderList = std::vector<OrderPair>(other.orderList);
    for (Customer *customer: other.customersList) {
        customersList.push_back(customer->clone()); ////Added clone function check if works
    }
}

//Copy Assignment Operator
Trainer &Trainer::operator=(const Trainer &other) {

    if (this != &other) {

        customersList.clear();
        orderList.clear();
        capacity = other.capacity;
        open = other.open;
        for (Customer *customer: other.customersList) {
            customersList.push_back(customer->clone());
        }
        for (OrderPair pair: other.orderList) {
            orderList.push_back(copyWorkout(pair));
        }
    }
    return *this;
}

// Move Constructor
Trainer::Trainer(Trainer &&other) : capacity(other.capacity), original_capacity(other.original_capacity),
                                    open(other.open), customersList(), orderList(), salary(other.salary) {
    customersList = std::move(other.customersList);
    orderList = std::move(other.orderList);
}

// Move Assignment operator
const Trainer &Trainer::operator=(Trainer &&other) {
    if (this != &other) {

        customersList.clear();
        orderList.clear();
        capacity = other.capacity;
        open = other.open;
        original_capacity = other.original_capacity;
        salary = other.salary;
        customersList = std::move(other.customersList);
        orderList = std::move(other.orderList);
    }
    return *this;
}


int Trainer::getCapacity() const { return capacity; }

void Trainer::addCustomer(Customer *customer) {
    capacity = capacity - 1;
    customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    int counter = 0;
    for (Customer *customer: customersList) {
        counter++;
        if (customer->getId() == id) {
            customersList.erase(customersList.begin() + counter); //check if cause memory leak
            break;
        }
    }
    capacity = capacity + 1;
}

Customer *Trainer::getCustomer(int id) {
    Customer *customer;
    for (Customer *customer1: customersList) {
        if (customer1->getId() == id) {
            customer = customer1;
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
                                                   Workout(workout.getId(), workout.getName(), workout.getPrice(),
                                                           workout.getType())));
                break;
            }
        }
    }
}

void Trainer::openTrainer() { open = true; }

void Trainer::closeTrainer() {
    open = false;
    capacity = original_capacity;
    salary = getSalary();
    for (Customer *customer: customersList) {
        delete customer;
    }
    customersList.clear();
    orderList.clear();

}

int Trainer::getSalary() {
    int tempsalary = 0;
    for (OrderPair pair: orderList) {

        tempsalary += pair.second.getPrice();
    }
    return tempsalary + salary;

}

bool Trainer::isOpen() { return open; }

void Trainer::setOrders(std::vector <OrderPair> orders) {
    orderList.clear();
    for (OrderPair pair: orders) {
        orderList.push_back(copyWorkout(pair));
    }
}

void Trainer::addOrder(OrderPair order) {
    orderList.push_back(copyWorkout(order));
}

Trainer *Trainer::clone() {
    return new Trainer(*this);
}

OrderPair Trainer::copyWorkout(OrderPair pair) {
    return (std::make_pair(pair.first,Workout(pair.second.getId(), pair.second.getName(),
                                              pair.second.getPrice(), pair.second.getType())));
}