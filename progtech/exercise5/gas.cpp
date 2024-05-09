#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct PathCost {
    int distance;
    int destination;
};

bool isPossiblePath(int startCity, int tankCapacity, int endCity, vector<int>& path, vector<vector<PathCost>>& cityMap, vector<bool>& visited) {
    path.push_back(startCity);
    visited[startCity] = true;

    if (startCity == endCity) {
        return true;
    }

    for (const auto& city : cityMap[startCity]) {
        if (city.distance <= tankCapacity && !visited[city.destination]) {
            if (isPossiblePath(city.destination, tankCapacity, endCity, path, cityMap, visited)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

int getMinimumRefills(int tankCapacity, const vector<int>& path, const vector<vector<int>>& roadInfo) {
    int refills = 1;
    int remainingCapacity = tankCapacity;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int currentCity = path[i];
        int nextCity = path[i + 1];
        remainingCapacity -= roadInfo[currentCity][nextCity];

        if (remainingCapacity < 0) {
            remainingCapacity = tankCapacity - roadInfo[currentCity][nextCity];
            refills++;
        }
    }

    if (remainingCapacity < 0) {
        refills++;
    }

    return refills;
}

int main() {
    int numCities, numRoads, city1, city2, distance, numQueries, startCity, endCity, tankCapacity;
    cin >> numCities >> numRoads;

    vector<vector<PathCost>> cityMap(numCities);
    vector<vector<int>> roadInfo(numCities, vector<int>(numCities, 0));

    for (int i = 0; i < numRoads; ++i) {
        cin >> city1 >> city2 >> distance;
        PathCost diesel1 = {distance, city2};
        PathCost diesel2 = {distance, city1};
        cityMap[city1].push_back(diesel1);
        cityMap[city2].push_back(diesel2);
        roadInfo[city1][city2] = distance;
        roadInfo[city2][city1] = distance;
    }

    cin >> numQueries;

    for (int i = 0; i < numQueries; ++i) {
        cin >> startCity >> endCity >> tankCapacity;
        vector<bool> visited(numCities, false);
        vector<int> path;

        if (isPossiblePath(startCity, tankCapacity, endCity, path, cityMap, visited)) {
            cout << "POSSIBLE: " << getMinimumRefills(tankCapacity, path, roadInfo) << " fill(s),";
            for (int city : path) {
                cout << " " << city;
            }
            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
