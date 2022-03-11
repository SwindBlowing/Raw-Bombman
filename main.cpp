#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
using namespace std;
int n = 20, m = 20;
Player p1(1, 1, 1), p2(1, m, 2), p3(n, 1, 3), p4(n, m, 4);
Map M(n, m);
Bomb b1, b2;
void deal_with_input();
void deal_with_timer();
void init();
void display();
int main()
{
    init();
    display();
    int count = 0;
    while (!p1.isDead() && !p2.isDead()) {
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
        if (!p1.isDead()) {
            if (ch == 'a' && M.movePlayer(1, 0, p1.get_location())) p1.Move(0);
            if (ch == 'w' && M.movePlayer(1, 1, p1.get_location())) p1.Move(1);
            if (ch == 'd' && M.movePlayer(1, 2, p1.get_location())) p1.Move(2);
            if (ch == 's' && M.movePlayer(1, 3, p1.get_location())) p1.Move(3);
            if (ch == ' ') {
                M.bombPut(p1.get_location());
                b1.init(p1.get_location());
            }
        }
        if (!p2.isDead()) {
            if (ch == 'j' && M.movePlayer(2, 0, p2.get_location())) p2.Move(0);
            if (ch == 'i' && M.movePlayer(2, 1, p2.get_location())) p2.Move(1);
            if (ch == 'l' && M.movePlayer(2, 2, p2.get_location())) p2.Move(2);
            if (ch == 'k' && M.movePlayer(2, 3, p2.get_location())) p2.Move(3);
            if (ch == 13) {
                M.bombPut(p2.get_location());
                b2.init(p2.get_location());
            }
        }
        display();
    }
}
void deal_with_timer()
{
    if (M.notStep(p1.get_location())) {
        p1.die();
        printf("\n");
        printf("Player 1 died\n");
        printf("Please press enter to end the game");
    }
    if (M.notStep(p2.get_location())) {
        p2.die();
        printf("\n");
        printf("Player 2 died\n");
        printf("Please press enter to end the game");
    }
    if (b1.hasOver()) {
        b1.overing();
        M.bombLeft(b1.get_location(), 1);
        display();
    }
    if (b2.hasOver()) {
        b2.overing();
        M.bombLeft(b2.get_location(), 1);
        display();
    }
    if (b1.isExisted() && b1.hasBombed()) {
        b1.bombBomb();
        b1.startToOver();
        M.bombBomb(b1.get_location(), 1);
        display();
    }
    if (b2.isExisted() && b2.hasBombed()) {
        b2.bombBomb();
        b2.startToOver();
        M.bombBomb(b2.get_location(), 1);
        display();
    }
}
void init()
{

}
void display()
{
    system("cls");
    M.printMap();
}
