/*
 * Progarm Name: test-conflict-check.cpp
 * Created Time: 2017-03-28 10:04:47
 * Last modified: 2017-04-11 16:13:11
 * @author: minphone.linails linails@foxmail.com 
 */

#include "test-conflict-check.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <map>
#include <list>
#include <gtest/gtest.h>
#include <sstream>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::make_pair;
using std::list;
using std::stringstream;

vector<device_t> TesterConflict::devices_set;
vector<scene_t>  TesterConflict::orig_scenes;
ConflictCheck   *TesterConflict::cc = nullptr;

void TesterConflict::SetUpTestCase(void)
{
    for(int i=0; i<1000; i++){
        device_t dev = {
            i,
            "myhome : 009029876758893798759832",
            "status 0"
        };

        devices_set.push_back(dev);
    }

    init_scenes();

    cout << "devies_set.size() : " << devices_set.size() << endl;
    cout << "orig_scenes.size() : " << orig_scenes.size() << endl;

}

void TesterConflict::TearDownTestCase(void)
{
    if(nullptr != cc){
        delete cc;
    }
}

int  TesterConflict::init_scenes(void)
{
    vector<device_t> &vdev = devices_set;

    {
        scene_t scene;

        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 1;
        scene.time              = 100;
        scene.timetype          = 1;

        cdevs.push_back(vdev[2]);

        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[5]);
        rdevs.push_back(vdev[6]);
        rdevs.push_back(vdev[7]);
        rdevs.push_back(vdev[8]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        //orig_scenes.push_back(scene);
    }

    return 0;
}

TEST_F(TesterConflict, init_ConflictCheck)
{
    if(nullptr == cc){
        cc = new ConflictCheck(&devices_set, &orig_scenes);
        ASSERT_NE(nullptr, cc);
        cout << "new cc" << endl;
    }else{
        cout << "cc != nullptr" << endl;
    }
}

TEST_F(TesterConflict, add_scene_1_)
{
    {
        vector<device_t> &vdev = devices_set;

        scene_t scene;

        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 1;
        scene.time              = 100;
        scene.timetype          = 1;

        cdevs.push_back(vdev[2]);

        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[5]);
        //rdevs.push_back(vdev[6]);
        //rdevs.push_back(vdev[7]);
        //rdevs.push_back(vdev[8]);
        //rdevs.push_back(vdev[18]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        if(nullptr != cc){
            int ret = cc->check(scene);
            cout << "cc->check() : " << ret << endl;
            EXPECT_EQ(-1, ret);
        }else{
            cout << "cc->check() is null" << endl;
        }
    }
}

TEST_F(TesterConflict, add_scene_2_)
{
#if 0
    {
        vector<device_t> &vdev = devices_set;

        vdev[3].status = "status 1";

        scene_t scene;

        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 2;
        scene.time              = 100;
        scene.timetype          = 1;

        cdevs.push_back(vdev[9]);

        rdevs.push_back(vdev[3]);   // <--
        rdevs.push_back(vdev[14]);
        rdevs.push_back(vdev[15]);
        rdevs.push_back(vdev[16]);
        rdevs.push_back(vdev[17]);
        rdevs.push_back(vdev[18]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        if(nullptr != cc){
            int ret = cc->check(scene);
            cout << "cc->check() : " << ret << endl;
            EXPECT_NE(-1, ret);
        }else{
            cout << "cc->check() is null" << endl;
        }
    }
#endif
}

TEST_F(TesterConflict, init0)
{
}

