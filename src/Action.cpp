
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
        for (Customer *customer: customers) {
            trainer->addCustomer(customer);
            if (trainer->getCapacity() == 0) break;
        }
        complete();
    }
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) {
    trainerId = id;
    customers = customersList;
}

//Order functions

Order::Order(int id) { trainerId = id; }

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer->isOpen()) error("Trainer does not exist or is not open");
    else {
        std::vector <Workout> workout_options = studio.getWorkoutOptions();
        for (Customer *customer: customers) {
            std::vector<int> order = customer->order(workout_options);
            trainer->order(customer->getId(), order, workout_options); //need to take order function of trainer from guy
            // need to add the action string to a string which will contain all the orders and print them at the end of the loop
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
    else {
        srctrainer.removeCustomer(id);
        if (srctrainer.getCustomers().empty())
            srctrainer.closeTrainer();
        dsttrainer.addCustomer(id);
        complete();
    }
}


