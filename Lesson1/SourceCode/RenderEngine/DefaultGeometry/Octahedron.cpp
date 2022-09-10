#include "Octahedron.h"
#include "../Shaders/ShadersHelper.h"

Octahedron::Octahedron()
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_octVertices, sizeof(s_octVertices))
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_octTriList, sizeof(s_octTriList))
	);

	m_ProgramHandle = ShadersHelper::LoadProgram("vs_cubes", "fs_cubes");
}
