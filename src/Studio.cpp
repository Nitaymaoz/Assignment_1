#include "../include/Studio.h"
#include <fstream>
#include <algorithm>

Studio::Studio(const std::string &configFilePath) {
    std::ifstream configFile("ExampleInput.txt");
    if (configFile.is_open()) {
        std::string line;
        int counter = 0;
        int numberOfTrainers;
        int workoutIds = 0;
        while (getline(configFile, line)) {

            if (line.empty()) continue;

            if (line[0] == '#') {
                counter++
                continue;
            }

            if (counter == 2) {
                line.erase(std::remove_if(line.begin(), line.end(), isspace()), line.end());
                std::string trainerCapacity;
                for (int i = 0; i < line.size(); ++i) {
                    if (line[i] != ',') trainerCapacity.push_back(line[i])
                    else {
                        trainers.push_back(new Trainer(std::stoi(trainerCapacity)));
                        trainerCapacity.clear;
                    }
                }
            }

            if (counter == 3){
                line.erase(std::remove_if(line.begin(), line.end(), isspace()), line.end());
                std::vector<int> commaIndexes;
                int j = 0;
                for (int i = 0; i < line.size() && j < 2; ++i) {
                    if (line[i] == ','){
                        commaIndexes.push_back(i);
                        j++;
                    }
                }
                std::string name = line.substr(0,commaIndexes[0]);
                int price = std::stoi(line.substr(commaIndexes[1]+1,std::string::npos));
                WorkoutType type;
                switch(line[commaIndexes[0]+1]){
                    case 'A':
                        type = ANAEROBIC;
                        break;
                    case 'M':
                        type = MIXED;
                        break;
                    case 'C':
                        type = CARDIO;
                        break;
                }

                workout_options.push_back(new Workout(workoutIds,name,price,type));
                workoutIds++;
            }

            if (counter == 1) {
                continue;
            }

        }
    }
}

void Studio::start() {
    std::cout << "Studio is now open!"std
    ::endl;
}

//Rule of 5
//Destructor
Studio::~Studio() {
    if (trainers) {
        for (Trainer *trainer: trainers) {
            if (*trainer != nullptr) {
                delete *trainer;
                *trainer = nullptr;
            }
        }
    }
    if (actionsLog) {
        for (BaseAction *action: actionsLog) {
            if (*action != nullptr) {
                delete *action;
                *action = nullptr;
            }
        }
    }

    trainers.clear();
    actionsLog.clear();
    workout_options.clear();
}

//Copy Constructor
Studio::Studio(const Studio &other) {
    open = other.open;
    workout_options = other.workout_options;
    trainers = new std::vector<Trainer *>;
    actionsLog = new std::vector<BaseAction *>;
    for (int i = 0; i < other.trainers.size(); ++i) {
        trainers.push_back(new Trainer(other.trainers[i])); //Check if Works
    }
    for (int i = 0; i < other.actionsLog.size(); ++i) {
        actionsLog.push_back(new BaseAction(other.actionsLog[i]));
    }
}

//Copy Assignment Operator
Studio &Studio::operator=(const Studio &other) {
    if (this != &other) {

        if (trainers) trainers.clear();
        if (actionsLog) actionsLog.clear();
        workout_options = other.workout_options;
        open = other.open;
        for (Trainer *trainer: other.trainers) {
            trainers.push_back(new Trainer(*trainer));
        }
        for (BaseAction *action: other.actionsLog) {
            actionsLog.push_back(new BaseAction(action)); //check if BaseAction default copy cons. works
        }
    }
    return *this;
}

//Move Constructor
Studio::Studio(Studio &&other) {
    workout_options = other.workout_options;
    open = other.open;
    trainers = other.trainers;
    actionsLog = other.actionsLog;
    other.trainers = nullptr;
    other.actionsLog = nullptr;
}

//Move Assignment Operator
const Studio &Studio::operator=(Studio &&other) {
    if (this != &other) {

        if (trainers) trainers.clear();
        if (actionsLog) actionsLog.clear();
        workout_options = other.workout_options;
        open = other.open;
        trainers = other.trainers;
        actionsLog = other.actionsLog;
        other.trainers = nullptr;
        other.actionsLog
                = nullptr;
    }
    return *this;
}

int Studio::getNumOfTrainers() const { return trainers.size(); }

Trainer *Studio::getTrainer(int tid) { return trainers[tid]; } //what happens if ID trainer is out of bounds

const std::vector<BaseAction *> &Studio::getActionsLog() const { return &actionsLog; }

std::vector <Workout> &Studio::getWorkoutOptions() { return &workout_options; }