// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace gene {
    class Random {
    public:
        static float FloatRange(float min, float max);
        static int IntRange(int min, int max);

        static void Seed(unsigned seed);
    };
}
