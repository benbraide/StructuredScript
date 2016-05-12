#include "MemoryStateParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::MemoryStateParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto value = parser.term(well, scanner, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto declaration = dynamic_cast<IDeclarationNode *>(value.get());
	if (declaration == nullptr){//Declaration required
		if (dynamic_cast<ITypeIdentifierNode *>(value.get()) != nullptr)//Unnamed declaration
			return std::make_shared<Nodes::DeclarationNode>(value, nullptr, state_, Storage::MemoryAttributes({}));

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + state_.str() + " " + value->str() + "': Expected declaration after state modifier!"));
	}

	if ((declaration->states() & state_.states()) != 0u){//Bad declaration
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + state_.str() + " " + value->str() + "': Bad declaration!"));
	}

	declaration->states(declaration->states() | state_.states());//Add state to declaration states
	return value;
}

const StructuredScript::Storage::MemoryState & StructuredScript::Parser::MemoryStateParser::state() const{
	return state_;
}

unsigned short StructuredScript::Parser::MemoryStateParser::translate(const std::string &state){
	if (state == "const")
		return Storage::MemoryState::STATE_CONSTANT;

	if (state == "final")
		return Storage::MemoryState::STATE_FINAL;

	if (state == "static")
		return Storage::MemoryState::STATE_STATIC;

	if (state == "private")
		return Storage::MemoryState::STATE_PRIVATE;

	if (state == "protected")
		return Storage::MemoryState::STATE_PROTECTED;

	if (state == "public")
		return Storage::MemoryState::STATE_PUBLIC;

	if (state == "ref")
		return Storage::MemoryState::STATE_REFERENCE;

	if (state == "val")
		return Storage::MemoryState::STATE_RVALUE;

	return Storage::MemoryState::STATE_NONE;
}
