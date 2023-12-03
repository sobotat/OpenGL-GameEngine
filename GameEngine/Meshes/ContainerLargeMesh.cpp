#include "ContainerLargeMesh.h"

ContainerLargeMesh::ContainerLargeMesh() {
    setPoints(loadPointsFromFile("../res/fbx/Container_v1_large.fbx"));
}
