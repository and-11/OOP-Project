#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include <Helper.h>

void Initialize() {
    std::srand(std::time(0));
}

int Random() {

    return std::rand()%100+1;
}

class Stats{
private:
    int health,strength,stamina,precision,defence;
public:
    int get_health() {
        return health;
    }
    int get_strength() {
        return strength;
    }
    int get_stamina() {
        return stamina;
    }
    int get_precision() {
        return precision;
    }
    int get_defence() {
        return defence;
    }
    Stats() {
        strength=1,stamina=1,precision=1,health=1,defence=1;
    }
    Stats(int health,int strength,int stamina,int precision,int defence) {
        this->strength=strength;
        this->stamina=stamina;
        this->precision=precision;
        this->health=health;
        this->defence=defence;
    }
    friend std::ostream& operator<<(std::ostream& os,const Stats& st) {
        os <<"Stats:\n";
        os<<"   Health: "<<st.health<<"\n";
        os<<"   Strength: "<<st.strength<<"\n";
        os<<"   Stamina: "<<st.stamina<<"\n";
        os<<"   Precision: "<<st.precision<<"\n";
        os<<"   Defence: "<<st.defence<<"\n";
        return os;
    }
    void Increment_stat() {
        std::cout<<"Chose stat to increment:\nPress: 1 for Health | 2 for Strength | 3 for Stamina | 4 for Precision | 5 for Defence\n";
        int x;
        std::cin>>x;
        if ( x==1 )
            health+=1;
        else if ( x==2 )
            strength+=1;
        else if ( x==3 )
            stamina+=1;
        else if ( x==4 )
            precision+=1;
        else if ( x==5 )
            defence+=1;
        std::cout << *this;
    }
};

class Attack{
private:
    std::string name;
    int damage_multiplier;
    int precision_multiplier;
public:
    int get_damage_multiplier() {
        return damage_multiplier;
    }
    int get_precision_multiplier() {
        return precision_multiplier;
    }
    Attack() {
        name = "";
        damage_multiplier = 0;
        precision_multiplier = 0;
    }
    Attack(std::string name, int damage_multiplier, int precision_multiplier) {
        this->name = name;
        this->damage_multiplier = damage_multiplier;
        this->precision_multiplier = precision_multiplier;
    }
    ~Attack() {
        // std::cout << "deleted";
    }
    friend std::ostream& operator<<(std::ostream& os, const Attack& at) {
        os << "Name: " << at.name << "\n   damage_multiplier:" << at.damage_multiplier << "\n   precision_multiplier:" << at.precision_multiplier ;
        return os;
    }
};

class Character {
private:
    std::string name;
    int HP;
    Stats stats;
    std::vector<Attack>attacks;
public:
    Character() {
        name = "";
        stats = Stats();
        Attack fist("fist",2,3),kick("kick",3,1);
        attacks.push_back(fist);
        attacks.push_back(kick);
    }
    Character(std::string name) {
        this->name = name;
        stats = Stats();
        Attack fist("fist",2,3),kick("kick",3,1);
        attacks.push_back(fist);
        attacks.push_back(kick);
    }
    friend std::ostream& operator<<(std::ostream& os, const Character& pl) {
        os << "Name: " << pl.name << "\n";
        os << pl.stats << "\n";
        os << "Attacks:\n";
        for (int i=0;i<pl.attacks.size();i++) {
            os << pl.attacks[i] << "\n";
        }
        return os;
    }
    Character& operator=(const Character& pl) {
        name = pl.name;
        stats = pl.stats;
        for (int i=0;i<pl.attacks.size();i++) {
            attacks.push_back(pl.attacks[i]);
        }
    }
    Character(const Character& pl) {
        this->name = pl.name;
        stats = pl.stats;
        for (int i=0;i<pl.attacks.size();i++) {
            attacks.push_back(pl.attacks[i]);
        }
    }
    ~Character() {
        while (attacks.size() ){
            attacks.pop_back();
        }
    }
    int get_defence() {
        return stats.get_strength();
    }
    int get_HP() {
        return HP;
    }
    void set_HP(int HP) {
        this->HP = HP;
    }
    std::string get_name() {
        return name;
    }
    bool is_alive() {
        return HP>0;
    }
    void ready_for_fight() {
        HP= 15+2*stats.get_health() ;
    }

    void Spend_Skill_Points(int n) {
        std::cout<< "\n\n"<< name << " is spending " << n << " skill points: "<<"\n";
        for (int i=0;i<n;i++) {
            stats.Increment_stat();
        }
    }

    void Attack_Character( Character & pl ) {
        std::cout << "Select attack:\n";
        for (int i=0;i<attacks.size();i++) {
            std::cout << i+1 << ")" << attacks[i] << "\n";
        }
        int x;
        std::cin >> x;
        while( x<=0 or attacks.size()<x ) {
            std::cout << "invalid input\n";
            std::cin >> x;
        }

        x--;

        if ( 0.5*Random()*stats.get_precision()*attacks[x].get_precision_multiplier() > 1.0*Random()*pl.get_defence() ){
            pl.set_HP( pl.get_HP() - attacks[x].get_damage_multiplier()*stats.get_strength() );
            std::cout << "HIT! " << pl.get_name() << " now has " << pl.get_HP() << "HP\n";
        }
        else {
            std::cout << "MISS!\n";
        }
    }

};

void Fight(Character x,Character y) {
    x.ready_for_fight();
    y.ready_for_fight();

    bool step=0;
    while ( x.is_alive() and y.is_alive() ) {
        if ( step ) {
            std::cout << x.get_name() << "'s turn\n";
            x.Attack_Character(y);
        }
        else {
            std::cout << y.get_name() << "'s turn\n";
            y.Attack_Character(x);
        }
        step=!step;
    }
    if (x.is_alive())
        std::cout << x.get_name() ;
    else
        std::cout << y.get_name() ;
    std::cout << " is the WINNER!\n";
}


int main() {
    Initialize();



    Character A("Tyson"),C("MCgregor");
    A.Spend_Skill_Points(5);
    C.Spend_Skill_Points(5);

    Fight(A,C);



    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}