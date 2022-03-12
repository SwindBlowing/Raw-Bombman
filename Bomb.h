#ifndef BOMB_H
#define BOMB_H
#include <utility>
#include <ctime>
class Bomb
{
private:
    std::pair<int, int> location;
    double putTime, bombTime;
    bool existed, overed;
    int power, master;
public:
    bool hasBombed(void);
    void init(std::pair<int, int> location, int, int);
    std::pair<int, int> get_location();
    bool isExisted(void);
    void bombBomb(void);
    bool hasOver(void);
    void overing(void);
    void startToOver(void);
    int getPower(void);
    int getMaster(void);
};

int Bomb::getMaster(void)
{
    return master;
}
void Bomb::startToOver(void)
{
    overed = 1;
    bombTime = (double)clock();
}
void Bomb::bombBomb(void)
{
    existed = 0;
}
void Bomb::init(std::pair<int, int> location, int power, int master)
{
    this->power = power;
    this->location = location;
    existed = 1;
    this->master = master;
    putTime = (double)clock();
}
bool Bomb::hasBombed(void)
{
    double nowTime = (double)clock();
    return nowTime - putTime > 1000;
}
std::pair<int, int> Bomb::get_location()
{
    return location;
}
bool Bomb::isExisted(void)
{
    return existed;
}
bool Bomb::hasOver(void)
{
    if (!overed) return 0;
    double nowTime = (double)clock();
    return nowTime - bombTime > 1000;
}
void Bomb::overing(void)
{
    overed = 0;
}
int Bomb::getPower(void)
{
    return power;
}
#endif // BOMB_H
