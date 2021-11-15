#include "../include/Customer.h"

//Customer Functions

Customer::Customer(std::string c_name, int c_id) {}

std::string Customer::getName() const { return name; }

int Customer::getId() const { return id; }

std::vector<int> Customer::order(const std::vector <Workout> &workout_options) {}

std::string Customer::toString() const {}

//SweatyCustomer

std::vector<int> SweatyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> workout_plan;
    for (Workout workout: workout_options) {
        if (workout.getType() == 2) // 2 is the enum of cardio  - check if working
            workout_plan.insert(workout.getId())
    }

    return workout_plan;
}

//Cheap Customer

std::vector<int> CheapCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> workout_plan;
    int minPrice=workout_options[0].getPrice();
    int minId=workout_options[0].getId();
    for (Workout workout: workout_options) {
        if (workout.getPrice()<minPrice)
            minId=workout.getId();
    }
    workout_plan.insert(minId);

    return workout_plan;
}

//Heavy Muscle Customer

std::vector<int> HeavyMuscleCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<std::pair<int,int>> workout_plan; // first field is ID second is Price
    for(Workout workout : workout_options){
        if (workout.getType()==0) // get all the anaerobic workouts
            workout_plan.std::make_pair(workout.getId(),workout.getPrice()); // check if works
    }

    //add sort by value from most expensive to cheapest


}