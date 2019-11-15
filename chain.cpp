#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "block.h"

void AddBlock(std::vector<Block> &a, Block &b){
    bool f=true;
    for(int i=0;i<b.GetNonce();i++){
        if(b.GetHash()[i]!='0'){f=false;}
    }
if(f){
        //b.SetPH(a.back().GetHash());
        a.push_back(b);
    }
}

int main() {
    srand(2);
    std::vector<Block> chain;
    Block A;
    Transaction t;
    for(int i=0;i<100;i++){

        t.Amount=rand()%100;
        t.Output=hash("a"+std::to_string(rand()%50+i));
        t.Input=hash("f"+std::to_string(rand()%22));
        t.Id=i;
        A.Add(t);
    }
    A.Merk();
    A.Mine();
    AddBlock(chain,A);
    std::cout<<chain.back().GetHash();
    do{}while(1);
    return 0;
}