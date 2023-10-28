#include "GiftMesh.h"

#include "MeshData/Gift.hpp"

GiftMesh::GiftMesh() {
    data = make_shared<vector<float>>(vector<float>(std::begin(gift), std::end(gift)));
    setPoints(*data);
}
