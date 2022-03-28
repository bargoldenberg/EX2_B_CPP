#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <limits>
#include <bits/stdc++.h>
using ariel::Direction;
using namespace ariel;
using namespace std;
const int MAX_INT = 2147483647; 
const int ROW_SIZE = 100;
const double LOG_10 = log(10);
Notebook::Notebook(){
    this->min = MAX_INT;
    this->max = 0;
}

/**
 * @brief This method writes to the
 * 
 * @param page 
 * @param row 
 * @param column 
 * @param d 
 * @param s 
 */
void Notebook::write(int page,int row, int column, Direction d, string s){
    if(page<0||row<0||column<0){
        throw runtime_error("negative argument!");
    }
    if(d==ariel::Direction::Horizontal){
        if((size_t)column+s.size()>=ROW_SIZE){
            throw invalid_argument("out of bounds!");
        }
        for(int i=column;i<(size_t)column+s.size();i++){
            if(i==column&&this->m[page].count(row)==0){
                this->m[page][row].reserve(ROW_SIZE);
                for(size_t i =0;i<ROW_SIZE;i++){
                    this->m[page][row][i]='_';
                }
            }
            if(this->m[page][row][(size_t)i]=='~'){
                throw invalid_argument("Cannot write on erased pen");
            }
            if(this->m[page][row][(size_t)i]!='_'){
                throw invalid_argument("Cannot write on what is writen!");
            }
            if(isprint(s.at((size_t)(i-column)))==0){
                throw invalid_argument("cannot write this, char is unprintable!");
            }
            if(s.at((size_t)(i-column))=='~'){
                throw invalid_argument("use erase function to write ~");
            }
            this->m[page][row][(size_t)i]= (unsigned char)s.at((size_t)(i-column));
        }
    }else{
        if(column>=ROW_SIZE){
            throw invalid_argument("out of bounds!");
        }
        for(int i=row;i<(size_t)row+s.size();i++){
            if(this->m[page].count(i)==0){
                this->m[page][i].reserve(ROW_SIZE);
                for(int k=0;k<ROW_SIZE;k++){
                    this->m[page][i][(size_t)k]='_';
                }
            }
            if(this->m[page][i][(size_t)column]=='~'){
                throw invalid_argument("Cannot write on erased pen");
            }
            if(this->m[page][i][(size_t)column]!='_'){
                throw invalid_argument("Cannot write on what is writen!");
            }
            if(s.at((size_t)(i-row))=='~'){
                throw invalid_argument("use erase function to write ~");
            }
            this->m[page][i][(size_t)column] = (unsigned char)s.at((size_t)(i-row));
        }
        
    }
    
}


string Notebook::read(int page, int row, int column, Direction d, int length){
    string ans;
    if(page<0||row<0||column<0){
        throw runtime_error("negative argument!");
    }
    if(length<0){
        throw invalid_argument("Length must be positive!");
    }
    if(d==ariel::Direction::Horizontal){
        if((size_t)column+(size_t)length-1>=ROW_SIZE){
            throw invalid_argument("out of bounds!"+to_string((size_t)column)+" "+to_string((size_t)length));
        }
        for(int i=column;i<column+length;i++){
            if(this->m[page].count(row)==0){
                ans.push_back('_');
            }else{
                ans.push_back(this->m[page][row][(size_t)i]);
            }
        }
        return ans;
    }
    if(column>=ROW_SIZE){
        throw invalid_argument("out of bounds!");
    }
    for(int i=row;i<row+length;i++){
        if(this->m[page].count(i)==0){
            ans.push_back('_');
        }else{
            ans.push_back(this->m[page][i][(size_t)column]);
        }
        
    }
    return ans;
    
}
void Notebook::erase(int page, int row, int column, Direction d, int length){
    if(length<0){
        throw invalid_argument("Length must be positive!");
    }
    if(page<0||row<0||column<0){
        throw runtime_error("negative argument!");
    }
    if(ariel::Direction::Horizontal==d){
        if(column+length>ROW_SIZE){
            throw invalid_argument("trying to erase out of bounds!");
        }
        for(int i=column;i<column+length;i++){
            if(this->m[page].count(row)==0){
                this->m[page][row].reserve(ROW_SIZE);
                for(int k=0;k<ROW_SIZE;k++){
                    this->m[page][row][(size_t)k] = '_';
                }
            }
            // if(this->m[page][row][(size_t)i]=='~'){
            //     throw invalid_argument("cannot erase erased");
            // }
            this->m[page][row][(size_t)i]='~';
            
        }
        
    }else{
        if(column>=ROW_SIZE){
            throw invalid_argument("trying to erase out of bounds!");
        }
        for(int i=row;i<row+length;i++){
            if(this->m[page].count(i)==0){
                this->m[page][i].reserve(ROW_SIZE);
                for(int k=0;k<ROW_SIZE;k++){
                    this->m[page][i][(size_t)k] = '_';
                }
            }
            if(this->m[page][i][(size_t)column]=='~'){
                throw invalid_argument("cannot erase erased");
            }
            this->m[page][i][(size_t)column]='~';
           
        }
    }

}
/*
This function computes how much spaces to put before we start printing the line.
*/
void spaces(int i,int max){
    int maxlen = (int)((log(max)/LOG_10)+1);
    int len = (int)((log(i)/LOG_10)+1);
    string spaces;
    for(int i=0;i<maxlen-len;i++){
        spaces.push_back(' ');
    }
    cout<<i<<":"<<spaces;
    
}

int Notebook::findmin(int page){
    int minimum = this->min;
    for(const auto &myPair : this->m[page]){
        int key = myPair.first;
        if(key<minimum){
            minimum = key;
        }
    }
    if(minimum==0){
        return minimum;
    }
    return minimum-1;
    
}

int Notebook::findmax(int page){
    int maximum = this->max;
    for(const auto &myPair : this->m[page]){
        int key = myPair.first;
        if(key>maximum){
            maximum = key;
        }
    }
    return maximum+1;   
}

void Notebook::show(int page){
    if(page<0){
        throw invalid_argument("Page must be non-negitive!");
    }
    int minimum = findmin(page);
    int maximum = findmax(page);
    for(int i=minimum;i<=maximum;i++){
        spaces(i,maximum-1);
        if(this->m[page].count(i)==0){
            for(int j=0;j<ROW_SIZE;j++){
                cout<<'_';
            }
            cout<<endl;
        }else{
            for(int j=0;j<ROW_SIZE;j++){
                char c = this->m[page][i][(size_t)j];
                cout<<c;
            }
            cout<<endl;
        }
    }
}