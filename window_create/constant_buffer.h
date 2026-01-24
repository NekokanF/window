#pragma once
#include "device.h"
#include "descriptor_heap.h"

class ConstantBuffer final
{
public:
	//コンストラクタ
	ConstantBuffer() = default;

	//デストラクタ
	~ConstantBuffer();

	//コンスタントバッファの作成
	[[nodiscard]] bool create(UINT bufferSize) noexcept;

	//コンスタントを取得する
	[[nodiscard]] ID3D12Resource* constantBuffer() const noexcept;

	//ディスクリプタハンドルを取得する
	[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constantBuffer_{};
	UINT descriptorIndex_{};
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};
};

