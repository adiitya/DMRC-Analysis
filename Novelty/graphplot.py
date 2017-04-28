import matplotlib.pyplot as plt
x=list(range(154))
y=list(range(154))

def plotgraph(flag):
	file=open("../StationData/final_output.txt", "r")
	lines=file.readlines()
	file.close()
	i=1
	length=len(lines)
	#import re
	while i<length:
		#arr=re.split(' |\t', lines[i])
		arr=lines[i].split()
		i=i+1
		#print(arr)
		xc=[x[int(arr[0])], x[int(arr[1])]]
		yc=[y[int(arr[0])], y[int(arr[1])]]
		#print(xc)
		#print(yc)
		plt.plot(xc, yc)

	if flag==0:
		plt.ylim(77, 77.4)
		plt.xlim(28.3, 28.8)	
		plt.show()

	file=open("newEdges.txt", "r")
	for line in file:
		arr=line.split();
		xc=[x[int(arr[0])], x[int(arr[1])]]
		yc=[y[int(arr[0])], y[int(arr[1])]]
		plt.plot(xc, yc)

	plt.ylim(77, 77.4)
	plt.xlim(28.3, 28.8)	
	plt.show()


file=open("lat_long.txt", "r")
for line in file:
	arr=line.split()
	x[int(arr[0])]=float(arr[1]);
	y[int(arr[0])]=float(arr[2]);
file.close()

plotgraph(0)
plotgraph(1)
# file=open("../StationData/final_output.txt", "r")
# lines=file.readlines()
# file.close()
# i=1
# length=len(lines)
# #import re
# while i<length:
# 	#arr=re.split(' |\t', lines[i])
# 	arr=lines[i].split()
# 	i=i+1
# 	#print(arr)
# 	xc=[x[int(arr[0])], x[int(arr[1])]]
# 	yc=[y[int(arr[0])], y[int(arr[1])]]
# 	#print(xc)
# 	#print(yc)
# 	plt.plot(xc, yc)

# plt.ylim(77, 77.4)
# plt.xlim(28.3, 28.8)	
# plt.show()

# file=open("newEdges.txt", "r")
# for line in file:
# 	arr=line.split();
# 	xc=[x[int(arr[0])], x[int(arr[1])]]
# 	yc=[y[int(arr[0])], y[int(arr[1])]]
# 	plt.plot(xc, yc)

# plt.ylim(77, 77.4)
# plt.xlim(28.3, 28.8)	
# plt.show()

