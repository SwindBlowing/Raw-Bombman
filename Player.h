#ifndef CHARACTER_H
#define CHARACTER_H
#include <utility>
#include <ctime>
#include <cstdio>
class Player
{
private:
    int point;
    std::pair<int, int> location;
    bool isAlive;
    char symbol;
    int power;
    double speed;
    double startToPowerUp, lastMoveTime, startToSpeedUp, lastPutBomb;
    const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    void speedUp(void);
    void putPower(void);
    void checkPower(void);
    void checkSpeed(void);
public:
    Player(int x, int y, char symbol);
    void Move(int type);
    bool isDead(void);
    std::pair<int, int> get_location();
    void die(void);
    int getPower(void);
    bool canMove(void);
    void getBenefit(int id);
    void checkBenefit(void);
    void PointUp(int t);
    void printPoint(void);
    int getPoint(void);
    bool canPutAgain(void);
    void putBomb(void);
};

bool Player::canPutAgain(void)
{
    double nowTime = (double)clock();
    return nowTime - lastPutBomb > 3000;
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
    printf("The score of Player %c is %d\n", symbol, point);
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
    if (speed < 150 && nowTime - startToSpeedUp > 5000) speed = 200;
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
Player::Player(int x, int y, char symbol)
{
    location.first = x;
    location.second = y;
    isAlive = 1;
    power = 1;
    speed = 200;
    this->symbol = symbol;
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
#endif // CHARACTER_H
