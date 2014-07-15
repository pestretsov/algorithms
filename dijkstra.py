file_name = 'dijkstraData.txt'

def parser(g):
    g = [x for x in g.split("\t")]
    g.remove('\n')
    vertex = int(g[0])
    g = [x.split(",") for x in g[1:]]
    for i in range(len(g)):
        n = (int(g[i][0])-1,int(g[i][1]))
        g[i] = n
    return vertex-1, g

def add_edge(gr, new_node):
     gr[new_node[0]] = new_node[1]

def create_graph(graph):
    with open(file_name, "r") as f:
        for l in f:
            add_edge(graph, parser(l))

def dijkstra(g,s):
    # vertices processed so far
    X = [False]*len(g)
    # keeps track for all shortest path to key vertices
    A = [1000000]*len(g)
    A[s] = 0

    while False in X:
        i = 0
        min = 1000000
        while i < len(X):
            if not X[i]:
                if A[i] < min:
                    u = i
                    min = A[u]
            i+=1
        X[u] = True
        for v in g[u]:
            if (A[v[0]] > A[u] + v[1]):
                A[v[0]] = A[u] + v[1]

    return A


g = {}
create_graph(g)
dijkstra(g,0)
