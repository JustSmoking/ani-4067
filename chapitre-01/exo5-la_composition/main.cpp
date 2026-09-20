#include <iostream>
#include <cmath>

class point
{
    public:
        float _x;
        float _y;
        float _z;
        point() : _x(0.0f), _y(0.0f), _z(0.0f) {}
        point(float x, float y, float z): _x(x), _y(y), _z(z){}
        static point avant(){return point(0, 0, -1);}
        static point haut(){return point(0, 1, 0);}
        static point droite(){return point(1, 0, 0);}
        float getx(){return _x;}
        float gety(){return _y;}
        float getz(){return _z;}
        point& operator=(const point& b)
        {
            _x = b._x;
            _y = b._y;
            _z = b._z;

            return *this;
        }

        point& operator*=(const float& b)
        {
            _x *= b;
            _y *= b;
            _z *= b;

            return *this;
        }

        point& operator-(const point& b)
        {
            _x -= b._x;
            _y -= b._y;
            _z -= b._z;

            return *this;
        }

        point& operator+(const point& b)
        {
            _x += b._x;
            _y += b._y;
            _z += b._z;

            return *this;
        }
        void print(){ std::cout << _x << " " << _y << " "<< _z << std::endl; }
        float dot(point a)
        {
            return (_x * a._x +_y * a._y + _z * a._z);
        }
};

struct quaternion
{
    float mw;
    float mx;
    float my;
    float mz;
    quaternion() : mw(1.0f), mx(0.0f), my(0.0f), mz(0.0f) {}
    quaternion(float w, float x, float y, float z)
    {
        float qNorm = sqrt(w * w + x * x + y * y + z * z);
        mw = w / qNorm;
        mx = x/qNorm;
        my = y/qNorm;
        mz = z/qNorm;
    }
    float getw(){return mw;}
    float getx(){return mx;}
    float gety(){return my;}
    float getz(){return mz;}

};

struct Pose
{
    point _a;
    quaternion _b;
    point _Pose(point &P)
    {
        float a = _b.getx();
        float b = _b.gety();
        float c = _b.getz();
        float w = _b.getw();
        point U(a, b, c);
        point UP(b * P.getz() - c * P.gety(), c * P.getx() - a * P.getz(), a * P.gety() - b * P.getx());
        point UPP = UP;
        UP *= (2*w);
        point SUP(b * UPP.getz() - c * UPP.gety(), c * UPP.getx() - a * UPP.getz(), a * UPP.gety() - b * UPP.getx());
        SUP *= 2;   
        return UP + SUP + P + _a;;
    }

    point _PoseInverse(point &P)
    {
        float a = _b.getx();
        float b = _b.gety();
        float c = _b.getz();
        float w = _b.getw();
        point U(a, b, c);
        P = P + _a;
        point UP(b * P.getz() - c * P.gety(), c * P.getx() - a * P.getz(), a * P.gety() - b * P.getx());
        point UPP = UP;
        UP *= (2*w);
        point SUP(b * UPP.getz() - c * UPP.gety(), c * UPP.getx() - a * UPP.getz(), a * UPP.gety() - b * UPP.getx());
        SUP *= 2;
        return UP + SUP + P;
    }

    point _inversePose(point &P)
    {
        // Rot Inv de P
        float a = -_b.getx();
        float b = -_b.gety();
        float c = -_b.getz();
        float w = _b.getw();
        point U(a, b, c);
        point UP(b * P.getz() - c * P.gety(), c * P.getx() - a * P.getz(), a * P.gety() - b * P.getx());
        point UPP = UP;
        UP *= (2*w);
        point SUP(b * UPP.getz() - c * UPP.gety(), c * UPP.getx() - a * UPP.getz(), a * UPP.gety() - b * UPP.getx());
        SUP *= 2;
        point SUMROTP = UP + SUP + P;

        //Rotation inversion de la ()
        point UPI(b * _a.getz() - c * _a.gety(), c * _a.getx() - a * _a.getz(), a * _a.gety() - b * _a.getx());
        point UPPI = UPI;
        UPI *= (2*w);
        point SUPI(b * UPPI.getz() - c * UPPI.gety(), c * UPPI.getx() - a * UPPI.getz(), a * UPPI.gety() - b * UPPI.getx());
        SUPI *= 2;
        
        return SUMROTP - UPI - SUPI - _a;
    }

    point _composePose(Pose &second, point &P)
    {
        point temp = second._Pose(P);
        return this->_Pose(temp);
    }

};

void _poseTest()
{
// 1. Lecture de la position de la pose 
    float px, py, pz;
    std::cin >> px >> py >> pz;
    point positionPose(px, py, pz);

    // 2. Lecture du quaternion d'orientation (w, x, y, z)
    float qw, qx, qy, qz;
    std::cin >> qw >> qx >> qy >> qz;
    quaternion orientationPose(qw, qx, qy, qz);

    // 3. Initialisation de la Pose
    Pose maPose;
    maPose._a = positionPose;
    maPose._b = orientationPose;

    // 4. Lecture du point de l'entité à transformer 
    float x, y, z;
    std::cin >> x >> y >> z;
    point pointLocal(x, y, z);

    // 5. Calcul de la transformation finale 
    point pointEspace = maPose._Pose(pointLocal);

    // 6. Affichage du point transformé
    pointEspace.print();
}

void _poseTInverseTest()
{
    // 1. Lecture de la position de la pose
    float px, py, pz;
    std::cin >> px >> py >> pz;
    point positionPose(px, py, pz);

    // 2. Lecture du quaternion d'orientation
    float qw, qx, qy, qz;
    std::cin >> qw >> qx >> qy >> qz;
    quaternion orientationPose(qw, qx, qy, qz);

    // 3. Initialisation de la Pose
    Pose maPose;
    maPose._a = positionPose;
    maPose._b = orientationPose;

    // 4. Lecture du point à inverser 
    float x, y, z;
    std::cin >> x >> y >> z;
    point pointMonde(x, y, z);

    // 5. Calcul de l'inverse 
    point pointLocal = maPose._PoseInverse(pointMonde);

    // 6. Affichage du point transformé
    pointLocal.print();
}

void _inversePoseTest()
{
    // 1. Lecture de la position de la pose
    float px, py, pz;
    std::cin >> px >> py >> pz;
    point positionPose(px, py, pz);

    // 2. Lecture du quaternion d'orientation
    float qw, qx, qy, qz;
    std::cin >> qw >> qx >> qy >> qz;
    quaternion orientationPose(qw, qx, qy, qz);

    // 3. Initialisation de la Pose
    Pose maPose;
    maPose._a = positionPose;
    maPose._b = orientationPose;

    // 4. Lecture du point à inverser 
    float x, y, z;
    std::cin >> x >> y >> z;
    point pointMonde(x, y, z);

    // 5. Calcul de l'inverse 
    point pointLocal = maPose._inversePose(pointMonde);

    // 6. Affichage du point transformé
    pointLocal.print();
}

void _composePoseTest()
{
    // 1. Lecture de la position de la pose 1
    float px, py, pz;
    std::cin >> px >> py >> pz;
    point positionPose(px, py, pz);

    // 2. Lecture du quaternion d'orientation (w, x, y, z)1
    float qw, qx, qy, qz;
    std::cin >> qw >> qx >> qy >> qz;
    quaternion orientationPose(qw, qx, qy, qz);

    // 1. Lecture de la position de la pose 2
    float px1, py1, pz1;
    std::cin >> px1 >> py1 >> pz1;
    point positionPose1(px1, py1, pz1);

    // 2. Lecture du quaternion d'orientation (w, x, y, z)2 
    float qw1, qx1, qy1, qz1;
    std::cin >> qw1 >> qx1 >> qy1 >> qz1;
    quaternion orientationPose1(qw1, qx1, qy1, qz1);

    // 3. Initialisation de la Pose
    Pose maPose;
    maPose._a = positionPose;
    maPose._b = orientationPose;

    Pose maPose1;
    maPose1._a = positionPose1;
    maPose1._b = orientationPose1;

    // 4. Lecture du point de l'entité à transformer 
    float x, y, z;
    std::cin >> x >> y >> z;
    point pointLocal(x, y, z);

    // 5. Calcul de la transformation finale 
    point pointEspace = maPose._composePose(maPose1, pointLocal);

    // 6. Affichage du point transformé
    pointEspace.print();

    std::cout << "Resultat apres la Pose 2" << std::endl;
    point p1 = maPose1._Pose(pointLocal);
    p1.print();

    std::cout << "Resultat apres la Pose 1 suivi de la pose 2 (Resultat final)" << std::endl;

    point p2 = maPose._Pose(p1);
    p2.print();
}

int main()
{
    //_poseTest();
    //_inversePoseTest();

    _composePoseTest();
    
}