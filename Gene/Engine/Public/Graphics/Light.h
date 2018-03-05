#include <Math/Vector3.h>
#include <Graphics/Color.h>

namespace Gene { namespace Graphics {
    class Light 
    {
    private:
        Vector3 m_Position;
		Color m_Color;

    public:
        Light(const Vector3& pos, const Color& color);
    };
}}
