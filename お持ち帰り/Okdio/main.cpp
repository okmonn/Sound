#include <mmdeviceapi.h>
#include <cassert>
#include <cstdint>
#include <vector>

struct DeviceCallback :
	public IMMNotificationClient {
public:
	/*�R���X�g���N�^*/
	DeviceCallback() {
		count = 1;
	}
	/*����̖�����������̃I�[�f�B�I�G���h�|�C���g�f�o�C�X���ύX���ꂽ���Ƃ�ʒm*/
	long __stdcall OnDefaultDeviceChanged(EDataFlow flow, ERole role, const wchar_t* default_edevice_id) {
		return S_OK;
	}
	/*�V���ɃI�[�f�B�I�G���h�|�C���g�f�o�C�X���ǉ����ꂽ���Ƃ�ʒm*/
	long __stdcall OnDeviceAdded(const wchar_t* device_id) {
		return S_OK;
	}
	/*�I�[�f�B�I�G���h�|�C���g�f�o�C�X���폜����Ă��Ƃ�ʒm*/
	long __stdcall OnDeviceRemoved(const wchar_t* device_id) {
		return S_OK;
	}
	/*�I�[�f�B�I�G���h�|�C���g�f�o�C�X�̏�Ԃ��ω��������Ƃ�ʒm*/
	long __stdcall OnDeviceStateChanged(const wchar_t* device_id, unsigned long new_state) {
		return S_OK;
	}
	/*�I�[�f�B�I�G���h�|�C���g�f�o�C�X�ɑ�����v���p�e�B�̒l���ύX���ꂽ���Ƃ�ʒm*/
	long _stdcall OnPropertyValueChanged(const wchar_t* device_id, const PROPERTYKEY key) {
		return S_OK;
	}
	/*�Q�ƃJ�E���g���Z*/
	unsigned long __stdcall AddRef(void) {
		return InterlockedIncrement(&count);
	}
	/*�Q�ƃJ�E���g�̌���*/
	unsigned long __stdcall Release(void) {
		auto hr = InterlockedDecrement(&count);
		if (SUCCEEDED(hr)) {
			delete this;
		}

		return hr;
	}
	/*�T�|�[�g�`�F�b�N*/
	long __stdcall QueryInterface(const GUID& id, void** obj) {
		if (obj == nullptr) {
			return E_INVALIDARG;
		}

		*obj = nullptr;
		if (id == __uuidof(IMMNotificationClient)) {
			*obj = this;
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}

private:
	/*�Q�ƃJ�E���g*/
	std::uint32_t count;
};

struct EndPoint :
	public IMMEndpoint {
public:
	/*�R���X�g���N�^*/
	EndPoint() {
		count = 1;
	}
	long __stdcall GetDataFlow(EDataFlow* data_flow) {
		return S_OK;
	}
	/*�Q�ƃJ�E���g���Z*/
	unsigned long __stdcall AddRef(void) {
		return InterlockedIncrement(&count);
	}
	/*�Q�ƃJ�E���g�̌���*/
	unsigned long __stdcall Release(void) {
		auto hr = InterlockedDecrement(&count);
		if (SUCCEEDED(hr)) {
			delete this;
		}

		return hr;
	}
	/*�T�|�[�g�`�F�b�N*/
	long __stdcall QueryInterface(const GUID& id, void** obj) {
		if (obj == nullptr) {
			return E_INVALIDARG;
		}

		*obj = nullptr;
		if (id == __uuidof(IMMEndpoint)) {
			*obj = this;
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}

private:
	/*�Q�ƃJ�E���^*/
	std::uint32_t count;
};

int main()
{
	auto hr = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	assert(hr == S_OK);

	IMMDeviceEnumerator* enumerator = nullptr;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&enumerator));
	assert(hr == S_OK);
	DeviceCallback* callback = new DeviceCallback();
	enumerator->RegisterEndpointNotificationCallback(callback);
	IMMDeviceCollection* collection = nullptr;
	hr = enumerator->EnumAudioEndpoints(EDataFlow::eAll, DEVICE_STATE_ACTIVE, &collection);
	assert(hr == S_OK);
	std::uint32_t device_num = 0;
	hr = collection->GetCount(&device_num);
	assert(hr == S_OK);
	std::vector<IMMDevice*>device(device_num);
	for (std::uint32_t i = 0; i < device.size(); ++i) {
		EndPoint* end_point = new EndPoint();
		EDataFlow* data= nullptr;
		hr = device[i]->QueryInterface(__uuidof(IMMEndpoint), nullptr);
		assert(hr == S_OK);
		end_point->Release();
	}
	for (auto& i : device) {
		i->Release();
	}
	collection->Release();
	enumerator->UnregisterEndpointNotificationCallback(callback);
	callback->Release();
	enumerator->Release();
	CoUninitialize();
	return 0;
}