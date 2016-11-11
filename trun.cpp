#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class card
{
    public:
        card(string name, int attack, int defense, int health ): name_{name}, attack_{attack}, defense_{defense}, health_{health} {}

    private:
        string name_;
        int attack_, defense_, health_;
        string effect_;
}