#pragma once

#ifndef STRUCTURED_SCRIPT_NODE_QUERY_H
#define STRUCTURED_SCRIPT_NODE_QUERY_H

#include <list>

#include "../Interfaces/Nodes/IOperatorNode.h"
#include "../Interfaces/Nodes/IEmptyNode.h"
#include "../Interfaces/Nodes/IIdentifierNode.h"
#include "../Interfaces/Nodes/IDeclarationNode.h"
#include "../Interfaces/Nodes/IFunctionNode.h"
#include "../Interfaces/Nodes/IGroupNode.h"
#include "../Interfaces/Nodes/IIndexNode.h"
#include "../Interfaces/Nodes/IBlockNode.h"
#include "../Interfaces/Nodes/IPropertyNode.h"
#include "../Interfaces/Nodes/IStorageResolver.h"
#include "../Interfaces/Nodes/ITypeResolver.h"
#include "../Interfaces/Nodes/IMemoryResolver.h"
#include "../Interfaces/Nodes/IControlNode.h"
#include "../Interfaces/Nodes/IExceptionHandler.h"

#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Query{
		class Node{
		public:
			typedef std::list<INode::Ptr> ListType;

			static bool isEmpty(INode::Ptr node);

			static bool isIdentifier(INode::Ptr node);

			static bool isIdentifierExpression(INode::Ptr node);

			static bool isOperatorIdentifier(INode::Ptr node);

			static bool isTypeIdentifier(INode::Ptr node);

			static bool isExpandedTypeIdentifier(INode::Ptr node);

			static bool isDeclaration(INode::Ptr node);

			static bool isInitialization(INode::Ptr node);

			static bool isParameter(INode::Ptr node);

			static bool isMember(INode::Ptr node);

			static bool isControl(INode::Ptr node);

			static bool isFunction(INode::Ptr node);

			static bool isFunctionDeclaration(INode::Ptr node);

			static bool isFunctionDefinition(INode::Ptr node);

			static bool isLoop(INode::Ptr node);

			static bool isSelection(INode::Ptr node);

			static bool isGroup(INode::Ptr node);

			static bool isIndex(INode::Ptr node);

			static bool isBlock(INode::Ptr node);

			static bool isPlainBlock(INode::Ptr node);

			static INode::Ptr getBaseId(INode::Ptr node);

			static void split(const std::string &value, INode::Ptr node, ListType &list, bool forceBinary = false);

			static IStorage *resolveAsStorage(INode::Ptr node, IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT);

			static IType::Ptr resolveAsType(INode::Ptr node, IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT);

			static IMemory::Ptr resolveAsMemory(INode::Ptr node, IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NODE_QUERY_H */