#ifndef CHARACTER_H
#define CHARACTER_H
#include <utility>
#include <ctime>
#include <cstdio>
#include "Map.h"
#include "Bomb.h"
class Player
{
private:
    int point;
    std::pair<int, int> location;
    bool isAlive;
    int id;
    int power;
    double speed; // which is actually "moveInterval"
    double startToPowerUp, lastMoveTime, startToSpeedUp, lastPutBomb;
    const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    void speedUp(void);
    void putPower(void);
    void checkPower(void);
    void checkSpeed(void);
    int getEnemy(void);
public:
    Player(int x, int y, int id);
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
    bool robotMove(void);
    bool robotPutBomb(void);
};
#endif // CHARACTER_H
