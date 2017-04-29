import matplotlib.pyplot as plt
x=list(range(154))
y=list(range(154))

def plotgraph(flag):
	file=open("../StationData/final_output.txt", "r")
	lines=file.readlines()
	file.close()
	i=1
	length=len(lines)

	plt.figure(figsize = (13, 8))
	if flag == 0:
		plt.title("Delhi Metro Map")
	else:
		plt.title("Delhi Metro combined with new connections")

	while i<length:
		arr=lines[i].split()
		i=i+1

		xc=[x[int(arr[0])], x[int(arr[1])]]
		yc=[y[int(arr[0])], y[int(arr[1])]]

		plt.plot(xc, yc, color = "red")

	if flag==0:
		plt.ylim(77, 77.4)
		plt.xlim(28.3, 28.8)	
		plt.show()

	if flag == 0:
		plt.figure(figsize = (13, 8))
		plt.title("New connection to be added")
	
	file=open("newEdges.txt", "r")
	for line in file:
		arr=line.split();
		xc=[x[int(arr[0])], x[int(arr[1])]]
		yc=[y[int(arr[0])], y[int(arr[1])]]
		plt.plot(xc, yc, color = "green")

	plt.ylim(77, 77.4)
	plt.xlim(28.3, 28.8)	
	plt.show()


file=open("../StationData/lat_long.txt", "r")
for line in file:
	arr=line.split()
	x[int(arr[0])]=float(arr[1]);
	y[int(arr[0])]=float(arr[2]);
file.close()

plotgraph(0)
plotgraph(1)