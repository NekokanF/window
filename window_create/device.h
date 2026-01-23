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

	static Device& instance() noexcept {
		static Device instance;
		return instance;
	}

	//-----------------------------------------------------
	//デバイスを作成する
	[[nodiscard]] bool create(const DXGI& dxgi) noexcept;

	//-----------------------------------------------------
	//デバイスを取得する
	[[nodiscard]] ID3D12Device* get() const noexcept;

	//DXGI インスタンスを取得する
	[[nodiscard]] const DXGI& dxgi() const noexcept;

private:
	DXGI          dxgiInstance_{}; //DXGIインスタンス
	ID3D12Device* device_;         //デバイス
};