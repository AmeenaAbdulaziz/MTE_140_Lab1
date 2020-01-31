//
//  main.cpp
//  Polynom_Header
//
//  Created by Ameena Abdulaziz on 2020-01-21.
//  Copyright © 2020 Ameena Abdulaziz. All rights reserved.
//

#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>

using namespace std;

class Polynomial {
private:
    vector<int> data;
    
public:
    Polynomial() ;
    Polynomial (int A[], int size);
    Polynomial(const Polynomial & p0) ;
    Polynomial(int size);
    
    friend class Polynomial_Test;
    
    Polynomial(string);

    //        ~Polynomial();

    bool operator == (const Polynomial& target);
    void print();
    Polynomial operator+ (const Polynomial& target);
    Polynomial operator- (const Polynomial& target);
    Polynomial operator* (const Polynomial& target);
    Polynomial derivative();
    
};

#endif
