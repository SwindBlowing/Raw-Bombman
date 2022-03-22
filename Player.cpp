#include "Player.h"
bool Player::canPutAgain(void)
{
    double nowTime = (double)clock();
    return nowTime - lastPutBomb > 2000;
}
void Player::putBomb(void)
{
    lastPutBomb = (double)clock();
}
int Player::getPoint(void)
{
    return point;
}
void Player::printPoint(void)
{
    printf("The score of Player %d is %d\n", id, point);
}
void Player::PointUp(int t)
{
    point += t;
}
void Player::checkBenefit(void)
{
    checkPower();
    checkSpeed();
}
void Player::getBenefit(int id)
{
    if (id == 2) putPower(), PointUp(10);
    else if (id == 3) speedUp(), PointUp(10);
}
void Player::speedUp(void)
{
    speed /= 2;
    startToSpeedUp = (double)clock();
}
void Player::checkSpeed(void)
{
    double nowTime = (double)clock();
    if (speed < 200 && nowTime - startToSpeedUp > 5000) speed = 300;
}
bool Player::canMove(void)
{
    double nowTime = (double)clock();
    return nowTime - lastMoveTime > speed;
}
void Player::checkPower(void)
{
    double nowTime = (double)clock();
    if (power > 1 && nowTime - startToPowerUp > 5000) power = 1;
}
void Player::putPower(void)
{
    power++;
    startToPowerUp = (double)clock();
}
Player::Player(int x, int y, int id)
{
    location.first = x;
    location.second = y;
    isAlive = 1;
    power = 1;
    speed = 300;
    this->id = id;
    point = 0;
}
void Player::Move(int type)
{
    lastMoveTime = (double)clock();
    location.first += dx[type];
    location.second += dy[type];
}
bool Player::isDead(void)
{
    return !isAlive;
}
std::pair<int, int> Player::get_location()
{
    return location;
}
void Player::die(void)
{
    isAlive = 0;
}
int Player::getPower(void)
{
    return power;
}
int Player::getEnemy(void)
{
    int s = location.first, t = location.second;
    extern Player p[5];
    int minDis = 10000, target = 0;
    for (int i = 1; i <= 4; i++)
        if (!p[i].isDead()){
            int x = p[i].get_location().first, y = p[i].get_location().second;
            int nowDis = abs(x - s) + abs(y - t);
            if (nowDis)
                minDis = nowDis < minDis ? nowDis : minDis, target = i;
    }
    return target;
}
bool Player::robotMove(void)
{
    int s = location.first, t = location.second;
    extern Map M;
    extern Bomb b[20];
    if (!canMove()) return 0;
    int val[4] = {0}, minn = 10000, standard = M.getVal(location, id);
    for (int i = 0; i < 4; i++) {
        std::pair<int, int> nowLoc = {s + dx[i], t + dy[i]};
        val[i] = M.getVal(nowLoc, id);
        minn = val[i] < minn ? val[i] : minn;
    }
    bool flag = 0;
    for (int i = 0; i < 20; i++)
        if (b[i].isExisted()) {
            int x = b[i].get_location().first, y = b[i].get_location().second;
            if ((x == location.first && abs(y - location.second) <= b[i].getPower()) || (y == location.second && abs(x - location.first) <= b[i].getPower())) {
                flag = 1;
                break;
            }
        }
    if (standard < minn && !flag) return 0;
    int enemy = getEnemy();
    extern Player p[5];
    int dir = M.shortestPath(location, p[enemy].get_location());
    if (dir >= 0 && val[dir] == minn) {
        int now = M.movePlayer(id, dir, location);
        getBenefit(now);
        if (now) {
            Move(dir);
            return 1;
        }
    }
    int str = rand() % 4;
    for (int i = 0; i < 4; i++)
        if (val[(str + i) % 4] == minn) {
            dir = (str + i) % 4;
            break;
        }
    int now = M.movePlayer(id, dir, location);
    getBenefit(now);
    if (now) {
        Move(dir);
        return 1;
    }
    return 0;
}
bool Player::robotPutBomb(void)
{
    extern Map M;
    extern int bombNum;
    extern Bomb b[20];
    if (canPutAgain() && M.existSoftWallOrPlayers(location, power) && M.bombPut(location)) {
        putBomb();
        bombNum = (bombNum + 1) % 20;
        b[bombNum].init(location, power, id);
        return 1;
    }
    return 0;
}
