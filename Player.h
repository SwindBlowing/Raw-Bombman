#ifndef CHARACTER_H
#define CHARACTER_H
#include <utility>
class Player
{
private:
    std::pair<int, int> location;
    bool isAlive;
    char symbol;
    const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
public:
    Player(int x, int y, char symbol);
    void Move(int type);
    bool isDead(void);
    std::pair<int, int> get_location();
    void die(void);
};

Player::Player(int x, int y, char symbol)
{
    location.first = x;
    location.second = y;
    isAlive = 1;
    this->symbol = symbol;
}
void Player::Move(int type)
{
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
#endif // CHARACTER_H
