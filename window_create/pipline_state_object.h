#pragma once

#include "device.h"
#include "shader.h"
#include "root_signature.h"

class PiplineStateObject final {
public:
	//コンストラクタ
	PiplineStateObject() = default;

	//デストラクタ
	~PiplineStateObject();

	//パイプラインステートオブジェクトを作成する
	[[nodiscard]] bool create(const Device& device, const Shader& shader, const RootSignature& rootSignature) noexcept;

	//パイプラインステートを取得する
	[[nodiscard]] ID3D12PipelineState* get() const noexcept;

private:
	ID3D12PipelineState* pipelineState_ = {}; //パイプラインステート
};

