#include "Map.h"
struct tmp
{
    std::pair<int, int> location;
    int fromPoint;
};
Map::Map(int x, int y)
{
    n = x;
    m = y;
    generateMap();
}
void Map::dfs(int x, int y)
{
    extern bool vis[205][205];
    vis[x][y] = 1;
    for (int k = 0; k < 4; k++)
        if (check(x + dx[k], y + dy[k]) && !vis[x + dx[k]][y + dy[k]] && ch[x + dx[k]][y + dy[k]] != '#') dfs(x + dx[k], y + dy[k]);
    return ;
}
bool Map::checkMap()
{
    extern bool vis[205][205];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            vis[i][j] = 0;
    dfs(1, 1);
    return (vis[1][m] && vis[n][1] && vis[n][m]);
}
inline bool Map::check(int x, int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m;
}
void Map::generateMap(void)
{
    do {
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
                else if (p < 7) ch[i][j] = ' ';
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
    }while (!checkMap());
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
bool Map::bombPut(std::pair<int, int> location)
{
    int s = location.first, t = location.second;
    if (bombMap[s][t] == '!') return 0;
    bombMap[s][t] = '!';
    return 1;
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
            if (check(s + i * dx[k], t + i * dy[k]) && (preCh[s + i * dx[k]][t + i * dy[k]] == '!' || (preCh[s + i * dx[k]][t + i * dy[k]] >= '1' && preCh[s + i * dx[k]][t + i * dy[k]] <= '4')))
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
int Map::getVal(std::pair<int, int> location, int id)
{
    int s = location.first, t = location.second;
    int val = 0;
    if (!check(s, t) || bombing[s][t]) return 20000;
    if (ch[s][t] == '*' || ch[s][t] == '#') return 10000;
    if (ch[s][t] >= '1' && ch[s][t] <= '4' && ch[s][t] != id + '0') return 10000;
    if (ch[s][t] == 'A' || ch[s][t] == 'B') val -= 75;
    for (int i = -3; i <= 3; i++)
        for (int j = -3; j <= 3; j++) {
            int nowx = s + i, nowy = t + j;
            if (check(nowx, nowy) && bombMap[nowx][nowy] == '!') {
                for (int k = 0; k <= 4; k++)
                    if ((s == nowx && abs(t - nowy) == k) || (abs(s - nowx) == k && t == nowy)) val += (5 - k) * 25;
            }
        }
    return val;
}
bool Map::existSoftWallOrPlayers(std::pair<int, int> location, int len)
{
    int s = location.first, t = location.second;
    for (int i = 1; i <= len; i++)
        for (int k = 0; k < 4; k++)
            if (check(s + i * dx[k], t + i * dy[k]) && ch[s + i * dx[k]][t + i * dy[k]] == '*')
                return 1;
            else if (check(s + i * dx[k], t + i * dy[k]) && ch[s + i * dx[k]][t + i * dy[k]] >= '1' && ch[s + i * dx[k]][t + i * dy[k]] <= '4')
                return 1;
    return 0;
}
int Map::shortestPath(std::pair<int, int> location1, std::pair<int, int> location2)
{
    int s = location1.first, t = location1.second;
    std::queue<tmp> Q;
    while (!Q.empty()) Q.pop();
    extern bool vis[205][205];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            vis[i][j] = 0;
    vis[s][t] = 1;
    for (int k = 0; k < 4; k++)
        if (check(s + dx[k], t + dy[k]) && ch[s + dx[k]][t + dy[k]] != '#') {
            Q.push((tmp){{s + dx[k], t + dy[k]}, k});
            vis[s + dx[k]][t + dy[k]] = 1;
        }
    while (!Q.empty()) {
        tmp now = Q.front();
        Q.pop();
        if (now.location == location2) return now.fromPoint;
        for (int k = 0; k < 4; k++) {
            int nowx = now.location.first, nowy = now.location.second;
            if (check(nowx + dx[k], nowy + dy[k]) && !vis[nowx + dx[k]][nowy + dy[k]] && ch[nowx + dx[k]][nowy + dy[k]] != '#') {
                Q.push((tmp){{nowx + dx[k], nowy + dy[k]}, now.fromPoint});
                vis[nowx + dx[k]][nowy + dy[k]] = 1;
            }
        }
    }
    return -1;
}
