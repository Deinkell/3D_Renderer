#pragma once

struct Index
{
public: 
	int _0, _1, _2;

public:
	Index() = default;
	FORCEINLINE constexpr Index(const float& _ref1, const float& _ref2, const float& _ref3)
	: _0(_ref1), _1(_ref2), _2(_ref2) {};
	FORCEINLINE Index(float&& _ref1, float&& _ref2, float&& _ref3)
	: _0(std::move(_ref1)), _1(std::move(_ref2)), _2(std::move(_ref2)) {};
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

