#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "block.h"

std::vector<User> users;
std::vector<Block> chain;
bool check(Block a){
    bool f=true;
    for(int i=0;i<a.GetDif();i++){
        if(a.GetHash()[i]!='0'){f=false;}
    }
    return f;
}

bool checkTrans (Transaction x){
    std::string in=x.GetI();
    int a=x.GetA();
    int amount=0;
    for(Block q:chain){
        std::vector<Transaction> temp=q.GetT();
        for(Transaction t:temp){
            if(t.GetI()==in){
                amount-=t.GetA();
            }
            if(t.GetO()==in){
                amount+=t.GetA();
            }
        }
    }
    if(a<=amount){return true;} else {return false;}
}
std::string FindN(std::string p){
    for(User x:users){
        if(x.Public==p){return x.Name;}
    }
    return "";
}


std::string Names[]={"James ","John ","Bella ","Saul ","Alita ","Levi ","Nicole ","Larry ","Rem ","Alex ","Scarlet ","Mitchell ", "Phoenix ","River ","Jojo ", "Joseph ", "Jonathan ","Ceasar ","Iggy ","Jean ", "Pierre ","Igor ", "Al ","Edd ","Jeff ","Blair ","Suzie ","Sora ","Elijah ","Adrian ","Erina ","Gordon "};
std::string LNames[]={"Kazan","Tresher","Jenkins","Lugosi","Waters","Styx","Emeth","Woo","Leaven","Argentum","Wood","Black","Reilly","Sheppard","Worth","Sunderland","Pendleton","Joestar","Quentin","Wright","Alsup","Halloway","Eggstein","Avdol","Araki","Bates","Ora","Quatro","Speedwagon","Fuentes","Newman","Ramsey","Freeman"};

int main() {
    srand(time(NULL));
    std::vector<Transaction> tran;
    for(int i=0;i<1000;i++){
        User u;
        u.Name=Names[rand()%32]+LNames[rand()%32];
        u.Public=hash(u.Name+base[rand()%64]+std::to_string(rand()%500));
        users.push_back(u);
    }
    for(int i=0;i<10000;i++){
        Transaction t(users[rand()%1000].Public,users[rand()%1000].Public,rand()%100+1);
        // kai kurios tranzakcijos "suklastotos"
        if(rand()%1989==333) {
            t.SetA(rand()%500);
        }
        if(hash(t.GetI()+t.GetO()+std::to_string(t.GetA()))==t.GetID()){
            tran.push_back(t);
        } else {
            std::cout<<"Tranzakcija "<<t.GetID()<<" suklastota.\n";
        }
    }

    // "genesis" block. Kai kuriems vartotojams pervedama Nignog'u
    Block A;
    for(int i=0;i<300;i++){
        Transaction t("",users[rand()%1000].Public,rand()%300+50);
        A.Add(t);
    }
    A.Merk();
    A.Mine();
    if(check(A)){
        chain.push_back(A);
    }



    while(tran.size()>0){
        Block B;
        for(int i=0;i<100 && tran.size()>0;i++){
            if(checkTrans(tran.front())) {
                B.Add(tran.front());
                std::cout<<FindN(tran.front().GetI())<<"--- "<<tran.front().GetA()<<" nignogs ---->"<<FindN(tran.front().GetO())<<"\n";
            } else {
                std::cout<<"Vartotojas "<<FindN(tran.front().GetI())<<" neturi "<<tran.front().GetA()<<" Nignog'u pervedimui.\n";
                i--;
            }
            tran.erase(tran.begin());
        }
        B.Merk();
        B.SetPH(chain.back().GetHash());
        B.Mine();
        if(check(B)){
            chain.push_back(B);
        }
    }

    for(Block x:chain){
        std::cout<<"_____________________________________________________\n\n| Hash: "<<x.GetHash()<<"\n| Merkle root: "<<x.GetMerk()<<"\n| Nonce: "<<x.GetNonce()<<"\n______________________________________________\n\t\t|\n\t\t|\n\t\t|\n\t\tV\n";
    }
    //std::cout<<chain.back().GetHash();
    do{}while(1);
    return 0;
}