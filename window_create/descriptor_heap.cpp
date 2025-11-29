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
[[nodiscard]] bool Descriptorheap::create(const Dx12& dx12, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept {
	//ヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type                       = type;
	heapDesc.NumDescriptors             = numDescriptors;
	heapDesc.Flags                      = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	type_ = type; //ヒープのタイプを保存

	// ディスクリプタヒープの生成
	//HRESULT hr = dx12.get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap_));
}
