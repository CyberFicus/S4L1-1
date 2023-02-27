#include <iostream>
#include <fstream>

using namespace std;

class LSFR { // многочлен f(x) = x^15 + x^1 + 1 -> смотрим на 0 и 14 (если считать от 0 до 15) биты, т.е. & с 1 и 16 384   
private:
    unsigned short num;
    int shift() {
        int res = 1; // т.к. f(x) = ... + 1
        if (!(num & 16384))
            res += 1;
        if (!(num & 2))
            res += 1;
        res %= 2;
        num = num << 1;
        num += res;
        return res % 2;
    }
    char cipher_byte(char c) {
        char gamma = this->shift();
        for (int i = 0; i < 7; i++) {
            gamma <<= 1;
            gamma += this->shift();
        }
        return c ^ gamma;
    }
public:
    LSFR(int a) { num = a; };
    void cipher_file(ifstream &fin, ofstream &fout) {
        char c = 0;
        if (fin.is_open() && fout.is_open()) {
            fin >> noskipws >> c;
            while (!fin.eof()) {
                fout << this->cipher_byte(c);
                fin >> noskipws >> c;
            }
            fin.close();
            fout.close();
        }
    }
};


int main() {
    ifstream fin;
    ofstream fout;
    register LSFR lsfr1(0), lsfr2(0);
    //шифруем
    fin.open("f1.txt");
    fout.open("f2.txt");
    lsfr1.cipher_file(fin, fout);
    //дешифруем
    fin.open("f2.txt");
    fout.open("f3.txt");
    lsfr2.cipher_file(fin, fout);

	//system("pause");
	return 0;
}
