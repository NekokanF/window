#pragma once

#include <wrl.h>
#include "device.h"	
#include "descriptor_heap.h"

//コンスタントバッファクラス
class ConstantBuffer
{
public:
	//コンストラクタ
	ConstantBuffer() = default;

	//デストラクタ
	~ConstantBuffer();

	//コンスタントバッファの作成
	[[nodiscard]] bool create(UINT bufferSize) noexcept;

	//コンスタントバッファを取得する
	[[nodiscard]] ID3D12Resource* constantBuffer() const noexcept;

	//GPU 用ディスクリプタハンドルを取得する
	[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE getGppuDescriptorHandle() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constantBuffer_{};  //コンスタントバッファ
	UINT                                   descriptorIndex_{}; //ディスクリプタヒープ
	D3D12_GPU_DESCRIPTOR_HANDLE            gpuHandle_{};       //GPU用ディスクリプタハンドル


};

