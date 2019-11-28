#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include "hash.h"

class Transaction{
private:
    std::string Id;
    std::string Input;
    std::string Output;
    std::string Timestamp;
    int Amount;
public:
    // inicializavimas
    Transaction(std::string i, std::string o, int a){
        Input=i;
        Output=o;
        Amount=a;
        std::time_t result = std::time(nullptr);
        Timestamp=std::asctime(std::localtime(&result));
        Id=hash(i+o+std::to_string(a)+Timestamp);
    }
    std::string GetI() { return Input; }
    std::string GetO() { return Output; }
    int GetA() { return Amount; }
    std::string GetT() { return Timestamp; }
    std::string GetID() { return Id; }
    // demonstracijai
    void SetA(int a){Amount=a;}
};

struct User {
    std::string Name;
    std::string Public;
   // unsigned int Balance;
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
    // inicializavimas su numatytais parametrais
    Block(int ver=1, int D=1){
        Version=ver;
        DifT=D;
        PrevHash="";
        Merkle="";
    }
    // merkle root hash sudarymas. Tai turbut turetu buti daroma pridejus kiekviena tranzakcija, bet tai labai ilgai uztruktu
    std::string Merk(){
        if(!Tran.empty()) {
            // surasoma i merkle medi visos bloko tranzakcijos (uzhasuotos)
            std::vector <std::string> MHash;
            for (Transaction x:Tran) {
                MHash.push_back(hash(x.GetID()));
            }
            // merkle root hash'as sudaromas
            while (MHash.size() > 1) {
                std::vector<std::string> new_mhash;
                if(MHash.size()%2 > 0){
                    MHash.push_back(MHash.back());
                }
                for (auto i = MHash.begin(); i != MHash.end(); i+=2) {
                    std::string aa=*i;
                    std::string bb=*(i+1);
                    std::string cc=aa+bb;
                    new_mhash.push_back(hash(cc));
                }
                MHash=new_mhash;
            }
            Merkle = MHash[0];
            return MHash[0];
        } else return "";
    }
    // tranzakcijos pridejimas
    void Add(Transaction a) {
    Tran.push_back(a);
    //std::cout<<a.Output<<"\n";
    }
    std::string GetHash(){ return Hash;}
    std::string GetMerk(){ return Merkle;}
    int GetNonce() {return Nonce;}
    int GetDif() {return DifT;}
    std::vector<Transaction> GetT() {return Tran;}
    void SetPH(std::string p){
        PrevHash=p;
    }
    // kasimas
    bool Mine(unsigned int count=4294967295){
        unsigned int i=0;
        std::string can;
        int n=-1;
        bool done=false;
        while(!done){
            i++;
            if(i==count){
                return false;
            }
            std::time_t result = std::time(nullptr);
            Timestamp=std::asctime(std::localtime(&result));
            n++;
            can=hash(std::to_string(Version)+PrevHash+Merkle+Timestamp+std::to_string(n));
            //std::cout<<std::to_string(Version)+PrevHash+Merkle+Timestamp+std::to_string(n)<<" "<<can<<"  "<<n<<"\n";
            done=true;
            for(int i=0;i<DifT;i++){
                if(can[i]!='0'){
                    done=false;
                }
            }
        }
        Nonce=n;
        Hash=can;
        return true;
    }
};

