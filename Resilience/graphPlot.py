## Plot graph of 3 centralities on same window


import matplotlib.pyplot as plot


def plotGraph(fileName, lineColor, lineLabel):
	file = open(fileName, "r")

	xcoord = []		# fsa
	ycoord = []		# scf

	for line in file:
		coord = line.split()
	
		xcoord.append(float(coord[0]));
		ycoord.append(float(coord[1]));

	plot.plot(xcoord, ycoord, color = lineColor, linewidth = 2, label = lineLabel)


plot.figure(figsize = (13, 7))

plot.title("Comparing different centralities for resilience")
plot.xlabel("Fraction of Station Active [FSA]")
plot.ylabel("State of Critical Functionality [SCF]")

plotGraph("coordinatesbetweennessRank.txt", 	"red", 		"Betweenness Centrality")
plotGraph("coordinatesclosenessRank.txt", 		"blue", 	"Closeness Centrality")
plotGraph("coordinateseigenvectorRank.txt", 	"green", 	"Eigenvector Centrality")

plot.legend(loc = "lower right", frameon = True)
plot.show()