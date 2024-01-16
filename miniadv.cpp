//chaitrali shinde//
#include <bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);
// debug


class character{
    public:
    int row,col;
    character(int x,int y){
        row=x,col=y;
    }
    ~character(){
        cout<<"obj destructed!"<<endl;
    }
};
class player:public character{
    public:
    int hp=100;
    player(int x,int y,int h):character(x,y){
        hp=h;
    }
    void setpos(int x,int y){
        row=x,col=y;
    }
    void decrease_hp(){
        this->hp=1;
    }
    void increase_hp(){
        this->hp+=50;
        this->hp=min(this->hp,100);
        
    }
};
class Maze{
    public:
    int size;
    vector<vector<int>>v;
    set<pair<int,int>>st;
    Maze(int s){
        v.resize(s,vector<int>(s,0));   
    }
    ~Maze(){
        cout<<"obj destroyed"<<endl;
    }

    
};
void solve() {
    
    set<pair<int,int>>monsters_remaining;

    int s;
    char move;
    player p(0,0,100);

    cout<<"ENTER THE SIZE OF MAZE <=10"<<endl;
    cin>>s;
    if(s>10){
        cout<<"l";
        return;
    }
    Maze maze1(s);
    srand(9);
    for(int i=0,x,y;i<s-2;i++){
        x=rand()%(s-1);
        y=rand()%(s-1);
        if(x==0 && y==0)i--;
        else {
            maze1.v[x][y]=1;
        monsters_remaining.insert({x,y});
        }
    }
    for(auto i:maze1.v){
        for(auto j:i)cout<<j<<" ";
        cout<<endl;
    }

    int monsters_encountered=0;


    while(p.row!=s-1 || p.col!=s-1 ){
        cout<<"YOUR ROW IS "<<p.row<<" AND YOUR COL IS: "<<p.col<<endl<<endl;
        cout<<"enter move U D L R press E to exit: "<<endl;
        cin>>move;
        switch (move)
        {
        case 'L':{
            
            if(p.col==0)
                cout<<"CANNOT MOVE TO THE GIVEN POSITION"<<endl;
            else p.setpos(p.row,p.col-1);
            break;

        }
        case 'R':{
            if(p.col==s-1)
                cout<<"CANNOT MOVE TO THE GIVEN POSITION"<<endl;
            else p.setpos(p.row,p.col+1);
            break;
        }
        case 'U':{
            if(p.row==0)
                cout<<"CANNOT MOVE TO THE GIVEN POSITION"<<endl;
            else p.setpos(p.row-1,p.col);
            break;
        }
        case 'D':{
            
            if(p.row==s-1)
                cout<<"CANNOT MOVE TO THE GIVEN POSITION"<<endl;
            else p.setpos(p.row+1,p.col);
            break;
        }
        case 'E':{
            cout<<"YOU LOSE!!"<<endl;
            return;
        }
        default:
            break;
        }
        if(maze1.v[p.row][p.col]==1){
            monsters_encountered++;
            cout<<"YOU ENCOUNTERED A MONSTER!!"<<endl<<endl;
            monsters_remaining.erase({p.row,p.col});
            maze1.v[p.row][p.col]=0;
            if(monsters_encountered>=2 ||p.hp<100){
                cout<<"YOU LOSE!!"<<endl;
                return;
            }

        }
        if(p.hp<100){
            // you should not go near a monster when ur hp is less than 100
            if(monsters_remaining.size()){
                int mini=1e9;

                for(auto i:monsters_remaining){
                    mini=min(abs(p.row-i.first)+abs(p.col-i.second),mini);
                }
                cout<<"NEXT MONSTER IS AT MINIMUM DISTANCE :"<<mini<<endl<<endl;
            }
            // your hp will increase if and only if you step on nonvisited cell as maze power is low
            if(maze1.v[p.row][p.col]!=2) p.increase_hp();
            if(p.hp==100){
                cout<<"u restored your hp!!"<<endl;
            }
            cout<<"your current hp is: "<<p.hp<<endl<<endl;
            maze1.v[p.row][p.col]=2;
        }
        // maze power is restored
        else{
            for(auto &i:maze1.v){
                for(auto &j:i)
                if(j==2)j=0;
            }
        }
        
        if(monsters_encountered){
            cout<<"Do u want to kill this monster (press 1 else 0)??\n WARNING:ur hp will reduce to 1 if full hp else ;() "<<endl;
            cin>>move;
            if(move=='1'){
                if(p.hp<100){
                    cout<<"YOU LOSE!!"<<endl;
                    return;
                }
                p.decrease_hp();
                monsters_encountered--;
                maze1.v[p.row][p.col]=2;
            }
        }
        
    }
    cout<<"YOU WON!!";
}
int main() {
    FAST
    
    solve();
    cout<<endl;

    return 0;
}
