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

/*�`���[�g���A��1*/
/*�E�B���h�n���h��*/
void* window = nullptr;

/*�`���[�g���A��2*/
/*�f�o�C�X*/
ID3D12Device6* device = nullptr;
/*�R�}���h�A���P�[�^*/
ID3D12CommandAllocator* allocator = nullptr;
/*�R�}���h�L���[*/
ID3D12CommandQueue* queue = nullptr;
/*�R�}���h���X�g*/
ID3D12GraphicsCommandList5* list = nullptr;
/*�R�}���h�����I�u�W�F�N�g*/
struct CommandAsync {
public:
	/*�������J��*/
	void Release(void) {
		if (fence != nullptr) {
			fence->Release();
			fence = nullptr;
		}
	}

public:
	/*�t�F���X*/
	ID3D12Fence1* fence = nullptr;
	/*�ҋ@�J�E���g*/
	std::uint64_t cnt = 0;
}async;
/*�X���b�v�`�F�C��*/
IDXGISwapChain4* swap = nullptr;
/*�����_�[�^�[�Q�b�g�I�u�W�F�N�g*/
struct RenderTarget {
public:
	/*�������J��*/
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
	/*�q�[�v*/
	ID3D12DescriptorHeap* heap = nullptr;
	/*���\�[�X*/
	std::vector<ID3D12Resource1*>rsc;
}render;

/*�`���[�g���A��3*/
/*���_���\�[�X*/
ID3D12Resource1* vertex = nullptr;
/*�����\��*/
struct Acceleration {
public:
	/*�������J��*/
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
	/*�X�N���b�`���\�[�X*/
	ID3D12Resource1* scratch = nullptr;
	/*���U���g���\�[�X*/
	ID3D12Resource1* result = nullptr;
	/*�C���X�^���X���\�[�X*/
	ID3D12Resource1* instance = nullptr;
}bottom, top;

/*�`���[�g���A��4*/
/*�V�F�[�_���*/
ID3DBlob* shader = nullptr;
/*���[�g�V�O�l�`��(�O���[�o��)*/
ID3D12RootSignature* global = nullptr;
/*���[�g�V�O�l�`��(���[�J��)*/
std::vector<ID3D12RootSignature*>local;
/*�X�e�[�g�I�u�W�F�N�g*/
ID3D12StateObject* state = nullptr;

/*�`���[�g���A��6*/
/*�q�[�v*/
ID3D12DescriptorHeap* heap = nullptr;
/*���\�[�X*/
ID3D12Resource1* rsc = nullptr;

/*�`���[�g���A��5*/
/*�V�F�[�_�e�[�u��*/
std::vector<ID3D12Resource1*>shader_table;
