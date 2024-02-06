#include "Game.h"
using namespace kr;
using namespace math;
std::ostream& operator<< (std::ostream& stream, const kr::math::Vec2& vec)
{
    stream << vec.x << ", " <<vec.y;
    return stream;
}
int main()
{
    std::string d("src/game.conf");
    Game g(d);
    g.run();
    std::cout<<"ok";
}
