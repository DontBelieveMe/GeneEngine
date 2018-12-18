// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#define G2_PP_STR(x) G2_PP_XSTR(x)
#define G2_PP_XSTR(x) #x

#define G2_PP_CONCAT(x, y) x##y
#define G2_PP_CONCAT_STR(x, y) x y