#pragma once
#include "device.h"

class RootSignature final {
public:
	//コンストラクタ
	RootSignature() = default;

	//デストラクタ
	~RootSignature();

	//ルートシグネチャを作成する
	[[nodiscard]] bool create(const Device& device) noexcept;

	//ルートシグネチャを取得する
	[[nodiscard]] ID3D12RootSignature* get() const noexcept;

private:
	ID3D12RootSignature* rootSignature_{}; //ルートシグネチャ
};

