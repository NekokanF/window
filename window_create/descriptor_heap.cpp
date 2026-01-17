//ディスクリプターヒープ制御クラス

#include "descriptor_heap.h"
#include "device.h"
#include <cassert>
#include <wrl/client.h>

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

	//全ディスクリプタをフリーリストに登録
	maxDescriptorCount_ = numDescriptors;
	for (UINT i = 0; i < maxDescriptorCount_; ++i) {
		freeIndices_.push_back(i);
	}

	return true;
}




//ディスクリプタヒープを取得する
[[nodiscard]] ID3D12DescriptorHeap* Descriptorheap::get() const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプタヒープが未生成です");
	}

	return heap_.Get();
}

//ディスクリプタヒープのタイプを取得する
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE Descriptorheap::getType() const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプタヒープが未生成です");
	}
	return type_;
}

//ディスクリプタを確保する
[[nodiscord]] optional<UINT> allocateDescriptor() noexcept {
	if (freeIndices_.empty()) {
		return nullopt;
	}
	const auto index = freeIndices_.back();
	freeIndices_.pop_back();
	return index;
}

//解放予定のディスクリプタを登録する
void releaseDescriptor(UINT descriptionIndex) noexcept {
	//10フレーム語に解放するよう登録
	pendingFreeIndices_.push_back(descriptionIndex);
}

//コンストラクタ
DescriptorHeapContainer::DescriptorHeapContainer() = default;

//デストラクタ
DescriptorHeapContainer::~DescriptorHeapContainer() {
	map_.clear();
}

[[nodiscard]] bool DescriptorHeapContainer::create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept {
	if (map_.find(type) != map_.end()) {
		return false;
	}

	auto p = make_unique<Descriptorheap>();
	if (p->create(type,numDescriptors,shaderVisible)) {
		map_.emplace(type, move(p));
	}

	return true;
}

void DescriptorHeapContainer::applyPendingFree() noexcept {
	for (auto& [key, p] : map_) {
		p->applyPendingFree();
	}
}