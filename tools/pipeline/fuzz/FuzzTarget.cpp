/**
*** Copyright (c) 2016-present,
*** Jaguar0625, gimre, BloodyRookie, Tech Bureau, Corp. All rights reserved.
***
*** This file is part of Catapult.
***
*** Catapult is free software: you can redistribute it and/or modify
*** it under the terms of the GNU Lesser General Public License as published by
*** the Free Software Foundation, either version 3 of the License, or
*** (at your option) any later version.
***
*** Catapult is distributed in the hope that it will be useful,
*** but WITHOUT ANY WARRANTY; without even the implied warranty of
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*** GNU Lesser General Public License for more details.
***
*** You should have received a copy of the GNU Lesser General Public License
*** along with Catapult. If not, see <http://www.gnu.org/licenses/>.
**/

#include "../impl/Pipeline.h"
#include <boost/dll/runtime_symbol_info.hpp>
#include "catapult/plugins.h"

extern "C" PLUGIN_API int LLVMFuzzerTestOneInput(const uint8_t* pData, size_t size);

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

extern "C" PLUGIN_API int LLVMFuzzerTestOneInput(const uint8_t* pData, size_t size) {
        static catapult::tools::pipeline::Pipeline pipeline(boost::dll::program_location().parent_path().generic_string());

	pipeline.process({ pData, size });
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
