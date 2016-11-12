#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

class card
{
    public:

        card() : name_{""}, attack_{}, defense_{}, health_{}, effect_{""} {}
        card(string n, int a, int d, int h, string e) : name_{n}, attack_{a}, defense_{d}, health_{h}, effect_{e} {}

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
            const int nameWidth     = 15;
            const int numWidth      = 10;

            cout << left << setw(nameWidth) << setfill(separator) << getName();
            cout << left << setw(numWidth) << setfill(separator) << getAttack();
            cout << left << setw(numWidth) << setfill(separator) << getDefense();
            cout << left << setw(numWidth) << setfill(separator) << getHealth();
            cout << left << setw(nameWidth) << setfill(separator) << getEffect();
            cout << endl;
        }

    
    private:
        string name_;
        int attack_, defense_, health_;
        string effect_;
};


class hand
{
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
            n = NULL;
            size = size - 1;
            return d;
        }
        else
        {
            cout << "Mao Vazia!" << endl;
        }
        
    }
    void showHand()
    {
        if(size > 0)
        {
            Node *temp;
            temp = head;
            while(temp!=NULL)
            {
                temp->d_.showCard();
                temp=temp->next;
            }
        }
        else
        {
            cout << "Mao Vazia!" << endl;
        }
    }

    void shuffleH()
    {
        vector<card> ca;

        for (int i = 0; i < size; ++i) 
        {
            ca.push_back(popCard());
        }
        srand(time(0));
        random_shuffle(ca.begin(),ca.end());

        for (const auto& card: ca) 
        {
            addCard(card);
        }
    }

    int showSize() { return size;}
// private member
private:
    Node *head; // this is the private member variable. It is just a pointer to the first Node
    int size;
};

class player
{
    public:
        player(string name) : name_{name}, score{0} {}
        player() : name_{""}, score{0} {}
        
        void setpname(string pname) { name_ = pname;}
        string getpname() {return name_;}

        void addpcard(card c)
        {
            player_hand.addCard(c);
        }
        card play_card()
        {
            card d = player_hand.popCard();
            return d;
        }
        void showPcard()
        {
            player_hand.showHand();
        }
        void more_score()
        {
            score++;
        }
        int get_score() {return score;}
        void show_score()
        {
            const char separator    = ' ';
             const int nameWidth     = 15;
            const int numWidth      = 10;

            cout << left << setw(nameWidth) << setfill(separator) << getpname();
            cout << left << setw(numWidth) << setfill(separator) << get_score();
            cout << endl;
        }
        void show_player_hand()
        {
            player_hand.showHand();
        }
        
    private:
    string name_;
    hand player_hand;
    int score;
};


class table
{
    public:
        void deck_init()
        {
            deck_size = 0;
            string cname,catt,cdef,chea,ceff;
            ifstream infile;
            infile.open ("cards.txt");
            while(!infile.eof()) 
            {
                getline(infile,cname); 
                getline(infile,catt);
                getline(infile,cdef);
                getline(infile,chea);
                getline(infile,ceff);

                int at = stoi(catt);
                int de = stoi(cdef);
                int he = stoi(chea);

                deck.addCard(cname, at, de, he, ceff);
                deck_size++;
            }
            infile.close();
        }
        void deck_header()
        {
            const char separator    = ' ';
            const int nameWidth     = 15;
            const int numWidth      = 10;

            cout << left << setw(nameWidth) << setfill(separator) << "Name";
            cout << left << setw(numWidth) << setfill(separator) << "Attack";
            cout << left << setw(numWidth) << setfill(separator) << "Defense";
            cout << left << setw(numWidth) << setfill(separator) << "Health";
            cout << left << setw(nameWidth) << setfill(separator) << "Effect";
            cout <<endl;

        }
        void show_deck()
        {
            deck_header();
            deck.showHand();
        }
        void player_header()
        {
            const char separator    = ' ';
             const int nameWidth     = 15;
            const int numWidth      = 10;

            cout << left << setw(nameWidth) << setfill(separator) << "Name";
            cout << left << setw(numWidth) << setfill(separator) << "Score";
            cout << endl;
        }
        void set_table_deck() 
        { 
            deck_init();
            cout << endl;
            deck_header();
            deck.showHand();
            cout << endl;
            deck.shuffleH();
        }
        int get_number_players() { return play_number; }
        card give_card()
        {   
            deck_size--;
            return deck.popCard();
        }
        void set_players()
        {
            string n1,n2;
            cout << "(Player 1)Name: " << endl;
            getline(cin,n1);
            p1.setpname(n1);
            cout << "(Player 2)Name: "<< endl;
            getline(cin,n2);
            p2.setpname(n2);
            cout << endl;

            for(int i = 0; i < 7; i++)
            {
                card d1 = give_card();
                card d2 = give_card();
                p1.addpcard(d1);
                p2.addpcard(d2);
            }
        }
        void show_players()
        {
            cout << p1.getpname() << endl;
            deck_header();
            p1.show_player_hand();
            cout << endl;
            cout << p2.getpname() << endl;
            deck_header();
            p2.show_player_hand();
            cout << endl;
        }
        void compare(int i)
        {
            const char separator    = '-';
            const int nWidth     = 15;

            int op;
            if(i == 0)
            {
                cout << endl;
                cout << "Player " << p1.getpname() << " choose an attribute: ";
                
            }
            else
            {
                cout << endl;
                cout << "Player " << p2.getpname() << " choose an attribute: ";
            }
            cout << "1 - Attack | 2 - Defense | 3 - Health : " << endl;
            cin >> op;
            cout << endl;
            card c1 = p1.play_card();
            card c2 = p2.play_card();
            cout << endl;
            player_header();
            p1.show_score();
            cout << endl;
            deck_header();
            c1.showCard();
            cout << endl;
            

            cout << endl;
            player_header();
            p2.show_score();
            cout << endl;
            deck_header();
            c2.showCard();
            cout << endl;

            switch(op)
            {
                case 1: 
                {
                     if(c1.getAttack() > c2.getAttack())  { p1.more_score(); }
                     else { p2.more_score();}
                     break;
                }
                case 2: 
                {
                    if(c1.getDefense() > c2.getDefense())  { p1.more_score(); }
                    else  { p2.more_score();}
                    break;
                }
                case 3: 
                {
                    if(c1.getHealth() > c2.getHealth()) { p1.more_score(); }
                    else { p2.more_score();}
                    break;
                }
            }
            cout << endl;
            player_header();
            p1.show_score();
            p2.show_score();
            cout << endl;

        }

        void competition()
        {
            for (int i = 0; i < 5; i++)
            {
                int t = i%2;
                compare(t);
            }

        }

        void win()
        {
            if(p1.get_score() > p2.get_score())
            {
                cout << endl;
                cout << p1.getpname() << " ganhou com " << p1.get_score() << " pontos!" << endl;
            }
            else
            {
                cout << endl;
                cout << p2.getpname() << " ganhou com " << p2.get_score() << " pontos!" << endl;
            }
        }
        void start()
        {
            set_table_deck();
            set_players();
            show_players();
            competition();
            win();
        }
        
    private:
        hand deck;
        hand onplay;
        int deck_size;
        player p1,p2;
        int play_number;

};

int main()
{
    table game;
    game.start();

}