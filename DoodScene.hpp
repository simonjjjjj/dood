//
// Created by sijoj on 21/02/2023.
//

#ifndef THREEPP_VCPKG_TEST_DOODSCENE_HPP
#define THREEPP_VCPKG_TEST_DOODSCENE_HPP

#include "threepp/threepp.hpp"
#include <iostream>
#include <unordered_map>

using namespace threepp;

class Dood {
public:

    Dood(int doodType) {
        makeDood(doodType);
    }

    void makeDood(int i) {  //Just for testing, needs implementing
        {
            std::shared_ptr<BoxGeometry> boxGeometry_ = BoxGeometry::create(1, 1, 0);

            auto doodMaterial = MeshBasicMaterial::create();

            switch (i%6) {
                case 0:
                    doodMaterial->color = Color::red;
                    break;
                case 1:
                    doodMaterial->color = Color::green;
                    break;
                case 2:
                    doodMaterial->color = Color::blue;
                    break;
                case 3:
                    doodMaterial->color = Color::purple;
                    break;
                case 4:
                    doodMaterial->color = Color::yellow;
                    break;
                case 5:
                    doodMaterial->color = Color::gainsboro;
                    break;
            }

            doodBod_ = Mesh::create(boxGeometry_, doodMaterial);
            doodBox_ = Box3().setFromObject(*doodBod_);  //WTF? Figure this one out plz

            doodHelper_ = Box3Helper::create(doodBox_, Color::blue);

        }
    }

    Box3 getDoodBox() {
        return doodBox_;
    }

    std::shared_ptr<Mesh> getDoodMesh() {
        return doodBod_;
    }

    std::shared_ptr<Box3Helper> getDoodHelper() {
        return doodHelper_;
    }

    Vector3 getPosition() {
        return position_;
    }

    void setPosition(Vector3 position) {
        position_ = position;
        updatePos();
    }

    void setPosition(float x, float y) {
        oldPosition_ = position_;
        position_.setX(x);
        position_.setY(y);
        updatePos();
    }



    void updatePos(){
        doodBod_->position = position_;
        doodBox_.set(position_ - doodSize_/2, position_ + doodSize_/2);
        //doodBox_.translate(position_ - oldPosition_); //PLZ REVISIT!
    }



private:
    std::shared_ptr<Mesh> doodBod_;
    Box3 doodBox_;
    std::shared_ptr<Box3Helper> doodHelper_;
    Vector3 position_;
    Vector3 oldPosition_;
    Vector3 doodSize_ = {1, 1, 0};
};

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

        /*Dood firstDood(0);
        scene_->add(firstDood.getDoodMesh());
        scene_->add(firstDood.getDoodHelper());
        doodMap_.insert({0, firstDood});*/


    }


    void update(float dt) {
        dt_ = dt;
        std::printf("!1!\n");
        if (!moving_) {
            fdKey_++;
            Dood newDood(fdKey_);
            doodMap_.insert({fdKey_, newDood});
            std::printf("!2!\n");
        }
        shootDood(doodMap_.at(fdKey_));
    }

    void setCoordSystem(int gridSize) {
        gridSize_ = gridSize;   //gridSize is specifiable by function
        OrigoX_ = -gridSize_ / 2 + 0.5; //Making the x and y origo for a coordinate system
        OrigoY_ = gridSize_ / 2 - 0.5;
    }



 /*   void makeDood(int i) {  //Just for testing, needs implementing
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
    }*/


    int getGridSize() {
        return gridSize_;
    }

    std::shared_ptr<Scene> getScene() {
        return scene_;
    }

    std::shared_ptr<OrthographicCamera> getCamera() {
        return camera_;
    }

    Dood getDood(int doodKey) {
        return doodMap_.at(doodKey);
    }

    void setAngle(float angle) {
        angle_ = angle;

    }

    float getAngle() {
        return angle_;
    }

    void setDoodPos(float x, float y, Dood body) {
        auto position = body.getPosition();
        position.setX(OrigoX_ + round(x));
        position.setY(OrigoY_ - round(y));


        body.setPosition(position);
    }

    float getDoodPosX(Dood body) {
        return body.getPosition().x - OrigoX_;
    }

    float getDoodPosY(Dood body) {
        return -(body.getPosition().y - OrigoY_);
    }

    int getDoodCoordX(Dood body) {
        return round(body.getPosition().x) - OrigoX_;
    }

    int getDoodCoordY(Dood body) {
        return -(round(body.getPosition().y) - OrigoY_);
    }





    void moveFrameWise(float angle, Dood& body, float dt) {  //consider moving to Dood
        moveAngle_ = angle;
        float deltaDist = moveSpeed_ * dt;
        auto position = body.getPosition();
        std::cout << position << " - ";
        position.setX(position.x + deltaDist * cos(moveAngle_));
        position.setY(position.y - deltaDist * sin(moveAngle_));
        std::cout << position << std::endl;
        body.setPosition(position);
    }

    void shootDood(Dood& body) {
        if (!moving_) {
            angle_ = math::randomInRange(math::PI / 8, math::PI - math::PI / 8); //Debug stuff lies here
            moveAngle_ = angle_;
            std::printf("!3!\n");
            scene_->add(body.getDoodMesh());
            scene_->add(body.getDoodHelper());
            std::printf("!4!\n");
            body.setPosition(0, OrigoY_);
            std::printf("!5!\n");

        }

        lastCoord_.set(getDoodCoordX(body), getDoodCoordY(body), 0);
        arrow_->setDirection(getShootDirection());
        if (borderDectX(body)) {
            moveAngle_ = math::PI - moveAngle_;
        }
        if (!borderDectY(body)) {


            //if (!cellOccupied(getDoodCoordX(doodMap_.at(doodKey)), getDoodCoordY(doodMap_.at(doodKey)))) {
            if(!collision(body) || body.getPosition() == Vector3(0, 0, 0)){
                std::cout << body.getPosition() << std::endl;
                std::printf("!6!\n");

                moveFrameWise(moveAngle_, body, dt_);
                moving_ = true;

            } else {
                moving_ = false;
                setDoodPos(getDoodPosX(body), getDoodPosY(body), body);
                std::printf("Collision\n");
            }
        }
        else {
            moving_ = false;
            setDoodPos(getDoodPosX(body), getDoodPosY(body), body);
            std::printf("Bord.det_Y\n");
        }
    }

    bool borderDectY(Dood body) {
        if (getDoodPosY(body) >= gridSize_ - 1) {
            std::printf("!Y true!\n");
            return true;
        }
        return false;
    }

    bool borderDectX(Dood body) {
        if ((getDoodPosX(body) >= gridSize_ - 1) || (getDoodPosX(body) < 0)) {
            std::printf("!X true!\n");
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

    /*bool cellOccupied(int x, int y) {
        for (int i = 1; i < doodMap_.size(); i++) {
            if (x == getDoodCoordX(doodMap_[i])) {
                if (y == getDoodCoordY(doodMap_[i]) - 1) { //Wut?, Added -1 to make work, Fix dis plz
                    return true;
                }
            }
        }
        return false;
    }*/

    /*bool collision(Dood body){
        for(auto it = doodMap_.begin(); it != doodMap_.end(); ++it) {  //IMPORTANT:: will return true if it on self check; needs exclusion
            if(body.getDoodBox().intersectsBox(it->second.getDoodBox()) && it->first != fdKey_) {
                std::printf("!true!\n");
                return true;
            }
        }
        std::printf("!false!\n");
        return false;
    }*/

    bool collision(Dood body) {
        Box3 bodyBox = body.getDoodBox();
        for (auto& it : doodMap_) {
            if (it.first == fdKey_) {
                continue;  // skip self-check
            }
            Box3 otherBox = it.second.getDoodBox();
            if (bodyBox.intersectsBox(otherBox)) {
                return true; //dude
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
    float moveSpeed_ = 10;
    float angle_;
    float moveAngle_;
    float dt_;
    int fdKey_ = 0;

    bool moving_ = false;

    Vector3 arrowSize_;
    Vector3 shootOrigin_;
    Vector3 lastCoord_;

    Vector3 shootDirection_;
    std::unordered_map<int, Dood> doodMap_;
    std::unordered_map<int, Box3> boxMap_;



};


#endif //THREEPP_VCPKG_TEST_DOODSCENE_HPP
