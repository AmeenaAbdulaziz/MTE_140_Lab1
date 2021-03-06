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
    	return true;
    }
    return false;
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
                curr.data[i+j] += data[j] * target.data[i];
            else
                curr.data[i+j] += data[i] * target.data[j];
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

void Polynomial::print() { 
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
    
    Polynomial_Test () {
    	nums1[0] = 1;
    	nums1[1] = 2;
    	nums1[2] = 3;
    	nums1[3] = 4;
    	nums1[4] = 5;
    	nums2[0] = 2;
    	nums2[1] = 4;
    	nums2[2] = 6;
    	nums2[3] = 4;
    	nums2[4] = 9;
    	nums2[5] = 9;
    	nums2[6] = 10;
	    howMany = 5;
	    howMany2 = 7;
	    poly1 = Polynomial(nums1, howMany);
	    poly2 = Polynomial(nums1, howMany);
	    poly3 = Polynomial(nums2, howMany2);
    }
    
    bool testEquals() {
    	assert((poly1 == poly2) == true);
    	assert(!(poly1 == poly3) == true);
    }
    
    bool testAdd() {
    	int testArr1[] = {2, 4, 6, 8, 10};
    	int testArr2[] = {3, 6, 9, 8, 14, 9, 10};
    	Polynomial testAdd1(testArr1, howMany);
    	Polynomial testAdd2(testArr2, howMany2);
    	assert((poly1 + poly2) == testAdd1);
    	assert((poly1 + poly3) == testAdd2);
    }
    
    bool testSub() {
    	int testArr1[]= {-1, -2, -3, 0, -4, 9, 10};
    	int testArr2[] = {1, 2, 3, 0, 4, 9 ,10};
    	Polynomial testSub1(testArr1, howMany2);
    	Polynomial testSub2(testArr2, howMany2);
    	assert((poly1 - poly3) == testSub1);
    	assert((poly3 - poly1) == testSub2);
    }
    
    void run () {
    	if(testEquals()) {
    		cout << "== passed" << endl;
    	} else {
    		cout << "== failed" << endl;	
    	}
    	if(testAdd()) {
    		cout << "+ passed" << endl;
    	} else {
    		cout << "+ failed" << endl;	
    	}
    	if(testSub()) {
    		cout << "- passed" << endl;
    	} else {
    		cout << "- failed" << endl;	
    	}
    }

    bool testConstructor1() {//no parameters
      Polynomial test;
      if (test.data.size() <= 1000 && test.data.size() >= 0){
        for (int i = 0; i < test.data.size(); i++){
          if (!(test.data[i] <= 1000 && test.data[i] >= -1000))
            return false;
        }
        return true;
      }
      return false;
    }


    bool testConstructor2() {//from array + size
      const int SIZE = 5;
      int arr[SIZE] = {1, 2, 3, 4, 5};
      Polynomial test (arr, SIZE);
      if (test.data.size() == SIZE){
        for (int i = 0; i < SIZE; i++){
          if (!(test.data[i] == arr[i]))
            return false;
        }
        return true;
      }
      return false;
    }


    bool testConstructor3() {//from file
      const int SIZE = 5;
      int fileContents[SIZE] = {3, 4, 1, 5, 9};
      string fileName = "test.txt";

      Polynomial test ("test.txt");

      if (test.data.size() == SIZE){
        for (int i = 0; i < SIZE; i++){
          if (!(test.data[i] == fileContents[i]))
            return false;
        }
        return true;
      }
      return false;
    }


    bool testConstructor4(){//copy
      const int SIZE = 5;
      int arr[SIZE] = {1, 2, 3, 4, 5};
      Polynomial reference (arr, SIZE);
      Polynomial copy (reference);
      
      if (copy.data.size() == SIZE){
        for (int i = 0; i < SIZE; i++){
          if (!(copy.data[i] == reference.data[i]))
            return false;
        }
        return true;
      }
      return false;
    }

  public:
    void run(){
      if (testConstructor1())
        cout << "Test Constructor1 Passed";
      else
        cout <<"Test Constructor1 Not Passed";
      cout << endl;

      if (testConstructor2())
        cout << "Test Constructor2 Passed";
      else
        cout <<"Test Constructor2 Not Passed";
      cout << endl;
      
      if (testConstructor3())
        cout << "Test Constructor3 Passed";
      else
        cout <<"Test Constructor3 Not Passed";
      cout << endl;
      
      if (testConstructor4())
        cout << "Test Constructor4 Passed";
      else
        cout <<"Test Constructor4 Not Passed";
      cout << endl;
    }
    
    
    
};

int main(){
    Polynomial_Test test;
    test.testDerivative();
    
}

//Test cases:
