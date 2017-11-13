//
//  loadObj.cpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/09.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#include "loadObj.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>

using namespace std;

istream &safeGetLine(std::istream &is, std::string &str){
    str.clear();
    
    istream::sentry se(is,true);
    streambuf *sb = is.rdbuf();
    
    for(;;){
        int c = sb->sbumpc();
        switch(c){
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n'){
                    sb->sbumpc();
                }
                return is;
            case EOF:
                if(str.empty()){
                    is.setstate(ios::eofbit);
                }
                return is;
            default:
                str += static_cast<char>(c);
        }
    }
}

bool Mesh::loadObj(const string &path){
    ifstream ifs;
    ifs.open(path.c_str(), ios::in);
    if(!ifs.is_open()){
        cerr << "Fail to open the file: " << path << endl;
        exit(1);
    }
    
    string line;
    string buf;
    
    while(!safeGetLine(ifs, line).eof()){
        istringstream input(line);
        
        input >> buf;
        if(buf.empty()){
            continue;
        }
        switch(buf.at(0)){
            case '#':
                break;
            case 'v':
                vertexParce(input,buf);
                numVertices_ += 1;
                break;
            case 'f':
                faceParce(input);
                numIndices_ += 1;
                break;
            default:
                break;
        }
        buf.clear();
    }
    return true;
}

void Mesh::vertexParce(istringstream &input, const string &buf){
    if(buf.size() == 1){
        float x,y,z;
        input >> x >> y >> z;
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }
}

// 三角形か四角形にのみ対応
void Mesh::faceParce(istringstream& input)
{
    std::vector<unsigned int> indexV;
    unsigned int count = 0;
    unsigned int index = 0;
    
    std::string element;
    input >> element;
    std::string tmp;
    for (int i = 0; i < element.size(); i++) {
        if (element.at(i) == '/') {
            if (index == 0) {
                indexV.push_back(std::stoi(tmp));
                index++;
            }
            tmp.clear();
        } else {
            tmp += element.at(i);
        }
    }
    if (index == 0) {
        indexV.push_back(std::stoi(tmp));
    }
    count++;
    while (!input.eof()) {
        index = 0;
        tmp.clear();
        input >> element;
        for (int i = 0; i < element.size(); i++) {
            if (element.at(i) == '/') {
                if (index == 0) {
                    indexV.push_back(std::stoi(tmp));
                    index++;
                }
                tmp.clear();
            } else {
                tmp += element.at(i);
            }
        }
        if (index == 0) {
            indexV.push_back(std::stoi(tmp));
        }
        count++;
        if (count > 3) {
            break;
        }
    }
    
    if (count == 3) {
        for (auto v : indexV) {
            vertexIndex.push_back(v - 1);
        }
    } else if (count == 4) {
        vertexIndex.push_back(indexV.at(0) - 1);
        vertexIndex.push_back(indexV.at(1) - 1);
        vertexIndex.push_back(indexV.at(2) - 1);
        vertexIndex.push_back(indexV.at(2) - 1);
        vertexIndex.push_back(indexV.at(3) - 1);
        vertexIndex.push_back(indexV.at(0) - 1);
    }
}
