
#include "../include/Action.h"
//BaseAction functions

void BaseAction::complete() { status = COMPLETED; }

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
    std::cout << errorMsg << std::endl;
}


//OpenTrainer functions

void OpenTrainer::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer->isOpen()) { error("Workout Session does not exist or is already open."); }
    else {
        trainer->openTrainer(); // Opening workout session
        for (Customer *customer: customers) {
            trainer->addCustomer(customer);
            if (trainer->getCapacity() == 0) break;
        }
        complete();
    }
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) { //maybe need to start the baseaction constructor as well
    trainerId = id;
    customers = customersList;
}

//Order functions

Order::Order(int id) { trainerId = id; }

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer->isOpen()) error("Trainer does not exist or is not open");
    else {
        //std::string orders_list = "order "+ std::to_string(trainerId)+"/n";
        std::vector <Workout> workout_options = studio.getWorkoutOptions();
        for (Customer *customer: customers) {
            std::vector<int> order = customer->order(workout_options);
            trainer->order(customer->getId(), order, workout_options);
            //orders_list += customer->getName() + " Is Doing "+
            // need to take the string from tostring of "order"
        }
        complete();
    }
}


//MoveCustomer functions

MoveCustomer::MoveCustomer(int src, int dst, int customerId) {
    srcTrainer = src;
    dstTrainer = dst;
    id = customerId;
}

void MoveCustomer::act(Studio &studio) {
    Trainer &srctrainer = studio.getTrainer(srcTrainer);
    Trainer &dsttrainer = studio.getTrainer(dstTrainer);
    if (srctrainer == nullptr || dsttrainer == nullptr || !srctrainer->isOpen() || !dsttrainer->isOpen() ||
        srctrainer->getCustomer(id) ==
        nullptr || dsttrainer->getCapacity() == 0) {
        error("Cannot move customer");
    }
    else {//need to fix action in order to change orderlist and salary
        std::vector<OrderPair> orderlist = srctrainer.getOrders(); //reference type
        srctrainer.removeCustomer(id);
        std::vector<OrderPair> newOrderList;
        std::vector<OrderPair> removedOrders;//will only save the removed orders
        for(OrderPair pair : orderlist){
            if (pair.first!=id){
                newOrderList.insert(newOrderList.begin(), pair);   // add all values to a new list - we'll maybe need to use makepair function
            }
            else{
                removedOrders.push_back(pair);
            }
        }
        orderlist = newOrderList; //using copy constructor

        if (srctrainer.getCustomers().empty())
            srctrainer.closeTrainer();

        // add to the new trainer customer + orders
        dsttrainer.addCustomer(id);
        std::vector<OrderPair> dstOrderList = dsttrainer.getOrders(); //reference type
        for(OrderPair pair : removedOrders){
            dstOrderList.push_back(pair);
        }
        complete();
    }
}

// Class Close

Close::Close(int id) {
    trainerId=id;
}

void Close::act(Studio &studio) {
    Trainer& trainer = studio.getTrainer(trainerId);
    if (trainer== nullptr||!trainer.isOpen()){
        error("Trainer does not exist or is not open")
    }
    else{
        std::cout << trainer.getSalary() << std::endl; //This row has to be before closeTrainer because getSalary updates the trainers salary
        trainer.closeTrainer();
    }
}


