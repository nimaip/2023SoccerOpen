
class Goal {
    public:
        Goal();
        double Process(double ball, int Orientation, double goalOrientation, int initialOrientation);
        double goalAngle;
        void Kick(double goalDist,bool capture, double correction);
    private:
        int kickTimer;
        int kickActivate;

};