#pragma once

#include <algorithm>
#include <exception>
#include <optional>
#include <string>
#include <vector>

namespace ld {
	template<typename T>
	using Nullable = std::optional<T>;

	template<typename T>
	using Ref = std::reference_wrapper<T>;

	template<typename T>
	using NullableRef = Nullable<Ref<T>>;

	template<typename T>
	auto get(const NullableRef<T>& ref) -> T& {
		if (!ref.has_value()) {
			throw std::runtime_error{ "ref is null" };
		}
		return ref.value().get();
	}

	template<typename T, typename Predicate>
	auto firstOrDefault(const std::vector<T>& vec, Predicate pred) -> NullableRef<T> {
		auto it = std::find_if(vec.begin(), vec.end(), pred);
		if (it == vec.end()) {
			return std::nullopt;
		}
		return std::ref(const_cast<T&>(*it));
	}

	template<typename T, typename Predicate>
	auto firstOrDefault(std::vector<T>& vec, Predicate pred) -> NullableRef<T> {
		auto it = std::find_if(vec.begin(), vec.end(), pred);
		if (it == vec.end()) {
			return std::nullopt;
		}
		return std::ref(*it);
	}

	template<typename T, typename Predicate>
	auto first(std::vector<T>& vec, Predicate pred) -> T& {
		auto it = std::find_if(vec.begin(), vec.end(), pred);
		if (it == vec.end()) {
			throw std::runtime_error{ "Element not found" };
		}
		return *it;
	}

	template<typename T, typename Predicate>
	auto where(std::vector<T>& vec, Predicate pred) -> std::vector<Ref<T>> {
		auto ret = std::vector<Ref<T>>{};
		ret.reserve(vec.size());
		std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(ret), pred);
		return ret;
	}

	template<typename T, typename Action>
	auto each(const std::vector<T>& vec, Action action) -> void {
		std::for_each(vec.cbegin(), vec.cend(), action);
	}

	template<typename T, typename Action>
	auto each(std::vector<T>& vec, Action action) -> void {
		std::for_each(vec.begin(), vec.end(), action);
	}

	template<typename T, typename Predicate>
	auto every(const std::vector<T>& vec, Predicate pred) -> bool {
		return std::all_of(vec.cbegin(), vec.cend(), pred);
	}

	template<typename T, typename Predicate>
	auto any(const std::vector<T>& vec, Predicate pred) -> bool {
		return std::any_of(vec.cbegin(), vec.cend(), pred);
	}

	template<typename TOut, typename TIn, typename Mapper>
	auto map(const std::vector<TIn>& vec, Mapper mapper) -> std::vector<TOut> {
		auto ret = std::vector<TOut>{};
		ret.reserve(vec.size());
		std::transform(vec.begin(), vec.end(), std::back_inserter(ret), mapper);
		return ret;
	}
}	// namespace ld