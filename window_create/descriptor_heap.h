#pragma once

#include <d3d12.h>
#include <unordered_map>
#include <optional>
#include <memory>
#include "device.h"

using namespace std;

class Descriptorheap final {
public:
	//-------------------------------------------------------------
	//コンストラクタ
	Descriptorheap() = default;

	//-------------------------------------------------------------
	//デストラクタ
	~Descriptorheap();

	//-------------------------------------------------------------
	//ディスクリプタヒープを生成する
	[[nodiscard]] bool create(const Device& device,D3D12_DESCRIPTOR_HEAP_TYPE type,UINT numDescriptors,bool shaderVisible = false) noexcept;

	//-------------------------------------------------------------
	//ディスクリプタヒープを取得する
	[[nodiscard]] ID3D12DescriptorHeap* get() const noexcept;

	//-------------------------------------------------------------
	//ディスクリプタヒープのタイプを取得する
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE getType() const noexcept;

	void applyPendingFree() noexcept {
		if (pendingFreeIndices_.empty()) {
			return;
		}

		for (auto i : pendingFreeIndices_) {
			freeIndices_.push_back(i);
		}
		pendingFreeIndices_.clear();
	}

private:
	ID3D12DescriptorHeap*        heap_{}; //ディスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE   type_{}; //ヒープのタイプ

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};				 //ディスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE                   type_{};				 //ヒープのタイプ
	UINT										 maxDescriptorCount_{};  //最大ディスクリプタ数
	vector<UINT>								 freeIndices_{};		 //空きディスクリプタインデックスのリスト
	vector<UINT>                                 pendingFreeIndices_{};  //解放町ディスクリプタインデックスのリスト
};

class DescriptorHeapContainer final {
public:
	//インスタンスの取得
	static DescriptorHeapContainer& instance() noexcept {
		static DescriptorHeapContainer instance;
		return instance;
	}

	//ディスクリプタヒープを生成する
	[[nodiscard]] bool create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false) noexcept;

	//解放予約されているディスクリプタを解放する
	void applyPendingFree() noexcept;

	//ディスクリプタヒープを取得する
	[[nodiscard]] ID3D12DescriptorHeap* get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept;

	//ディスクリプタを確保する
	[[nodiscard]] optional<UINT> allocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	//解放予定のディスクリプタを登録する
	void releaseDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorIndex) noexcept;

private:
	//コンストラクタ
	DescriptorHeapContainer();

	//デストラクタ
	~DescriptorHeapContainer();

	//コピーとムーブの禁止
	DescriptorHeapContainer(const DescriptorHeapContainer& r)            = delete;
	DescriptorHeapContainer& operator=(const DescriptorHeapContainer& r) = delete;
	DescriptorHeapContainer(DescriptorHeapContainer&& r)                 = delete;
	DescriptorHeapContainer& operator=(DescriptorHeapContainer&& r)      = delete;

private:
	unordered_map<UINT, unique_ptr<Descriptorheap>> map_{};
};




