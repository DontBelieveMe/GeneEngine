// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Math/Vector3.h>
#include <Graphics/Color.h>

namespace gene { namespace graphics {
    class Light 
    {
    private:
        Vector3 m_Position;
		Color m_Color;

    public:
        Light(const Vector3& pos, const Color& color);
    };
}}
