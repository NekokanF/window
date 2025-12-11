#pragma once
#include "device.h"

class Shader final {
public:
	//コンストラクタ
	Shader() = default;

	//デストラクタ
	~Shader();

	//シェーダーを作成する
	[[nodiscard]] bool create(const Device& device) noexcept;

	//頂点シェーダーを取得する
	[[nodiscard]] ID3DBlob* vertexShader() const noexcept;

	//ピクセルシェーダーを取得する
	[[nodiscard]] ID3DBlob* pixelShader() const noexcept;

private:
	ID3DBlob* vertexShader_{}; //頂点シェーダー
	ID3DBlob* pixelShader_{};  //ピクセルシェーダー
};

