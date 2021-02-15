//
// dna.h
//
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

class dna {
private:
    //
    // This implementation is a doubly-linked structure.  The nodes are structs
    // called Nucleotides.  Size could keep track of how many Nucleotides are
    // currently in the list.  front should always point to the first
    // Nucleotide and back should point to the last one.
    struct Nucleotide {
        char value;
        Nucleotide *next;
        Nucleotide *prev;
    };
    int Size;
    Nucleotide *front;
    Nucleotide *back;
    
    //
    // findFirst: (private)
    //
    // Searches dna for the first copy of the sequence target, returning a
    // pointer to that occurrence or nullptr if the target sequence isn't
    // present.
    // Performance requirement:  this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    Nucleotide* findFirst(dna target) {
        Nucleotide* curr = this->front;
        Nucleotide* check = nullptr;
        bool findFirstMatch = true;  // assume it's true when it found the same letter
        int index;  // when the letter is found get the index
        int count = 0; // count how many letters are the same
        int i = 0;
        Nucleotide* targetPtr = target.front;
        while (i < Size) {
            if (curr->value == targetPtr->value) {
                if (findFirstMatch) {
                    index = i;  // get index at this specific loc
                    findFirstMatch = false;  // make it false 
                    check = curr;  // pointer to current pointer
                }
                count++;
                curr = curr->next;  // move to the next pointer in list
                targetPtr = targetPtr->next;
            } else {
                if (findFirstMatch == false) {  // in case they're not the same
                    curr = check;  // go back to that saved pointer
                    findFirstMatch = true;
                }
                i = i - count;  // move back target.size() back 
                count = 0;
                curr = curr->next;
                targetPtr = target.front;
            }
            if (count == target.Size) {
                return check;
            }
        i++;
        }
        return nullptr;
    }
public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create an empty dna object with two
    // Nucleotides, each with the value of 'X'.
    //
    dna() {
        front = new Nucleotide;
        back = new Nucleotide;
        front->value = 'X';
        front->next = back;
        front->prev = nullptr;
        back->next = nullptr;
        back->prev = front;
        back->value = 'X';
        Size = 2;
    }
    //
    // second constructor:
    //
    // Produces a new strand of nucleotides spelled out in the sequence given
    // by str.
    // Performance requirement: O(n)
    //
    dna(const string& str) {
        Nucleotide* prevv = nullptr;
        // if it's an empty string
        if (str == "") {
            front = nullptr;
            back = nullptr;
        }
        Size = str.size();
        for (int i=0; i<str.size(); i++) {
            Nucleotide* curr = new Nucleotide;
            curr->value = str[i];
            if (i==0) {
                curr->prev = nullptr;
                front = curr;
                prevv = curr;
            } else if (i==str.size()-1) {
                curr->next = nullptr;
                back = curr;
                prevv->next = curr;
                curr->prev = prevv;
            } else {
                prevv->next = curr;
                curr->prev = prevv;
                prevv = curr;
            }
        }
    }
    //
    // copy constructor:
    //
    // Called automatically by C++ to create a dna object that contains a copy
    // of an existing dna object.
    // Performance requirement: O(n)
    //
    dna(const dna& other) {
        Nucleotide* otherPtr = other.front;
        this->Size = other.Size;
        Nucleotide* prevv = nullptr;
        for (int i=0; i<other.Size; i++) {
            Nucleotide* curr = new Nucleotide;                
            curr->value = otherPtr->value;
            if (i==0) {
                curr->prev = nullptr;
                this->front = curr;
                prevv = curr;
                otherPtr = otherPtr->next;
            } else if (i == other.Size -1) {
                curr->next = nullptr;
                this->back = curr;
                curr->prev = prevv;
                prevv->next = curr;
                otherPtr->next = nullptr;
            } else {
                curr->prev = prevv;
                prevv->next = curr;
                prevv = curr;
                otherPtr = otherPtr->next;
            }
        }
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by
    // the dna object.
    // Performance requirement: O(n)
    //
    virtual ~dna() {
        clear();
    }
    //
    // clear:
    //
    // Frees all memory in the chain of nucleotides in the dna obeject.  This
    // function should also set front, back, and Size, appropriately.
    // Performance requirement: O(n)
    //
    void clear() {
        Nucleotide* curr = front;
        while (curr != nullptr) {
            Nucleotide* next = curr->next;
            delete curr;
            curr = next;
        }
        this->front = nullptr;
        this->back = nullptr;
        this->Size = 0;
    }
    //
    // operator=
    //
    // Called when you assign one dna object into another, i.e. this = other;
    // Performance requirement: O(n)
    //
    dna& operator=(const dna& other) {
        clear();
        Nucleotide* otherPtr = other.front;
        Nucleotide* prevv = nullptr;
        this->Size = other.Size;
        for (int i=0; i<other.Size; i++) {
            Nucleotide* curr = new Nucleotide;                
            curr->value = otherPtr->value;
            if (i==0) {
                curr->prev = nullptr;
                this->front = curr;
                prevv = curr;
                otherPtr = otherPtr->next;
            } else if (i == other.Size -1) {
                curr->next = nullptr;
                curr->prev = prevv;
                prevv->next = curr;
                this->back = curr;
                otherPtr->next = nullptr;
            } else {
                curr->prev = prevv;
                prevv->next = curr;
                prevv = curr;
                otherPtr = otherPtr->next;
            }
        }
        if (this == &other) {
            return *this;
        }
    }
    //
    // size:
    //
    // Returns the # of Nucleotides currently in the dna strand.
    // Performance requirement: O(1)
    //
    int size() const {
        return Size;  // TO DO: update this.
    }
    
    //
    // at(i):
    //
    // Returns a reference to the ith Nucleotide's value, which allows
    // you to read (access) or write (modify) this value.  If i is out of
    // bounds, an exception is thrown.
    // Performance requirement: O(n)
    //
    char& at(int i) {
        if (i>=Size) {
            throw out_of_range("Dna: i out of bounds");
        }
        int j;
        Nucleotide* curr = front;
        for (j=0; j<Size;j++) {
            if (j == i) {
                return  curr->value;
            } else {
                curr = curr->next;
            }
        }
        return curr->value;
    }
    //
    // toString:
    //
    // Returns a string spelling out the contents of the dna sequence.
    // Performance requirement: O(n)
    //
    string toString() const {
        string s="";
        Nucleotide* curr = front;
        for (int i=0; i<Size;i++) {
            s = s + curr->value;
            curr = curr->next;
        }
        return s;  
    }
    //
    // operator==
    //
    // This operator determines how you define equality between two operators.
    // In this function, you should compare other and this.  The two objects
    // should be considered equal if they have the same sequence of values and
    // in the same order.
    // Performance requirement: O(n)
    //
    bool operator==(const dna& other) const {
        
        if (this->Size == 0) {
            return true;
        }
        if (this->Size != other.Size) {
            return false;
        }
        Nucleotide* curr = this->front;
        Nucleotide* ot = other.front;
        for (int i=0; i<other.Size; i++) {
            if (curr->value  == ot->value) {
                curr = curr->next;
                ot = ot->next;
            } else {
                return false;
            }
        }
        return true;
    }
    
    //
    // splice:
    //
    // Removes the first copy of the sequence in target that appears in the
    // dna sequence of current object.  This requires the linked structure to
    // be properly re-wired after removal.
    // Performance requirement: this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    // function that deletes the elements and rewires them
    bool splice(dna target) {
        Nucleotide* getFirst = findFirst(target);
        if (getFirst == nullptr) {
            return false;
        }
        this->Size = this->Size - target.Size;  // actualize the size with the new one
        Nucleotide* prevv = getFirst->prev;  // get the left of getFirst
        Nucleotide* curr = getFirst->next;  // get the right of get First
        // if it's at the beginning of the list
        if (getFirst->prev == nullptr) {  // if it's at the beginning
            for (int i=0; i<target.Size; i++) {
                curr->prev = nullptr;
                delete getFirst;
                getFirst = curr;
                curr = curr->next;
                
            }
            this->front = getFirst;
        } else {
            for (int i=0; i<target.Size; i++) {  // if it's at the end
                if (curr == nullptr) {
                    prevv->next = curr;
                    delete getFirst;
                    this->back = prevv;
                    return true;
                }
                prevv->next = curr;
                curr->prev = prevv;
                delete getFirst;
                getFirst = curr;
                curr = curr->next;              
            }
        }
        return true;
    }
    //
    // isLinked()
    //
    // Checks if a strand is linked correctly.  This is provided for you.
    // You should use it to test your linked structure often.
    // Performance requirement: O(n)
    //
    bool isLinked() {
        Nucleotide* start = front;
        // If we're at the start of a strand,
        // we should not have a previous pointer.
        if (start != nullptr && start->prev != nullptr) {
            return false;
        }
        // Walk the list, ensuring at each point that the next/prev pointers
        // are consistent with one another.
        for (Nucleotide* curr = start; curr != nullptr; curr = curr->next) {
            if (curr->next != nullptr && curr->next->prev != curr) return false;
            if (curr->prev != nullptr && curr->prev->next != curr) return false;
        }
        return true;
    }
};
