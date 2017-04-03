from igraph import *
f = open("output.txt")
n = int(f.readline().strip())
graph = []
for i in range(n):
	graph.append((f.readline().strip().split(' ')))

#print (graph);

g = Graph()
g.add_vertices(n)
#g.add_edges([(0,1),(1,2)])
i=0
for i in range(n):
	for j in range(n):
		if i>j and graph[i][j]=='1':
			g.add_edges([(i,j)]);

color = f.readline().strip().split(' ')
col_dict = {"1" : "red","2" : "green","3" : "blue"}
i=0
g.vs["color"] = [col_dict[color[i]] for i in range(n)]
i=0
g.vs["name"] = [i+1 for i in range(n)]
g.vs["label"] = g.vs["name"]
layout = g.layout("kk")
plot(g, layout = layout)