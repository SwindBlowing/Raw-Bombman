#include <iostream>
#include <conio.h>
#include <map>
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
using namespace std;
int n = 20, m = 20;
bool vis[205][205];
Player p[5] = {Player(0, 0, 0), Player(1, 1, 1), Player(1, m, 2), Player(n, 1, 3), Player(n, m, 4)};
Map M(n, m);
Bomb b[20];
map<char, int> mapping;
int bombNum;
void deal_with_input(void);
void deal_with_timer(void);
void init(void);
void display(void);
int getWinner(void);
int main(void)
{
    init();
    display();
    int count = 0;
    while (1) {
        deal_with_input();
        count++;
        if (count == 100) {
            deal_with_timer();
            count = 0;
        }
        int numAlive = 0;
        for (int i = 1; i <= 4; i++)
            if (!p[i].isDead()) numAlive++;
        if (numAlive <= 1) break;
    }
    printf("The winner is Player %d.\n", getWinner());
    printf("Please press enter to end the game.\n");
    return 0;
}

int getWinner(void)
{
    int nowWinner = 1, nowPoint = 0;
    for (int i = 1; i <= 4; i++)
        if (p[i].getPoint() > nowPoint) {
            nowPoint = p[i].getPoint();
            nowWinner = i;
        }
    return nowWinner;
}
void deal_with_input(void)
{
    char ch;
    if (_kbhit()) {
        ch = _getch();
        for (int i = 1; i <= 2; i++) {
            if (!p[i].isDead()) {
                if (i == 1) {
                    if (p[i].canMove()){
                        if (ch == 'a' || ch == 'w' || ch == 'd' || ch == 's') {
                            int dir = mapping[ch];
                            int now = M.movePlayer(1, dir, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(dir), display();
                        }
                    }
                    if (ch == ' ' && M.bombPut(p[i].get_location())) {
                        bombNum = (bombNum + 1) % 20;
                        b[bombNum].init(p[i].get_location(), p[i].getPower(), i);
                        display();
                    }
                }
                else if (i == 2) {
                    if (p[i].canMove()){
                        if (ch == 'j' || ch == 'i' || ch == 'l' || ch == 'k') {
                            int dir = mapping[ch];
                            int now = M.movePlayer(2, dir, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(dir), display();
                        }
                    }
                    if (ch == 13 && M.bombPut(p[i].get_location())) {
                        bombNum = (bombNum + 1) % 20;
                        b[bombNum].init(p[i].get_location(), p[i].getPower(), i);
                        display();
                    }
                }
            }
        }
    }
}
void deal_with_timer(void)
{
    for (int i = 3; i <= 4; i++)
        if (!p[i].isDead()){
            if (p[i].robotPutBomb()) display();
            if (p[i].robotMove()) display();
        }
    for (int i = 1; i <= 4; i++)
        if (!p[i].isDead()){
            p[i].checkBenefit();
            if (M.notStep(p[i].get_location())) {
                p[i].die();
                display();
            }
        }
    for (int i = 0; i < 20; i++) {
        if (b[i].hasOver()) {
            b[i].overing();
            display();
        }
        if (b[i].isExisted() && b[i].hasBombed()) {
            b[i].bombBomb();
            display();
        }
    }
}
void init(void)
{
    mapping['a'] = mapping['j'] = 0;
    mapping['w'] = mapping['i'] = 1;
    mapping['d'] = mapping['l'] = 2;
    mapping['s'] = mapping['k'] = 3;
}
void display(void)
{
    system("cls");
    M.printMap();
    for (int i = 1; i <= 4; i++)
        p[i].printPoint();
    for (int i = 1; i <= 4; i++)
        if (p[i].isDead())
            printf("Player %d has died.\n", i);
}
