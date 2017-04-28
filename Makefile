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


## Efficiency calculation ##
runEfficiency: efficiency
	cd $(EFFICIENCY_DIR) &&\
	./efficiencySmallWorld.exe

efficiency: $(EFFICIENCY_DIR)/efficiencySmallWorld.exe


## Centrality calculation ##
runCentrality: centrality
	cd $(CENTRALITY_DIR) &&\
	./rankBetweennessCentrality.exe &&\
	./rankClosenessCentrality.exe &&\
	./rankEigenvectorCentrality.exe

centrality: $(CENTRALITY_DIR)/rankClosenessCentrality.exe $(CENTRALITY_DIR)/rankEigenvectorCentrality.exe $(CENTRALITY_DIR)/rankBetweennessCentrality.exe


## Compare centralities
runResilience: resilience
	cd $(RESILIENCE_DIR) &&\
	./compareCentralities.exe

resilience: $(RESILIENCE_DIR)/compareCentralities.exe


## --------------------------------------------------


%.exe: %.cpp
	$(COM) $< -o $@ $(CFLAG) $(CPP11)