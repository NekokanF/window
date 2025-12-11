#pragma once

#include "DXGI.h"
#include <d3d12.h>

class Device final{
public:

	//-----------------------------------------------------
	//コンストラクタ
	Device() = default;

	//-----------------------------------------------------
	//デストラクタ
	~Device();

	//-----------------------------------------------------
	//デバイスを作成する
	[[nodiscard]] bool create(const DXGI& dxgi) noexcept;

	//-----------------------------------------------------
	//デバイスを取得する
	[[nodiscard]] ID3D12Device* get() const noexcept;

private:
	ID3D12Device* device_; //デバイス
};

