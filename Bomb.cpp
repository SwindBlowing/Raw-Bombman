#include "Bomb.h"
void Bomb::startToOver(void)
{
    overed = 1;
    bombTime = (double)clock();
}
void Bomb::bombBomb(void)
{
    extern Map M;
    extern Player p[5];
    existed = 0;
    startToOver();
    int num = M.bombBomb(location, power);
    p[master].PointUp(num);
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
    extern Map M;
    overed = 0;
    M.bombLeft(location, power);
}
int Bomb::getPower(void)
{
    return power;
}
