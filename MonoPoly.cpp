#include "MonoPoly.h"
#include<iostream>
#include<string>
#include<time.h>
using namespace std;

int main(){
    mono m;
    int decision = 0;
    vector<play> current;
    vector<map> mapInfo;
    while(1){
        cout<< "What do you want to do? ";
        cin >> decision;
        if(decision==1){
            m.AddMap();
        }
        else if(decision==2){
            m.showmap();
        }
        else if(decision==3){
            m.AddPlayer();
        }
        else if(decision==4){
            m.showplayer();
        }
        else if(decision==5){
            m.RowDie();
        }
        else if(decision==6){
            current = m.getStatus();
            mapInfo = m.getMap();
            vector<int> mapOwner;
            cout<<"Now player = "<< current[NOWPLAYER].id<<endl;
            cout<<"Player money = "<<current[NOWPLAYER].money<<endl;
            cout<<"Player place = "<< current[NOWPLAYER].nowPlace<<endl;
            for(int i =0;i<mapInfo.size();i++){
                if(mapInfo[i].nowOwner == current[NOWPLAYER].id)
                    mapOwner.push_back(mapInfo[i].id);
            }
            cout<<"Player's property : ";
            for(int i =0;i<mapOwner.size();i++){
                cout<<mapOwner[i];
                if(i!=mapOwner.size()-1)
                    cout<<", ";
            }
            cout<<endl;
        }
        else{
            break;
        }
    }
    return 0;
}


void mono::AddPlayer(){
    play newPlayer;
    int money;
    int place;
    /*cout<< "Player's money : ";
    cin >> money;*/
    newPlayer.id = playerid;
    newPlayer.money = 1000;
    newPlayer.nowPlace = 0;
    players.push_back(newPlayer);
    playerid++;
}
void mono::AddMap(){
    map newMap;
    /*int cost;
    cout<< "Map cost : ";
    cin >> cost;*/
    newMap.id = mapid;
    newMap.cost = mapcost;
    newMap.nowOwner = -1;
    maps.push_back(newMap);
    mapcost+=50;
    mapid++;
}
void mono::showmap(){
    cout<<"----------------------------"<<endl;
    for(int i = 0;i<maps.size();i++){
        cout<<" map id :"<< maps[i].id<<endl;
        cout<<" map cost : "<<maps[i].cost<<endl;
        cout<<" map owner(player id) : "<<maps[i].nowOwner<<endl;
        cout<<"---------------------------"<<endl;  
    }
}
void mono::showplayer(){
    cout<<"-------------------------"<<endl;
    for(int i = 0;i<players.size();i++){
        cout<<" player id : "<< players[i].id<<endl;
        cout<<" player money : "<<players[i].money<<endl;
        cout<<" player location at(map id) : "<<players[i].nowPlace<<endl;
        cout<<"----------------------------"<<endl; 
    }
}
void mono::RowDie(){
    //cout<<"now player = " <<players[NOWPLAYER].id<<endl;
    int min = 1;
    int max = 6;
    int currentPlace;
    srand(time(NULL));
    int dieNum = rand() % (min + max -1) + min;
    cout<<"----------------------------------"<<endl;
    cout<<"die = " <<dieNum <<endl;
    if(players[NOWPLAYER].nowPlace + dieNum > maps.size()-1){
        currentPlace = (players[NOWPLAYER].nowPlace + dieNum) % maps.size();
    }
    else{
        currentPlace = players[NOWPLAYER].nowPlace + dieNum;
    }
    //cout<< "current = " <<currentPlace<<endl;
    if(maps[currentPlace].nowOwner == -1 ){
        buy(maps[currentPlace].cost,currentPlace);
    }
    else if(maps[currentPlace].nowOwner !=-1 && maps[currentPlace].nowOwner != players[NOWPLAYER].id){
        cout<< "Map "<< maps[currentPlace].id << " is own by player "<<maps[currentPlace].nowOwner<<endl;
        //cout<<"map cost = "<<maps[currentPlace].cost<<" player money = "<< players[NOWPLAYER].money<<endl;
        players[NOWPLAYER].money -= maps[currentPlace].cost;
        players[maps[currentPlace].nowOwner-1].money += maps[currentPlace].cost;
        cout<<"Pay "<< maps[currentPlace].cost <<" dollars." <<endl;
    }
    else{
        cout<<"You're in your place."<<endl;
        upgrade(int cost, int current);
        /*if(NOWPLAYER + 1 >players.size()-1)
            NOWPLAYER = 0;
        else
            NOWPLAYER++;*/
    }
    if(NOWPLAYER + 1 >players.size()-1)
        NOWPLAYER = 0;
    else
        NOWPLAYER++;
    cout<<"------------------------------"<< endl;
}
void mono::buy(int cost, int current){
    int choice;
    cout<<"Do you want to buy?(Press 1 buy place, other for skip)"<<endl;
    cin>>choice;
    if(choice==1){
        players[NOWPLAYER].money -= cost;
        maps[current].nowOwner = players[NOWPLAYER].id;
        players[NOWPLAYER].nowPlace = maps[current].id;
        cout<<"Buy place"<<endl;
    }
    else{
        cout<<"Skip"<<endl;
        return;
    }
}
void mono::upgrade(int cost, int current){
    int choice;
    cout<<"Press 1 to pay double and upgrade, other for skip"<<endl;
    cin>>choice;
    if(choice==1){
        maps[current].cost *= 2;
        players[NOWPLAYER].money -= maps[current].cost;
        cout<<"Upgrade place to "<< maps[current].cost << endl;
    }
    else
        cout <<"Skip" <<endl;
        return;

}
vector<play> mono::getStatus(){
    return players;
}
vector<map> mono::getMap(){
    return maps;
}