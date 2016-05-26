class String{
	String(const ref val string value = "")
		: value_(value){}

	bool operator bool(){
		return !value_.empty();
	}

	string operator string(){
		return value_;
	}

	@[Call(String.Cast)]
	numeric_type operator typename numeric_type();

	ref String operator =(const ref val string value){
		value_ = value;
		return self;
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

	array Split(const ref val string delimiter){
		array split = [];
		any size = value_.length;

		if (!delimiter.empty()){
			any index = value_.find(delimiter), last = 0u;
			while (index < size){
				split[] = new String(value_.substr(last, index - last));
				last = index + 1;
				index = value_.find(delimiter, last);
			}

			split[] = new String(value_.substr(last));
		}
		else{
			for (unsigned int i = 0; i < size; ++i)
				split[] = value_.at(i);
		}

		return split;
	}

	any Node{
		@[Call(String.Node)]
		node_type get();
	}

	any Length{
		unsigned int get(){
			return value_.length;
		}
	}

	private string value_;
}

//require_once("String.ss")