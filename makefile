# All Targets
all: bin/studio

bin/studio: bin/main.o bin/Customer.o bin/Action.o bin/Workout.o bin/Trainer.o bin/Studio.o
#bin/Customer.o bin/action.o bin/workout.o bin/Trainer.o bin/Studio.o //TODO copy this to line 4
	@echo 'Building target: main'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/studio bin/Action.o bin/Studio.o bin/Trainer.o bin/Workout.o bin/main.o
	#bin/studio bin/action.o bin/Studio.o bin/Trainer.o bin/workout.o bin/main.o//TODO copy this to line 4
	@echo 'Finished building target: main'
	@echo ' '


bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

bin/Workout.o: src/Workout.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Workout.o src/Workout.cpp

bin/Studio.o: src/Studio.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Studio.o src/Studio.cpp

bin/Trainer.o: src/Trainer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Trainer.o src/Trainer.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp