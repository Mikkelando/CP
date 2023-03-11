//
// Created by msmkl on 11.03.2023.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <string>
using namespace std;

// Component
class Password_Generator
{
public:
    virtual string generate(){
        assert(false);
    };
    virtual string allowed_chars(){
        assert(false);
    }
    virtual void addGen(Password_Generator* p) {
        assert(false);
    }
    virtual ~Password_Generator() {}
};



class Basic_Password_Generator: public Password_Generator
{
private:
    size_t len = 4;
public:

    size_t length(){
        return len;
    }

};


class digit_gen: public Basic_Password_Generator
{
private:
    string digits = "1234567890";
public:
    size_t L = length();
    string allowed_chars(){
        string string1 = "";
        for(int i = 0; i < L; i++){
            string1 += digits[rand() % 10];
        }
        return string1;
    }
};

class lower_letter_generator: public Basic_Password_Generator
{
private:
    string letters_lower = "abcdefghijklmnopqrstuvwxyz";
public:
    size_t L = length();
    string allowed_chars(){
        string string1 = "";
        for(int i = 0; i < L; i++){
            string1 += letters_lower[rand() % 26];
        }
        return string1;
    }
};

class upper_letter_generator: public Basic_Password_Generator
{
private:
    string letters_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
public:
    size_t L = length();
    string allowed_chars(){
        string string1 = "";
        for(int i = 0; i < L; i++){
            string1 += letters_upper[rand() % 26];
        }
        return string1;
    }
};

class symbol_gen: public Basic_Password_Generator
{
private:
    string symbols = "~!@#$%^&*()_+-=?><|";
public:
    size_t L = length();
    string allowed_chars(){
        string string1 = "";
        for(int i = 0; i < L; i++){
            string1 += symbols[rand() % 19];
        }
        return string1;
    }
};



// Composite
class CompositeUnit: public Password_Generator
{
private:
    std::vector<Password_Generator*> c;

public:
    string generate(){
        string S = "";

        for(int i = 0; i < c.size(); i++){

            S += c[i]->allowed_chars();
        }
        random_shuffle(S.begin(), S.end());
        return S;
    }

    void addGen(Password_Generator* p) {
        c.push_back(p);
    }
    ~CompositeUnit() {
        for(int i=0; i<c.size(); ++i)
            delete c[i];
    }



};



int main()
{
    srand(time(NULL));
    CompositeUnit* password1 = new CompositeUnit;
    password1->addGen(new digit_gen);
    password1->addGen(new symbol_gen);
    password1->addGen(new upper_letter_generator);
    password1->addGen(new lower_letter_generator);

    cout << password1->generate() << endl;


    CompositeUnit* password2 = new CompositeUnit;
    password2->addGen(new digit_gen);
    password2->addGen(new upper_letter_generator);
    password2->addGen(new lower_letter_generator);

    cout << password2->generate() << endl;

    CompositeUnit* password3 = new CompositeUnit;
    password3->addGen(new digit_gen);
    password3->addGen(new upper_letter_generator);

    cout << password3->generate() << endl;
    cout << password3->generate() << endl;
    cout << password3->generate() << endl;


    return 0;
}