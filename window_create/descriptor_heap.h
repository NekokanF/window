#pragma once

#include "Dx12.h"

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
	[[nodiscard]] bool create(const Dx12& dx12,D3D12_DESCRIPTOR_HEAP_TYPE type,UINT numDescriptors,bool shaderVisible = false) noexcept;

	//-------------------------------------------------------------
	//ディスクリプタヒープを取得する
	[[nodiscard]] ID3D12DescriptorHeap* get() const noexcept;

	//-------------------------------------------------------------
	//ディスクリプタヒープのタイプを取得する
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE getType() const noexcept;

private:
	ID3D12DescriptorHeap*        heap_{}; //ディスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE   type_{}; //ヒープのタイプ
};

