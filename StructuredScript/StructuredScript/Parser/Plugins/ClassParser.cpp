#include "ClassParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::ClassParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto name = parser.term(well, scanner, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (!Query::Node::isEmpty(name) && (!Query::Node::isIdentifier(name) || Query::Node::isOperatorIdentifier(name) || Query::Node::isTypeIdentifier(name))){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'class...': Expected an identifier!"));
	}

	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'class " + name->str() + "...': Bad expression!"));
	}

	INode::Ptr value;
	auto nameStr = name->str();

	while (scanner.hasMore(well)){
		INode::Ptr right;

		auto next = scanner.peek(well).value();
		if (next == "~" || (nameStr.empty() && next == "__destructor")){//Destructor
			scanner.next(well);//Ignore
			if (next == "~"){
				if (nameStr.empty()){
					return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
						"'~': Bad expression in class definition!"));
				}

				next = scanner.next(well).value();
				if (next != nameStr){
					return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
						"'~" + next + "...': Bad expression in class definition!"));
				}
			}
		}
		else if (next == nameStr || (nameStr.empty() && next == "__constructor")){//Constructor
			scanner.next(well);//Ignore
		}
		else{//Parse line
			right = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
				return (next.value() != ";");
			});

			while (scanner.peek(well).value() == ";")//Skip ';'
				scanner.next(well);
		}

		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (value == nullptr)
			value = right;
		else//Create a pair of lines
			value = std::make_shared<Nodes::BlockPairNode>(value, right);
	}

	if (!scanner.close(well)){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'class " + name->str() + "{...': Bad expression!"));
	}

	return std::make_shared<Nodes::ClassNode>(name, value);
}
