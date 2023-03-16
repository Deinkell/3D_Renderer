#pragma once

struct Index
{
public: 
	int _0, _1, _2;	

public:
	Index() = default;
	constexpr Index(const int& _ref1, const int& _ref2, const int& _ref3)
	: _0(_ref1), _1(_ref2), _2(_ref3){};
	Index(int&& _ref1, int&& _ref2, int&& _ref3, bool&& _CheckingCalc)
	: _0(std::move(_ref1)), _1(std::move(_ref2)), _2(std::move(_ref3)) {};
	~Index() = default;

public:
	template<typename T> requires std::is_same<Index, T>::value
	FORCEINLINE constexpr T operator= (T&& _ref)
	{
		if(this == &_ref)
			return *this;

		_0 = std::forward<float>(_ref._0);
		_1 = std::forward<float>(_ref._1);
		_2 = std::forward<float>(_ref._2);

		return *this;
	}
};

