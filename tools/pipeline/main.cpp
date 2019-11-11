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

#include "tools/ToolMain.h"
#include "impl/Pipeline.h"
#include "catapult/io/RawFile.h"

namespace catapult { namespace tools { namespace pipeline {

	namespace {
		class PipelineTool : public Tool {
		public:
			std::string name() const override {
				return "Pipeline Tool";
			}

			void prepareOptions(OptionsBuilder& optionsBuilder, OptionsPositional&) override {
				optionsBuilder("resources,r",
						OptionsValue<std::string>(m_resourcesPath)->default_value(".."),
						"the path to the resources directory");
				optionsBuilder("inputFilename,i",
						OptionsValue<std::string>(m_inputFilename)->default_value(""),
						"the path to the file to process");
			}

			int run(const Options&) override {
				Pipeline pipeline(m_resourcesPath);

				io::RawFile inputFile(m_inputFilename, io::OpenMode::Read_Only);
				std::vector<uint8_t> inputDataBuffer(inputFile.size());
				inputFile.read(inputDataBuffer);

				pipeline.process(inputDataBuffer);
				return 0;
			}

		private:
			std::string m_resourcesPath;
			std::string m_inputFilename;
		};
	}
}}}

int main(int argc, const char** argv) {
	catapult::tools::pipeline::PipelineTool tool;
	return catapult::tools::ToolMain(argc, argv, tool);
}
