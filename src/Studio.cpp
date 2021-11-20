#include "../include/Studio.h"


void Studio::start() {std::cout <<"Studio is now open!"std::endl;}

int Studio::getNumOfTrainers() const {return trainers.size();}

Trainer *Studio::getTrainer(int tid) {return trainers[tid];} //what happens if ID trainer is out of bounds

const std::vector<BaseAction *> &Studio::getActionsLog() const {return &actionsLog;}

std::vector <Workout> &Studio::getWorkoutOptions() {return &workout_options;}