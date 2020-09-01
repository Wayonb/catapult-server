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

#pragma once
#include "catapult/types.h"

namespace catapult { namespace model {

#pragma pack(push, 1)

	/// Finalization round composed of an epoch and point.
	struct FinalizationRound {
	public:
		/// Finalization epoch.
		FinalizationEpoch Epoch;

		/// Finalization point.
		FinalizationPoint Point;

	public:
		/// Returns \c true if this round is equal to \a rhs.
		bool operator==(const FinalizationRound& rhs) const;

		/// Returns \c true if this round is not equal to \a rhs.
		bool operator!=(const FinalizationRound& rhs) const;

		/// Returns \c true if this round is less than \a rhs.
		bool operator<(const FinalizationRound& rhs) const;

		/// Returns \c true if this round is less than or equal to \a rhs.
		bool operator<=(const FinalizationRound& rhs) const;

		/// Returns \c true if this round is greater than \a rhs.
		bool operator>(const FinalizationRound& rhs) const;

		/// Returns \c true if this round is greater than or equal to \a rhs.
		bool operator>=(const FinalizationRound& rhs) const;
	};

#pragma pack(pop)

	/// Insertion operator for outputting \a round to \a out.
	std::ostream& operator<<(std::ostream& out, const FinalizationRound& round);
}}
