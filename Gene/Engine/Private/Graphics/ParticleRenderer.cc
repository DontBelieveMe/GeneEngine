#include <Graphics/ParticleRenderer.h>
#include <Core/Random.h>

using namespace gene::graphics;
using namespace gene;

#define MAX_PARTICLES 500

static float s_VertexData[] = {
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.5f
};

platform::Timer timer;
void ParticleRenderer::Init(const Matrix4& projection)
{
	m_Shader = new GLSLShader;
	m_Shader->CompileFromFiles("Data/Shaders/ParticleVertex.shader", "Data/Shaders/ParticleFragment.shader");
	
	m_Shader->Enable();
	m_Shader->LoadUniformMatrix4f("u_Projection", projection);

	m_VertexArray = new VertexArray;
	m_VertexArray->Enable();

	m_VertexBuffer = new Buffer(Buffer::Type::ArrayBuffer);
	
	BufferDescriptor vertexBufferDesc;
	vertexBufferDesc.Data = s_VertexData;
	vertexBufferDesc.DataType = opengl::GLType::Float;
	vertexBufferDesc.DrawType = BufferDrawType::Static;
	vertexBufferDesc.Size = sizeof(s_VertexData);

	m_VertexBuffer->SetData(vertexBufferDesc);

	m_Shader->BindAttributeIndex(0, "in_Position");

	AttributeDescriptor positionDesc;
	positionDesc.ByteOfffset = 0.0f;
	positionDesc.ComponentCount = 3;
	positionDesc.Stride = 0.0f;
	positionDesc.Index = 0;

	m_VertexArray->RegisterAttribute(m_VertexBuffer, positionDesc);
	m_Shader->Disable();
	timer.Start();
}

void ParticleRenderer::Draw(const Array<Particle>& particles)
{
	m_Shader->Enable();
	m_VertexArray->Enable();
	
	for (const Particle& particle : particles) {
		if (particle.Alive) {
			Matrix4 modelMatrix = Matrix4::Translate(particle.Position);
			modelMatrix = modelMatrix * Matrix4::Scale(5.0f);
			m_Shader->LoadUniformMatrix4f("u_ModelView", modelMatrix);
			m_VertexArray->DrawArrays(0, 3 * 6);
		}
	}

	m_VertexArray->Disable();
	m_Shader->Disable();
}

void ParticleRenderer::Draw(const ParticleEmitter& emitter) 
{
	Draw(emitter.GetParticlesList());
}

void ParticleEmitter::EmitParticle()
{
	Particle x;
	x.Position = Position;
	x.Life = 100.f;
	x.Alive = true;

	const float VELOCITY_RANGE = 0.1f;

	float xVel = Random::FloatRange(-VELOCITY_RANGE, VELOCITY_RANGE);
	x.Velocity = Vector3(xVel, -VELOCITY_RANGE, 0.0f);

	m_Particles.push_back(x);
}

void ParticleEmitter::Tick(const platform::GameTime & time)
{
	LOG(LogLevel::Infomation, ToString(time.RunningTimeMilliseconds()));
	
	if (timer.ElapsedTimeMs() > 50) {
		EmitParticle();
		timer.Stop();
		timer.Start();
	}

	for (Particle& particle : m_Particles)
	{
		particle.Life -= 1.0f;
		if (particle.Life <= 0) {
			particle.Alive = false;
		}
		
		particle.Position = particle.Position + particle.Velocity * time.DeltaInMilliSeconds();
	}

	for (int i = 0; i < m_Particles.size(); i++) {
		if (!m_Particles[i].Alive) {
			m_Particles.erase(m_Particles.begin() + i);
		}
	}
}
