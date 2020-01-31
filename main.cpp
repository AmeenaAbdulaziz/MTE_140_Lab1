//
//  main.cpp
//  Polynom
//
//  Created by Ameena Abdulaziz on 2020-01-21.
//  Copyright © 2020 Ameena Abdulaziz. All rights reserved.
//

#include <iostream>
#include "Polynomial.h"
#include <random>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

Polynomial::Polynomial() {
    srand(time(0));
    int size = rand() % 1001;
    data.resize(size);
    for (int i = 0; i < size; i ++) {
        data[i] = rand() % 1001;
        if (rand() % 2 == 0) {
            data[i] *= -1;
        }
    }
}

Polynomial::Polynomial(int A[], int size) {
    data.resize(size);
    for (int i = 0; i < size; i ++) {
        data[i] = A[i];
    }
}

Polynomial::Polynomial(const Polynomial & p0) {
    data.resize(p0.data.size());
    for (int i = 0; i < data.size(); i ++) {
        data[i] = p0.data[i];
    }
}

Polynomial::Polynomial(int size) {
    data.resize(size);
    for (int i = 0; i < size; i ++) {
        data[i] = 0;
    }
}

Polynomial::Polynomial(string file) {
    ifstream fin;
    fin.open(file);
    int size = 0;
    fin >> size;
    data.resize(size);
    
    for (int i = 0; i < size; i ++) {
        if (!fin)
            data[i] = 0;
        else
            fin >> data[i];
    }
    fin.close();
}

bool Polynomial::operator==(const Polynomial& target) {
    if (data.size() == target.data.size()) {
        for (int i = 0; i < data.size(); i ++) {
            if (target.data[i] != data[i])
                return false;
        }
    }
    return true;
}

Polynomial Polynomial::operator+(const Polynomial& target) {
    int small = (int)data.size();
    bool target_small = true;
    Polynomial curr;
    
    if (data.size() > target.data.size()) {
        small = (int)target.data.size();
        curr = Polynomial((*this));
        target_small = false;
    } else {
        curr = Polynomial(target);
    }

    for (int i = 0; i < small; i ++) {
        if (target_small)
            curr.data[i] += data[i];
        else
            curr.data[i] += target.data[i];
    }
    
    return curr;
}

Polynomial Polynomial::operator-(const Polynomial& target) {
    int small = (int)data.size();
    bool target_small = true;
    bool big_min_small = true;
    Polynomial curr;
    
    if (data.size() > target.data.size()) {
        small = (int)target.data.size();
        curr = Polynomial(*this);
        target_small = false;
    } else {
        curr = Polynomial (target);
        big_min_small = false;
    }
    
    for (int i = 0; i < small; i ++) {
        if (target_small)
            curr.data[i] -= data[i];
        else
            curr.data[i] -= target.data[i];
        if (!big_min_small)
            curr.data[i] *= -1;
    }
    
    return curr;
}

Polynomial Polynomial::operator*(const Polynomial& target) {
    int small = (int)data.size();
    int large = (int)target.data.size();
    bool target_small = false;
    Polynomial curr(data.size() + target.data.size());
    
    if (data.size() > target.data.size()) {
        small = (int)target.data.size();
        large = (int)data.size();
        target_small = true;
    }
    
    for (int i = 0; i < small; i ++) {
        for (int j = 0; j < large; j++){
            if (target_small)
                curr.data[i+j] = data[j] * target.data[i];
            else
                curr.data[i+j] = data[i] * target.data[j];
        }
    }
    return curr;
}

Polynomial Polynomial:: derivative() {

    Polynomial curr(*this);
    for(int i = 0; i < data.size(); i++)
        curr.data[i] = curr.data[i+1]*(i+1);
    
    curr.data.resize(data.size()-1);
    
    return curr;
    
}

void Polynomial::print() { //THIS WAS UPDATED-------------------------------------------------------
    bool first = true;
    
        for(int index = (int)data.size()-1; index >= 0; index --) {
            
            if (data[index] != 0){
                if (!first)
                    cout << " + ";
                else
                    first = false;
                cout << data[index];
                if (index != 0)
                    cout << "x^" << index << " ";
            }
            else if (index == data.size()-1)
                cout << "0";
        }
    cout << endl;
}

class Polynomial_Test {
    
public:
    
};

int main(){
    Polynomial_Test test;
    test.testDerivative();
    
}

//Test cases:
