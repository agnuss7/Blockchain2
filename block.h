#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include "hash.h"

struct Transaction{
    int Id;
    std::string Input;
    std::string Output;
    int Amount;
    //std::string Hash;
};

struct User {
    std::string Name;
    std::string Public;
    unsigned int Balance;
};

class Block {
private:
    std::string Hash;
    int Version;
    std::string Timestamp;
    std::string PrevHash;
    std::string Merkle;
    int Nonce;
    int DifT;
    std::vector<Transaction> Tran;

public:
    Block(int ver=1, int D=1){
        Version=ver;
        DifT=D;
        PrevHash="";
    }
    void Merk(){
        std::vector<std::string> MHash;
        for (Transaction x:Tran){
            std::string temp=std::to_string(x.Id)+x.Input+x.Output+std::to_string(x.Amount);
            MHash.push_back(hash(temp));
        }
        while(MHash.size()>1){
            int k=MHash.size();
            for(int i=0;i<k/2;i++){
                MHash[i]=hash(MHash[i]+MHash[i+1]);
                MHash.erase(MHash.begin()+i+1);
            }
            if(k%2>0){
                MHash[k/2]=hash(MHash[k/2]+MHash[k/2]);
            }
        }
        Merkle=MHash[0];
    }
    void Add(Transaction a) {
    Tran.push_back(a);
    //Merk();
    //std::cout<<a.Output<<"\n";
    }
    std::string GetHash(){ return Hash;}
    int GetNonce() {return Nonce;}
    int GetDif() {return DifT;}
    void SetPH(std::string p){
        PrevHash=p;
    }
    void Mine(){
        std::string can;
        int n=-1;
        bool done=false;
        while(!done){
            std::time_t result = std::time(nullptr);
            Timestamp=std::asctime(std::localtime(&result));
            n++;
            can=hash(std::to_string(Version)+PrevHash+Merkle+Timestamp+std::to_string(n));
            //std::cout<<std::to_string(Version)+Merkle+std::to_string(n)<<" "<<can<<"  "<<n<<"\n";
            done=true;
            for(int i=0;i<DifT;i++){
                if(can[i]!='0'){
                    done=false;
                }
            }
        }
        Nonce=n;
        Hash=can;

        std::cout<<"_____________________________________________________\n\n| Hash: "<<can<<"\n| Merkle root: "<<Merkle<<"\n| Nonce: "<<n<<"\n______________________________________________\n\t\t|\n\t\t|\n\t\t|\n\t\tV\n";
    }
};

