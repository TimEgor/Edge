#include "DefaultRenderer.h"

#include "TinySimCommon/Core/UtilsMacros.h"
#include "TinySimCommon/Core/FileName/FileName.h"
#include "TinySimCommon/Math/ComputeMath/ComputeMatrix.h"

#include "TinySimPhysics/Visualizer/IDebugVisualizationDataController.h"

#include "TinySimFramework/FrameworkCore.h"
#include "TinySimFramework/Application/Application.h"
#include "TinySimFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicPlatform.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/Shader.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"
#include "TinySimFramework/Recources/AssetsDirectoryController/AssetsDirectoryController.h"

#include "PrimitiveShapes/Cube.h"
#include "PrimitiveShapes/Sphere.h"


bool TS_DEF_RENDERER::DefaultRenderer::initPointRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_pointRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Point.vshader"));
	TS_CHECK_RETURN_FALSE(m_pointRenderData.m_vertexShader);

	m_pointRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Point.pshader"));
	TS_CHECK_RETURN_FALSE(m_pointRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PointRenderData::PointData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PointRenderData::PointData, m_color), 1, TS::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PointRenderData::PointData), TS::InputLayoutBindingType::InstanceBinding });

	m_pointRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_pointRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_pointRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PointRenderData::PointData);
	pointDataBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_pointRenderData.m_pointData.init(pointDataBufferDesc, 512));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initLineRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_lineRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Line.vshader"));
	TS_CHECK_RETURN_FALSE(m_lineRenderData.m_vertexShader);

	m_lineRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Line.pshader"));
	TS_CHECK_RETURN_FALSE(m_lineRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "POSITION", 0, 0, offsetof(LineRenderData::VertexData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "COLOR", 0, 0, offsetof(LineRenderData::VertexData, m_color), 1, TS::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineRenderData::VertexData), TS::InputLayoutBindingType::VertexBinding });

	m_lineRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_lineRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_lineRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc lineDataBufferDesc{};
	lineDataBufferDesc.m_stride = sizeof(LineRenderData::LineData);
	lineDataBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	lineDataBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_lineRenderData.m_lineData.init(lineDataBufferDesc, 512));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initPlaneRenderData(TS::GraphicDevice& device,
	const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_planeRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Plane.vshader"));
	TS_CHECK_RETURN_FALSE(m_planeRenderData.m_vertexShader);

	m_planeRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Plane.pshader"));
	TS_CHECK_RETURN_FALSE(m_planeRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PlaneRenderData::PlaneData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 0, 0, offsetof(PlaneRenderData::PlaneData, m_sizeX), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_NORMAL", 0, 0, offsetof(PlaneRenderData::PlaneData, m_normal), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 1, 0, offsetof(PlaneRenderData::PlaneData, m_sizeY), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_directionRight), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_color), 1, TS::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PlaneRenderData::PlaneData), TS::InputLayoutBindingType::InstanceBinding });

	m_planeRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_planeRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_planeRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PlaneRenderData::PlaneData);
	pointDataBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_planeRenderData.m_planeData.init(pointDataBufferDesc, 64));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initWireframePlaneRenderData(TS::GraphicDevice& device,
	const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframePlaneRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframePlane.vshader"));
	TS_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_vertexShader);

	m_wireframePlaneRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframePlane.pshader"));
	TS_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PlaneRenderData::PlaneData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 0, 0, offsetof(PlaneRenderData::PlaneData, m_sizeX), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_NORMAL", 0, 0, offsetof(PlaneRenderData::PlaneData, m_normal), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 1, 0, offsetof(PlaneRenderData::PlaneData, m_sizeY), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_directionRight), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_color), 1, TS::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PlaneRenderData::PlaneData), TS::InputLayoutBindingType::InstanceBinding });

	m_wireframePlaneRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframePlaneRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PlaneRenderData::PlaneData);
	pointDataBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_planeData.init(pointDataBufferDesc, 64));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initBoxRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_boxRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Box.vshader"));
	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_vertexShader);

	m_boxRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Box.pshader"));
	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = CubeShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 0, 1, offsetof(TS::FloatMatrix4x4, m_row1), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 1, 1, offsetof(TS::FloatMatrix4x4, m_row2), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 2, 1, offsetof(TS::FloatMatrix4x4, m_row3), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 3, 1, offsetof(TS::FloatMatrix4x4, m_row4), 4, TS::InputLayoutElementType::Float32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(CubeShape::Vertex), TS::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(TS::FloatMatrix4x4), TS::InputLayoutBindingType::InstanceBinding });

	m_boxRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_boxRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_inputLayout);

	CubeShape boxShape(std::move(CubeShape::create(TS::FloatVector3One)));

	const CubeShape::VertexCollection& cubeVertices = boxShape.getVertices();

	TS::GPUBufferDesc boxVertexBufferDesc{};
	boxVertexBufferDesc.m_size = sizeof(CubeShape::Vertex) * cubeVertices.size();
	boxVertexBufferDesc.m_stride = sizeof(CubeShape::Vertex);
	boxVertexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxVertexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(CubeShape::Vertex) * cubeVertices.size());

	m_boxRenderData.m_vertexBuffer = device.createBuffer(boxVertexBufferDesc, &boxVerticesData);
	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_vertexBuffer);

	const CubeShape::IndexCollection& cubeIndices = *boxShape.getIndices();

	TS::GPUBufferDesc boxIndexBufferDesc{};
	boxIndexBufferDesc.m_size = sizeof(CubeShape::VertexIndex) * cubeIndices.size();
	boxIndexBufferDesc.m_stride = sizeof(CubeShape::VertexIndex);
	boxIndexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_INDEX_BUFFER;
	boxIndexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(CubeShape::VertexIndex) * cubeIndices.size());

	m_boxRenderData.m_indexBuffer = device.createBuffer(boxIndexBufferDesc, &boxIndicesData);
	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc boxTransformBufferDesc{};
	boxTransformBufferDesc.m_stride = sizeof(TS::FloatMatrix4x4);
	boxTransformBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxTransformBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_boxRenderData.m_transformData.init(boxTransformBufferDesc, 128));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initWireframeBoxRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframeBoxRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframeBox.vshader"));
	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_vertexShader);

	m_wireframeBoxRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframeBox.pshader"));
	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = LineCubeShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 0, 1, offsetof(TS::FloatMatrix4x4, m_row1), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 1, 1, offsetof(TS::FloatMatrix4x4, m_row2), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 2, 1, offsetof(TS::FloatMatrix4x4, m_row3), 4, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 3, 1, offsetof(TS::FloatMatrix4x4, m_row4), 4, TS::InputLayoutElementType::Float32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineCubeShape::Vertex), TS::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(TS::FloatMatrix4x4), TS::InputLayoutBindingType::InstanceBinding });

	m_wireframeBoxRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframeBoxRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_inputLayout);

	LineCubeShape boxShape(std::move(LineCubeShape::create(TS::FloatVector3One)));

	const LineCubeShape::VertexCollection& cubeVertices = boxShape.getVertices();

	TS::GPUBufferDesc boxVertexBufferDesc{};
	boxVertexBufferDesc.m_size = sizeof(LineCubeShape::Vertex) * cubeVertices.size();
	boxVertexBufferDesc.m_stride = sizeof(LineCubeShape::Vertex);
	boxVertexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxVertexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(LineCubeShape::Vertex) * cubeVertices.size());

	m_wireframeBoxRenderData.m_vertexBuffer = device.createBuffer(boxVertexBufferDesc, &boxVerticesData);
	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_vertexBuffer);

	const LineCubeShape::IndexCollection& cubeIndices = *boxShape.getIndices();

	TS::GPUBufferDesc boxIndexBufferDesc{};
	boxIndexBufferDesc.m_size = sizeof(LineCubeShape::VertexIndex) * cubeIndices.size();
	boxIndexBufferDesc.m_stride = sizeof(LineCubeShape::VertexIndex);
	boxIndexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_INDEX_BUFFER;
	boxIndexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(LineCubeShape::VertexIndex) * cubeIndices.size());

	m_wireframeBoxRenderData.m_indexBuffer = device.createBuffer(boxIndexBufferDesc, &boxIndicesData);
	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc boxTransformBufferDesc{};
	boxTransformBufferDesc.m_stride = sizeof(TS::FloatMatrix4x4);
	boxTransformBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxTransformBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_transformData.init(boxTransformBufferDesc, 128));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initSphereRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_sphereRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Sphere.vshader"));
	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_vertexShader);

	m_sphereRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/Sphere.pshader"));
	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = SphereShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 1, offsetof(SphereRenderData::SphereData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 1, offsetof(SphereRenderData::SphereData, m_directionForward), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 1, 1, offsetof(SphereRenderData::SphereData, m_directionUp), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_RADIUS", 0, 1, offsetof(SphereRenderData::SphereData, m_radius), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR",0, 1, offsetof(SphereRenderData::SphereData, m_color), 1, TS::InputLayoutElementType::UInt32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(SphereShape::Vertex), TS::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(SphereRenderData::SphereData), TS::InputLayoutBindingType::InstanceBinding });

	m_sphereRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_sphereRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_inputLayout);

	SphereShape sphereShape(std::move(SphereShape::create(1.0f, 8, 12)));

	const SphereShape::VertexCollection& cubeVertices = sphereShape.getVertices();

	TS::GPUBufferDesc sphereVertexBufferDesc{};
	sphereVertexBufferDesc.m_size = sizeof(SphereShape::Vertex) * cubeVertices.size();
	sphereVertexBufferDesc.m_stride = sizeof(SphereShape::Vertex);
	sphereVertexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereVertexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData sphereVerticesData(cubeVertices.data(), sizeof(SphereShape::Vertex) * cubeVertices.size());

	m_sphereRenderData.m_vertexBuffer = device.createBuffer(sphereVertexBufferDesc, &sphereVerticesData);
	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_vertexBuffer);

	const SphereShape::IndexCollection& cubeIndices = *sphereShape.getIndices();

	m_sphereRenderData.m_indexCountPerSphere = cubeIndices.size();

	TS::GPUBufferDesc sphereIndexBufferDesc{};
	sphereIndexBufferDesc.m_size = sizeof(SphereShape::VertexIndex) * m_sphereRenderData.m_indexCountPerSphere;
	sphereIndexBufferDesc.m_stride = sizeof(SphereShape::VertexIndex);
	sphereIndexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_INDEX_BUFFER;
	sphereIndexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData sphereIndicesData(cubeIndices.data(), sizeof(SphereShape::VertexIndex) * m_sphereRenderData.m_indexCountPerSphere);

	m_sphereRenderData.m_indexBuffer = device.createBuffer(sphereIndexBufferDesc, &sphereIndicesData);
	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc sphereTransformBufferDesc{};
	sphereTransformBufferDesc.m_stride = sizeof(SphereRenderData::SphereData);
	sphereTransformBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereTransformBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_sphereRenderData.m_sphereData.init(sphereTransformBufferDesc, 128));

	return true;
}

bool TS_DEF_RENDERER::DefaultRenderer::initWireframeSphereRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframeSphereRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframeSphere.vshader"));
	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_vertexShader);

	m_wireframeSphereRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRendererPlugin", "Shaders/WireframeSphere.pshader"));
	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_pixelShader);

	TS::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = LineSphereShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 1, offsetof(SphereRenderData::SphereData, m_position), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR",0, 1, offsetof(SphereRenderData::SphereData, m_directionForward), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 1, 1, offsetof(SphereRenderData::SphereData, m_directionUp), 3, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_RADIUS", 0, 1, offsetof(SphereRenderData::SphereData, m_radius), 1, TS::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 1, offsetof(SphereRenderData::SphereData, m_color), 1, TS::InputLayoutElementType::UInt32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineSphereShape::Vertex), TS::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(SphereRenderData::SphereData), TS::InputLayoutBindingType::InstanceBinding });

	m_wireframeSphereRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframeSphereRenderData.m_vertexShader);
	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_inputLayout);

	LineSphereShape sphereShape(std::move(LineSphereShape::create(1.0f, 8, 12)));

	const LineSphereShape::VertexCollection& cubeVertices = sphereShape.getVertices();

	TS::GPUBufferDesc sphereVertexBufferDesc{};
	sphereVertexBufferDesc.m_size = sizeof(LineSphereShape::Vertex) * cubeVertices.size();
	sphereVertexBufferDesc.m_stride = sizeof(LineSphereShape::Vertex);
	sphereVertexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereVertexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(LineSphereShape::Vertex) * cubeVertices.size());

	m_wireframeSphereRenderData.m_vertexBuffer = device.createBuffer(sphereVertexBufferDesc, &boxVerticesData);
	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_vertexBuffer);

	const LineSphereShape::IndexCollection& cubeIndices = *sphereShape.getIndices();

	m_wireframeSphereRenderData.m_indexCountPerSphere = cubeIndices.size();

	TS::GPUBufferDesc sphereIndexBufferDesc{};
	sphereIndexBufferDesc.m_size = sizeof(LineSphereShape::VertexIndex) * m_wireframeSphereRenderData.m_indexCountPerSphere;
	sphereIndexBufferDesc.m_stride = sizeof(LineSphereShape::VertexIndex);
	sphereIndexBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_INDEX_BUFFER;
	sphereIndexBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const TS::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(LineSphereShape::VertexIndex) * m_wireframeSphereRenderData.m_indexCountPerSphere);

	m_wireframeSphereRenderData.m_indexBuffer = device.createBuffer(sphereIndexBufferDesc, &boxIndicesData);
	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc sphereTransformBufferDesc{};
	sphereTransformBufferDesc.m_stride = sizeof(SphereRenderData::SphereData);
	sphereTransformBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereTransformBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	TS_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_sphereData.init(sphereTransformBufferDesc, 128));

	return true;
}

void TS_DEF_RENDERER::DefaultRenderer::releasePointRenderData()
{
	TS_SAFE_DESTROY(m_pointRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_pointRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_pointRenderData.m_inputLayout);

	m_pointRenderData.m_pointData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseLineRenderData()
{
	TS_SAFE_DESTROY(m_lineRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_lineRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_lineRenderData.m_inputLayout);

	m_lineRenderData.m_lineData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releasePlaneRenderData()
{
	TS_SAFE_DESTROY(m_planeRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_planeRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_planeRenderData.m_inputLayout);

	m_planeRenderData.m_planeData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseWireframePlaneRenderData()
{
	TS_SAFE_DESTROY(m_wireframePlaneRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_wireframePlaneRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_wireframePlaneRenderData.m_inputLayout);

	m_wireframePlaneRenderData.m_planeData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseBoxRenderData()
{
	TS_SAFE_DESTROY(m_boxRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_boxRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_boxRenderData.m_inputLayout);
	TS_SAFE_DESTROY(m_boxRenderData.m_vertexBuffer);
	TS_SAFE_DESTROY(m_boxRenderData.m_indexBuffer);

	m_boxRenderData.m_transformData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseWireframeBoxRenderData()
{
	TS_SAFE_DESTROY(m_wireframeBoxRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_wireframeBoxRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_wireframeBoxRenderData.m_inputLayout);
	TS_SAFE_DESTROY(m_wireframeBoxRenderData.m_vertexBuffer);
	TS_SAFE_DESTROY(m_wireframeBoxRenderData.m_indexBuffer);

	m_wireframeBoxRenderData.m_transformData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseSphereRenderData()
{
	TS_SAFE_DESTROY(m_sphereRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_sphereRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_sphereRenderData.m_inputLayout);
	TS_SAFE_DESTROY(m_sphereRenderData.m_vertexBuffer);
	TS_SAFE_DESTROY(m_sphereRenderData.m_indexBuffer);

	m_sphereRenderData.m_sphereData.release();
}

void TS_DEF_RENDERER::DefaultRenderer::releaseWireframeSphereRenderData()
{
	TS_SAFE_DESTROY(m_wireframeSphereRenderData.m_vertexShader);
	TS_SAFE_DESTROY(m_wireframeSphereRenderData.m_pixelShader);
	TS_SAFE_DESTROY(m_wireframeSphereRenderData.m_inputLayout);
	TS_SAFE_DESTROY(m_wireframeSphereRenderData.m_vertexBuffer);
	TS_SAFE_DESTROY(m_wireframeSphereRenderData.m_indexBuffer);

	m_wireframeSphereRenderData.m_sphereData.release();
}

bool TS_DEF_RENDERER::DefaultRenderer::init()
{
	const TS::Application& application = TS::FrameworkCore::getInstance().getApplication();

	TS::GraphicDevice& device = application.getGraphicPlatform().getGraphicDevice();

	m_graphicContext = device.createDeferredGraphicContext();
	TS_CHECK_INITIALIZATION(m_graphicContext);


	m_baseRasterizationState = device.createRasterizationState(TS::RasterizationStateDesc{});
	TS_CHECK_INITIALIZATION(m_baseRasterizationState);

	TS::GPUBufferDesc cameraBufferDesc{};
	cameraBufferDesc.m_size = sizeof(CameraShaderData);
	cameraBufferDesc.m_usage = TS::GPU_BUFFER_USAGE_CONSTANT_BUFFER;
	cameraBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	m_cameraTransformBuffer = device.createBuffer(cameraBufferDesc, nullptr);
	TS_CHECK_INITIALIZATION(m_cameraTransformBuffer);

	const TS::AssetsDirectoryController& assetsDirectoryController = application.getAssetsDirectoryController();

	TS_CHECK_INITIALIZATION(initPointRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initLineRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initPlaneRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initWireframePlaneRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initBoxRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initWireframeBoxRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initSphereRenderData(device, assetsDirectoryController));
	TS_CHECK_INITIALIZATION(initWireframeSphereRenderData(device, assetsDirectoryController));

	return true;
}

void TS_DEF_RENDERER::DefaultRenderer::release()
{
	releasePointRenderData();
	releaseLineRenderData();
	releasePlaneRenderData();
	releaseWireframePlaneRenderData();
	releaseBoxRenderData();
	releaseWireframeBoxRenderData();
	releaseSphereRenderData();
	releaseWireframeSphereRenderData();

	TS_SAFE_DESTROY(m_graphicContext);
	TS_SAFE_DESTROY(m_baseRasterizationState);
	TS_SAFE_DESTROY(m_depthBuffer);
	TS_SAFE_DESTROY(m_cameraTransformBuffer);

}

void TS_DEF_RENDERER::DefaultRenderer::preparePointRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t pointCount = visualizationData.getPointCount();
	m_pointRenderData.m_pointCount = pointCount;

	m_pointRenderData.m_pointData.updateBuffers(deltaTime, pointCount);

	if (pointCount > 0)
	{
		RenderDataBufferCacheIterator pointDataIter(m_pointRenderData.m_pointData, *m_graphicContext);

		for (uint32_t pointIndex = 0; pointIndex < pointCount; ++pointIndex)
		{
			const TS::IDebugVisualizationDataController::PointData& pointDebugData = visualizationData.getPoint(pointIndex);
			PointRenderData::PointData& pointData = *pointDataIter.getCurrentTypedElement<PointRenderData::PointData>();
			pointData.m_position = pointDebugData.m_position;
			pointData.m_color = PackedColor(TS::FloatVector4(pointDebugData.m_color.m_x, pointDebugData.m_color.m_y, pointDebugData.m_color.m_z, 1.0f));

			pointDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareLineRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t lineCount = visualizationData.getLineCount();
	const uint32_t arrowCount = visualizationData.getArrowCount();
	const uint32_t totalLineCount = lineCount + arrowCount * 3;

	m_lineRenderData.m_lineCount = totalLineCount;

	m_lineRenderData.m_lineData.updateBuffers(deltaTime, totalLineCount);

	if (totalLineCount > 0)
	{
		RenderDataBufferCacheIterator lineDataIter(m_lineRenderData.m_lineData, *m_graphicContext);

		for (uint32_t lineIndex = 0; lineIndex < lineCount; ++lineIndex)
		{
			const TS::IDebugVisualizationDataController::LineData& lineDebugData = visualizationData.getLine(lineIndex);
			LineRenderData::LineData& lineData = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

			PackedColor color(TS::FloatVector4(lineDebugData.m_color.m_x, lineDebugData.m_color.m_y, lineDebugData.m_color.m_z, 1.0f));

			lineData.m_point1.m_position = lineDebugData.m_position1;
			lineData.m_point1.m_color = color;

			lineData.m_point2.m_position = lineDebugData.m_position2;
			lineData.m_point2.m_color = color;

			lineDataIter.next();
		}

		for (uint32_t arrowIndex = 0; arrowIndex < arrowCount; ++arrowIndex)
		{
			const TS::IDebugVisualizationDataController::ArrowData& arrowDebugData = visualizationData.getArrow(arrowIndex);

			PackedColor color(TS::FloatVector4(arrowDebugData.m_color.m_x, arrowDebugData.m_color.m_y, arrowDebugData.m_color.m_z, 1.0f));

			const TS::ComputeVector endPoint = TS::ComputeVector(arrowDebugData.m_position) + TS::ComputeVector(arrowDebugData.m_direction);
			const TS::ComputeVector normalizeDir = TS::ComputeVector(arrowDebugData.m_direction).normalize() * arrowDebugData.m_size;
			const TS::ComputeVector headPerpendicular = TS::ComputeVector(calculateArrowHeadPerpendicular(arrowDebugData.m_direction)) * arrowDebugData.m_size;

			LineRenderData::LineData& lineData = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

			lineData.m_point1.m_position = arrowDebugData.m_position;
			lineData.m_point1.m_color = color;

			lineData.m_point2.m_position = endPoint.getFloatVector3();
			lineData.m_point2.m_color = color;

			lineDataIter.next();

			if (arrowDebugData.m_size > 0.0f)
			{
				LineRenderData::LineData& headLineData1 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

				headLineData1.m_point1.m_position = (endPoint - normalizeDir + headPerpendicular).getFloatVector3();
				headLineData1.m_point1.m_color = color;

				headLineData1.m_point2.m_position = lineData.m_point2.m_position;
				headLineData1.m_point2.m_color = color;

				lineDataIter.next();

				LineRenderData::LineData& headLineData2 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

				headLineData2.m_point1.m_position = (endPoint - normalizeDir - headPerpendicular).getFloatVector3();
				headLineData2.m_point1.m_color = color;

				headLineData2.m_point2.m_position = lineData.m_point2.m_position;
				headLineData2.m_point2.m_color = color;

				lineDataIter.next();
			}
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::preparePlaneRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t planeCount = visualizationData.getPlaneCount();
	m_planeRenderData.m_planeCount = planeCount;

	m_planeRenderData.m_planeData.updateBuffers(deltaTime, planeCount);

	if (planeCount > 0)
	{
		RenderDataBufferCacheIterator planeDataIter(m_planeRenderData.m_planeData, *m_graphicContext);

		for (uint32_t planeIndex = 0; planeIndex < planeCount; ++planeIndex)
		{
			const TS::IDebugVisualizationDataController::PlaneData& planeDebugData = visualizationData.getPlane(planeIndex);
			PlaneRenderData::PlaneData& planeData = *planeDataIter.getCurrentTypedElement<PlaneRenderData::PlaneData>();
			planeData.m_position = planeDebugData.m_position;
			planeData.m_sizeX = planeDebugData.m_size.m_x;
			planeData.m_normal = planeDebugData.m_normal;
			planeData.m_sizeY = planeDebugData.m_size.m_y;
			planeData.m_directionRight = planeDebugData.m_directionRight;
			planeData.m_color = PackedColor(TS::FloatVector4(planeDebugData.m_color.m_x, planeDebugData.m_color.m_y, planeDebugData.m_color.m_z, 1.0f));

			planeDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareWireframePlaneRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t planeCount = visualizationData.getWireframePlaneCount();
	m_wireframePlaneRenderData.m_planeCount = planeCount;

	m_wireframePlaneRenderData.m_planeData.updateBuffers(deltaTime, planeCount);

	if (planeCount > 0)
	{
		RenderDataBufferCacheIterator planeDataIter(m_wireframePlaneRenderData.m_planeData, *m_graphicContext);

		for (uint32_t planeIndex = 0; planeIndex < planeCount; ++planeIndex)
		{
			const TS::IDebugVisualizationDataController::PlaneData& planeDebugData = visualizationData.getWireframePlane(planeIndex);
			PlaneRenderData::PlaneData& planeData = *planeDataIter.getCurrentTypedElement<PlaneRenderData::PlaneData>();
			planeData.m_position = planeDebugData.m_position;
			planeData.m_sizeX = planeDebugData.m_size.m_x;
			planeData.m_normal = planeDebugData.m_normal;
			planeData.m_sizeY = planeDebugData.m_size.m_y;
			planeData.m_directionRight = planeDebugData.m_directionRight;
			planeData.m_color = PackedColor(TS::FloatVector4(planeDebugData.m_color.m_x, planeDebugData.m_color.m_y, planeDebugData.m_color.m_z, 1.0f));

			planeDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareBoxRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t boxCount = visualizationData.getBoxCount();
	m_boxRenderData.m_boxCount = boxCount;

	m_boxRenderData.m_transformData.updateBuffers(deltaTime, boxCount);

	if (boxCount > 0)
	{
		RenderDataBufferCacheIterator boxDataIter(m_boxRenderData.m_transformData, *m_graphicContext);

		for (uint32_t boxIndex = 0; boxIndex < boxCount; ++boxIndex)
		{
			const TS::IDebugVisualizationDataController::BoxData& boxDebugData = visualizationData.getBox(boxIndex);
			TS::FloatMatrix4x4& boxTransform = *boxDataIter.getCurrentTypedElement<TS::FloatMatrix4x4>();
			boxTransform = boxDebugData.m_transform.m_matrix;

			assert(boxTransform.m_row4.m_w == 1.0f);

			PackedColor color(TS::FloatVector4(boxDebugData.m_color.m_x, boxDebugData.m_color.m_y, boxDebugData.m_color.m_z, 1.0f));
			boxTransform.m_row4.m_w = *reinterpret_cast<float*>(&color.m_data);

			//m_graphicContext->prepareMatrixForShader(boxTransform, boxTransform);

			boxDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareWireframeBoxRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t boxCount = visualizationData.getWireframeBoxCount();
	m_wireframeBoxRenderData.m_boxCount = boxCount;

	m_wireframeBoxRenderData.m_transformData.updateBuffers(deltaTime, boxCount);

	if (boxCount > 0)
	{
		RenderDataBufferCacheIterator boxDataIter(m_wireframeBoxRenderData.m_transformData, *m_graphicContext);

		for (uint32_t boxIndex = 0; boxIndex < boxCount; ++boxIndex)
		{
			const TS::IDebugVisualizationDataController::BoxData& boxDebugData = visualizationData.getWireframeBox(boxIndex);
			TS::FloatMatrix4x4& boxTransform = *boxDataIter.getCurrentTypedElement<TS::FloatMatrix4x4>();
			boxTransform = boxDebugData.m_transform.m_matrix;

			assert(boxTransform.m_row4.m_w == 1.0f);

			PackedColor color(TS::FloatVector4(boxDebugData.m_color.m_x, boxDebugData.m_color.m_y, boxDebugData.m_color.m_z, 1.0f));
			boxTransform.m_row4.m_w = *reinterpret_cast<float*>(&color.m_data);

			//m_graphicContext->prepareMatrixForShader(boxTransform, boxTransform);

			boxDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareSphereRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t sphereCount = visualizationData.getSphereCount();
	m_sphereRenderData.m_sphereCount = sphereCount;

	m_sphereRenderData.m_sphereData.updateBuffers(deltaTime, sphereCount);

	if (sphereCount > 0)
	{
		RenderDataBufferCacheIterator sphereDataIter(m_sphereRenderData.m_sphereData, *m_graphicContext);

		for (uint32_t sphereIndex = 0; sphereIndex < sphereCount; ++sphereIndex)
		{
			const TS::IDebugVisualizationDataController::SphereData& sphereDebugData = visualizationData.getSphere(sphereIndex);
			SphereRenderData::SphereData& sphereData = *sphereDataIter.getCurrentTypedElement<SphereRenderData::SphereData>();
			sphereData.m_position = sphereDebugData.m_position;
			sphereData.m_directionForward = sphereDebugData.m_directionForward;
			sphereData.m_directionUp = sphereDebugData.m_directionUp;
			sphereData.m_radius = sphereDebugData.m_radius;
			sphereData.m_color = PackedColor(TS::FloatVector4(sphereDebugData.m_color.m_x, sphereDebugData.m_color.m_y, sphereDebugData.m_color.m_z, 1.0f));

			sphereDataIter.next();
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareWireframeSphereRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData)
{
	const uint32_t sphereCount = visualizationData.getWireframeSphereCount();
	m_wireframeSphereRenderData.m_sphereCount = sphereCount;

	m_wireframeSphereRenderData.m_sphereData.updateBuffers(deltaTime, sphereCount);

	if (sphereCount > 0)
	{
		RenderDataBufferCacheIterator sphereDataIter(m_wireframeSphereRenderData.m_sphereData, *m_graphicContext);

		for (uint32_t sphereIndex = 0; sphereIndex < sphereCount; ++sphereIndex)
		{
			const TS::IDebugVisualizationDataController::SphereData& sphereDebugData = visualizationData.getWireframeSphere(sphereIndex);
			SphereRenderData::SphereData& sphereData = *sphereDataIter.getCurrentTypedElement<SphereRenderData::SphereData>();
			sphereData.m_position = sphereDebugData.m_position;
			sphereData.m_directionForward = sphereDebugData.m_directionForward;
			sphereData.m_directionUp = sphereDebugData.m_directionUp;
			sphereData.m_radius = sphereDebugData.m_radius;
			sphereData.m_color = PackedColor(TS::FloatVector4(sphereDebugData.m_color.m_x, sphereDebugData.m_color.m_y, sphereDebugData.m_color.m_z, 1.0f));

			sphereDataIter.next();
		}
	}
}

TS::FloatVector3 TS_DEF_RENDERER::DefaultRenderer::calculateArrowHeadPerpendicular(const TS::FloatVector3& arrowDirection)
{
	if (fabs(arrowDirection.m_x) > fabs(arrowDirection.m_y))
	{
		const float length = sqrtf(arrowDirection.m_x * arrowDirection.m_x + arrowDirection.m_z * arrowDirection.m_z);
		return (TS::ComputeVector(TS::FloatVector3(arrowDirection.m_z, 0.0f, -arrowDirection.m_x)) / length).getFloatVector3();
	}

	const float length = sqrtf(arrowDirection.m_y * arrowDirection.m_y + arrowDirection.m_z * arrowDirection.m_z);
	return (TS::ComputeVector(TS::FloatVector3(0.0f, arrowDirection.m_z, -arrowDirection.m_y)) / length).getFloatVector3();
}

void TS_DEF_RENDERER::DefaultRenderer::prepareData(const CameraTransforms& cameraTransforms, const TS::IDebugVisualizationDataController& visualizationData)
{
	const TS::Application& application = TS::FrameworkCore::getInstance().getApplication();
	const float deltaTime = application.getDeltaTime();

	m_cameraShaderData.m_transforms = cameraTransforms;

	preparePointRenderData(deltaTime, visualizationData);
	prepareLineRenderData(deltaTime, visualizationData);
	preparePlaneRenderData(deltaTime, visualizationData);
	prepareWireframePlaneRenderData(deltaTime, visualizationData);
	prepareBoxRenderData(deltaTime, visualizationData);
	prepareWireframeBoxRenderData(deltaTime, visualizationData);
	prepareSphereRenderData(deltaTime, visualizationData);
	prepareWireframeSphereRenderData(deltaTime, visualizationData);
}

void TS_DEF_RENDERER::DefaultRenderer::drawPoints()
{
	if (m_pointRenderData.m_pointCount > 0)
	{
		m_graphicContext->setVertexShader(*m_pointRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_pointRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::TriangleStrip);
		m_graphicContext->setInputLayout(*m_pointRenderData.m_inputLayout);

		uint32_t remainedPointCount = m_pointRenderData.m_pointCount;
		const uint32_t pointPerBuffer = m_pointRenderData.m_pointData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_pointRenderData.m_pointData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPointCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPointCount, pointPerBuffer);
			remainedPointCount -= pointPerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_pointRenderData.m_pointData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_pointRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(4, drawingPointCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawLines()
{
	if (m_lineRenderData.m_lineCount > 0)
	{
		m_graphicContext->setVertexShader(*m_lineRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_lineRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_lineRenderData.m_inputLayout);

		uint32_t remainedLineCount = m_lineRenderData.m_lineCount;
		const uint32_t linePerBuffer = m_lineRenderData.m_lineData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_lineRenderData.m_lineData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedLineCount > 0; ++bufferIndex)
		{
			const uint32_t drawingLineCount = std::min(remainedLineCount, linePerBuffer);
			remainedLineCount -= linePerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_lineRenderData.m_lineData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_lineRenderData.m_inputLayout->getDesc());
			m_graphicContext->draw(drawingLineCount * 2);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawPlanes()
{
	if (m_planeRenderData.m_planeCount > 0)
	{
		m_graphicContext->setVertexShader(*m_planeRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_planeRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::TriangleStrip);
		m_graphicContext->setInputLayout(*m_planeRenderData.m_inputLayout);

		uint32_t remainedPlaneCount = m_planeRenderData.m_planeCount;
		const uint32_t planePerBuffer = m_planeRenderData.m_planeData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_planeRenderData.m_planeData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPlaneCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPlaneCount, planePerBuffer);
			remainedPlaneCount -= planePerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_planeRenderData.m_planeData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_planeRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(4, drawingPointCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawWireframePlanes()
{
	if (m_wireframePlaneRenderData.m_planeCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframePlaneRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframePlaneRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::LineStrip);
		m_graphicContext->setInputLayout(*m_wireframePlaneRenderData.m_inputLayout);

		uint32_t remainedPlaneCount = m_wireframePlaneRenderData.m_planeCount;
		const uint32_t planePerBuffer = m_wireframePlaneRenderData.m_planeData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframePlaneRenderData.m_planeData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPlaneCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPlaneCount, planePerBuffer);
			remainedPlaneCount -= planePerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_wireframePlaneRenderData.m_planeData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_wireframePlaneRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(5, drawingPointCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawBoxes()
{
	if (m_boxRenderData.m_boxCount > 0)
	{
		m_graphicContext->setVertexShader(*m_boxRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_boxRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::TriangleList);
		m_graphicContext->setInputLayout(*m_boxRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_boxRenderData.m_indexBuffer);

		uint32_t remainedBoxCount = m_boxRenderData.m_boxCount;
		const uint32_t boxPerBuffer = m_boxRenderData.m_transformData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_boxRenderData.m_transformData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedBoxCount > 0; ++bufferIndex)
		{
			const uint32_t drawingBoxCount = std::min(remainedBoxCount, boxPerBuffer);
			remainedBoxCount -= boxPerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_boxRenderData.m_transformData.getBuffer(bufferIndex);

			TS::GPUBuffer* vertexBuffers[2] = { m_boxRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_boxRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(36, drawingBoxCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawWireframeBoxes()
{
	if (m_wireframeBoxRenderData.m_boxCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframeBoxRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframeBoxRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_wireframeBoxRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_wireframeBoxRenderData.m_indexBuffer);

		uint32_t remainedBoxCount = m_wireframeBoxRenderData.m_boxCount;
		const uint32_t boxPerBuffer = m_wireframeBoxRenderData.m_transformData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframeBoxRenderData.m_transformData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedBoxCount > 0; ++bufferIndex)
		{
			const uint32_t drawingBoxCount = std::min(remainedBoxCount, boxPerBuffer);
			remainedBoxCount -= boxPerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_wireframeBoxRenderData.m_transformData.getBuffer(bufferIndex);

			TS::GPUBuffer* vertexBuffers[2] = { m_wireframeBoxRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_wireframeBoxRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(24, drawingBoxCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawSpheres()
{
	if (m_sphereRenderData.m_sphereCount > 0)
	{
		m_graphicContext->setVertexShader(*m_sphereRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_sphereRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::TriangleList);
		m_graphicContext->setInputLayout(*m_sphereRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_sphereRenderData.m_indexBuffer);

		uint32_t remainedSphereCount = m_sphereRenderData.m_sphereCount;
		const uint32_t spherePerBuffer = m_sphereRenderData.m_sphereData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_sphereRenderData.m_sphereData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedSphereCount > 0; ++bufferIndex)
		{
			const uint32_t drawingSphereCount = std::min(remainedSphereCount, spherePerBuffer);
			remainedSphereCount -= spherePerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_sphereRenderData.m_sphereData.getBuffer(bufferIndex);

			TS::GPUBuffer* vertexBuffers[2] = { m_sphereRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_sphereRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(m_sphereRenderData.m_indexCountPerSphere, drawingSphereCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::drawWireframeSpheres()
{
	if (m_wireframeSphereRenderData.m_sphereCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframeSphereRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframeSphereRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(TS::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_wireframeSphereRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_wireframeSphereRenderData.m_indexBuffer);

		uint32_t remainedSphereCount = m_wireframeSphereRenderData.m_sphereCount;
		const uint32_t spherePerBuffer = m_wireframeSphereRenderData.m_sphereData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframeSphereRenderData.m_sphereData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedSphereCount > 0; ++bufferIndex)
		{
			const uint32_t drawingSphereCount = std::min(remainedSphereCount, spherePerBuffer);
			remainedSphereCount -= spherePerBuffer;

			TS::GPUBuffer* instanceDataBuffer = &m_wireframeSphereRenderData.m_sphereData.getBuffer(bufferIndex);

			TS::GPUBuffer* vertexBuffers[2] = { m_wireframeSphereRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_wireframeSphereRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(m_wireframeSphereRenderData.m_indexCountPerSphere, drawingSphereCount);
		}
	}
}

void TS_DEF_RENDERER::DefaultRenderer::prepareDepthBuffer(const TS::Texture2DSize& bufferSize)
{
	bool needRecreation = false;

	if (!m_depthBuffer)
	{
		needRecreation = true;
	}
	else
	{
		const TS::Texture2DSize& currentSize = m_depthBuffer->getDesc().m_size;
		if (currentSize.m_x != bufferSize.m_x || currentSize.m_y != bufferSize.m_y)
		{
			needRecreation = true;
		}
	}

	if (needRecreation)
	{
		TS_SAFE_DESTROY(m_depthBuffer);

		TS::Texture2DDesc depthBufferDesc{};
		depthBufferDesc.m_size = bufferSize;
		depthBufferDesc.m_format = TS::GraphicResourceFormat::D24_UNORM_S8_UINT;
		depthBufferDesc.m_usage = TS::TEXTURE_USAGE_DEPTH_STENCIL;
		depthBufferDesc.m_access = TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ | TS::GRAPHIC_RESOURCE_ACCESS_GPU_WRITE;

		TS::GraphicDevice& device = TS::FrameworkCore::getInstance().getApplication().getGraphicPlatform().getGraphicDevice();

		m_depthBuffer = device.createTexture2D(depthBufferDesc);
	}
}

void TS_DEF_RENDERER::DefaultRenderer::render(TS::Texture2D& targetTexture)
{
	const TS::Texture2DDesc& targetTextureDesc = targetTexture.getDesc();

	TS::Viewport viewport(targetTextureDesc.m_size.m_x, targetTextureDesc.m_size.m_y);

	prepareDepthBuffer(targetTextureDesc.m_size);

	//m_graphicContext->prepareMatrixForShader(m_cameraShaderData.m_transforms.m_viewTransform, m_cameraShaderData.m_transforms.m_viewTransform);
	//m_graphicContext->prepareMatrixForShader(m_cameraShaderData.m_transforms.m_projTransform, m_cameraShaderData.m_transforms.m_projTransform);
	m_cameraShaderData.m_screenSize = targetTextureDesc.m_size;

	CameraShaderData* mappedCameraShaderData;
	m_graphicContext->mapBuffer(*m_cameraTransformBuffer, TS::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE, TS::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD,
		reinterpret_cast<void**>(&mappedCameraShaderData));

	memcpy(mappedCameraShaderData, &m_cameraShaderData, sizeof(CameraShaderData));

	m_graphicContext->unmapBuffer(*m_cameraTransformBuffer);

	m_graphicContext->setConstantBuffer(*m_cameraTransformBuffer, 0, TS::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX);

	m_graphicContext->setRenderTarget(targetTexture, m_depthBuffer);

	m_graphicContext->setRasterizationState(*m_baseRasterizationState);
	m_graphicContext->setViewport(viewport);

	m_graphicContext->clearRenderTarget(targetTexture, TS::FloatVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_graphicContext->clearDepthStencil(*m_depthBuffer);

	//

	drawPoints();
	drawLines();
	drawPlanes();
	drawWireframePlanes();
	drawBoxes();
	drawWireframeBoxes();
	drawSpheres();
	drawWireframeSpheres();

	TS::GraphicDevice& device = TS::FrameworkCore::getInstance().getApplication().getGraphicPlatform().getGraphicDevice();
	device.executeGraphicContext(*m_graphicContext);
}
