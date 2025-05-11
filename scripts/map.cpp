#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Configurable room dimensions
#define LOBBY_WIDTH 3
#define LOBBY_HEIGHT 3
#define GAME1_WIDTH 3
#define GAME1_HEIGHT 2
#define GAME2_WIDTH 3
#define GAME2_HEIGHT 2
#define GAME3_WIDTH 2
#define GAME3_HEIGHT 2

enum TileType {
    EMPTY,
    LOBBY,
    GAME1,
    GAME2,
    GAME3,
    CORRIDOR,
};

/*
 * UnionFind (Disjoint Set Union - DSU)
 *
 * @brief Data structure to help track connectivity between two nodes 
 *
 * This class implements the Union-Find (Disjoint Set Union) data structure,
 * which efficiently tracks a collection of disjoint sets and supports two primary operations:
 *
 * - find(i): Determines the representative (root) of the set containing element i.
 * - unite(i, j): Merges the sets containing elements i and j.
 */
class UnionFind {

    vector<int> parent;

public:
    UnionFind(int size) {

        parent.resize(size);

        // Initialize the parent array with each 
        // element as its own representative
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the
    // set that includes element i
    int find(int i) {

        // If i itself is root or representative
        if (parent[i] == i) {
            return i;
        }

        // Else recursively find the representative 
        // of the parent
        return find(parent[i]);
    }

    // Unite (merge) the set that includes element 
    // i and the set that includes element j
    void unite(int i, int j) {

        // Representative of set containing i
        int irep = find(i);

        // Representative of set containing j
        int jrep = find(j);

        // Make the representative of i's set
        // be the representative of j's set
        parent[irep] = jrep;
    }
};


pair<pair<int, int>, pair<int, int>> placeRoom(vector<vector<int>>* map, int roomHeight, int roomWidth, TileType roomID) {
    // randomize orientation of room
    if (rand() % 2 == 0) swap(roomHeight, roomWidth);

    // check if occupied
    bool canPlaceRoom;
    int yRandom, xRandom;
    do {
        canPlaceRoom = true;

        // calculate random position
        yRandom = rand() % ((*map).size() - roomHeight);
        xRandom = rand() % ((*map)[0].size() - roomWidth);

        // check if full room size is placeable
        for (int i = 0; i < roomHeight; i++) {
            for (int j = 0; j < roomWidth; j++) {
                if ((*map)[yRandom + i][xRandom + j] != 0) canPlaceRoom = false;
                continue;
            }
        }

    } while (!canPlaceRoom);

    // place room
    for (int i = 0; i < roomHeight; i++) {
        for (int j = 0; j < roomWidth; j++) {
            (*map)[yRandom + i][xRandom + j] = roomID;
        }
    }

    // return min and max corner of room
    return { {yRandom, xRandom}, {yRandom + roomHeight, xRandom + roomWidth} };
}

int connectRoom(vector<vector<int>>* map, UnionFind* uf, pair<int, int> roomMin, pair<int, int> roomMax, TileType roomID) {
    set<pair<int, int>> explored = {};                                          // already explored
    queue<pair<int, int>> frontier = {};                                        // to be explored next
    vector<vector<pair<int, int>>> previous(                                    // path reconstruction
        (*map).size(), vector<pair<int, int>>((*map)[0].size(), { -1, -1 })
    );
    pair<int, int> directions[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };        // NESW

    // explore entire room
    for (int i = roomMin.first; i < roomMax.first; i++) {
        for (int j = roomMin.second; j < roomMax.second; j++) {
            explored.insert({ i, j });
            frontier.push({ i, j });
        }
    }

    // breadth-first search
    while (!frontier.empty()) {
        // get next vertex
        pair<int, int> vertex = frontier.front();
        frontier.pop();

        // check if found new disconnected room
        if ((*map)[vertex.first][vertex.second] != roomID &&                    // check if new room other than self
            (*map)[vertex.first][vertex.second] != EMPTY &&                     // check if not empty space
            uf->find(roomID) != uf->find((*map)[vertex.first][vertex.second]))  // check if disjoint from its self
        {
            // path reconstruction
            pair<int, int> current = vertex;
            while (current != std::pair<int, int>{-1, -1}) {

                // mark path taken
                if ((*map)[current.first][current.second] == EMPTY)
                    (*map)[current.first][current.second] = roomID;

                // get previous pointer
                current = previous[current.first][current.second];
            }

            // return connected room
            return (*map)[vertex.first][vertex.second];
        }

        // look at all neighbors of current vertex
        for (int x = 0; x < 4; x++) {
            // calculate neighbor given direction
            pair<int, int> neighbor = { vertex.first + directions[x].first, vertex.second + directions[x].second };

            // check if neighbor is in bounds
            if (neighbor.first < 0 || neighbor.first >= (*map).size() ||
                neighbor.second < 0 || neighbor.second >= (*map)[0].size())
                continue;

            // explore neighbor if it hasn't been already
            if (explored.find(neighbor) == explored.end()) {
                frontier.push(neighbor);
                explored.insert(neighbor);
                previous[neighbor.first][neighbor.second] = { vertex.first, vertex.second };
            }
        }
    }

    // no path found
    return -1;
}

vector<vector<int>> generateMap(int height, int width) {
    vector<vector<int>> map(height, vector<int>(width, EMPTY));
    vector<pair<pair<int, int>, pair<int, int>>> roomPositions = {};

    // place starting room
    roomPositions.push_back(placeRoom(&map, LOBBY_HEIGHT, LOBBY_WIDTH, LOBBY));

    // place minigame rooms
    roomPositions.push_back(placeRoom(&map, GAME1_HEIGHT, GAME1_WIDTH, GAME1));
    roomPositions.push_back(placeRoom(&map, GAME2_HEIGHT, GAME2_WIDTH, GAME2));
    roomPositions.push_back(placeRoom(&map, GAME3_HEIGHT, GAME3_WIDTH, GAME3));

    // connect rooms
    UnionFind uf(roomPositions.size());
    for (int i = 0; i < roomPositions.size() - 1; i++) {
        uf.unite(i + 1,
            connectRoom(&map, &uf, roomPositions[i].first, roomPositions[i].second, (TileType)(i + 1)));
    }

    return map;
}


bool isCastableToInt(const string& str) {
    try {
        size_t pos;
        stoi(str, &pos);
        return pos == str.length();
    }
    catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {
    // argument count sanity check
    if (argc != 3) {
        cerr << "Expecting 3 arguments and got " << argc << endl;
        cerr << "Required: \"./map HEIGHT WIDTH\"" << endl;
        return 1;
    }

    // argument input sanity check
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (!isCastableToInt(arg)) {
            cerr << "Expecting integer but got " << argv[i] << endl;
            cerr << "Required: \"./map HEIGHT WIDTH\"" << endl;
            return 1;
        }
    }

    // initialize random seed
    srand(time(0));

    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    vector<vector<int>> map = generateMap(height, width);

    // create/overwrite map.txt file
    ofstream outfile("map.txt");
    if (!outfile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    // reconstruct map in terminal
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            string tile = map[j][i] == 0 ? " " : to_string(map[j][i]);
            outfile << tile << " ";
        }
        outfile << endl;
    }

    outfile.close();
    return 0;
}