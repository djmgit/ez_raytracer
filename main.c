#include <raylib.h>
#include <ez_tracer.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define VIEWPORT_WIDTH 1
#define VIEWPORT_HEIGHT 1
#define CAMERA_VIEWPORT_DISTANCE 1
#define T_MAX 32768
#define FPS 60

const Vec3 ORIGIN = (Vec3){0, 0, 0};
const Vec3 BACKGROUND_COLOR = (Vec3){255, 255, 255};

typedef struct {
    Vec3 center;
    float radius;
    Color3 color;
} sphere_t;

typedef struct {
    sphere_t *spheres
} scene_t;

void screenDrawPixel(int x, int y, Color c, Image *image) {
    int sX = (SCREEN_WIDTH / 2) + x;
    int sY = (SCREEN_HEIGHT / 2) - y;

    ImageDrawPixel(image, (int)x, (int)y, c);
}

Vec3 screenToViewPort(int sX, int sY) {
    return (Vec3){
        (float)(sX*VIEWPORT_WIDTH/SCREEN_WIDTH), 
        (float)(sY*VIEWPORT_HEIGHT/SCREEN_HEIGHT),
        CAMERA_VIEWPORT_DISTANCE
    };
}

void getRaySphereIntersection(Vec3 *origin, Vec3 *rayDir, sphere_t *sphere, int *t1, int *t2) {
    float r = sphere->radius;
    Vec3 centerToOrigin = sub(origin, &sphere->center);

    float a = dot(rayDir, rayDir);
    float b = 2*dot(&centerToOrigin, rayDir);
    float c = dot(&centerToOrigin, &centerToOrigin);

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        *t1 = T_MAX;
        *t2 = T_MAX;
    }

    *t1 = (float)((-b + sqrt(discriminant)) / (2*a));
    *t2 = (float)((-b - sqrt(discriminant)) / (2*a));
}

Color3 traceRay(Vec3 *origin, Vec3 *rayDir, float tMin, float tMax, scene_t *scene) {
    float closestT = T_MAX;
    sphere_t *closestSphere = NULL;
    for (int i = 0; i < 3; i++) {
        sphere_t sphere = scene->spheres[i];
        int t1, t2;
        getRaySphereIntersection(origin, rayDir, &sphere, &t1, &t2);
        if (tMin <= t1 <= tMax) {
            closestT = t1;
            closestSphere = &(scene->spheres[i]);
        }
        if (tMin <= t2 <= tMax) {
            closestT = t2;
            closestSphere = &(scene->spheres[i]);
        }
    }

    if (closestSphere == NULL) {
        return BACKGROUND_COLOR;
    }
    return closestSphere->color;
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ez_raytracer");
    SetTargetFPS(FPS);


    Image image = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255,255,255,255});
    sphere_t spheres[3] = {
        {{0, -1, 3}, 1, {255, 0, 0}},
        {{2, 0, 4}, 1, {0, 0, 255}},
        {{-2, 0, 4}, 1, {0, 255, 0}}
    };

    scene_t scene;
    scene.spheres = malloc(sizeof(sphere_t) * 3);
    scene.spheres = spheres;

    for (int x = -1*(SCREEN_WIDTH / 2); x <= (SCREEN_WIDTH / 2); x++) {
        for (int y = -1 * (SCREEN_HEIGHT / 2); y <= (SCREEN_HEIGHT / 2); y++) {
            Vec3 d = screenToViewPort(x, y);
            Color3 color = traceRay(&ORIGIN, &d, 1, T_MAX, &scene);
            screenDrawPixel(x, y, (Color){color.x, color.y, color.z}, &image);
        }
    }

    ExportImage(image, "o.png");

    //CloseWindow();
    return 0;
}
