#include "Main.h"
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxcompiler.lib")

#define RELEASE(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }

/*ウィンドウコールバック*/
#ifdef _WIN64
__int64 __stdcall WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam)
#else
long __stdcall WindowProc(void* hWnd, unsigned int message, unsigned int wParam, long lParam)
#endif
{
	switch (message) {
	case WM_CLOSE:
		DestroyWindow(HWND(hWnd));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(HWND(hWnd), message, wParam, lParam);
}

// メッセージの確認
bool CheckMsg(void)
{
	static MSG msg{};
	static const wchar_t* name = nullptr;
	static void* instance      = nullptr;

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		switch (msg.message) {
		case WM_CREATE:
		{
			auto wnd = (LPWNDCLASSEX)GetWindowLongPtr(msg.hwnd, GWLP_HINSTANCE);
			name = wnd->lpszClassName;
			instance = wnd->hInstance;
			break;
		}
		case WM_QUIT:
			UnregisterClass(name, HINSTANCE(instance));
			return false;
		default:
			break;
		}
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}

/*ウィンドウハンドルの生成*/
void* CreateWnd(const std::uint32_t& width, const std::uint32_t& height)
{
	WNDCLASSEX wnd{};
	wnd.cbSize        = sizeof(WNDCLASSEX);
	wnd.hbrBackground = CreateSolidBrush(COLOR_APPWORKSPACE);
	wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wnd.hIcon         = nullptr;
	wnd.hIconSm       = nullptr;
	wnd.hInstance     = GetModuleHandle(0);
	wnd.lpfnWndProc   = WNDPROC(WindowProc);
	wnd.lpszClassName = L"おかもん";
	wnd.lpszMenuName  = L"おかもん";
	wnd.style         = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wnd);

	RECT rect{};
	rect.bottom = height;
	rect.right  = width;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	auto window = CreateWindowEx(WS_EX_ACCEPTFILES, wnd.lpszClassName, wnd.lpszClassName, WS_OVERLAPPEDWINDOW, 0x80000000, 0x80000000,
		(rect.right - rect.left), (rect.bottom - rect.top), nullptr, nullptr, wnd.hInstance, nullptr);
	assert(window != nullptr);

	ShowWindow(HWND(window), SW_SHOW);

	return window;
}

/*デバイスの生成*/
ID3D12Device6* CreateDevice(void)
{
	/*機能レベル一覧*/
	const D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	};

	Microsoft::WRL::ComPtr<IDXGIFactory7>factory = nullptr;
	std::uint32_t flag = 0;
#ifdef _DEBUG
	flag = DXGI_CREATE_FACTORY_DEBUG;
#endif
	auto hr = CreateDXGIFactory2(flag, IID_PPV_ARGS(&factory));
	assert(hr == S_OK);

	ID3D12Device6* device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4>adaptor = nullptr;
	for (std::uint32_t i = 0; factory->EnumAdapters1(i, (IDXGIAdapter1**)adaptor.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; ++i) {
		DXGI_ADAPTER_DESC3 desc{};
		hr = adaptor->GetDesc3(&desc);
		assert(hr == S_OK);

		for (auto& level : levels) {
			if (SUCCEEDED(D3D12CreateDevice((IDXGIAdapter*)adaptor.Get(), level, IID_PPV_ARGS(&device)))) {
				break;
			}
		}

		D3D12_FEATURE_DATA_D3D12_OPTIONS5 option{};
		hr = device->CheckFeatureSupport(D3D12_FEATURE::D3D12_FEATURE_D3D12_OPTIONS5, &option, sizeof(option));
		assert(hr == S_OK);

		if (option.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
		{
			break;
		}
	}

	return device;
}

/*コマンドアロケータの生成*/
ID3D12CommandAllocator* CreateAllocator(ID3D12Device* device,
	const D3D12_COMMAND_LIST_TYPE& type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT)
{
	ID3D12CommandAllocator* allocator = nullptr;
	auto hr = device->CreateCommandAllocator(type, IID_PPV_ARGS(&allocator));
	assert(hr == S_OK);

	return allocator;
}

/*コマンドキューの生成*/
ID3D12CommandQueue* CreateQueue(ID3D12Device* device,
	const D3D12_COMMAND_LIST_TYPE& type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Flags    = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type     = type;

	ID3D12CommandQueue* queue = nullptr;
	auto hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	assert(hr == S_OK);

	return queue;
}

/*コマンドリストの生成*/
ID3D12GraphicsCommandList5* CreateList(ID3D12Device* device, ID3D12CommandAllocator* allocator,
	const D3D12_COMMAND_LIST_TYPE& type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT)
{
	ID3D12GraphicsCommandList5* list = nullptr;
	auto hr = device->CreateCommandList(0, type, allocator, nullptr, IID_PPV_ARGS(&list));
	assert(hr == S_OK);

	hr = list->Close();
	assert(hr == S_OK);

	return list;
}

/*コマンドリストの生成*/
ID3D12GraphicsCommandList5* CreateList(ID3D12Device5* device, 
	const D3D12_COMMAND_LIST_TYPE& type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT)
{
	ID3D12GraphicsCommandList5* list = nullptr;
	auto hr = device->CreateCommandList1(0, type, D3D12_COMMAND_LIST_FLAGS::D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&list));
	assert(hr == S_OK);

	return list;
}

/*コマンド同期オブジェクトの生成*/
CommandAsync CreateCommandAsync(ID3D12Device* device)
{
	CommandAsync async{};
	auto hr = device->CreateFence(0, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&async.fence));
	assert(hr == S_OK);

	return async;
}

/*スワップチェインの生成*/
IDXGISwapChain4* CreateSwapChain(void* window, ID3D12CommandQueue* queue, const std::uint32_t& back_buffer_num = 2)
{
	Microsoft::WRL::ComPtr<IDXGIFactory7>factory = nullptr;
	std::uint32_t flag = 0;
#ifdef _DEBUG
	flag = DXGI_CREATE_FACTORY_DEBUG;
#endif
	auto hr = CreateDXGIFactory2(flag, IID_PPV_ARGS(&factory));
	assert(hr == S_OK);

	RECT rect{};
	GetClientRect(HWND(window), &rect);

	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.AlphaMode   = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount = back_buffer_num;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags       = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.Format      = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Height      = rect.bottom;
	desc.SampleDesc  = { 1, 0 };
	desc.Scaling     = DXGI_SCALING::DXGI_SCALING_STRETCH;
	desc.Stereo      = false;
	desc.SwapEffect  = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Width       = rect.right;

	IDXGISwapChain4* swap = nullptr;
	hr = factory->CreateSwapChainForHwnd(queue, HWND(window),
		&desc, nullptr, nullptr, (IDXGISwapChain1**)&swap);
	assert(hr == S_OK);

	return swap;
}

/*ヒープの生成*/
ID3D12DescriptorHeap* CreateHeap(ID3D12Device* device, const D3D12_DESCRIPTOR_HEAP_TYPE& type,
	const std::uint32_t& view_num, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags = flag;
	desc.NodeMask = 0;
	desc.NumDescriptors = view_num;
	desc.Type = type;

	ID3D12DescriptorHeap* heap = nullptr;
	auto hr = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
	assert(hr == S_OK);

	return heap;
}

/*ヒーププロパティの取得*/
D3D12_HEAP_PROPERTIES GetHeapProp(const D3D12_HEAP_TYPE& type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 0;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = type;
	prop.VisibleNodeMask      = 0;

	return prop;
}

/*リソースの生成(バッファ―)*/
ID3D12Resource1* CreateRsc(ID3D12Device* device, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_FLAGS& flag,
	const std::uint64_t& size, const D3D12_RESOURCE_STATES& state)
{
	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = flag;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = size;

	ID3D12Resource1* rsc = nullptr;
	auto hr = device->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&desc, state, nullptr, IID_PPV_ARGS(&rsc));
	assert(hr == S_OK);

	return rsc;
}

/*リソースの生成(テクスチャ)*/
ID3D12Resource1* CreateRsc(ID3D12Device* device, IDXGISwapChain1* swap, 
	const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_FLAGS& flag, const D3D12_RESOURCE_STATES& state)
{
	DXGI_SWAP_CHAIN_DESC1 swap_desc{};
	auto hr = swap->GetDesc1(&swap_desc);
	assert(hr == S_OK);

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Flags            = flag;
	desc.Format           = swap_desc.Format;
	desc.Height           = swap_desc.Height;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = swap_desc.Width;

	ID3D12Resource1* rsc = nullptr;
	hr = device->CreateCommittedResource(&prop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&desc, state, nullptr, IID_PPV_ARGS(&rsc));
	assert(hr == S_OK);

	return rsc;
}

/*RTVの生成*/
void RTV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const std::uint32_t& index = 0)
{
	Microsoft::WRL::ComPtr<ID3D12Device5>device = nullptr;
	auto hr = heap->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	D3D12_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format        = rsc->GetDesc().Format;
	desc.Texture2D     = { 0, 0 };
	desc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += device->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	device->CreateRenderTargetView(rsc, &desc, handle);
}

/*SRVの生成(加速構造)*/
void SRV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, Acceleration& top, const std::uint32_t& index = 0)
{
	Microsoft::WRL::ComPtr<ID3D12Device5>device = nullptr;
	auto hr = heap->GetDevice(IID_PPV_ARGS(&device));

	D3D12_SHADER_RESOURCE_VIEW_DESC desc{};
	desc.RaytracingAccelerationStructure.Location = top.result->GetGPUVirtualAddress();
	desc.Shader4ComponentMapping                  = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	desc.ViewDimension                            = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += device->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	device->CreateShaderResourceView(rsc, &desc, handle);
}

/*UAVの生成(テクスチャ)*/
void UAV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const std::uint32_t& index = 0)
{
	Microsoft::WRL::ComPtr<ID3D12Device5>device = nullptr;
	auto hr = heap->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	D3D12_UNORDERED_ACCESS_VIEW_DESC desc{};
	desc.Format        = rsc->GetDesc().Format;
	desc.ViewDimension = D3D12_UAV_DIMENSION::D3D12_UAV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += device->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	device->CreateUnorderedAccessView(rsc, nullptr, &desc, handle);
}

/*レンダーターゲットオブジェクトの生成*/
RenderTarget CreateRenderTarget(IDXGISwapChain* swap)
{
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	auto hr = swap->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	DXGI_SWAP_CHAIN_DESC desc{};
	hr = swap->GetDesc(&desc);
	assert(hr == S_OK);

	RenderTarget render{};
	render.heap = CreateHeap(device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
		desc.BufferCount, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	render.rsc.resize(desc.BufferCount);
	for (std::uint32_t i = 0; i < render.rsc.size(); ++i)
	{
		hr = swap->GetBuffer(i, IID_PPV_ARGS(&render.rsc[i]));
		assert(hr == S_OK);

		RTV(render.heap, render.rsc[i], i);
	}

	return render;
}

/*データのマッピング*/
void Map(ID3D12Resource* rsc, const void* data, const std::uint64_t& size)
{
	std::uint8_t* buffer = nullptr;
	D3D12_RANGE range{};
	auto hr = rsc->Map(0, &range, (void**)&buffer);
	assert(hr == S_OK);

	std::memcpy(buffer, data, size);

	rsc->Unmap(0, &range);
}

/*ルートシグネチャの生成*/
ID3D12RootSignature* CreateRootSignature(ID3D12Device* device, ID3DBlob* blob)
{
	ID3D12RootSignature* root = nullptr;
	auto hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&root));
	assert(hr == S_OK);

	return root;
}

/*ルートシグネチャの生成*/
ID3D12RootSignature* CreateRootSignature(ID3D12Device* device, const D3D12_DESCRIPTOR_RANGE* range, const std::uint64_t& num,
	const D3D12_ROOT_SIGNATURE_FLAGS& flag = D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_NONE)
{
	D3D12_ROOT_PARAMETER param{};
	param.DescriptorTable.NumDescriptorRanges = std::uint32_t(num);
	param.DescriptorTable.pDescriptorRanges   = range;
	param.ParameterType                       = D3D12_ROOT_PARAMETER_TYPE::D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	param.ShaderVisibility                    = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;

	D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc{};
	desc.Desc_1_0.Flags             = flag;
	desc.Desc_1_0.NumParameters     = (num != 0) ? 1 : 0;
	desc.Desc_1_0.NumStaticSamplers = 0;
	desc.Desc_1_0.pParameters       = &param;
	desc.Desc_1_0.pStaticSamplers   = nullptr;
	desc.Version                    = D3D_ROOT_SIGNATURE_VERSION::D3D_ROOT_SIGNATURE_VERSION_1_0;

	Microsoft::WRL::ComPtr<ID3DBlob>sig   = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob>error = nullptr;
	auto hr = D3D12SerializeVersionedRootSignature(&desc, &sig, &error);
	assert(hr == S_OK);

	ID3D12RootSignature* root = nullptr;
	hr = device->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	assert(hr == S_OK);

	return root;
}

/*ステートオブジェクトの生成*/
ID3D12StateObject* CreateStateObject(ID3D12Device5* device, D3D12_STATE_SUBOBJECT* sub, const std::uint64_t& num)
{
	D3D12_STATE_OBJECT_DESC desc{};
	desc.NumSubobjects = std::uint32_t(num);
	desc.pSubobjects   = sub;
	desc.Type          = D3D12_STATE_OBJECT_TYPE::D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE;

	ID3D12StateObject* state = nullptr;
	auto hr = device->CreateStateObject(&desc, IID_PPV_ARGS(&state));
	assert(hr == S_OK);

	return state;
}

/*シェーダテーブルの生成*/
std::vector<ID3D12Resource1*>CreateShaderTable(ID3D12StateObject* state, const wchar_t** name, ID3D12DescriptorHeap** heap, const std::uint64_t& num)
{
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	auto hr = state->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	Microsoft::WRL::ComPtr<ID3D12StateObjectProperties>prop = nullptr;
	hr = state->QueryInterface(IID_PPV_ARGS(&prop));
	assert(hr == S_OK);

	std::uint32_t size = D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES + 8;
	size = ((size + (D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT - 1)) / D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT) * D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT;

	std::vector<ID3D12Resource1*>rsc(num);
	for (std::uint32_t i = 0; i < num; ++i) {
		rsc[i] = CreateRsc(device.Get(), GetHeapProp(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE,
			size, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

		std::uint8_t* buffer = nullptr;
		hr = rsc[i]->Map(0, nullptr, (void**)&buffer);
		assert(hr == S_OK);

		std::memcpy(buffer, prop->GetShaderIdentifier(name[i]), D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
		if (heap[i] != nullptr) {
			*(std::uint64_t*)(buffer + D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES) = heap[i]->GetGPUDescriptorHandleForHeapStart().ptr;
		}

		rsc[i]->Unmap(0, nullptr);
	}

	return rsc;
}

/*リソースバリアのセット*/
void Barrier(ID3D12GraphicsCommandList* list, ID3D12Resource* rsc,
	const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& after)
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource   = rsc;
	barrier.Transition.StateAfter  = after;
	barrier.Transition.StateBefore = befor;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;

	list->ResourceBarrier(1, &barrier);
}

/*リソースバリアのセット(UAV)*/
void Barrier(ID3D12GraphicsCommandList* list, ID3D12Resource* rsc)
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Flags         = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Type          = D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_UAV;
	barrier.UAV.pResource = rsc;

	list->ResourceBarrier(1, &barrier);
}

/*レンダーターゲットのクリア*/
void ClearRenderTarget(ID3D12GraphicsCommandList* list, ID3D12DescriptorHeap* heap, const std::uint32_t& index)
{
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	auto hr = list->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += device->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	list->OMSetRenderTargets(1, &handle, 0, nullptr);

	const float color[] = {
		1.0f, 0.0f, 0.0f, 1.0f
	};
	list->ClearRenderTargetView(handle, color, 0, nullptr);
}

/*加速構造の生成(ボトムレベル)*/
Acceleration CreateAcceleration(ID3D12GraphicsCommandList4* list, ID3D12Resource* vertex, const std::uint64_t& stride)
{
	Microsoft::WRL::ComPtr<ID3D12Device5>device = nullptr;
	auto hr = list->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	D3D12_RAYTRACING_GEOMETRY_DESC geo{};
	geo.Flags = D3D12_RAYTRACING_GEOMETRY_FLAGS::D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
	geo.Triangles.VertexBuffer.StartAddress  = vertex->GetGPUVirtualAddress();
	geo.Triangles.VertexBuffer.StrideInBytes = stride;
	geo.Triangles.VertexCount                = std::uint32_t(vertex->GetDesc().Width / geo.Triangles.VertexBuffer.StrideInBytes);
	geo.Triangles.VertexFormat               = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
	geo.Type                                 = D3D12_RAYTRACING_GEOMETRY_TYPE::D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{};
	input.DescsLayout    = D3D12_ELEMENTS_LAYOUT::D3D12_ELEMENTS_LAYOUT_ARRAY;
	input.Flags          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
	input.NumDescs       = 1;
	input.pGeometryDescs = &geo;
	input.Type           = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO info{};
	device->GetRaytracingAccelerationStructurePrebuildInfo(&input, &info);

	Acceleration bottom{};
	bottom.scratch = CreateRsc(device.Get(), GetHeapProp(), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		info.ScratchDataSizeInBytes, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
	
	bottom.result = CreateRsc(device.Get(), GetHeapProp(), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		info.ResultDataMaxSizeInBytes, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC desc{};
	desc.DestAccelerationStructureData    = bottom.result->GetGPUVirtualAddress();
	desc.Inputs                           = input;
	desc.ScratchAccelerationStructureData = bottom.scratch->GetGPUVirtualAddress();

	list->BuildRaytracingAccelerationStructure(&desc, 0, nullptr);
	Barrier(list, bottom.result);

	return bottom;
}

/*加速構造の生成(トップレベル)*/
Acceleration CreateAcceleration(ID3D12GraphicsCommandList4* list, const Acceleration& bottom)
{
	Microsoft::WRL::ComPtr<ID3D12Device5>device = nullptr;
	auto hr = list->GetDevice(IID_PPV_ARGS(&device));
	assert(hr == S_OK);

	Acceleration top{};
	top.instance = CreateRsc(device.Get(), GetHeapProp(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE,
		sizeof(D3D12_RAYTRACING_INSTANCE_DESC), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	D3D12_RAYTRACING_INSTANCE_DESC* buffer = nullptr;
	hr = top.instance->Map(0, nullptr, (void**)&buffer);
	assert(hr == S_OK);
	buffer->AccelerationStructure               = bottom.result->GetGPUVirtualAddress();
	buffer->Flags                               = D3D12_RAYTRACING_INSTANCE_FLAGS::D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
	buffer->InstanceContributionToHitGroupIndex = 0;
	buffer->InstanceID                          = 0;
	buffer->InstanceMask                        = 0xFF;
	for (std::uint32_t y = 0; y < 3; ++y) {
		for (std::uint32_t x = 0; x < 4; ++x) {
			if (y == x) {
				buffer->Transform[y][x] = 1.0f;
			}
			else {
				buffer->Transform[y][x] = 0.0f;
			}
		}
	}
	top.instance->Unmap(0, nullptr);

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{};
	input.DescsLayout   = D3D12_ELEMENTS_LAYOUT::D3D12_ELEMENTS_LAYOUT_ARRAY;
	input.Flags         = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE;
	input.InstanceDescs = top.instance->GetGPUVirtualAddress();
	input.NumDescs      = 1;
	input.Type          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO info{};
	device->GetRaytracingAccelerationStructurePrebuildInfo(&input, &info);

	top.scratch = CreateRsc(device.Get(), GetHeapProp(), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		info.ScratchDataSizeInBytes, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
	top.result = CreateRsc(device.Get(), GetHeapProp(), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		info.ResultDataMaxSizeInBytes, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC desc{};
	desc.DestAccelerationStructureData    = top.result->GetGPUVirtualAddress();
	desc.Inputs                           = input;
	desc.ScratchAccelerationStructureData = top.scratch->GetGPUVirtualAddress();

	list->BuildRaytracingAccelerationStructure(&desc, 0, nullptr);
	Barrier(list, top.result);

	return top;
}

/*加速構造の更新*/
void UpDateAcceleration(ID3D12GraphicsCommandList4* list, Acceleration& top, const Acceleration& bottom)
{
	D3D12_RAYTRACING_INSTANCE_DESC* buffer = nullptr;
	auto hr = top.instance->Map(0, nullptr, (void**)&buffer);
	assert(hr == S_OK);
	buffer->AccelerationStructure               = bottom.result->GetGPUVirtualAddress();
	buffer->Flags                               = D3D12_RAYTRACING_INSTANCE_FLAGS::D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
	buffer->InstanceContributionToHitGroupIndex = 0;
	buffer->InstanceID                          = 0;
	buffer->InstanceMask                        = 0xFF;
	for (std::uint32_t y = 0; y < 3; ++y) {
		for (std::uint32_t x = 0; x < 4; ++x) {
			if (y == x) {
				buffer->Transform[y][x] = 1.0f;
			}
			else {
				buffer->Transform[y][x] = 0.0f;
			}
		}
	}
	top.instance->Unmap(0, nullptr);

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{};
	input.DescsLayout   = D3D12_ELEMENTS_LAYOUT::D3D12_ELEMENTS_LAYOUT_ARRAY;
	input.Flags         = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE
		                | D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE;
	input.InstanceDescs = top.instance->GetGPUVirtualAddress();
	input.NumDescs      = 1;
	input.Type          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC desc{};
	desc.DestAccelerationStructureData    = top.result->GetGPUVirtualAddress();
	desc.Inputs                           = input;
	desc.ScratchAccelerationStructureData = top.scratch->GetGPUVirtualAddress();
	desc.SourceAccelerationStructureData  = top.result->GetGPUVirtualAddress();

	list->BuildRaytracingAccelerationStructure(&desc, 0, nullptr);
	Barrier(list, top.result);
}

/*コマンドの実行*/
void Execution(ID3D12CommandQueue* queue, const std::initializer_list<ID3D12GraphicsCommandList*>& lists)
{
	std::vector<ID3D12CommandList*>list;
	for (auto& i : lists) {
		auto hr = i->Close();
		assert(hr == S_OK);

		list.push_back(i);
	}

	queue->ExecuteCommandLists(std::uint32_t(list.size()), list.data());
}

/*コマンド実行の待機*/
void Wait(ID3D12CommandQueue* queue, CommandAsync& async)
{
	auto hr = queue->Signal(async.fence, ++async.cnt);
	assert(hr == S_OK);

	if (async.cnt != async.fence->GetCompletedValue()) {
		void* handle = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
		assert(handle != nullptr);

		hr = async.fence->SetEventOnCompletion(async.cnt, handle);
		assert(hr == S_OK);

		WaitForSingleObject(handle, INFINITE);

		CloseHandle(handle);
	}
}

/*シェーダのコンパイル*/
ID3DBlob* ShaderCompile(const std::wstring& file_path, const std::wstring& entry_func, const std::wstring& shader_model)
{
	Microsoft::WRL::ComPtr<IDxcLibrary>library = nullptr;
	auto hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&library));
	assert(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcIncludeHandler>handle = nullptr;
	hr = library->CreateIncludeHandler(&handle);
	assert(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcBlobEncoding>encode = nullptr;
	hr = library->CreateBlobFromFile(file_path.c_str(), nullptr, &encode);
	assert(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcCompiler>compile = nullptr;
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compile));
	assert(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcOperationResult>result = nullptr;
	hr = compile->Compile(encode.Get(), file_path.c_str(), entry_func.c_str(), shader_model.c_str(), nullptr, 0, nullptr, 0, handle.Get(), &result);
	assert(hr == S_OK);

	ID3DBlob* blob = nullptr;
	result->GetStatus(&hr);
	if (SUCCEEDED(hr)) {
		hr = result->GetResult((IDxcBlob**)&blob);
		assert(hr == S_OK);
	}
	else {
#ifdef _DEBUG
		Microsoft::WRL::ComPtr<IDxcBlobEncoding>print = nullptr;
		Microsoft::WRL::ComPtr<IDxcBlobEncoding>print16 = nullptr;

		hr = result->GetErrorBuffer(&print);
		assert(hr == S_OK);

		hr = library->GetBlobAsUtf16(print.Get(), &print16);
		assert(hr == S_OK);

		wprintf(L"%*s", (int)print16->GetBufferSize() / 2, (LPCWSTR)print16->GetBufferPointer());
#endif
	}

	return blob;
}

int main()
{
	HRESULT hr = S_OK;
#ifdef _DEBUG
	ID3D12Debug3* debug = nullptr;
	hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	assert(hr == S_OK);
	debug->EnableDebugLayer();
	RELEASE(debug);
#endif

	/*チュートリアル1*/
	window = CreateWnd(640, 480);

	/*チュートリアル2*/
	device    = CreateDevice();
	allocator = CreateAllocator(device);
	queue     = CreateQueue(device);
	list      = CreateList(device);
	async     = CreateCommandAsync(device);
	swap      = CreateSwapChain(window, queue, 3);
	render    = CreateRenderTarget(swap);

	/*チュートリアル3*/
	const float vtx[] = {
		   0.0f,  1.0f, 0.0f,
		 0.866f, -0.5f, 0.0f,
		-0.866f, -0.5f, 0.0f
	};
	vertex = CreateRsc(device, GetHeapProp(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD),
		D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE, sizeof(vtx), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	Map(vertex, vtx, sizeof(vtx));

	hr = allocator->Reset();
	assert(hr == S_OK);
	hr = list->Reset(allocator, nullptr);
	assert(hr == S_OK);
	bottom = CreateAcceleration(list, vertex, sizeof(float) * 3);
	top    = CreateAcceleration(list, bottom);
	Execution(queue, { list });
	Wait(queue, async);

	/*チュートリアル4*/
	shader = ShaderCompile(L"Raytracing.hlsl", L"", L"lib_6_4");
	global = CreateRootSignature(device, nullptr, 0);

	const wchar_t* shader_func[] = {
		L"RayGen",
		L"Miss",
		L"Chs"
	};
	const wchar_t* shader_variable[] = {
		L"global",
		L"ray",
		L"rayAsso",
		L"miss",
		L"missAsso",
		L"closest",
		L"closestAsso",
		L"hit",
		L"hitAsso",
		L"sConfig",
		L"sConfigAsso1",
		L"sConfigAsso2",
		L"sConfigAsso3",
		L"pConfig"
	};
	std::vector<D3D12_STATE_SUBOBJECT>sub;
	sub.reserve(10);
	std::vector<D3D12_EXPORT_DESC>expo;
	for (std::uint32_t i = 0; i < _countof(shader_func); ++i) {
		expo.push_back({ shader_func[i], nullptr, D3D12_EXPORT_FLAGS::D3D12_EXPORT_FLAG_NONE });
	}
	/*for (std::uint32_t i = 0; i < _countof(shader_variable); ++i) {
		expo.push_back({ shader_variable[i], nullptr, D3D12_EXPORT_FLAGS::D3D12_EXPORT_FLAG_NONE });
	}*/
	D3D12_DXIL_LIBRARY_DESC lib{};
	lib.DXILLibrary.BytecodeLength  = shader->GetBufferSize();
	lib.DXILLibrary.pShaderBytecode = shader->GetBufferPointer();
	lib.NumExports                  = std::uint32_t(expo.size());
	lib.pExports                    = expo.data();
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY, &lib });
	const wchar_t* hit_name = L"hit";
	D3D12_HIT_GROUP_DESC hit{};
	hit.AnyHitShaderImport       = nullptr;
	hit.ClosestHitShaderImport   = shader_func[2];
	hit.HitGroupExport           = hit_name;
	hit.IntersectionShaderImport = nullptr;
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP, &hit });
	const D3D12_DESCRIPTOR_RANGE_TYPE ray_root_type[] = {
		D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
		D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
	};
	std::unordered_map<D3D12_DESCRIPTOR_RANGE_TYPE, std::uint32_t>ray_root_reg = {
		{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0 },
		{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0 },
		{ D3D12_DESCRIPTOR_RANGE_TYPE::D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 0 }
	};
	std::vector<D3D12_DESCRIPTOR_RANGE>ray_root_range(_countof(ray_root_type));
	for (std::uint32_t i = 0; i < ray_root_range.size(); ++i) {
		ray_root_range[i].BaseShaderRegister                = ray_root_reg[ray_root_type[i]]++;
		ray_root_range[i].NumDescriptors                    = 1;
		ray_root_range[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		ray_root_range[i].RangeType                         = ray_root_type[i];
		ray_root_range[i].RegisterSpace                     = 0;
	}
	local.reserve(_countof(shader_func));
	local.push_back(CreateRootSignature(device, ray_root_range.data(), ray_root_range.size(), D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE));
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE, &local.back() });
	D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION ray_asso{};
	ray_asso.NumExports            = 1;
	ray_asso.pExports              = shader_func;
	ray_asso.pSubobjectToAssociate = &sub.back();
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION, &ray_asso });
	local.push_back(CreateRootSignature(device, nullptr, 0, D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE));
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE, &local.back() });
	D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION miss_hit_asso{};
	miss_hit_asso.NumExports            = 2;
	miss_hit_asso.pExports              = &shader_func[1];
	miss_hit_asso.pSubobjectToAssociate = &sub.back();
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION, &miss_hit_asso });
	D3D12_RAYTRACING_SHADER_CONFIG shader_config{};
	shader_config.MaxAttributeSizeInBytes = sizeof(float) * 2;
	shader_config.MaxPayloadSizeInBytes   = sizeof(float) * 3;
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_SHADER_CONFIG, &shader_config });
	D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION shader_asso{};
	shader_asso.NumExports            = _countof(shader_func);
	shader_asso.pExports              = shader_func;
	shader_asso.pSubobjectToAssociate = &sub.back();
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION, &shader_asso });
	D3D12_RAYTRACING_PIPELINE_CONFIG pipe_config{};
	pipe_config.MaxTraceRecursionDepth = 1;
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG, &pipe_config });
	sub.push_back({ D3D12_STATE_SUBOBJECT_TYPE::D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE, &global });
	state = CreateStateObject(device, sub.data(), sub.size());

	/*チュートリアル6*/
	heap = CreateHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 2);
	rsc = CreateRsc(device, swap, GetHeapProp(), D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_SOURCE);
	UAV(heap, rsc, 0);
	SRV(heap, nullptr, top, 1);

	/*チュートリアル5*/
	const wchar_t* record_name[] = {
		L"RayGen",
		L"Miss",
		L"hit"
	};
	ID3D12DescriptorHeap* record_heap[] = {
		heap, 
		nullptr, 
		nullptr
	};
	shader_table = CreateShaderTable(state, record_name, record_heap, _countof(record_name));

	while (CheckMsg() && !(GetKeyState(VK_ESCAPE) & 0x80)) {
		std::uint32_t index = swap->GetCurrentBackBufferIndex();
		
		hr = allocator->Reset();
		assert(hr == S_OK);
		hr = list->Reset(allocator, nullptr);
		assert(hr == S_OK);

		UpDateAcceleration(list, top, bottom);

		list->SetComputeRootSignature(global);
		list->SetPipelineState1(state);
		list->SetDescriptorHeaps(1, (ID3D12DescriptorHeap* const*)&heap);

		DXGI_SWAP_CHAIN_DESC1 swap_desc{};
		hr = swap->GetDesc1(&swap_desc);
		assert(hr == S_OK);

		D3D12_DISPATCH_RAYS_DESC desc{};
		desc.Depth  = 1;
		desc.Height = swap_desc.Height;
		desc.Width  = swap_desc.Width;

		desc.RayGenerationShaderRecord.SizeInBytes  = shader_table[0]->GetDesc().Width;
		desc.RayGenerationShaderRecord.StartAddress = shader_table[0]->GetGPUVirtualAddress();
		desc.MissShaderTable.SizeInBytes   = shader_table[1]->GetDesc().Width;
		desc.MissShaderTable.StartAddress  = shader_table[1]->GetGPUVirtualAddress();
		desc.MissShaderTable.StrideInBytes = shader_table[1]->GetDesc().Width;
		desc.HitGroupTable.SizeInBytes   = shader_table[2]->GetDesc().Width;
		desc.HitGroupTable.StartAddress  = shader_table[2]->GetGPUVirtualAddress();
		desc.HitGroupTable.StrideInBytes = shader_table[2]->GetDesc().Width;

		Barrier(list, rsc,
			D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		list->DispatchRays(&desc);
		Barrier(list, rsc);
		Barrier(list, rsc,
			D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_SOURCE);

		Barrier(list, render.rsc[index],
			D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_DEST);
		list->CopyResource(render.rsc[index], rsc);
		Barrier(list, render.rsc[index],
			D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT);

		Execution(queue, { list });
		swap->Present(0, 0);
		Wait(queue, async);
	}

	for (auto& i : shader_table) {
		RELEASE(i);
	}
	RELEASE(rsc);
	RELEASE(heap);
	RELEASE(state);
	for (auto& i : local) {
		RELEASE(i);
	}
	RELEASE(global);
	RELEASE(shader);
	top.Release();
	bottom.Release();
	RELEASE(vertex);
	render.Release();
	RELEASE(swap);
	async.Release();
	RELEASE(list);
	RELEASE(queue);
	RELEASE(allocator);
	RELEASE(device);
	return 0;
}
