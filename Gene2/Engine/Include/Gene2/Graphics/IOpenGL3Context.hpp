// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	/**
	 * Defines the different profiles that can be used to configure ContextAttributes::Profile.
	 */
	enum EOpenGLProfile
	{
		AG_PROFILE_CORE,
		AG_PROFILE_COMPATIBILITY
	};

	/**
	 * Defines the various attributes that are used to configure the OpenGL context.
	 */
	struct ContextAttributes {

		/**
		 * The target OpenGL major version. Defaults to 3.
		 */
		int TargetMajorVersion = 3;

		/**
		 * The target OpenGL minor version. Defaults to 2
		 */
		int TargetMinorVersion = 2;

		/**
		 * The profile to use - can be either AG_PROFILE_CORE (core profile) or AG_PROFILE_COMPATIBILITY (compatibility profile).
		 * Defaults to use the core profile. 
		 * Core profile means that deprecated OpenGL functions will not be available (e.g modern OpenGL only),
		 * whereas a compatibility profile means that legacy OpenGL will still be available.
		 *
		 * It is recommended to use the core profile.
		 */
		int Profile = AG_PROFILE_CORE;
	};

	class IOpenGL3Context {
	public:
		IOpenGL3Context(void* windowHandle, ContextAttributes attributes)
			: m_windowHandle(windowHandle), m_attributes(attributes) {}

		virtual void Create() = 0;
		virtual void SwapBuffers() = 0;

		static IOpenGL3Context* CreateContextForThisPlatform(void* windowHandle, ContextAttributes attributes);

	protected:
		void*             m_windowHandle;
		ContextAttributes m_attributes;
	};
}
