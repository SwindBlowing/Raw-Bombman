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
public:
    bool hasBombed(void);
    void init(std::pair<int, int> location);
    std::pair<int, int> get_location();
    bool isExisted(void);
    void bombBomb(void);
    bool hasOver(void);
    void overing(void);
    void startToOver(void);
};
void Bomb::startToOver(void)
{
    overed = 1;
    bombTime = (double)clock();
}
void Bomb::bombBomb(void)
{
    existed = 0;
}
void Bomb::init(std::pair<int, int> location)
{
    this->location = location;
    existed = 1;
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
#endif // BOMB_H
