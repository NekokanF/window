#pragma once
#include "device.h"
#include "swap_chain.h"
#include "descriptor_heap.h"
#include<vector>

//------------------------------------------------------------------------
class RenderTarget final{
public:
	//コンストラクタ
	RenderTarget() = default;

	//デストラクタ
	~RenderTarget();

	//バックバッファを生成する
	[[nodiscard]] bool createBackBuffer(const Device& device, const SwapChain& swapChain, const Descriptorheap& heap) noexcept;

	//ビュー（ディスクリプタハンドル）を取得する
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle(const Device& device, const Descriptorheap& heap, UINT index) const noexcept;

	//レンダ―ターゲットを取得する
	[[nodiscard]] ID3D12Resource* get(uint32_t index) const noexcept;

private:
	std::vector<ID3D12Resource*> renderTargets_; //レンダ―ターゲットリソースの配列
};

