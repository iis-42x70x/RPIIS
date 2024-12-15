def max_simple_cut(incidence_matrix=None, adjacency_matrix=None):
    from collections import deque

    def is_connected(subset, adjacency_list):
        if not subset:
            return False
        visited = set()
        queue = deque([subset[0]])
        while queue:
            node = queue.popleft()
            if node not in visited:
                visited.add(node)
                queue.extend([neighbor for neighbor in adjacency_list[node] if neighbor in subset])
        return len(visited) == len(subset)

    def convert_adjacency_to_incidence(adjacency_matrix):
        V = len(adjacency_matrix)
        edges = []
        for i in range(V):
            for j in range(i + 1, V):
                if adjacency_matrix[i][j] > 0:
                    edges.append((i, j, adjacency_matrix[i][j]))
        E = len(edges)
        incidence_matrix = [[0] * E for _ in range(V)]
        for edge_index, (u, v, weight) in enumerate(edges):
            incidence_matrix[u][edge_index] = weight
            incidence_matrix[v][edge_index] = weight
        return incidence_matrix

    if incidence_matrix is None and adjacency_matrix is None:
        raise ValueError("You must provide either an incidence matrix or an adjacency matrix.")
    if adjacency_matrix is not None:
        incidence_matrix = convert_adjacency_to_incidence(adjacency_matrix)
    V = len(incidence_matrix)
    E = len(incidence_matrix[0])
    adjacency_list = {i: [] for i in range(V)}
    for edge in range(E):
        u, v = None, None
        for vertex in range(V):
            if incidence_matrix[vertex][edge] > 0:
                if u is None:
                    u = vertex
                else:
                    v = vertex
                    break
        if u is not None and v is not None:
            adjacency_list[u].append(v)
            adjacency_list[v].append(u)
    max_cut_weight = float('-inf')
    best_partition = None

    def generate_partitions(V):
        partitions = []
        for i in range(2 ** V):
            partition = []
            for j in range(V):
                partition.append((i >> j) & 1)
            partitions.append(partition)
        return partitions

    all_partitions = generate_partitions(V)

    for partition in all_partitions:
        S = [i for i in range(V) if partition[i] == 0]
        T = [i for i in range(V) if partition[i] == 1]

        if not (is_connected(S, adjacency_list) and is_connected(T, adjacency_list)):
            continue

        cut_weight = 0
        for edge in range(E):
            incident_vertices = [i for i in range(V) if abs(incidence_matrix[i][edge]) > 0]

            if len(incident_vertices) == 2:
                u, v = incident_vertices
                if (u in S and v in T) or (u in T and v in S):
                    cut_weight += abs(incidence_matrix[u][edge])

        if cut_weight > max_cut_weight:
            max_cut_weight = cut_weight
            best_partition = (S, T)

    return max_cut_weight, best_partition


if __name__ == "__main__":
    choice = input("Enter '1' to input the adjacency matrix, or '2' to input the incidence matrix: ")

    if choice == '1':
        V = int(input("Enter the number of vertices: "))
        adjacency_matrix = []
        print("Enter the adjacency matrix row by row:")
        for i in range(V):
            row = list(map(int, input().split()))
            adjacency_matrix.append(row)

        max_cut_weight, best_partition = max_simple_cut(adjacency_matrix=adjacency_matrix)

    elif choice == '2':
        V = int(input("Enter the number of vertices: "))

        E = int(input("Enter the number of edges: "))
        incidence_matrix = []
        print("Enter the incidence matrix row by row:")
        for i in range(V):
            row = list(map(int, input().split()))
            incidence_matrix.append(row)
        max_cut_weight, best_partition = max_simple_cut(incidence_matrix=incidence_matrix)

    else:
        print("Invalid choice")
        exit()

    print("Max cut weight:", max_cut_weight)
    print("Optimal vertex partition:", best_partition)
