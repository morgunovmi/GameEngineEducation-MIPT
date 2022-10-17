#pragma once

#include "../RenderObject.h"
#include "../PosColorVertex.h"

class RENDERENGINE_API OctahedronRenderObject : public RenderObject
{
public:
	OctahedronRenderObject(RenderProxy* pRenderProxy);

	virtual void* GetVertices() const override { return (void*)s_octVertices; }
	virtual UINT32 GetVerticesSize() const override { return sizeof(s_octVertices); }
	virtual void* GetIndices() const override { return (void*)s_octTriList; }
	virtual UINT32 GetIndicesSize() const override { return sizeof(s_octTriList); }
	virtual std::string GetVsShaderName() const override { return "vs_cubes"; }
	virtual std::string GetPsShaderName() const override { return "fs_cubes"; }

private:
	inline static const PosColorVertex s_octVertices[] =
	{
		{  0.0f,  0.0f, - 0.7f, 0xff000000 },
		{ -0.5f, -0.5f,   0.0f, 0xff0000ff },
		{ -0.5f,  0.5f,   0.0f, 0xff00ff00 },
		{  0.5f,  0.5f,   0.0f, 0xff00ffff },
		{  0.5f, -0.5f,   0.0f, 0xffff0000 },
		{  0.0f,  0.0f,   0.7f, 0xffff00ff },
	};

	inline static const uint16_t s_octTriList[] =
	{
		0, 1, 4,
		0, 2, 1,
		0, 3, 2,
		0, 4, 3,
		1, 5, 4,
		2, 5, 1,
		3, 5, 2,
		4, 5, 3
	};
};
