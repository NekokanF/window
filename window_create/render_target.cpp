#include "render_target.h"
#include<cassert>

//---------------------------------------------------------------------
//デストラクタ
RenderTarget::~RenderTarget() {
	//レンダ―ターゲットリソースの解放
	for (auto& rt : renderTargets_) {
		if (rt) {
			rt->Release();
			rt = nullptr;
		}
	}
	renderTargets_.clear();
}

//---------------------------------------------------------------------
//バックバッファを生成する
[[nodiscard]] bool RenderTarget::createBackBuffer(const Device& device, const SwapChain& swapChain, const Descriptorheap& heap) noexcept {

	//スワップチェインの設定を取得
	const auto& desc = swapChain.getDesc();

	//レンダ―ターゲットリソースのサイズを設定
	renderTargets_.resize(desc.BufferCount);

	//ディスクリプタヒープのハンドルを取得
	auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

	//ディスクリプタヒープのタイプを取得
	auto heapType = heap.getType();
	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプタヒープのタイプが RTV ではありません");

	//バックバッファんｐ生成
	for (uint8_t i = 0; i < desc.BufferCount; i++) {
		const auto hr = swapChain.get()->GetBuffer(i, IID_PPV_ARGS(&renderTargets_[i]));
		if (FAILED(hr)) {
			assert(false && "バックバッファの取得に失敗しました");
			return false;
		}

		//レンダ―ターゲットビューを作成してディスクリプタヒープのハンドルと関連付ける
		device.get()->CreateRenderTargetView(renderTargets_[i], nullptr, handle);

		//次のハンドルへ移動
		handle.ptr += device.get()->GetDescriptorHandleIncrementSize(heapType);
	}
	return true;
}

//------------------------------------------------------------------------------
//ビュー（ディスクリプタハンドル）を取得する
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::getDescriptorHandle(const Device& device, const Descriptorheap& heap, UINT index) const noexcept {

	if (index >= renderTargets_.size() || !renderTargets_[index]) {
		assert(false && "不正なレンダ―ターゲットです");
	}

	//ディスクリプタヒープのハンドルを取得
	auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

	//ディスクリプタヒープのタイプを取得
	auto heapType = heap.getType();
	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプタヒープのタイプが RTV ではありません");

	//インデックスに応じてハンドルを移動
	handle.ptr += index * device.get()->GetDescriptorHandleIncrementSize(heapType);
	return handle;
}

//--------------------------------------------------------------------------
//レンダ―ターゲットを取得する
[[nodiscard]] ID3D12Resource* RenderTarget::get(uint32_t index) const noexcept {
	if (index >= renderTargets_.size() || !renderTargets_[index]) {
		assert(false && "不正なレンダ―ターゲットです");
		return nullptr;
	}
	return renderTargets_[index];
}
