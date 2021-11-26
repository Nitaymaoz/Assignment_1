#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

class BaseAction; //added forward declaration
class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    ~Studio(); // Destructor
    Studio(const Studio& other); // Copy Constructor
    Studio& operator= (const Studio &other); // Copy Assignment Operator
    Studio(Studio&& other); // Move Constructor
    const Studio& operator=(Studio&& other); // Move Assignment Operator
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    void setOpen(bool state); //Set open field
    std::string getWorkOutName(int workoutid);
    Customer* makeNewCustomer(std::string input,int id);
    int getCustomerID();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    int customerid;
};

#endif