#include <Arduino.h>
#include <trig.h>

class Localization {
    public: 
        Localization();
        double lrf1, lrf2; // lrf1 is back, lrf2 is right
        // coordinates are measured from the lower left corner intersection of the white lines
        double xCoord;
        double yCoord;

        void findPosition(double yellow_goal_angle, double blue_goal_angle);
        void lrfPosition(double right_lrf, double back_lrf);
        const double board_border_width = 182;
        const double board_border_length = 243; 
        const double board_field_width = 158;
        const double board_field_length = 219;
        const double goal_width = 7.4;
        const double goal_length = 60;
        double lrfxCoord = 0;
        double lrfyCoord = 0;
        double left_goal_pos;
        double right_goal_pos;

    private: 
        double thing;
};

