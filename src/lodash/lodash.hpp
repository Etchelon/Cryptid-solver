#pragma once

#include <algorithm>
#include <exception>
#include <string>
#include <vector>

namespace ld {
	template<typename T, typename Predicate>
	auto find(std::vector<T>& vec, Predicate pred) -> T& {
		auto it = std::find_if(vec.begin(), vec.end(), pred);
		if (it == vec.end()) {
			throw std::runtime_error{ "Element not found" };
		}
		return *it;
	}

	template<typename T, typename Predicate>
	auto constFind(const std::vector<T>& vec, Predicate pred) -> const T& {
		auto it = std::find_if(vec.cbegin(), vec.cend(), pred);
		if (it == vec.cend()) {
			throw std::runtime_error{ "Element not found" };
		}
		return *it;
	}

	template<typename T, typename Action>
	auto each(std::vector<T>& vec, Action action) -> void {
		std::for_each(vec.begin(), vec.end(), action);
	}

	template<typename T, typename Action>
	auto constEach(const std::vector<T>& vec, Action action) -> void {
		std::for_each(vec.cbegin(), vec.cend(), action);
	}

	template<typename T, typename Predicate>
	auto every(const std::vector<T>& vec, Predicate pred) -> bool {
		return std::all_of(vec.cbegin(), vec.cend(), pred);
	}

	template<typename TIn, typename TOut, typename Mapper>
	auto map(const std::vector<TIn>& vec, Mapper mapper) -> std::vector<TOut> {
		auto ret = std::vector<TOut>{};
		ret.reserve(vec.size());
		std::transform(vec.begin(), vec.end(), std::back_inserter(ret), mapper);
		return ret;
	}
}	// namespace ld