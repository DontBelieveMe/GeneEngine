// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Math/Vector2.h>
#include <Math/Vector3.h>

META_IMPL_FILE(Maths);

META_CLASS_REFLECT_IMPL(gene::Vector2)
    META_CLASS_MEMBER(float, X)
    META_CLASS_MEMBER(float, Y)
META_CLASS_END_REFLECT_IMPL()

META_CLASS_REFLECT_IMPL(gene::Vector3)
    META_CLASS_MEMBER(float, X)
    META_CLASS_MEMBER(float, Y)
    META_CLASS_MEMBER(float, Z)
META_CLASS_END_REFLECT_IMPL()

META_CLASS_REFLECT_IMPL(gene::Vector4)
    META_CLASS_MEMBER(float, X)
    META_CLASS_MEMBER(float, Y)
    META_CLASS_MEMBER(float, Z)
    META_CLASS_MEMBER(float, W)
META_CLASS_END_REFLECT_IMPL()