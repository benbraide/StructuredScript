#pragma once

#ifndef STRUCTURED_SCRIPT_NODE_QUERY_H
#define STRUCTURED_SCRIPT_NODE_QUERY_H

#include <list>

#include "../Interfaces/INode.h"
#include "../Interfaces/Nodes/IOperatorNode.h"
#include "../Interfaces/Nodes/IEmptyNode.h"
#include "../Interfaces/Nodes/IBlockNode.h"
#include "../Interfaces/Nodes/IIdentifierNode.h"

#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Query{
		class Node{
		public:
			typedef std::list<INode::Ptr> ListType;

			static bool isEmpty(const INode *node);

			static bool isDeclaration(const INode *node);

			static bool isAssignment(const INode *node);

			static bool isParameter(const INode *node);

			static bool isMember(const INode *node);

			static bool isControl(const INode *node);

			static bool isLoop(const INode *node);

			static bool isSelection(const INode *node);

			static bool isBlock(const INode *node);

			static bool isPlainBlock(const INode *node);

			static void split(const std::string &value, INode::Ptr node, ListType &list, bool forceBinary = false);

			static IStorage *resolveAsStorage(INode::Ptr node, IStorage *storage);

			static IType::Ptr resolveAsType(INode::Ptr node, IStorage *storage);

			static IMemory::Ptr resolveAsObject(INode::Ptr node, IStorage *storage);

		private:
			static bool resolvePartial_(INode::Ptr node, IStorage *&storage, std::string &value, bool &localOnly);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NODE_QUERY_H */