
#include "../include/Action.h"
//BaseAction functions


void BaseAction::complete() { status = COMPLETED; }

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
    std::cout << errorMsg << std::endl;
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::addtolog(std::string action) {
    log +=action + "\n";
}

std::string BaseAction::getLog() {
    return log;
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
    if(getStatus()==COMPLETED)
        addToLog(toString() + " Completed");
    else addtolog(toString() + " Error: "+ getErrorMsg());
}

OpenTrainer::OpenTrainer(int id,
                         std::vector<Customer *> &customersList) { //maybe need to start the baseaction constructor as well
    trainerId = id;
    customers = customersList;
}

std::string OpenTrainer::toString() const {
    std::string tostring = "open "+ std::to_string(trainerId);
    for(Customer* customer: customers){
        tostring += " " + customer->toString() ;
    }
    return tostring;
}

//Order functions

Order::Order(int id) { trainerId = id; }

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer->isOpen()) error("Trainer does not exist or is not open");
    else {
        //std::string orders_list = "order "+ std::to_string(trainerId)+"/n";
        std::vector <Workout> workout_options = studio.getWorkoutOptions();
        for (Customer *customer: trainer->getCustomers()) {
            std::vector<int> order = customer->order(workout_options);
            trainer->order(customer->getId(), order, workout_options);
            //orders_list += customer->getName() + " Is Doing "+
            // need to take the string from tostring of "order"
        }
        complete();
    }
    if(getStatus()==COMPLETED)
        addToLog(toString() + " Completed");
    else addtolog(toString() + " Error: "+ getErrorMsg());
}

std::string Order::toString() const {
    return ("order "+ trainerId);
}


//MoveCustomer functions

MoveCustomer::MoveCustomer(int src, int dst, int customerId) {
    srcTrainer = src;
    dstTrainer = dst;
    id = customerId;
}

void MoveCustomer::act(Studio &studio) {
    Trainer &srctrainer = studio.getTrainer(srcTrainer); //check if reference work
    Trainer &dsttrainer = studio.getTrainer(dstTrainer);
    if (srctrainer == nullptr || dsttrainer == nullptr || !srctrainer->isOpen() || !dsttrainer->isOpen() ||
        srctrainer->getCustomer(id) ==
        nullptr || dsttrainer->getCapacity() == 0) {
        error("Cannot move customer");
    } else {//need to fix action in order to change orderlist and salary
        std::vector <OrderPair> orderlist = srctrainer.getOrders(); //reference type
        srctrainer.removeCustomer(id);
        std::vector <OrderPair> newOrderList;
        std::vector <OrderPair> removedOrders;//will only save the removed orders
        for (OrderPair pair: orderlist) {
            if (pair.first != id) {
                newOrderList.insert(newOrderList.begin(),
                                    pair);   // add all values to a new list - we'll maybe need to use makepair function
            } else {
                removedOrders.push_back(pair);
            }
        }
        orderlist = newOrderList; //using assignment  constructor

        if (srctrainer.getCustomers().empty())
            srctrainer.closeTrainer();

        // add to the new trainer customer + orders
        dsttrainer.addCustomer(id);
        std::vector <OrderPair> dstOrderList = dsttrainer.getOrders(); //reference type
        for (OrderPair pair: removedOrders) {
            dstOrderList.push_back(pair);
        }
        complete();
    }
    if(getStatus()==COMPLETED)
        addToLog(toString() + " Completed");
    else addtolog(toString() + " Error: "+ getErrorMsg());
}

std::string MoveCustomer::toString() const {
    return ("move "+ toString(srcTrainer) +" "+toString(dstTrainer) + " " +toString(id));
}

// Class Close

Close::Close(int id) {
    trainerId = id;
}

void Close::act(Studio &studio) {
    Trainer &trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer.isOpen()) {
        error("Trainer does not exist or is not open")
    } else {
        std::cout << trainer.getSalary()
                  << std::endl; //This row has to be before closeTrainer because getSalary updates the trainers salary
        trainer.closeTrainer();
        complete();
    }
    addToLog(toString() + " Completed");
}

std::string Close::toString() const {
    return ("close "+ std::to_string(trainerId));
}



//Class CloseAll

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        Close c(i);
        c.act(studio);
    }
    complete();
    addToLog(toString() + " Completed");
}

std::string CloseAll::toString() const {
    return "closeall";
}

//Class PrintWorkoutOptions

PrintWorkoutOptions::PrintWorkoutOptions() {}

void PrintWorkoutOptions::act(Studio &studio) {
    for (Workout workout: studio.getWorkoutOptions()) {
        std::cout << workout.getName() + ", " + workout.getType() + ", " + std::to_string(workout.getPrice()) << std::endl();
    }
    complete();
    addToLog(toString() + " Completed");
}

std::string PrintWorkoutOptions::toString() const {
    return ("workout_options");
}

//Class PrintTrainerStatus

PrintTrainerStatus::PrintTrainerStatus(int id) {
    trainerId = id;
}

std::string PrintTrainerStatus::toString() const {
    return ("status " + std::to_string(trainerId));
}

void PrintTrainerStatus::act(Studio &studio) {
    if (!studio.getTrainer(trainerId)->isOpen()) {
        std::cout << "closed" << std::endl;
    } else {
        std::cout << "open" << std::endl;
        std::cout << "Customers:" << std::endl;
        for (Customer *customer: studio.getTrainer(trainerId)->getCustomers()) {
            std::cout << std::to_string(customer->getId())
            " " + std::to_string(customer->getName())
                    << std::endl(); //print all customers "<customer_ID> <Customer_Name>
        }
        std::cout << "Orders:" << std::endl;
        for (OrderPair pair: studio.getTrainer(trainerId)->getOrders()){
            std::cout << pair.second.getName() + " " + std::to_string(pair.second.getPrice()) + "NIS " + std::to_string(pair.first) << std::endl;
        }
    }
    complete();
    addToLog(toString() + " Completed");
}

//Class PrintActionslog

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Studio &studio) {
    std::cout << getLog() << std::endl;
}

