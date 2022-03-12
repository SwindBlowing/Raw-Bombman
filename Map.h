#ifndef MAP_H
#define MAP_H
#include<ctime>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <cstring>
class Map
{
private:
    int n, m;
    char ch[205][205], bombMap[205][205],preCh[205][205];
    bool bombing[205][205];
    int propsType[205][205];
    const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
public:
    Map(int x, int y);
    void generateMap(void);
    void printMap(void);
    int movePlayer(int role, int moveType, std::pair<int, int> location);
    void bombPut(std::pair<int, int> location);
    int bombBomb(std::pair<int, int> location, int power);
    void bombLeft(std::pair<int, int> location, int power);
    bool notStep(std::pair<int, int> location);
    inline bool check(int x, int y);
};

Map::Map(int x, int y)
{
    n = x;
    m = y;
    generateMap();
}
inline bool Map::check(int x, int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m;
}
void Map::generateMap(void)
{
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            bombMap[i][j] = ' ';
            preCh[i][j] = ' ';
            propsType[i][j] = ' ';
            if (i + j <= 3 || i + m - j <= 2 || n - i + j <= 2 || n - i + m - j <= 1) {
                ch[i][j] = ' ';
                continue;
            }
            int p = rand() % 10;
            if (p < 2) ch[i][j] = '#';
            else if (p < 5) ch[i][j] = ' ';
            else {
                ch[i][j] = '*';
                p = rand() % 10;
                if (!p) {
                    p = rand() % 2;
                    propsType[i][j] = 'A' + p;
                }
            }
        }
    ch[1][1] = '1'; ch[1][m] = '2';
    ch[n][1] = '3'; ch[n][m] = '4';
}
void Map::printMap(void)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            putchar(ch[i][j]);
        putchar('\n');
    }
}
int Map::movePlayer(int role, int moveType, std::pair<int, int> location)
{
    int s = location.first, t = location.second;
    if (s + dx[moveType] < 1 || s + dx[moveType] > n || t + dy[moveType] < 1 || t + dy[moveType] > m) return 0;
    if (ch[s + dx[moveType]][t + dy[moveType]] == '*' || ch[s + dx[moveType]][t + dy[moveType]] == '#') return 0;
    if (ch[s + dx[moveType]][t + dy[moveType]] >= '1' && ch[s + dx[moveType]][t + dy[moveType]] <= '4') return 0;
    if (bombMap[s][t] == '!') ch[s][t] = bombMap[s][t];
    else ch[s][t] = preCh[s][t];
    char usedCh = ch[s + dx[moveType]][t + dy[moveType]];
    ch[s + dx[moveType]][t + dy[moveType]] = role + '0';
    return usedCh == ' ' ? 1 : (usedCh - 'A' + 2);
}
void Map::bombPut(std::pair<int, int> location)
{
    int s = location.first, t = location.second;
    bombMap[s][t] = '!';
}
int Map::bombBomb(std::pair<int, int> location, int power)
{
    int num = 0;
    int s = location.first, t = location.second;
    bombing[s][t] = 1;
    for (int k = 0; k < 4; k++)
        for (int i = 1; i <= power; i++)
            if (check(s + i * dx[k], t + i * dy[k])) {
                if (ch[s + i * dx[k]][t + i * dy[k]] == '#') break;
                if (ch[s + i * dx[k]][t + i * dy[k]] == '*') num++;
                preCh[s + i * dx[k]][t + i * dy[k]] = ch[s + i * dx[k]][t + i * dy[k]];
                if (k == 0 || k == 2) ch[s + i * dx[k]][t + i * dy[k]] = '-';
                else ch[s + i * dx[k]][t + i * dy[k]] = '|';
                bombing[s + i * dx[k]][t + i * dy[k]] = 1;
            }
    for (int k = 0; k < 4; k++)
        for (int i = 1; i <= power; i++)
            if (check(s + i * dx[k], t + i * dy[k]) && preCh[s + i * dx[k]][t + i * dy[k]] == '!')
                preCh[s + i * dx[k]][t + i * dy[k]] = ' ';
    return num;
}
void Map::bombLeft(std::pair<int, int> location, int power)
{
    int s = location.first, t = location.second;
    bombing[s][t] = 0;
    bombMap[s][t] = ' ';
    ch[s][t] = ' ';
    for (int k = 0; k < 4; k++)
        for (int i = 1; i <= power; i++)
            if (check(s + i * dx[k], t + i * dy[k])) {
                 if (ch[s + i * dx[k]][t + i * dy[k]] == '#') break;
                 ch[s + i * dx[k]][t + i * dy[k]] = preCh[s + i * dx[k]][t + i * dy[k]];
                 preCh[s + i * dx[k]][t + i * dy[k]] = ' ';
                 bombing[s + i * dx[k]][t + i * dy[k]] = 0;
            }
    for (int k = 0; k < 4; k++)
        for (int i = 1; i <= power; i++)
            if (check(s + i * dx[k], t + i * dy[k])) {
               if (ch[s + i * dx[k]][t + i * dy[k]] == '*') {
                   ch[s + i * dx[k]][t + i * dy[k]] = propsType[s + i * dx[k]][t + i * dy[k]];
               }
               else if (ch[s + i * dx[k]][t + i * dy[k]] == '#') break;
            }
}
bool Map::notStep(std::pair<int, int> location)
{
    int s = location.first, t = location.second;
    return bombing[s][t];
}
#endif // MAP_H
