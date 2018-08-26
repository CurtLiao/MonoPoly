#ifndef MONOPOLY_H
#define MONOPOLY_H
#include<vector>
#include<iostream>

using namespace std;

int NOWPLAYER = 0;

struct play{
    int id;
    int money;
    int nowPlace;
};
struct map{
    int id;
    int cost;
    int nowOwner;
};

class mono{
public:
    mono(){};
    ~mono(){};
    int playerid = 1;
    int mapid = 0;
    int mapcost = 50;
    void AddPlayer();
    void AddMap();
    void showmap();
    void showplayer();
    void RowDie();
    void buy(int cost, int dienumber);
    void upgrade(int cost, int current);
    vector<play> getStatus();
    vector<map> getMap();
protected:
    
private:
    vector<play> players;
    vector<map> maps;
};
#endif
