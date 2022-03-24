#ifndef MAP_H
#define MAP_H
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <cstring>
#include <cmath>
#include <queue>
class Map
{
private:
    int n, m;
    char ch[205][205], bombMap[205][205], preCh[205][205];
    bool bombing[205][205];
    int propsType[205][205];
    const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    void generateMap(void);
    inline bool check(int x, int y);
    void dfs(int x, int y);
    bool checkMap(void);
public:
    Map(int x, int y);
    void printMap(void);
    int movePlayer(int role, int moveType, std::pair<int, int> location);
    bool bombPut(std::pair<int, int> location);
    int bombBomb(std::pair<int, int> location, int power);
    void bombLeft(std::pair<int, int> location, int power);
    bool notStep(std::pair<int, int> location);
    int getVal(std::pair<int, int> location, int id);
    bool existSoftWallOrPlayers(std::pair<int, int> location, int len);
    int shortestPath(std::pair<int, int> location1, std::pair<int, int> location2);
};
#endif // MAP_H
