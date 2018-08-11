// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Core/Array.h>
#include <Graphics/Particle.h>
#include <Math/Matrix4.h>
#include <Graphics/GLSLShader.h>
#include <Graphics/Buffer.h>
#include <Graphics/VertexArray.h>
#include <Platform/Time.h>

namespace gene {
	namespace graphics {
		class ParticleEmitter;

		class ParticleRenderer {
		private:
			GLSLShader *m_Shader;
			Buffer     *m_VertexBuffer;
			VertexArray *m_VertexArray;
		public:
			void Init(const Matrix4& projection);

			void Draw(const Array<Particle>& particles);
			void Draw(const ParticleEmitter& emitter);
		};

		class ParticleEmitter {
		public:
			void Tick(const platform::GameTime& time);

			const Array<Particle>& GetParticlesList() const { return m_Particles; }

			void EmitParticle();

			Vector3 Position;

		private:
			Array<Particle> m_Particles;
		};
	}
}