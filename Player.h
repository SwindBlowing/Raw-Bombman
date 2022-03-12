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
#endif // CHARACTER_H
