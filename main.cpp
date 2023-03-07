
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "DoodScene.hpp"

using namespace threepp;

int main() {

    DoodScene scene(10);

    Canvas canvas;

    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::black);

scene.makeDood(1);

    canvas.onWindowResize([&](WindowSize size) { //Resizes the canvas, but keeps the grid in a locked aspect ratio

        float aspectRatio = static_cast<float>(size.width) / static_cast<float>(size.height);
        scene.getCamera()->left = (-scene.getGridSize() / 2) * aspectRatio;
        scene.getCamera()->right = (scene.getGridSize() / 2) * aspectRatio;
        scene.getCamera()->bottom = scene.getGridSize() / 2;
        scene.getCamera()->top = -scene.getGridSize() / 2;
        scene.getCamera()->updateProjectionMatrix();
        renderer.setSize(size);

    });




    float angle = math::randomInRange(0.0, math::PI);

    scene.setAngle(angle);
    //scene.setAngle(math::PI/2);
    std::cout << "Ang2. " << angle << "  ";


    canvas.animate([&](float t, float dt) {

        scene.update(dt);
        renderer.render(scene.getScene(), scene.getCamera());



    });
}







