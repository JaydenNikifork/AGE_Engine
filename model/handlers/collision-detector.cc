#include <vector>
#include "collision-detector.h"
#include "../game-object.h"
#include "../components/sprite.h"
#include "../components/transform.h"

void CollisionDetector::detect() {
    for (auto &ha1 : handlers) {
        for (auto &ha2 : handlers) {
            if (ha1 == ha2) break;

            GameObject *go1 = dynamic_cast<GameObject*>(ha1);
            GameObject *go2 = dynamic_cast<GameObject*>(ha2);

            if (go1->z != go2->z) break;

            Sprite *spr1 = go1->getComponent<Sprite>();
            Sprite *spr2 = go2->getComponent<Sprite>();

            bool colDet = false;
            for (auto &pix1 : spr1->getPixels()) {
                for (auto &pix2 : spr2->getPixels()) {
                    // if (pix1.x + go1->x - 1 <= pix2.x + go2->x &&
                    //     pix2.x + go2->x <= pix1.x + go1->x + 1 &&
                    //     pix1.y + go1->y - 1 <= pix2.y + go2->y &&
                    //     pix2.y + go2->y <= pix1.y + go1->y + 1) {

                    if (pix1.x + go1->x == pix2.x + go2->x && pix1.y + go1->y == pix2.y + go2->y) {
                        ha1->onDetected(CollisionDetected{go2});
                        ha2->onDetected(CollisionDetected{go1});
                        colDet = true;
                        break;
                    }
                }
                if (colDet) break;
            }
        }
    }
}
