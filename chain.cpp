#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "block.h"
std::vector<Transaction> tran;
std::vector<User> users;
std::vector<Block> chain;
// bloko validavimas
bool check(Block a){
    bool f=true;
    for(int i=0;i<a.GetDif();i++){
        if(a.GetHash()[i]!='0'){f=false;}
    }
    return f;
}
// istrinti tranzakcija is pool'o
void delT(Transaction t){
    for(int i=0;i<tran.size();i++){
        if(t.GetID()==tran[i].GetID()){
            tran.erase(tran.begin()+i);
            break;
        }
    }
}
// tikrinama, ar vartotojas turi pakankamai lesu pervedimui
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
// surast vartotojo varda pagal jo public rakta
std::string FindN(std::string p){
    for(User x:users){
        if(x.Public==p){return x.Name;}
    }
    return "";
}

std::string Names[]={"James ","Giorno ","Mai ","Trish ","Walter ","Miles ","Jill ","Keith ","Rowan ","John ","Bella ","Lisa ","Saul ","Alita ","Levi ","Emeth ","Nicole ","Larry ","Rem ","Alex ","Scarlet ","Mitchell ", "Phoenix ","River ","Jojo ", "Joseph ", "Jonathan ","Ceasar ","Iggy ","Jean ", "Pierre ","Igor ", "Al ","Edd ","Jeff ","Blair ","Suzie ","Sora ","Elijah ","Adrian ","Erina ","Gordon "};
std::string LNames[]={"Kazan","Erewell","Zeppelli","Una","Valentine","Chambers","von Stroheim","Jenkins","Garland","Thor","Lugosi","Heavens","Styx","Woo","Leaven","Argentum","Ramone","Noir","Reilly","Sheppard","Worth","Sunderland","Pendleton","Joestar","Quentin","Wright","Alsup","Halloway","Eggstein","Avdol","Araki","Bates","Ora","Quatro","Speedwagon","Fuentes","Newman","Ramsey","Freeman"};

int main() {
    srand(time(NULL));

    for(int i=0;i<1000;i++){
        User u;
        u.Name=Names[rand()%42]+LNames[rand()%38];
        u.Public=hash(u.Name+base[rand()%64]+std::to_string(rand()%500));
        users.push_back(u);
    }
    for(int i=0;i<10000;i++){
        Transaction t(users[rand()%1000].Public,users[rand()%1000].Public,rand()%50+1);
        // kai kurios tranzakcijos "suklastotos"
        if(rand()%1989==333) {
            //t.SetA(rand()%500);
        }
        if(hash(t.GetI()+t.GetO()+std::to_string(t.GetA()))==t.GetID()){
            tran.push_back(t);
        } else {
            std::cout<<"Tranzakcija "<<t.GetID()<<" suklastota.\n";
        }
    }

    // "genesis" block. Kai kuriems vartotojams pervedama Nignog'u
    Block A;
    for(int i=0;i<400;i++){
        Transaction t("",users[rand()%1000].Public,rand()%200+100);
        A.Add(t);
    }
    A.Merk();
    A.Mine();
    if(check(A)){
        chain.push_back(A);
        //std::cout<<A.GetMerk()<<" "<<A.GetHash()<<"\n";
    }



    while(tran.size()>0) {
        Block B[5];
        for (int i = 0; i < 5; i++) {
            std::vector<Transaction> copy=tran;
            for (int j = 0; j < 100 && copy.size()>0; j++) {
                int temp=rand()%copy.size();
                if (checkTrans(copy[temp])) {
                    B[i].Add(copy[temp]);
                    copy.erase(copy.begin()+temp);
                    std::cout << FindN(copy[temp].GetI()) << "--- " << copy[temp].GetA() << " nignogs ---->" << FindN(copy[temp].GetO()) << "\n";
                } else {
                    std::cout << "Vartotojas " << FindN(copy[temp].GetI()) << " neturi " << copy[temp].GetA()
                              << " Nignog'u pervedimui.\n";
                    j--;
                    copy.erase(copy.begin()+temp);
		            delT(copy[temp]);
                }
            }
            B[i].Merk();
            B[i].SetPH(chain.back().GetHash());
        }
        if(B[0].GetMerk()=="" || B[1].GetMerk()=="" || B[2].GetMerk()=="" || B[3].GetMerk()=="" || B[4].GetMerk()==""){break;}
        bool done = false;
        unsigned int n = 1000;
        while (!done) {
            std::cout<<"iterate with "<<n<<"\n";
            int iter[5]={0,1,2,3,4};
            for(int i=0;i<5;i++){
                int temp2=rand()%5;
                int temp3=iter[i];
                iter[i]=iter[temp2];
                iter[temp2]=temp3;
            }
            for (int i = 0; i < 5; i++) {
                if (B[iter[i]].Mine(n)) {
                    if (check(B[iter[i]])) {
                        chain.push_back(B[iter[i]]);
                    }
                    done = true;
                    for(Transaction x:B[iter[i]].GetT()){
                        delT(x);
                    }
                    break;
                }
            }
            n *= 2;
        }
    }


    for(Block x:chain){
        std::cout<<"_____________________________________________________\n\n| Hash: "<<x.GetHash()<<"\n| Merkle root: "<<x.GetMerk()<<"\n| Nonce: "<<x.GetNonce()<<"\n______________________________________________\n\t\t|\n\t\t|\n\t\t|\n\t\tV\n";
    }
    //std::cout<<chain.back().GetHash();
    do{
        int nr;
        std::cout<<"Kelinto bloko informacijos norit? (0-"<<chain.size()-1<<" imtinai)\n";
        std::cin>>nr;
        if(nr<chain.size()){
            std::cout<<"_____________________________________________________\n\n| Hash: "<<chain[nr].GetHash()<<"\n| Merkle root: "<<chain[nr].GetMerk()<<"\n| Nonce: "<<chain[nr].GetNonce()<<"\n______________________________________________\nTransactions:\n";
            for(Transaction t:chain[nr].GetT()){
                std::cout << FindN(t.GetI()) << "--- " << t.GetA() << " nignogs ---->" << FindN(t.GetO()) << "\n";
            }
        }
    }while(1);
    return 0;
}