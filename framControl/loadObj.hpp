//
//  loadObj.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/09.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef loadObj_hpp
#define loadObj_hpp

#include<vector>
#include<string>

using namespace std;

class Mesh{
public:
    Mesh() : numVertices_(0), numIndices_(0){};
    ~Mesh(){};
    
    bool load(const string &path){
        if(!loadObj(path)){
            return false;
        };
        filePath_ = path;
        return true;
    }
    
    unsigned int getVerticesNum() const{return numIndices_;}
    unsigned int getIndicesNum() const{return numIndices_;}
    vector<float> vertices;
    vector<unsigned int> vertexIndex;
private:
    bool loadObj(const string &path);
    void vertexParce(istringstream &inout, const string &buf);
    void faceParce(istringstream &input);
    
    unsigned int numVertices_;
    unsigned int numIndices_;
    string filePath_;
};

#endif /* loadObj_hpp */
