//
// Created by msmkl on 18.03.2023.
//
#include <iostream>
#include <string>

using namespace std;
class Gas_Barrel {
public:
    double Volume = 10;
    double Mass = 1;
    double Molar = 0.1;

//    Gas_Barrel(double V, double m, double M){
//        Volume = V;
//        Mass = m;
//        Molar = M;
//    };
    double GetPressure(int T){
        return (Mass/Molar) * 8.31 * T / Volume ;
    }
    double AmountOfMatter(){
        return (Mass/Molar);
    }
    string ToString(){
//        cout << "Volume: " << Volume << endl;
//        cout << "Mass: " << Mass << endl;
//        cout << "Molar: " << Molar << endl;
        return to_string(Volume)+'\n'+ to_string(Mass) +'\n' + to_string(Molar)+'\n'+to_string(AmountOfMatter()) + '\n';
    }
};

class Mod_Gas_Barrel{
public:
    virtual void ModifVolume(double dV) = 0;
    virtual double GetDp(int T0, int T) = 0;
    virtual string Passport() = 0;
};

class Adapter: public Gas_Barrel, public Mod_Gas_Barrel{
private:
    Gas_Barrel * MB;
public:
    Adapter(Gas_Barrel* b1): MB(b1) {

    }
    void ModifVolume(double dV){
        MB->Volume += dV;
    }

    double GetDp(int T0, int T){
        return (MB->GetPressure(T)) - (MB->GetPressure(T0));
    }

    string Passport(){
        return MB->ToString();
    }

};



int main(){

    Mod_Gas_Barrel * p = new Adapter(new Gas_Barrel);
    cout << p->Passport() << endl << endl;
    cout << p->GetDp(100, 200) << endl << endl;
    p->ModifVolume(10);
    cout << p->Passport() << endl;
    cout << p->GetDp(100, 200) << endl;

}