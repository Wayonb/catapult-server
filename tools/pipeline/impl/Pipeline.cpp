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

#include "Pipeline.h"
// #include "tools/ToolMain.h"
#include "tools/ToolConfigurationUtils.h"
#include "tools/ToolKeys.h"
// #include "catapult/extensions/ExtensionManager.h"
#include "catapult/extensions/ProcessBootstrapper.h"
#include "catapult/extensions/ServiceRegistrar.h"
#include "catapult/extensions/ServiceState.h"
// #include "catapult/ionet/PacketHandlers.h"
#include "catapult/local/server/LocalNode.h"

namespace catapult { namespace tools { namespace pipeline {

	namespace {
		class CapturingServiceRegistrar : public extensions::ServiceRegistrar {
		public:
			explicit CapturingServiceRegistrar(ionet::ServerPacketHandlers& packetHandlers) : m_packetHandlers(packetHandlers)
			{}

		public:
			extensions::ServiceRegistrarInfo info() const override {
				return { "Capturing", extensions::ServiceRegistrarPhase::Post_Packet_Handlers };
			}

			void registerServiceCounters(extensions::ServiceLocator&) override {
				// do nothing
			}

			void registerServices(extensions::ServiceLocator&, extensions::ServiceState& state) override {
				m_packetHandlers = state.packetHandlers();
			}

		private:
			ionet::ServerPacketHandlers& m_packetHandlers;
		};
	}

	struct Pipeline::Impl {
	public:
		Impl() : KeyPair(GenerateRandomKeyPair())
		{}

	public:
		crypto::KeyPair KeyPair;
		ionet::ServerPacketHandlers PacketHandlers;
		std::unique_ptr<local::LocalNode> pLocalNode;
	};

	Pipeline::Pipeline(const std::string& resourcesPath) : m_pImpl(std::make_unique<Impl>()) {
		auto pBootstrapper = std::make_unique<extensions::ProcessBootstrapper>(
				LoadConfiguration(resourcesPath),
				resourcesPath + "/resources",
				extensions::ProcessDisposition::Production,
				"pipeline");
		pBootstrapper->extensionManager().addServiceRegistrar(std::make_unique<CapturingServiceRegistrar>(m_pImpl->PacketHandlers));
		pBootstrapper->loadExtensions();

		m_pImpl->pLocalNode = local::CreateLocalNode(m_pImpl->KeyPair, std::move(pBootstrapper));
	}

	Pipeline::~Pipeline() = default;

	Pipeline::ProcessResult Pipeline::process(const RawBuffer& buffer) {
		const auto* pPacket = reinterpret_cast<const ionet::Packet*>(buffer.pData);
		if (buffer.Size < sizeof(ionet::PacketHeader) || pPacket->Size != buffer.Size)
			return ProcessResult::Skipped_Corrupt;

		if (!m_pImpl->PacketHandlers.canProcess(*pPacket))
			return ProcessResult::Skipped_Unsupported;

		ionet::ServerPacketHandlerContext handlerContext(m_pImpl->KeyPair.publicKey(), "127.0.0.1");
		m_pImpl->PacketHandlers.process(*pPacket, handlerContext);
		return ProcessResult::Processed;
	}
}}}
