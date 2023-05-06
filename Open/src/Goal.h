
class Goal {
    public:
        Goal();
        double blue_goal_angle;
        double yellow_goal_angle;
        void Kick(bool capture);
    private:
        int kickTimer;
        int kickActivate;

};