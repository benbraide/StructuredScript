#include "FileCharacterWell.h"

StructuredScript::Scanner::FileCharacterWell::FileCharacterWell(const std::string &path)
	: StringCharacterWell(""), file_(path){
	if (file_)//Read first line
		std::getline(file_, value_);
}

char StructuredScript::Scanner::FileCharacterWell::peek(){
	if (end_ < value_.size())
		return value_[end_];

	return load() ? peek() : '\0';
}

std::string StructuredScript::Scanner::FileCharacterWell::peek(unsigned int length){
	if (end_ < value_.size()){
		if ((end_ + length) <= value_.size() || !load())
			return value_.substr(end_, length);

		return peek(length);
	}

	return load() ? peek(length) : "";
}

char StructuredScript::Scanner::FileCharacterWell::next(){
	if (end_ < value_.size())
		return value_[end_++];

	return load() ? next() : '\0';
}

void StructuredScript::Scanner::FileCharacterWell::step(int steps){
	if (steps < 0){
		if (static_cast<unsigned int>(-steps) > (end_ - start_))
			end_ = start_;
		else
			end_ -= static_cast<unsigned int>(-steps);
	}
	else if((end_ + steps) > value_.size() && !load())
		end_ = value_.size();
	else
		step(steps);
}

bool StructuredScript::Scanner::FileCharacterWell::stepTo(char target){
	return stepTo_(target, end_);
}

bool StructuredScript::Scanner::FileCharacterWell::load(){
	if (!file_)
		return false;

	std::string line;
	std::getline(file_, line);
	value_ += "\n" + line;

	return true;
}

bool StructuredScript::Scanner::FileCharacterWell::stepTo_(char target, unsigned int offset){
	auto index = value_.find(target, offset);
	if (index < value_.size()){
		end_ = static_cast<int>(index);
		return true;
	}

	offset = value_.size();
	return load() ? stepTo_(target, offset) : false;
}
