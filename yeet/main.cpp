#include "emscripten.h"
#include "box.hpp"
#include "boxinfo.hpp"
#include "container.hpp"
#include "pack.hpp"
#include "packer.hpp"
#include "vec3usi.hpp"
#include <iostream>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    // unsigned char: 0 to 255
    int pack(int length, unsigned char dimensions[]) {
        std::vector<Container> containers;
        containers.push_back(Container(containers.size() + 1, Vec3usi(58, 140, 78)));

        std::vector<BoxInfo> boxesInfo;
        for (int i = 0; i < length; i += 3) {
            Vec3usi boxDimensions = Vec3usi(dimensions[i], dimensions[i + 1], dimensions[i + 2]);
            boxesInfo.push_back(BoxInfo(boxesInfo.size() + 1, boxDimensions, 1));
        }

        Packer packer;
        std::vector<Pack> packs = packer.pack(containers, boxesInfo);

        return packs.size();
    }
}
