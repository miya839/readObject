//
//  View.hpp
//  framControl
//
//  Created by 宮本栄作 on 2017/11/10.
//  Copyright © 2017年 宮本栄作. All rights reserved.
//

#ifndef View_hpp
#define View_hpp

#include<glm/glm.hpp>

class View{
public:
    View(glm::vec3 position, glm::vec3 up = glm::vec3(0.0,1.0,0.0));
    View(const View &other) = delete;
    View& operator=(const View& other) = delete;
    ~View() = default;
    
    glm::mat4 getViewMatrix() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    glm::vec3 getDirection() const;
    
    void setPosition(glm::vec3 position);
    void setUp(glm::vec3 up);
    void setDirectionHorizontalAngle(float angle);
    void setDirectionVerticalAngle(float angle);
    void move(glm::vec3 translation);
    
    glm::vec3 rotateUpHorizontal(float angle);
    glm::vec3 rotateUpVertical(float angle);
    
    glm::vec3 rotateDirectionHorizontal(float angle);
    glm::vec3 rotateDirectionVertical(float angle);
    
private:
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 up_;
    glm::vec3 right_;
    
    float horizontalAngle_;
    float verticalAngle_;
    
    void calcDirection();
};

#endif /* View_hpp */
