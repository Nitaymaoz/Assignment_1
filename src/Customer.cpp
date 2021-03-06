#include "../include/Customer.h"
#include <bits/stdc++.h>
//using namespace std;

//Customer Functions

Customer::Customer(std::string c_name, int c_id) : name(c_name), id(c_id) {}

std::string Customer::getName() const {return name;}

int Customer::getId() const { return id; }


//SweatyCustomer
SweatyCustomer::SweatyCustomer(std::string name, int id) :Customer(name,id){
}

std::vector<int> SweatyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> workout_plan;
    for (Workout workout: workout_options) {
        if (workout.getType() == 2) // 2 is the enum of cardio  - check if working
            workout_plan.push_back(workout.getId());
    }

    return workout_plan;
}

std::string SweatyCustomer::toString() const {
    return (getName() + "," + "swt");
}

Customer *SweatyCustomer::clone() {
    return new SweatyCustomer(*this);
}


//Cheap Customer

CheapCustomer::CheapCustomer(std::string name, int id):Customer(name,id) {}

std::vector<int> CheapCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> workout_plan;
    int minPrice = workout_options[0].getPrice();
    int minId = workout_options[0].getId();
    for (Workout workout: workout_options) {
        if (workout.getPrice() < minPrice) {
            minId = workout.getId();
            minPrice = workout.getPrice();
        }

    }
    workout_plan.push_back(minId);

    return workout_plan;
}

std::string CheapCustomer::toString() const {
    return (getName() + "," + "chp");
}

Customer *CheapCustomer::clone() {
    return new CheapCustomer(*this);
}


//Heavy Muscle Customer

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):Customer(name,id) {}

std::vector<int> HeavyMuscleCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector <std::pair<int, int>> workout_plan; // first field is price second is ID
    for (Workout workout: workout_options) {
        if (workout.getType() == 0) // get all the anaerobic workouts
            workout_plan.push_back(std::make_pair(workout.getPrice(), workout.getId()));
    }
    std::vector<int> workout_plan_output;
    if (workout_plan.empty()) return workout_plan_output; //if there are none anaerobic workouts

    std::stable_sort(workout_plan.begin(),
                     workout_plan.end()); // sort from the cheapest to the most expensive . the reason to include <bits/stdc++.h>
    for (std::pair<int, int> workout: workout_plan) {
        workout_plan_output.insert(workout_plan_output.begin(),workout.second);
    }
    return workout_plan_output;
}

std::string HeavyMuscleCustomer::toString() const {
    return (getName() + "," + "mcl");
}

Customer *HeavyMuscleCustomer::clone() {
    return new HeavyMuscleCustomer(*this);
}


//Full Body Customer

FullBodyCustomer::FullBodyCustomer(std::string name, int id) :Customer(name,id){}

std::vector<int> FullBodyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector <std::pair<int, int>> sort_cardio;
    std::vector <std::pair<int, int>> sort_anaerobic;
    std::vector <std::pair<int, int>> sort_mix;
    for (Workout workout: workout_options) {
        if (workout.getType() == 0) sort_anaerobic.push_back(std::make_pair(workout.getPrice(), workout.getId()));
        else if (workout.getType() == 1) sort_mix.push_back(std::make_pair(workout.getPrice(), workout.getId()));
        else sort_cardio.push_back(std::make_pair(workout.getPrice(), workout.getId()));
    }
    std::vector<int> workout_plan;
    if (sort_mix.empty() && sort_cardio.empty() && sort_anaerobic.empty()) return workout_plan;

    if (!sort_cardio.empty()) {
        std::stable_sort(sort_cardio.begin(), sort_cardio.end());
        workout_plan.push_back(sort_cardio.begin()->second);     //id of cheapest cardio
    }

    if (!sort_mix.empty()) {
        std::stable_sort(sort_mix.begin(), sort_mix.end());
        int highestMixPrice = sort_mix.end()->second;
        for (int i = sort_mix.size() - 2; i >= 0; i--) {
            if (sort_mix[i].first != highestMixPrice)
                workout_plan.push_back(sort_mix[i + 1].second); // id of most expensive mix (with the smallest id)
        }
    }

    if (!sort_anaerobic.empty()) {
        std::stable_sort(sort_anaerobic.begin(), sort_anaerobic.end());
        workout_plan.push_back(sort_anaerobic.begin()->second);  // id of the cheapest anaerobic
    }

    return workout_plan;
}


std::string FullBodyCustomer::toString() const {
    return (getName() + "," + "fbd");
}

Customer *FullBodyCustomer::clone() {
    return new FullBodyCustomer(*this);
}




