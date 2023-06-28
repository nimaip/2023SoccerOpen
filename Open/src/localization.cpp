#include <localization.h>


Localization::Localization(){
    right_goal_pos = (board_border_width/2 - goal_length/2);
    left_goal_pos = (board_border_width/2 + goal_length/2);
}

void Localization::findPosition(double yellow_goal_angle, double blue_goal_angle){
    

    double slope1 = 1/tan(toRadians(yellow_goal_angle));
    double slope2 = 1/tan(toRadians(blue_goal_angle));
    // Serial.print("Slope 1:");
    // Serial.println(slope1);
    // Serial.print("Slope 2:");
    // Serial.println(slope2);

    double xval = board_field_width/2 - board_field_length/(slope1 - slope2);
    
    
}
void Localization::lrfPosition(double right_lrf, double back_lrf)
{
        lrf2 = right_lrf;
    lrf1 = back_lrf;
    lrf2 /= 10;
    lrf1 /= 10;
    lrfyCoord = lrf1 - (board_border_length - board_field_length)/2;
    lrfxCoord = (board_border_width + board_field_width)/2 - lrf2;


    xCoord = lrfxCoord;
    yCoord = lrfyCoord;
}

