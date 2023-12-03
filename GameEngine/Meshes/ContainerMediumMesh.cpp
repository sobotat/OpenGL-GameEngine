#include "ContainerMediumMesh.h"

ContainerMediumMesh::ContainerMediumMesh() {
    setPoints(loadPointsFromFile("../res/fbx/Container_v1_medium.fbx"));
}
