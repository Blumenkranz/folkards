#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class card
{
    public:

        card() : name_{""}, attack_{0}, defense_{0}, health_{0}, effect_{""} {}

        string getName() { return name_; }
        int getAttack() { return attack_; }
        int getDefense() { return defense_; }
        int getHealth() { return health_; }
        string getEffect() { return effect_; }

        void setName(string n) { name_ = n; }
        void setAttack(int a) { attack_ = a; }
        void setDefense(int d) { defense_ = d; }
        void setHealth(int h) { health_ = h; }
        void setEffect(string e) { effect_ = e; }
        
        void showCard()
        {
            const char separator    = ' ';
            const int nameWidth     = 12;
            const int numWidth      = 5;

            cout << left << setw(nameWidth) << setfill(separator) << getName();
            cout << left << setw(numWidth) << setfill(separator) << getAttack();
            cout << left << setw(numWidth) << setfill(separator) << getDefense();
            cout << left << setw(numWidth) << setfill(separator) << getHealth();
            cout << left << setw(numWidth) << setfill(separator) << getEffect();
            cout << endl;
        }

    
    private:
        string name_;
        int attack_, defense_, health_;
        string effect_;
};

class hand{
    struct Node {
        card d_;
        Node *next;
    };
public:
    hand(){
        head = NULL;
        size = 0; 
    }

    // This prepends a new value at the beginning of the list
    void addCard(card d){
        Node *n = new Node();   // create new Node
        n->d_ = d;             // set value
        n->next = head;         // make the node point to the next node.
                                //  If the list is empty, this is NULL, so the end of the list --> OK
        head = n;               // last but not least, make the head point at the new node.
        size++;
    }
    void addCard(string n, int a, int de, int h, string e)
    {
        card *d = new card();
        d->setName(n);
        d->setAttack(a);
        d->setDefense(de);
        d->setHealth(h);
        d->setEffect(e);

        Node *t = new Node();   // create new Node
        t->d_ = *d;             // set value
        t->next = head;         // make the node point to the next node.
                                //  If the list is empty, this is NULL, so the end of the list --> OK
        head = t;               // last but not least, make the head point at the new node.
        size++;

    }
    // returns the first element in the list and deletes the Node.
    // caution, no error-checking here!
    card popCard(){
        if(size > 0)
        {
            Node *n = head;
            card d = n->d_;
            head = head->next;
            delete n;
            size = size - 1;
            return d;
        }
        else
        {
            cout << "Mao Vazia!" << endl;
        }
        
    }
    int showSize() { return size;}
// private member
private:
    Node *head; // this is the private member variable. It is just a pointer to the first Node
    int size;
};



int main()
{
    
}
