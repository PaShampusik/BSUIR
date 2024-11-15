from collections import defaultdict, deque


class Graph:
    def __init__(self):
        self.graph = defaultdict(list)
        self.in_degree = defaultdict(int)

    def add_edge(self, u, v, weight):
        self.graph[u].append((v, weight))
        self.in_degree[v] += 1

    def topological_sort(self):
        topo_order = []
        zero_in_degree = deque([node for node in self.graph if self.in_degree[node] == 0])

        while zero_in_degree:
            node = zero_in_degree.popleft()
            topo_order.append(node)

            for neighbor, _ in self.graph[node]:
                self.in_degree[neighbor] -= 1
                if self.in_degree[neighbor] == 0:
                    zero_in_degree.append(neighbor)

        return topo_order

    def longest_path(self, start, end):
        topo_order = self.topological_sort()
        longest_dist = {node: float('-inf') for node in self.graph}
        longest_dist[start] = 0
        predecessor = {node: None for node in self.graph}

        for node in topo_order:
            if longest_dist[node] != float('-inf'):
                for neighbor, weight in self.graph[node]:
                    if longest_dist[neighbor] < longest_dist[node] + weight:
                        longest_dist[neighbor] = longest_dist[node] + weight
                        predecessor[neighbor] = node

        path = []
        current = end
        while current is not None:
            path.append(current)
            current = predecessor[current]
        path.reverse()

        return longest_dist[end] if longest_dist[end] != float('-inf') else None, path if longest_dist[end] != float(
            '-inf') else []
# Пример использования
if __name__ == "__main__":
    g = Graph()

    # Создаем граф с весами
    g.add_edge(0, 1, 5)
    g.add_edge(0, 2, 3)
    g.add_edge(1, 3, 6)
    g.add_edge(1, 4, 2)
    g.add_edge(2, 4, 7)
    g.add_edge(3, 5, 1)
    g.add_edge(4, 5, 4)
    g.add_edge(4, 6, 3)
    g.add_edge(5, 7, 8)
    g.add_edge(6, 7, 2)
    g.add_edge(5, 8, 4)
    g.add_edge(6, 8, 5)
    g.add_edge(7, 9, 9)
    g.add_edge(7, 8, 4)
    g.add_edge(8, 9, 6)

    start_vertex = 0
    end_vertex = 9
    longest_path_value, path = g.longest_path(start_vertex, end_vertex)

    if longest_path_value is not None:
        print(f"Максимальная сумма весов наидлиннейшего пути от {start_vertex} до {end_vertex}: {longest_path_value}")
        print(f"Самый длинный путь: {' -> '.join(map(str, path))}")
    else:
        print(f"Нет пути от {start_vertex} до {end_vertex}.")