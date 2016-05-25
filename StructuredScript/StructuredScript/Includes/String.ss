class String{
	String(const ref val string value = "")
		: value_(value){}

	bool operator bool(){
		return !value_.empty();
	}

	string operator string(){
		return value_;
	}

	char At(integral_type index){
		return value_.at(index);
	}

	ref String Append(const ref val string value){
		value_.append(value);
		return self;
	}

	ref String Insert(integral_type index, const ref val string value){
		value_.insert(index, value);
		return self;
	}

	ref String Erase(integral_type index, integral_type count = string::npos){
		value_.erase(index, count);
		return self;
	}

	void Clear(){
		value_.clear();
	}

	String Substr(integral_type index, integral_type count = string::npos){
		return new String(value_.substr(index, count));
	}

	unsigned int Find(const ref val string value, integral_type offset = 0){
		return value_.find(value, offset);
	}

	unsigned int FindLast(const ref val string value, integral_type offset = 0){
		return value_.find_last(value, offset);
	}

	bool Empty(){
		return value_.empty();
	}

	private string value_;
}

//require_once("String.ss")

any s=new String("ben");
echo s;
echo s.Append("braide");