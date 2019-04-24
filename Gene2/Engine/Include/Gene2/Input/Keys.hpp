// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	enum EKeyModifier {
		KMOD_SHIFT = 1 << 0,
		KMOD_CTRL  = 1 << 1,
		KMOD_ALT   = 1 << 2,
	};

	enum EKeyCode {
		K_a = 0,
		K_b = 1,
		K_c = 2,
		K_d = 3,
		K_e = 4,
		K_f = 5,
		K_g = 6,
		K_h = 7,
		K_i = 8,
		K_j = 9,
		K_k = 10,
		K_l = 11,
		K_m = 12,
		K_n = 13,
		K_o = 14,
		K_p = 15,
		K_q = 16,
		K_r = 17,
		K_s = 18,
		K_t = 19,
		K_u = 20,
		K_v = 21,
		K_w = 22,
		K_x = 23,
		K_y = 24,
		K_z = 25,

		K_lalt = 26,
		K_ralt = 27,
		K_lshift = 28,
		K_rshift = 29,
		K_lctrl = 30,
		K_rctrl = 31,

		K_space = 32,
		K_arrowleft = 33,
		K_arrowright = 34,
		K_arrowup = 35,
		K_arrowdown = 36
	};
}