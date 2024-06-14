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

typedef struct {
    Vec3 center;
    float radius;
    Color3 color;
} sphere_t;

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

Color3 traceRay(Vec3 origin, Vec3 rayDir, float tMin, float tMax) {
    float closetT = T_MAX;
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ez_raytracer");
    SetTargetFPS(FPS);

    Image i = GenImageColor(640, 400, (Color){255,255,255,255});
    for (int c = 0; c < SCREEN_WIDTH; c++) {
        ImageDrawPixel(&i, c, 10, (Color){0, 0, 255, 255});
    }
    ExportImage(i, "o.png");
    Vec3

    //CloseWindow();
    return 0;
}
