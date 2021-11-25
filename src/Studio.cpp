#include "../include/Studio.h"
#include <fstream>
#include <algorithm>
#include <map>

Studio::Studio(const std::string &configFilePath) { // **Check if needs to throw exceptions**
    std::ifstream configFile("ExampleInput.txt");
    if (configFile.is_open()) {
        std::string line;
        int counter = 0;
        int numberOfTrainers;
        int workoutIds = 0;
        while (getline(configFile, line)) {

            if (line.empty()) continue;

            if (line[0] == '#') {
                counter++;
                continue;
            }

            if (counter == 2) {
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                std::string trainerCapacity;
                for (int i = 0; i < line.size(); ++i) {
                    if (line[i] != ',') trainerCapacity.push_back(line[i]);
                    else {
                        trainers.push_back(new Trainer(std::stoi(trainerCapacity)));
                        trainerCapacity.clear();
                    }
                }
            }

            if (counter == 3) {
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                std::vector<int> commaIndexes;
                int j = 0; // counts the commas
                for (int i = 0; i < line.size() && j < 2; ++i) {
                    if (line[i] == ',') {
                        commaIndexes.push_back(i);
                        j++;
                    }
                }
                std::string name = line.substr(0, commaIndexes[0]);
                int price = std::stoi(line.substr(commaIndexes[1] + 1, std::string::npos));
                WorkoutType type;
                switch (line[commaIndexes[0] + 1]) {
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

                workout_options.push_back(Workout(workoutIds, name, price, type)); // check if need 'new'
                workoutIds++;
            }


        }
    }
}

void Studio::start() {
    open = true;
    int customerid = 0;
    std::cout << "Studio is now open!" << std::endl;
    while (open) {
        std::string input;
        std::cin >> input;
        std::string action = input.substr(0, input.find(" "));
        std::map<std::string, int> m{{"open",            1},
                                     {"order",           2},
                                     {"move",            3},
                                     {"close",           4},
                                     {"closeall",        5},
                                     {"workout_options", 6},
                                     {"status",          7},
                                     {"log",             8},
                                     {"backup",          9},
                                     {"restore",         10}};

        switch (m[action]) {

            case 1: {
                input.erase(0, 5);
                std::string trainerid = input.substr(0, input.find(" "));
                input.erase(0, input.find(" ") + 1);
                std::vector < Customer * > customerList;
                int capacity = trainers[std::stoi(trainerid)]->getCapacity();
                int trainercounter = 0;
                while (!input.empty() || capacity > trainercounter) {
                    customerList.push_back(Customer::makeNewCustomer(input, customerid));
                    trainercounter++;
                    customerid++;
                    input.erase(0, input.find(" ") + 1);
                }
                OpenTrainer::OpenTrainer(trainerid, customerList).act(this);
            }

            case 2: {
                std::string trainerid = input.substr(6, std::string::npos);
                Order::Order(std::stoi(trainerid)).act(this);
            }

            case 3: {
                input.erase(0, 5);
                std::string srctrainer = input.substr(0, input.find(" "));
                input.erase(0, input.find(" ") + 1);
                std::string dsttrainer = input.substr(0, input.find(" "));
                input.erase(0, input.find(" ") + 1);
                std::string customerid = input;
                MoveCustomer::MoveCustomer(std::stoi(srctrainer), std::stoi(dsttrainer), std::stoi(customerid)).act(
                        this);
            }

            case 4: {
                std::string trainerId = input.substr(6);
                Close::Close(std::stoi(trainerId)).act(this);
            }

            case 5: {
                CloseAll::CloseAll().act(this);
            }

            case 6: {
                PrintWorkoutOptions::PrintWorkoutOptions().act(this);
            }

            case 7: {
                std::string trainerid = input.substr(7);
                PrintTrainerStatus::PrintTrainerStatus(std::stoi(trainerid)).act(this);
            }
            case 8: {
                PrintActionsLog::PrintActionsLog().act(this);
            }
            case 9: {
                BackupStudio::BackupStudio().act(this);
            }

            case 10: {
                RestoreStudio::RestoreStudio().act(this);
            }
        }
    }

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
Studio::Studio(const Studio &other) : open(other.open), trainers(), workout_options(other.workout_options),
                                      actionsLog() {

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

const std::vector<BaseAction *> &Studio::getActionsLog() const { return actionsLog; }

std::vector <Workout> &Studio::getWorkoutOptions() { return workout_options; }

void Studio::setOpen(bool state) { open = state; }

std::string Studio::getWorkOutName(int workoutid) {
    for (Workout workout: workout_options) {
        if (workout.getId() == workoutid) return workout.getName();
    }
}