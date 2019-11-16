#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "block.h"

bool check(Block a){
    bool f=true;
    for(int i=0;i<a.GetDif();i++){
        if(a.GetHash()[i]!='0'){f=false;}
    }
    return f;
}

int main() {
    srand(time(NULL));
    std::vector<Block> chain;
    std::vector<Transaction> tran;
    std::vector<User> users;
    for(int i=0;i<1000;i++){
        User u;
        u.Name=base[rand()%64];
        u.Public=hash(u.Name+base[rand()%64]);
        u.Balance=rand()%2000;
        users.push_back(u);
    }
    for(int i=0;i<10000;i++){
        Transaction t;
        t.Id=i;
        t.Amount=rand()%100;
        t.Input=users[rand()%1000].Public;
        t.Output=users[rand()%1000].Public;
        while(t.Input==t.Output){t.Output=users[rand()%1000].Public;}
        tran.push_back(t);
    }

    Block A;
    for(int i=0;i<100 && tran.size()>0;i++){
        A.Add(tran.back());
        tran.pop_back();
    }
    A.Merk();
    A.Mine();
    if(check(A)){
        chain.push_back(A);
    }

    while(tran.size()>0){
        Block B;
        for(int i=0;i<100 && tran.size()>0;i++){
            B.Add(tran.back());
            tran.pop_back();
        }
        B.Merk();
        B.SetPH(chain.back().GetHash());
        B.Mine();
        if(check(B)){
            chain.push_back(B);
        }
    }
    //std::cout<<chain.back().GetHash();
    do{}while(1);
    return 0;
}