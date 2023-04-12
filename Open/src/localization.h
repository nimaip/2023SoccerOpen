#include <Arduino.h>
#include <trig.h>

class Localization {
    public: 
        Localization();
        double blue_goal_angle;
        double yellow_goal_angle;
        double lrf1, lrf2, lrf3, lrf4;
        // lrf {1,2,3,4} maps to {left, right, front, back} distances

        std::pair<double, double> findPosition();

        const double board_width = 10, board_length = 20; 

    private: 
        double thing;
};

