#include "Player.h"
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
