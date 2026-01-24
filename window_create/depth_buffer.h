#pragma once
#include "device.h"

class DepthBuffer final {
public:

	//コンストラクタ
	DepthBuffer() = default;

	//デストラクタ
	~DepthBuffer();

	//デプスバッファを生成する
	[[nodiscard]] bool create() noexcept;

	//デプスバッファを取得する
	[[nodiscard]] ID3D12Resource* depthBuffer() const noexcept;

	//ディスクリプタハンドルを取得する
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCpuDescriptorHandle() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_; //レンダーターゲットリソースの配列
	D3D12_CPU_DESCRIPTOR_HANDLE handle_{};				 //ディスクリプタハンドル
};

