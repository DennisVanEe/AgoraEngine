#pragma once

namespace agora
{
	namespace model_imp
	{
		enum class ImporterError
		{
			SUCCESS = 0,
			REQUEST_QUEUE_EMPTY,
			FAILED_TO_CONSTRUCT_THREADS,
			FAILED_TO_JOIN_THREADS,
			FAILED_TO_PARSE_FILE,
            UNSUPPORTED_TEXTURE_FORMAT,
            EMBEDDED_TEXTURES_NOT_SUPPORTED,
            FAILED_TO_LOAD_TEXTURE, 
		};
	}
}