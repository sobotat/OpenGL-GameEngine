#include "WallMesh.h"

WallMesh::WallMesh() {
    setPoints(loadPointsFromFile("../res/obj/wall/wall.obj"));
}
