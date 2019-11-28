# Blockchain užduotis 2: bitcoin imitacija
## v0.3
Tranzakcijų validacija ir realistiškesnis blokų prijungimas prie grandinės. Taip pat vartotojai dabar turi tikrus vardus!

## Merkle medžio šaknies funkcija
Įgivendinau merkle funkciją (bloko klasės metodą) panašiai kaip libbitcoin bibliotekoje:
```cpp
std::string Merk(){
        if(!Tran.empty()) {
            // surasoma i merkle medi visos bloko tranzakcijos Tran (uzhasuotos)
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
```
