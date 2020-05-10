#pragma once
#include <Windows.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxcapi.h>

#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <unordered_map>

/*チュートリアル1*/
/*ウィンドハンドル*/
void* window = nullptr;

/*チュートリアル2*/
/*デバイス*/
ID3D12Device6* device = nullptr;
/*コマンドアロケータ*/
ID3D12CommandAllocator* allocator = nullptr;
/*コマンドキュー*/
ID3D12CommandQueue* queue = nullptr;
/*コマンドリスト*/
ID3D12GraphicsCommandList5* list = nullptr;
/*コマンド同期オブジェクト*/
struct CommandAsync {
public:
	/*メモリ開放*/
	void Release(void) {
		if (fence != nullptr) {
			fence->Release();
			fence = nullptr;
		}
	}

public:
	/*フェンス*/
	ID3D12Fence1* fence = nullptr;
	/*待機カウント*/
	std::uint64_t cnt = 0;
}async;
/*スワップチェイン*/
IDXGISwapChain4* swap = nullptr;
/*レンダーターゲットオブジェクト*/
struct RenderTarget {
public:
	/*メモリ開放*/
	void Release() {
		for (auto& i : rsc) {
			if (i != nullptr) {
				i->Release();
				i = nullptr;
			}
		}
		if (heap != nullptr) {
			heap->Release();
			heap = nullptr;
		}
	}

public:
	/*ヒープ*/
	ID3D12DescriptorHeap* heap = nullptr;
	/*リソース*/
	std::vector<ID3D12Resource1*>rsc;
}render;

/*チュートリアル3*/
/*頂点リソース*/
ID3D12Resource1* vertex = nullptr;
/*加速構造*/
struct Acceleration {
public:
	/*メモリ開放*/
	void Release(void) {
		if (instance != nullptr) {
			instance->Release();
			instance = nullptr;
		}
		if (result != nullptr) {
			result->Release();
			result = nullptr;
		}
		if (scratch != nullptr) {
			scratch->Release();
			scratch = nullptr;
		}
	}

public:
	/*スクラッチリソース*/
	ID3D12Resource1* scratch = nullptr;
	/*リザルトリソース*/
	ID3D12Resource1* result = nullptr;
	/*インスタンスリソース*/
	ID3D12Resource1* instance = nullptr;
}bottom, top;

/*チュートリアル4*/
/*シェーダ情報*/
ID3DBlob* shader = nullptr;
/*ルートシグネチャ(グローバル)*/
ID3D12RootSignature* global = nullptr;
/*ルートシグネチャ(ローカル)*/
std::vector<ID3D12RootSignature*>local;
/*ステートオブジェクト*/
ID3D12StateObject* state = nullptr;

/*チュートリアル6*/
/*ヒープ*/
ID3D12DescriptorHeap* heap = nullptr;
/*リソース*/
ID3D12Resource1* rsc = nullptr;

/*チュートリアル5*/
/*シェーダテーブル*/
std::vector<ID3D12Resource1*>shader_table;
