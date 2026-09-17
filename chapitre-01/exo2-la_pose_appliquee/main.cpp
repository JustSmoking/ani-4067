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
        point SUM = UP + SUP + P + _a;
        return SUM;
    }

};

int main()
{
    
    // 1. Lecture de la position de la pose (Espace Monde)
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

    // 4. Lecture du point de l'entité à transformer (Espace Local)
    float x, y, z;
    std::cin >> x >> y >> z;
    point pointLocal(x, y, z);

    // 5. Calcul de la transformation finale (Espace Local -> Espace Monde)
    point pointEspace = maPose._Pose(pointLocal);

    // 6. Affichage du point transformé
    pointEspace.print();

    return 0;
}