#include <iostream>

class point
{
    public:
        float _x;
        float _y;
        float _z;
        point();
        point(float x, float y, float z): _x(x), _y(y), _z(z){};
        static point avant(){return point(0, 0, -1);}
        static point haut(){return point(0, 1, 0);}
        static point droite(){return point(1, 0, 0);}
        point& operator=(const point b)
        {
            _x = b._x;
            _y = b._y;
            _z = b._z;

            return *this;
        }
        void print(){ std::cout << _x << " " << _y << " "<< _z << std::endl; }
        float dot(point a)
        {
            return (_x * a._x +_y * a._y + _z * a._z);
        }
};

int main()
{
    float x, y , z;
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    point a(x, y, z);
    std::cout << "produit scalaire avec l'avant() " << a.dot(point::avant()) << std::endl;
    std::cout << "produit scalaire avec droite() " << a.dot(point::droite()) << std::endl; 
    std::cout << "produit scalaire avec haut() " << a.dot(point::haut()) << std::endl; 


}