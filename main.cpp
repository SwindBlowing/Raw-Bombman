#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
using namespace std;
int n = 20, m = 20;
Player p[5] = {Player(0, 0, '0'), Player(1, 1, '1'), Player(1, m, '2'), Player(n, 1, '3'), Player(n, m, '4')};
Map M(n, m);
Bomb b[20];
int bombNum;
void deal_with_input();
void deal_with_timer();
void init();
void display();
int main()
{
    init();
    display();
    int count = 0;
    while (!p[1].isDead() && !p[2].isDead()) {
        deal_with_input();
        count++;
        if (count == 100) {
            deal_with_timer();
            count = 0;
        }
    }
    return 0;
}

void deal_with_input()
{
    char ch;
    if (_kbhit()) {
        ch = _getch();
        for (int i = 1; i <= 4; i++) {
            if (!p[i].isDead()) {
                if (i == 1) {
                    if (p[i].canMove()){
                        if (ch == 'a') {
                            int now = M.movePlayer(1, 0, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(0), display();
                        }
                        if (ch == 'w') {
                            int now = M.movePlayer(1, 1, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(1), display();
                        }
                        if (ch == 'd') {
                            int now = M.movePlayer(1, 2, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(2), display();
                        }
                        if (ch == 's') {
                            int now = M.movePlayer(1, 3, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(3), display();
                        }
                    }
                    if (ch == ' ') {
                        M.bombPut(p[i].get_location());
                        bombNum = (bombNum + 1) % 20;
                        b[bombNum].init(p[i].get_location(), p[i].getPower(), i);
                        display();
                    }
                }
                else if (i == 2) {
                    if (p[i].canMove()) {
                        if (ch == 'j') {
                            int now = M.movePlayer(2, 0, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(0), display();
                        }
                        if (ch == 'i') {
                            int now = M.movePlayer(2, 1, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(1), display();
                        }
                        if (ch == 'l') {
                            int now = M.movePlayer(2, 2, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(2), display();
                        }
                        if (ch == 'k') {
                            int now = M.movePlayer(2, 3, p[i].get_location());
                            p[i].getBenefit(now);
                            if (now) p[i].Move(3), display();
                        }
                    }
                    if (ch == 13) {
                        M.bombPut(p[i].get_location());
                        bombNum = (bombNum + 1) % 20;
                        b[bombNum].init(p[i].get_location(), p[i].getPower(), i);
                        display();
                    }
                }
            }
        }
    }
}
void deal_with_timer()
{
    for (int i = 1; i <= 4; i++) {
        p[i].checkBenefit();
        if (M.notStep(p[i].get_location())) {
            p[i].die();
            printf("\n");
            printf("Player %d died\n", i);
            printf("Please press enter to end the game");
        }
    }
    for (int i = 0; i < 20; i++) {
        if (b[i].hasOver()) {
            b[i].overing();
            M.bombLeft(b[i].get_location(), b[i].getPower());
            display();
        }
        if (b[i].isExisted() && b[i].hasBombed()) {
            b[i].bombBomb();
            b[i].startToOver();
            int num = M.bombBomb(b[i].get_location(), b[i].getPower());
            p[b[i].getMaster()].PointUp(num);
            display();
        }
    }
}
void init()
{

}
void display()
{
    system("cls");
    M.printMap();
    for (int i = 1; i <= 4; i++)
        p[i].printPoint();
}
