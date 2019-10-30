/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <libsolidity/interface/StorageLayout.h>

#include <libsolidity/ast/AST.h>

using namespace std;
using namespace dev;
using namespace dev::solidity;

Json::Value StorageLayout::generate(ContractDefinition const& _contractDef)
{
	Json::Value storage(Json::arrayValue);
	auto typeType = dynamic_cast<TypeType const*>(_contractDef.type());
	solAssert(typeType, "");
	auto type = dynamic_cast<ContractType const*>(typeType->actualType());
	solAssert(type, "");
	for (auto const& var: type->stateVariables())
	{
		Json::Value varEntry;
		varEntry["name"] = get<0>(var)->name();
		varEntry["slot"] = get<1>(var).str();
		varEntry["offset"] = get<2>(var);
		varEntry["type"] = get<0>(var)->type()->toString();
		varEntry["numberOfSlots"] = get<0>(var)->type()->storageSize().str();
		varEntry["numberOfBytes"] = get<0>(var)->type()->storageBytes();
		storage.append(varEntry);
	}

	return storage;
}
