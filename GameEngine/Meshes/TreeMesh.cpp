#include "TreeMesh.h"

#include "MeshData/Tree.hpp"

TreeMesh::TreeMesh() {
    treeData = make_shared<vector<float>>(vector<float>(std::begin(tree), std::end(tree)));
    setPoints(*treeData);
}
