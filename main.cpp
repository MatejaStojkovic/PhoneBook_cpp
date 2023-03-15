#include "Phonebook.h"// <- ovde idu include-ovi implementiranih klasa
//#include "tst.h"
#include <iostream>
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
using namespace std;

// forward declare tested types

int main() { //int argc, char const *argv[]
    // Testovi se nece ocenjivati.
    // Sluze za testiranje funkcionalnosti bez manuelnog kucanja u terminal.
    // Ispisi su samo primeri, dozvoljeno ih je menjati.

    /*Test1::tst<PhoneBook>();
    Test2::tst<PhoneBook>();
    Test3::tst<PhoneBook>();
    Test4::tst<PhoneBook>();*/
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    PhoneBook& phonebook = PhoneBook::getInstance();
    phonebook.loadPhoneBook("tstmoj.csv");
    phonebook.openTerminal();

    return 0;
}
