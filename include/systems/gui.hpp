#pragma once
#include "main.h"

using namespace pros;

class odomGUI{
    public :
        void drawFieldObjects(){

        }
        void drawColoredRectangle(int x0, int y0, int x1, int y1, uint32_t color){
            screen::set_pen(color);
            screen::draw_rect(x0, y0, x1, y1);
            screen::fill_rect(x0, y0, x1, y1);

        }
        void drawField(){
            
            int fieldHeightPixel = 234;
            int fieldTileDimension = fieldHeightPixel/6;
            lv_style_t standardSizeStyle;
            lv_obj_t * mainFieldObj;
            // drawing dark spots
            lv_style_copy(&standardSizeStyle, &lv_style_plain);
            standardSizeStyle.body.main_color = LV_COLOR_MAKE(73, 75, 76);
            standardSizeStyle.body.grad_color = LV_COLOR_MAKE(73, 75, 76);
            standardSizeStyle.body.radius = 0;
            standardSizeStyle.body.border.width = 0;
            mainFieldObj = lv_obj_create(lv_scr_act(), NULL);
            lv_obj_set_style(mainFieldObj, &standardSizeStyle);
            lv_obj_set_size(mainFieldObj, fieldHeightPixel, fieldHeightPixel);
          
            // adding goals
            // adding the blue goal
            lv_style_t goalStyle;
            
            lv_obj_t * blueGoal;
            lv_style_copy(&goalStyle, &lv_style_plain);
            goalStyle.body.main_color = LV_COLOR_MAKE(19, 19, 100);
            goalStyle.body.grad_color = LV_COLOR_MAKE(19, 19, 100);
            goalStyle.body.radius = 0;
            goalStyle.body.border.width = 0;
            blueGoal = lv_obj_create(lv_scr_act(), NULL);
            lv_obj_set_style(blueGoal, &goalStyle);
            lv_obj_set_size(blueGoal, fieldTileDimension, fieldTileDimension * 2);
            lv_obj_set_pos(blueGoal, 0, fieldTileDimension * 2);
            lv_obj_del(blueGoal);
            // adding the red goal
            lv_obj_t * redGoal;
            lv_style_t goalStyle2;
            lv_style_copy(&goalStyle2, &lv_style_plain);
            goalStyle.body.main_color = LV_COLOR_MAKE(100, 19, 19);
            goalStyle.body.grad_color = LV_COLOR_MAKE(100, 19, 19);
            redGoal = lv_obj_create(lv_scr_act(), NULL);
            lv_obj_set_style(redGoal, &goalStyle);
            lv_obj_set_size(redGoal, fieldTileDimension, fieldTileDimension * 2);
            lv_obj_set_pos(redGoal, fieldTileDimension * 5, fieldTileDimension * 2);
        }
        void draw(){
            drawField();
            drawFieldObjects();
        }
};
class pidTuneGUI{

};