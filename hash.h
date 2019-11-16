#include <string>
#include <bitset>
#include <vector>

std::string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
class gib{
private:
    int seed;
public:
    gib(int s){seed=s;}
    int next() {
        unsigned int next = seed;
        int result;
        next *= 1103515245;
        next += 12345;
        result = (unsigned int) (next / 65536) % 2048;

        next *= 1103515245;
        next += 12345;
        result <<= 10;
        result ^= (unsigned int) (next / 65536) % 1024;

        next *= 1103515245;
        next += 12345;
        result <<= 10;
        result ^= (unsigned int) (next / 65536) % 1024;

        seed = next;

        return result;
    }
};
std::string hash(std::string a) {
    int leng=40;
    std::vector < bool > bin;
    int nn = 0;
    for (char x: a) {
        for (int i = 0; i < 8; i++) {
            bin.push_back(std::bitset < 8 > ((int) x)[i]);
        }
        nn += (int) x;
    }
    while (bin.size() / 6 < leng) {
        bin.push_back(0);
        bin.push_back(1);
    }
    gib R(nn);
    for (int i = 0; i < bin.size()+nn; i++) {
        int j = R.next() % bin.size();
        bin[j] = !bin[j];
    }
    int ll = (bin.size() - leng * 6) / leng;
    std::string out = "";
    std::bitset < 6 > letter;
    int stup=0;
    if(ll!=0) { stup = R.next() % ll; }
    int ct = stup;
    for (int i = 0; i < leng; i++) {
        for (int o = 0; o < 6; o++) {
            letter[o] = bin[ct + o];
        }
        if(ll!=0) { stup = R.next() % ll; }
        ct += 6 + stup;
        out += base[letter.to_ulong()];
    }
    return out;
}
