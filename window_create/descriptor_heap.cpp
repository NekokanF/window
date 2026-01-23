#include "descriptor_heap.h"
#include <cassert>

//-------------------------------------------------------------------------
//デストラクタ
Descriptorheap::~Descriptorheap() {
	if (heap_) {
		heap_->Release();
		heap_ = nullptr;
	}
}

//-------------------------------------------------------------------------
//ディスクリプタヒープを生成する
[[nodiscard]] bool Descriptorheap::create(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept {
	//ヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type                       = type;
	heapDesc.NumDescriptors             = numDescriptors;
	heapDesc.Flags                      = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	type_ = type; //ヒープのタイプを保存

	// ディスクリプタヒープの生成
	HRESULT hr = device.get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap_));
	if (FAILED(hr)) {
		assert(false && "ディスクリプタヒープの生成に失敗しました");
		return false;
	}
	return true;
}

//ディスクリプタヒープを取得する
[[nodiscard]] ID3D12DescriptorHeap* Descriptorheap::get() const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプタヒープが未生成です");
	}

	return heap_;
}

//ディスクリプタヒープのタイプを取得する
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE Descriptorheap::getType() const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプタヒープが未生成です");
	}
	return type_;
}
