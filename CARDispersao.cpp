#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

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

        void showName()
        {
            const char separator    = ' ';
            const int nameWidth     = 15;

            cout << " | " << getName();
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

    void showNamesHand()
    {
        if(size > 0)
        {
            Node *temp;
            temp = head;
            while(temp!=NULL)
            {
                temp->d_.showName();
                temp=temp->next;
            }
            cout << endl;
        }
        else
        {
            cout << "Mao Vazia!" << endl;
        }
    }

    int getSize()
    {
        return size;
    }
// private member
private:
    Node *head; // this is the private member variable. It is just a pointer to the first Node
    int size;
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
            cout << " Recomenda-se um numero primo, e abaixo do número de cartas(15)" << endl;
            cout << " Digite o tamanho da tabela: ";
            cin >> hash_size;
            tabela_dispersao = new hand[hash_size];
        }

        int gerar_k(card d)
        {
            string str = d.getName();
            int size = str.size();
            char *letras = new char[size];
            int somar = 0;
            for(int i =0;i < str.size();i++)
            {
                letras[i] = str[i];
                somar = letras[i] + somar;
            }
            return somar;
        }
        
        int diff_absol(int a, int b)
        {
            int resul = a - b;

            if (resul<0)
            {
                resul = resul*(-1);
            }

            return resul;
        }

        int hash_personalizada(int k, int tamanho_tabela)
        {
            int diff = diff_absol(k,tamanho_tabela);
            int hash = (k+diff)%(tamanho_tabela);
            return hash;
        }

        int hash_divisao(int k, int tamanho_tabela)
        {
            int hash = (k)%tamanho_tabela;
            return hash;
        }

        int hash_multiplicacao(int k, int tamanho_tabela)
        {
            double m,kf,a,resul;
            m = 512.0;
            kf = k;
            a = 0.66;
            double mod = 1.0;
            double kfa = kf*a;
            double r_kfa = fmod(kfa,mod);
            resul = m*r_kfa;
            resul = floor(resul);
            int i_resul = resul;
            int hash = i_resul%tamanho_tabela;
            return hash;
        }

        void choose_your_hash()
        {
            cout << "| 1 - Hash Personalizada | 2 - Hash Divisao | 3 - Hash Multiplicacao" << endl;
            int op;
            cin >> op;
            switch(op)
            {
                case 1:{cout << "Hash Personalizada selecionada! \n" << endl; run_p_hash();break;}
                case 2:{cout << "Hash Divisao selecionada! \n" << endl; run_d_hash();break;}
                case 3:{cout << "Hash Multiplicacao selecionada! \n" << endl; run_m_hash();break;}
            }
        }

        void run_p_hash()
        {
            deck_init();
            while(deck.getSize() > 0)
            {
                card d = deck.popCard();
                string card_name = d.getName();
                int k = gerar_k(d);
                int hash = hash_personalizada(k,hash_size);
                tabela_dispersao[hash].addCard(d);
            }
            cout << endl;
            for(int i = 0; i < hash_size; i++)
            {
                cout << "Endereço " << i << ": \n";
                tabela_dispersao[i].showNamesHand();
                cout << endl;
            }
        }

        void run_d_hash()
        {
            deck_init();
            while(deck.getSize() > 0)
            {
                card d = deck.popCard();
                string card_name = d.getName();
                int k = gerar_k(d);
                int hash = hash_divisao(k,hash_size);
                tabela_dispersao[hash].addCard(d);
            }
            for(int i = 0; i < hash_size; i++)
            {
                cout << "Endereço " << i << ": \n";
                tabela_dispersao[i].showNamesHand();
                cout << endl;
            }
        }

        void run_m_hash()
        {
            deck_init();
            while(deck.getSize() > 0)
            {
                card d = deck.popCard();
                string card_name = d.getName();
                int k = gerar_k(d);
                int hash = hash_multiplicacao(k,hash_size);
                tabela_dispersao[hash].addCard(d);
            }
            for(int i = 0; i < hash_size; i++)
            {
                cout << "Endereço " << i << ": \n";
                tabela_dispersao[i].showNamesHand();
                cout << endl;
            }
        }

        void start()
        {
            choose_your_hash();
            
        }
        
    private:
        hand* tabela_dispersao;
        hand deck;
        int deck_size;
        int hash_size;
};

int main()
{
    table hash;
    hash.start();
};