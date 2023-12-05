#include "SkyDomeMesh.h"

SkyDomeMesh::SkyDomeMesh() {
    setPoints(loadPointsFromFile("../res/obj/skydome/skydome.obj"));
}
