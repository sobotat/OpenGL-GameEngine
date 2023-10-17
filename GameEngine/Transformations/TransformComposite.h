#pragma once
#include <memory>
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Transform.hpp"

using namespace glm;
using namespace std;

class TransformComposite : public  Transform, public enable_shared_from_this<TransformComposite>{
protected:
    vector<shared_ptr<Transform>> transforms;
public:
    ~TransformComposite();
    mat4 transform() override;
    shared_ptr<TransformComposite> addTransform(shared_ptr<Transform> transform);
};





