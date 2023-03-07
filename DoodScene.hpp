//
// Created by sijoj on 21/02/2023.
//

#ifndef THREEPP_VCPKG_TEST_DOODSCENE_HPP
#define THREEPP_VCPKG_TEST_DOODSCENE_HPP

#include "threepp/threepp.hpp"
#include <iostream>
#include <unordered_map>

using namespace threepp;

//class Dood {
//public:

/*    Dood(int doodType) {

    }

    void makeDood(int i) {  //Just for testing, needs implementing
        {
            std::shared_ptr<BoxGeometry> boxGeometry_ = BoxGeometry::create(1, 1, 0);

            auto doodMaterial = MeshBasicMaterial::create();
            if (i%2 != 0) {doodMaterial->color = Color::red;}
            else{doodMaterial->color = Color::green;}


            doodMap_[i] = Mesh::create(boxGeometry_, doodMaterial);
            boxMap_[i] = Box3().setFromObject(*doodMap_[i]);  //WTF? Figure this one out plz



            auto helper = Box3Helper::create(boxMap_[i], Color::blue);
            scene_->add(helper);


            scene_->add(doodMap_[i]);
        }
    }
};*/

class DoodScene : public Scene, public KeyListener {
public:


    DoodScene(int gridSize) {


        scene_ = Scene::create();
        //scene->position.set(OrigoX_, OrigoY_, 0);
        gridSize_ = gridSize;
        setCoordSystem(gridSize);

        camera_ = OrthographicCamera::create(-gridSize_ / 2, gridSize_ / 2, -gridSize_ / 2, gridSize_ / 2);
        camera_->position.z = 5;    //Creates camera, and sets it to grid size



        {
            auto grid = GridHelper::create(gridSize_, gridSize_, 0x444444, 0x444444);
            grid->rotation.x = math::PI / 2;

            scene_->add(grid);

        }

        shootOrigin_.y = OrigoY_;
        arrow_ = ArrowHelper::create(shootDirection_, shootOrigin_, 2, Color::red);
        scene_->add(arrow_);


    }


    void update(float dt) {
        dt_ = dt;
        shootDood(fdKey_);
        if (!moving_) {
            fdKey_++;
            makeDood(fdKey_);

        }

    }

    void setCoordSystem(int gridSize) {
        gridSize_ = gridSize;   //gridSize is specifiable by function
        OrigoX_ = -gridSize_ / 2 + 0.5; //Making the x and y origo for a coordinate system
        OrigoY_ = gridSize_ / 2 - 0.5;
    }


    void makeDood(int i) {  //Just for testing, needs implementing
        {
            std::shared_ptr<BoxGeometry> boxGeometry_ = BoxGeometry::create(1, 1, 0);

            auto doodMaterial = MeshBasicMaterial::create();
            if (i % 2 != 0) { doodMaterial->color = Color::red; }
            else { doodMaterial->color = Color::green; }


            doodMap_[i] = Mesh::create(boxGeometry_, doodMaterial);
            boxMap_[i] = Box3().setFromObject(*doodMap_[i]);  //WTF? Figure this one out plz



            auto helper = Box3Helper::create(boxMap_[i], Color::blue);
            scene_->add(helper);


            scene_->add(doodMap_[i]);
        }
    }


    int getGridSize() {
        return gridSize_;
    }

    std::shared_ptr<Scene> getScene() {
        return scene_;
    }

    std::shared_ptr<OrthographicCamera> getCamera() {
        return camera_;
    }

    std::shared_ptr<Mesh> getDood(int doodKey) {
        return doodMap_[doodKey];
    }

    void setAngle(float angle) {
        angle_ = angle;

    }

    float getAngle() {
        return angle_;
    }

    void setDoodPos(float x, float y, std::shared_ptr<Mesh> body) {
        auto position = body->position;
        position.setX(OrigoX_ + round(x));
        position.setY(OrigoY_ - round(y));


        body->position = position;
    }

    float getDoodPosX(std::shared_ptr<Mesh> body) {
        return body->position.x - OrigoX_;
    }

    float getDoodPosY(std::shared_ptr<Mesh> body) {
        return -(body->position.y - OrigoY_);
    }

    int getDoodCoordX(std::shared_ptr<Mesh> body) {
        return round(body->position.x) - OrigoX_;
    }

    int getDoodCoordY(std::shared_ptr<Mesh> body) {
        return -(round(body->position.y) - OrigoY_);
    }

    //std::unordered_map



    void moveFrameWise(float angle, std::shared_ptr<Mesh> body, float dt) {
        moveAngle_ = angle;
        float deltaDist = moveSpeed_ * dt;
        auto position = body->position;
        position.setX(position.x + deltaDist * cos(moveAngle_));
        position.setY(position.y - deltaDist * sin(moveAngle_));
        body->position = position;
    }

    void shootDood(int doodKey) {
        if (!moving_) {
            angle_ = math::randomInRange(math::PI / 8, math::PI - math::PI / 8); //Debug stuff lies here
            moveAngle_ = angle_;
            setDoodPos(gridSize_ / 2, 0, doodMap_[doodKey]);
        }

        lastCoord_.set(getDoodCoordX(doodMap_[doodKey]), getDoodCoordY(doodMap_[doodKey]), 0);
        arrow_->setDirection(getShootDirection());
        if (borderDectX(doodMap_[doodKey])) {
            moveAngle_ = math::PI - moveAngle_;
        }
        if (!borderDectY(doodMap_[doodKey])) {


            if (!cellOccupied(getDoodCoordX(doodMap_[doodKey]), getDoodCoordY(doodMap_[doodKey]))) {

                moveFrameWise(moveAngle_, doodMap_[doodKey], dt_);
                moving_ = true;

            } else {
                moving_ = false;
                setDoodPos(lastCoord_.x, lastCoord_.y, doodMap_[doodKey]);
            }
        } else {
            moving_ = false;
            setDoodPos(getDoodPosX(doodMap_[doodKey]), getDoodPosY(doodMap_[doodKey]), doodMap_[doodKey]);
        }
    }

    bool borderDectY(std::shared_ptr<Mesh> body) {
        auto position = body->position;
        if (getDoodPosY(body) >= gridSize_ - 1) {
            return true;
        }
        return false;
    }

    bool borderDectX(std::shared_ptr<Mesh> body) {
        auto position = body->position;
        if ((getDoodPosX(body) >= gridSize_ - 1) || (getDoodPosX(body) < 0)) {
            return true;
        }
        return false;
    }

    Vector3 getShootDirection() {
        Vector3 direction;
        direction.x = cos(angle_);
        direction.y = -sin(angle_);
        return direction;
    }

    bool cellOccupied(int x, int y) {
        for (int i = 1; i < doodMap_.size(); i++) {
            if (x == getDoodCoordX(doodMap_[i])) {
                if (y == getDoodCoordY(doodMap_[i]) - 1) { //Wut?, Added -1 to make work, Fix dis plz
                    return true;
                }
            }
        }
        return false;
    }


private:
    std::shared_ptr<OrthographicCamera> camera_;
    std::shared_ptr<Scene> scene_;
    int gridSize_;
    std::shared_ptr<Mesh> dood_;
    std::shared_ptr<ArrowHelper> arrow_;
    float OrigoX_;
    float OrigoY_;
    float moveSpeed_ = 20;
    float angle_;
    float moveAngle_;
    float dt_;
    int fdKey_ = 1;

    bool moving_ = false;

    Vector3 arrowSize_;
    Vector3 shootOrigin_;
    Vector3 lastCoord_;

    Vector3 shootDirection_;
    std::unordered_map<int, std::shared_ptr<Mesh>> doodMap_;
    std::unordered_map<int, Box3> boxMap_;



};


#endif //THREEPP_VCPKG_TEST_DOODSCENE_HPP
