#pragma once
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Transform.hpp"

using namespace glm;
using namespace std;

class TransformComposite : public  Transform {
protected:
    vector<Transform*> transforms;
public:
    ~TransformComposite();
    mat4 transform() override;
    TransformComposite* addTransform(Transform* transform);
};





