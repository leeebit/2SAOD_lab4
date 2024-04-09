#include <iostream>
#include <vector>

using namespace std;

// Функция для проверки, можно ли добавить вершину v в путь, текущий путь path и матрицу смежности graph
bool isSafe(int v, const vector<int>& path, const vector<vector<int>>& graph) {
    int n = graph.size();
    if (graph[path.back()][v] == 0) // Проверяем, существует ли ребро между последней вершиной в пути и v
        return false;

    // Проверяем, посещали ли уже вершину v в текущем пути
    for (int vertex : path)
        if (vertex == v)
            return false;

    return true;
}

// Функция для поиска Гамильтонова цикла в графе
bool hamiltonianCycleUtil(vector<int>& path, vector<vector<int>>& graph) {
    int n = graph.size();
    if (path.size() == n) { // Если путь содержит все вершины, значит, Гамильтонов цикл найден
        if (graph[path.back()][path[0]] == 1) { // Проверяем, существует ли ребро между последней вершиной и первой
            return true;
        }
        else {
            return false; // Если такого ребра нет, Гамильтонов цикл не закрытый, возвращаем false
        }
    }

    // Попробовать добавить каждую вершину к текущему пути
    for (int v = 1; v < n; ++v) {
        if (isSafe(v, path, graph)) {
            path.push_back(v);
            if (hamiltonianCycleUtil(path, graph)) // Рекурсивный вызов для поиска следующей вершины
                return true;
            path.pop_back(); // Если текущий путь не приводит к Гамильтонову циклу, удаляем вершину из пути
        }
    }
    return false; // Если не удалось найти Гамильтонов цикл
}

// Функция для поиска Гамильтонова цикла в графе
bool hamiltonianCycle(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path;
    path.push_back(0); // Начинаем с вершины 0

    if (!hamiltonianCycleUtil(path, graph)) {
        cout << "Гамильтонов цикл не существует\n";
        return false;
    }

    // Выводим Гамильтонов цикл
    cout << "Гамильтонов цикл существует: ";
    for (int vertex : path)
        cout << vertex << " ";
    cout << path[0] << endl;
    return true;
}

int main() {
    system("chcp 1251");
    int n;
    cout << "Введите количество вершин в графе: ";
    cin >> n;

    // Ввод матрицы смежности графа
    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Введите матрицу смежности графа:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> graph[i][j];

    hamiltonianCycle(graph);

    return 0;
}
