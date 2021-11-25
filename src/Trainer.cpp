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

    orderList = std::vector<OrderPair>(other.orderList);
    for (int i = 0; i < other.customersList.size(); ++i) {
        customersList.push_back(other.customersList[i]->clone()); ////Added clone function check if works
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
            OrderPair newPair = std::make_pair(pair.first, pair.second);
            orderList.push_back(newPair); //check new pair
        }
    }
    return *this;
}

// Move Constructor
Trainer::Trainer(Trainer &&other) {
    capacity = other.capacity;
    open = other.open;
    original_capacity = other.original_capacity;
    salary = other.salary;
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
    bool deleted = false;
    for (int i = 0; i < customersList.size() || deleted; ++i) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin() + i); //check if cause memory leak
            deleted = true;
        }
    }
    capacity = capacity + 1;
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
    for (OrderPair pair : orderList) {

        tempsalary += pair.second.getPrice();
    }
    return tempsalary + salary;

}

bool Trainer::isOpen() { return open; }

void Trainer::setOrders(std::vector <OrderPair> orders) {
    orderList.clear();
    for(OrderPair pair : orders){
        orderList.push_back(pair);
    }
}

void Trainer::addOrder(OrderPair order) {
    orderList.push_back(order);
}
