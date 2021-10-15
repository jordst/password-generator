#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <sstream>
#include <unistd.h>

struct flags {
	int alpha;
	int alphaCaps;
	int specials;
	int nums;
	int vowels;
	int hex;
	int clipboard;
	double pLength;
} flag ;

void  readhelp();
int option(int argc, char *argv[]);
std::string passGen(std::string arr, int len, int rngx, int rngy);
void toc(std::string str);

int main(int argc, char *argv[]) {
    std::string alhpabet = {"abcdefghijklmnopqrstuvwxyz"};
    std::string alhpabetCaps = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::string num = {"1234567890"};
    std::string special = {"!@#$%\"^&*`'()_-+=~[]{};:,./<>\?"};
	std::string hexa = {"0123456789ABCDEF"};
	std::string vowel = {"01aeiouyAEIOUY"};

    std::string finalPass = "";
    std::string nuPass;

    option(argc, argv);
    
	for (int i=0; i<10; i++) {
	if (flag.alpha==1) finalPass += passGen(alhpabet, flag.pLength, 0, 25);
	if (flag.alphaCaps==1) finalPass += passGen(alhpabetCaps, flag.pLength, 0, 25);
	if (flag.specials==1) finalPass += passGen(special, flag.pLength, 0, 32);
	if (flag.nums==1) finalPass += passGen(num, flag.pLength, 0, 9);
	if (flag.hex==1) finalPass += passGen(hexa, flag.pLength, 0, 15);
	if (flag.vowels==1) finalPass += passGen(vowel, flag.pLength, 0, 13);

	nuPass += passGen(finalPass, flag.pLength, 1, finalPass.length()-1);
	std::cout<<nuPass<<std::endl;
	finalPass="";
	nuPass="";
	}
}

// array, password lenght, min range of array, max range of array
std::string passGen(std::string arr, int len, int rngx, int rngy) {
    std::mt19937_64 randr;
	std::uniform_int_distribution<std::mt19937_64::result_type> rng(rngx, rngy);
    randr.seed(std::random_device()());
    std::string ret;
	for (int i = 0; i < len; i++) {
		ret += arr[rng(randr)];
	}
	return ret;
}

void readhelp() {
	std::string line;
	std::ifstream file;
	file.open("helpscr.txt");

	if (file.is_open()) {
		while (getline(file, line)) {
			std::cout<<line<<std::endl;
		}
		file.close();
	} else {
		std::cout<<"error opening file"<<std::endl;
	}
	return;
}

int option(int argc, char *argv[]) {
	int c = 0;
	while ((c = getopt(argc, argv, ":HaAvscnhl:")) != -1) {
		switch (c) {
			case 'H':
				readhelp();
				break;
			case 'a':
				flag.alpha=1;
				break;
			case 'A':
				flag.alphaCaps = 1;
				break;
			case 's':
				flag.specials = 1;
				break;
			case 'n':
				flag.nums = 1;
				break;
			case 'h':
				flag.hex = 1;
				break;
			case 'c':
				flag.clipboard = 1;
				break;
			case 'v':
				flag.vowels = 1;
				break;
			case 'l':
				flag.pLength = atof(optarg);
				break;
			default:
				std::cout << "Unknown option" << std::endl;
				break;
		}
    }
	return 0;
}
