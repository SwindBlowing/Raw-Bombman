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
#endif // BOMB_H
