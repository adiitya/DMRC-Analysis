## Directories
CENTRALITY_DIR 	:= Centrality
EFFICIENCY_DIR 	:= Efficiency-Calc
NOVELTY_DIR 	:= Novelty
RESILIENCE_DIR 	:= Resilience
STATTION_DIR 	:= StattionData

## Compiler
COM 	:= g++
CFLAG 	:= -Wall -Wextra
CPP11 	:= -std=c++11


##-------------------------------------------------

runEfficiency:
	cd $(EFFICIENCY_DIR) &&\
	./efficiency

efficiency: $(EFFICIENCY_DIR)/efficiencySmallWorld.cpp
	$(COM) $< -o $(EFFICIENCY_DIR)/efficiency $(CFLAG) $(CPP11)

