#include "Animals.h"
int main()
{
    Animal* zoo[4];
    zoo[0] = new Dog("Rex", "Wof", "Dog", "House", 5);
    zoo[1] = new Cat("Cheshire", "Good afternoon!", "Cat", "Wonderland", 27);
    zoo[2] = new Cow("Burka", "Moo-moo", "Cow", "hills", 6);
    zoo[3] = new Raccoon("Rocket", "Leave me alone", "Raccoon", "Tree", 35);
    for (int i = 0; i < 4; i++) {
        cout << zoo[i]->Bark() << endl;
    }
}