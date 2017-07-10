#include <Math/Vector3.h>

namespace Gene { namespace Graphics {
    class Light 
    {
    private:
        Math::Vector3 m_Position;

    public:
        Light(const Math::Vector3& pos);
    };
}}
