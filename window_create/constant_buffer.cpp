#include "constant_buffer.h"
#include <cassert>

namespace {
	constexpr auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
}

////デストラクタ
//ConstantBuffer::~ConstantBuffer() {
//	//ディスクリプタヒープの解放も必要
//	DescriptorHeapContainer::
//}
