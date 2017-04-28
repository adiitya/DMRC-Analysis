## Directories
CENTRALITY_DIR 	:= Centrality
EFFICIENCY_DIR 	:= Efficiency
NOVELTY_DIR 	:= Novelty
RESILIENCE_DIR 	:= Resilience
STATION_DIR 	:= StationData

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


## Create new connection in the network
runNovelty: novelty
	cd $(NOVELTY_DIR) &&\
	./newConnections.exe

novelty: $(NOVELTY_DIR)/newConnections.exe


noveltyGraph: novelty
	cd $(NOVELTY_DIR) &&\
	python graphPlot.py

resilienceGraph: resilience
	cd $(RESILIENCE_DIR) &&\
	python graphPlot.py


## --------------------------------------------------


clean: 
	rm $(CENTRALITY_DIR)/*.exe
	rm $(EFFICIENCY_DIR)/*.exe
	rm $(NOVELTY_DIR)/*.exe
	rm $(RESILIENCE_DIR)/*.exe


%.exe: %.cpp
	$(COM) $< -o $@ $(CFLAG) $(CPP11)