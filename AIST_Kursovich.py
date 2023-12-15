class DisjointSet:
    def __init__(self, vertices):
        self.parent = {vertex: vertex for vertex in vertices}
        self.rank = {vertex: 0 for vertex in vertices}

    def find(self, vertex):
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]

    def union(self, root1, root2):
        if self.rank[root1] < self.rank[root2]:
            self.parent[root1] = root2
        elif self.rank[root1] > self.rank[root2]:
            self.parent[root2] = root1
        else:
            self.parent[root1] = root2
            self.rank[root2] += 1


def kruskal(vertices, graph):
    edges = []
    for i in range(len(vertices)):
        for j in range(i + 1, len(vertices)):
            if graph[i][j] != 0:
                edges.append((vertices[i], vertices[j], graph[i][j]))

    edges.sort(key=lambda x: x[2])

    result = []
    disjoint_set = DisjointSet(vertices)

    total_weight = 0

    for edge in edges:
        root1 = disjoint_set.find(edge[0])
        root2 = disjoint_set.find(edge[1])

        if root1 != root2:
            result.append((edge[0], edge[1]))
            disjoint_set.union(root1, root2)
            total_weight += edge[2]

    return result, total_weight

with open('uuu.txt', 'r') as file:
    lines = file.readlines()
    vertices = lines[0].split()
    graph = [list(map(int, line.split())) for line in lines[1:]]

result, total_weight = kruskal(vertices, graph)
for pair in result:
    print(f'{pair[0]} {pair[1]}')
print(total_weight)
