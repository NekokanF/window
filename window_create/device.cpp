//デバイスクラス
#include "device.h"
#include <cassert>

//ライブラリのリンク
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxguid.lib")

//---------------------------------------------------------
//デストラクタ
Device::~Device() {
	//デバイスの解放
	if (device_) {
		device_->Release();
		device_ = nullptr;
	}
}

//---------------------------------------------------------
//デバイスを作成
[[nodiscard]] bool Device::create(const DXGI& dxgi) noexcept {
	//デバイス作成
	const auto hr = D3D12CreateDevice(dxgi.displayAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
	if (FAILED(hr)) {
		assert(false && "デバイス作成に失敗");
		return false;
	}

	return true;

}

//---------------------------------------------------------
//デバイスを取得する
[[nodiscard]] ID3D12Device* Device::get() const noexcept {
	if (!device_) {
		assert(false && "デバイスが未作成です");
	}

	return device_;
}
 