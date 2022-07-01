/**	@file	dlph_tfile.hpp
 *	@brief	Dolphic Engine 用のファイルタイプ一覧
 */
#pragma once

namespace dlph {
	/**	@enum	RasterPictureFileType
	 *	@brief	ラスター画像ファイルタイプ一覧
	 */
	enum class RasterPictureFileType : unsigned char {
		//!	@brief	未対応のファイル
		Unknown,
		//!	@brief	TGA ファイル
		TGA,
		//!	@brief	PNG ファイル
		PNG,
		//!	@brief	JPEG ファイル
		JPG,
		//!	@brief	GIF ファイル
		GIF,
		//!	@brief	DDS ファイル
		DDS,
		//!	@brief	TIFF ファイル
		TIFF,
	};

	/**	@enum	VectorPictureFileType
	 *	@brief	ベクター画像ファイルタイプ一覧
	 */
	enum class VectorPictureFileType : unsigned char {
		//!	@brief	未対応のファイル
		Unknown,
		//!	@brief	SVG ファイル
		SVG
	};

	/**	@enum	TextDataFileType
	 *	@brief	テキスト形式データファイルタイプ一覧
	 */
	enum class TextDataFileType : unsigned char {
		//!	@brief	未対応のファイル
		Unknown,
		//!	@brief	CSV ファイル
		CSV,
		//!	@brief	TSV ファイル
		TSV,
		//!	@brief	XML ファイル
		XML,
		//!	@brief	JSON ファイル
		JSON
	};

	/**	@enum	ModelFileType
	 *	@brief	三次元モデルファイルタイプ一覧
	 */
	enum class ModelFileType : unsigned char {
		//!	@brief	未対応のファイル
		Unknown,
		//!	@brief	COLLADA ファイル
		DAE,
		//!	@brief	FBX ファイル
		FBX,
		//!	@brief	OBJ/MTL ファイル
		OBJ_MTL,
	};
}
