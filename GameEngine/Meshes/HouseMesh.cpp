#include "HouseMesh.h"

HouseMesh::HouseMesh() {
    setPoints(Mesh::loadPointsFromFile("../res/obj/house/house.obj"));
}
