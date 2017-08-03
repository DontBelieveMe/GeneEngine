#include <Math/Vector3.h>
#include <Graphics/Color.h>

namespace Gene { namespace Graphics {
    class Light 
    {
    private:
        Math::Vector3 m_Position;
		Color m_Color;

    public:
        Light(const Math::Vector3& pos, const Color& color);
    };
}}
