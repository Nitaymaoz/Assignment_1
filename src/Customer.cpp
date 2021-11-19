#include "../include/Customer.h"
#include <bits/stdc++.h>
//using namespace std;

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
    std::vector<std::pair<int,int>> workout_plan; // first field is price second is ID
    for(Workout workout : workout_options){
        if (workout.getType()==0) // get all the anaerobic workouts
            workout_plan.push_back(std::make_pair(workout.getPrice(),workout.getId()));
    }
    std::vector<int> workout_plan_output;
    if (workout_plan.empty()) return workout_plan_output; //if there are none anaerobic workouts

    std::stable_sort(workout_plan.begin(),workout_plan.end()); // sort from the cheapest to the most expensive . the reason to include <bits/stdc++.h>
    for(std::pair<int,int> id:workout_plan){
        workout_plan_output.push_back(id.second);
    }
    return workout_plan_output;
}


//Full Body Customer

std::vector<int> FullBodyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<std::pair<int,int>> sort_cardio;
    std::vector<std::pair<int,int>> sort_anaerobic;
    std::vector<std::pair<int,int>> sort_mix;
    for(Workout workout : workout_options){
        if (workout.getType()==0) sort_anaerobic.push_back(std::make_pair(workout.getPrice(),workout.getId()))
        else if (workout.getType()==1) sort_mix.push_back(std::make_pair(workout.getPrice(),workout.getId()))
        else sort_anaerobic.push_back(std::make_pair(workout.getPrice(),workout.getId()))
    }
    std::vector<int> workout_plan;
    if (sort_cardio.empty() || sort_mix.empty() || sort_anaerobic.empty()) return workout_plan;

    std::stable_sort(sort_cardio.begin(),workout_plan.end());
    std::stable_sort(sort_anaerobic.begin(),workout_plan.end());
    std::stable_sort(sort_mix.begin(),workout_plan.end());
    workout_plan.push_back(sort_cardio.begin()->second);    //id of cheapest cardio
    workout_plan.push_back(sort_mix.end()->second);         // id of most expensive mix
    workout_plan.push_back(sort_anaerobic.begin()->second); // id of cheapest anaerobic
    return workout_plan;
}

