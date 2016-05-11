#include "StringCharacterWell.h"

char StructuredScript::Scanner::StringCharacterWell::peek() const{
	return (end_ < value_.size()) ? value_[end_] : '\0';
}

std::string StructuredScript::Scanner::StringCharacterWell::peek(unsigned int length) const{
	return (end_ < value_.size()) ? value_.substr(end_, length) : "";
}

std::string StructuredScript::Scanner::StringCharacterWell::get() const{
	return value_.substr(start_, end_ - start_);
}

char StructuredScript::Scanner::StringCharacterWell::next(){
	return (end_ < value_.size()) ? value_[end_++] : '\0';
}

char StructuredScript::Scanner::StringCharacterWell::prev(){
	return (end_ > start_ && end_ <= value_.size()) ? value_[--end_] : '\0';
}

void StructuredScript::Scanner::StringCharacterWell::step(int steps){
	if (steps < 0){
		if (static_cast<unsigned int>(-steps) > (end_ - start_))
			end_ = start_;
		else
			end_ -= static_cast<unsigned int>(-steps);
	}
	else{
		end_ += steps;
		if (end_ > value_.size())
			end_ = value_.size();
	}
}

void StructuredScript::Scanner::StringCharacterWell::stepToEnd(){
	end_ = value_.size();
}

bool StructuredScript::Scanner::StringCharacterWell::stepTo(char target){
	auto index = value_.find(target, end_);
	if (index < value_.size()){
		end_ = static_cast<int>(index);
		return true;
	}

	return false;
}

void StructuredScript::Scanner::StringCharacterWell::collapse(){
	end_ = start_;
}

void StructuredScript::Scanner::StringCharacterWell::commit(){
	value_.erase(start_, end_ - start_);//Erase spanned value
	end_ = start_;//Collapse
}

void StructuredScript::Scanner::StringCharacterWell::fork(){
	forks_.push_back(start_);
	start_ = end_;
}

void StructuredScript::Scanner::StringCharacterWell::revert(){
	if (!forks_.empty()){//Remove last fork and restore 'start' and 'end'
		collapse();
		start_ = *forks_.rbegin();
		forks_.pop_back();
	}
}

void StructuredScript::Scanner::StringCharacterWell::discard(){
	if (!forks_.empty()){//Remove last fork, and its content, and restore 'start' and 'end'
		commit();
		start_ = *forks_.rbegin();
		forks_.pop_back();
	}
}

void StructuredScript::Scanner::StringCharacterWell::merge(){
	if (!forks_.empty()){//Remove last fork and merge 'start'
		start_ = *forks_.rbegin();
		forks_.pop_back();
	}
}

std::string StructuredScript::Scanner::StringCharacterWell::dump(){
	auto value = value_.substr(start_);//Get value extending to end of string

	value_.erase(start_);//Erase to end of string
	end_ = start_;//Collapse

	return value;
}

bool StructuredScript::Scanner::StringCharacterWell::load(){
	return false;
}

bool StructuredScript::Scanner::StringCharacterWell::empty() const{
	return value_.empty();
}

unsigned int StructuredScript::Scanner::StringCharacterWell::getLineNumber() const{
	return line_;
}

unsigned int StructuredScript::Scanner::StringCharacterWell::getStartIndex() const{
	return start_;
}

unsigned int StructuredScript::Scanner::StringCharacterWell::getEndIndex() const{
	return end_;
}

std::string StructuredScript::Scanner::StringCharacterWell::getOffset() const{
	return ("line " + std::to_string(line_) + ", character " + std::to_string(start_));
}
