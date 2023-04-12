#include <localization.h>


Localization::Localization(){
    yellow_goal_angle = 0; // read from pin
}

std::pair<double, double> Localization::findPosition(){
    

    double slope1 = tan(yellow_goal_angle);
    double slope2 = tan(blue_goal_angle);

    double xval = board_width/2 - board_length/(slope1 - slope2);
    double yval = (xval - board_width/2) * slope2;

    // mesh with lrf distances

    return std::make_pair(xval, yval);

}