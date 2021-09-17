#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Hero
{
    private:
    int power;
    
    public:
    Hero():power(100){}
    int getPower(){return power;}
    void attack(int n);
    void attacked(int n);
};

void Hero::attack(int n)
{
    cout<<"Your hero attacks!"<<endl;
    power-=n;
    if(power >= 0){
        cout<<"The remaining power of the hero is "<<power<<" ."<<endl;
    }else{
        cout<<"The hero's power is exhausted."<<endl;
    }
}
void Hero::attacked(int n){
    cout<<"Your hero was attacked by an enemy."<<endl;
    power-=n;
    if(power >= 0){
        cout<<"The remaining power of the hero is "<<power<<" ."<<endl;
    }else{
        cout<<"The hero's power is exhausted."<<endl;
    }
}

class Satan
{
    private:
    int power;
    
    public:
    Satan():power(100){}
    int getPower(){return power;}
    void attack(int n);
    void attacked(int n);
};

void Satan::attack(int n)
{
    cout<<"Your enemy Satan attacks!"<<endl;
    power-=n;
    if(power <= 0){
        cout<<"The satan's power is exhausted."<<endl;
    }
}
void Satan::attacked(int n){
    cout<<"Your enemy Satan was attacked by your hero."<<endl;
    power-=n;
    if(power <= 0){
        cout<<"The satan's power is exhausted."<<endl;
    }
}

class KBF
{
    private:
    Satan ryuo;
    Hero roto;
    int satan_place;
    int hero_plase;

    public:
    KBF();
    void battle();
    void kurikaesi_battle();
};

KBF::KBF(){
    srand( (unsigned)time( NULL ) ); //乱数の初期化
    satan_place = rand() % 5 + 1;//rand()% 5は0～4の中のでたらめな数（乱数）
    cout << "The satan is hiding in one of the places 1-5." << endl;
    cout << "Decide where your hero hides from 1-5." << endl;
    cin >> hero_plase;//ヒーローの場所を入力
}

void KBF::battle(){
    int place,attack_power;
    cout<<"\nChoose from 1 to 5 where the hero will attack."<<endl;
    cin>>place;
    cout<<"Decide the power that the hero will use to attack in the range of 1-100."<<endl;
    cin>>attack_power;
    cout<<endl;
    roto.attack(attack_power);

    if(roto.getPower()<0){ //攻撃で自分のパワーが0になればバトル終了
        return;
    }
    if(satan_place==place){
        ryuo.attacked(attack_power * 2);
        if(ryuo.getPower()<0){ //攻撃で敵のパワーが0になればバトル終了
            return;
        }
    }else{
        cout<<"The hero's attack has been evaded."<<endl;
    }

    cout<<endl;
    cout<<"It is an attack of the enemy satan."<<endl;
    cout<<"Press enter."<<endl;
    cin.sync();
    cin.get();
    place = rand() % 5 + 1;
    attack_power = rand() % 50 + 1;
    ryuo.attack(attack_power);

    if(ryuo.getPower()<0){
        return; //攻撃で敵のパワーが0になればバトル終了
    }

    if(hero_plase == place){
        roto.attacked(attack_power * 2);
    }else{
        cout<<"The satan's attack has been evaded."<<endl;
    }

    cout<<"\nIt can be dangerous to stay in the same place. Let's move."<<endl;
    satan_place = rand() % 5 + 1;//rand()% 5は0～4の中のでたらめな数（乱数）
    cout << "The satan is hiding in one of the places 1-5." << endl;
    cout << "Decide where your hero hides from 1-5." << endl;
    cin >> hero_plase;//ヒーローの場所を入力
}

void KBF::kurikaesi_battle(){
    int temp;
    while(1){
        battle();
        temp = roto.getPower();
        if(temp<0){
            cout<<"\nYour hero loses."<<endl;
            break;
        }
        temp = ryuo.getPower();
        if(temp<0){
            cout<<"\nYour hero's victory. Congratulations!"<<endl;
            break;
        }
    }
}

int main(){
    KBF dokoka;
    dokoka.kurikaesi_battle();
    return 0;
}