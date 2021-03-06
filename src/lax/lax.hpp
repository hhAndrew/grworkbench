#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include <boost/static_assert.hpp>
#include "value.hpp"

namespace lax_interpreter
{

  template<typename T> class from_value;
  template<typename T> class to_value;

  class lax
  {
  public:

    explicit lax(const std::shared_ptr<const values::value>&);
    template<typename A> lax(const A& a) : _(to_value<A>()(a)) {}
    template <typename A> operator const A() const { return from_value<A>()(evaluated().value()); }

    const lax evaluated() const;
		const lax evaluated_at(const lax&) const;
		const lax operator()(const lax&) const;

		const bool is_call() const;

    void swap(lax&);

		const lax get_left() const;
		const lax get_right() const;

		template <class T> const std::shared_ptr<const T> dynamic_value() const
		{
			return dynamic_pointer_cast<const T>(_);
		}

		const std::shared_ptr<const values::value>& value() const;
    
  private:
		lax();
    std::shared_ptr<const values::value> _;
  };

  template<> class to_value<int>
  {
  public:
    const std::shared_ptr<const values::value> operator()(const int& i) const;
  };

  template<> class to_value<std::string>
  {
  public:
    const std::shared_ptr<const values::value> operator()(const std::string& i) const;
  };

  template<> class to_value<double>
  {
  public:
    const std::shared_ptr<const values::value> operator()(const double& i) const;
  };

  template<> class to_value<bool>
  {
  public:
    const std::shared_ptr<const values::value> operator()(const bool& i) const;
  };

  template<> class to_value<char>
  {
  public:
    const std::shared_ptr<const values::value> operator()(const char& i) const;
  };

  template<> class from_value<std::string>
  {
  public:
    const std::string operator()(const std::shared_ptr<const values::value>& p) const;
  };

  template<> class from_value<int>
  {
  public:
    const int operator()(const std::shared_ptr<const values::value>& p) const;
  };

  template<> class from_value<bool>
  {
  public:
    const bool operator()(const std::shared_ptr<const values::value>& p) const;
  };

  template<> class from_value<char>
  {
  public:
    const char operator()(const std::shared_ptr<const values::value>& p) const;
  };

  template<> class from_value<double>
  {
  public:
    const double operator()(const std::shared_ptr<const values::value>& p) const;
  };

  template<typename T> const bool is_lax(const lax&);

  template<> const bool is_lax<bool>(const lax&);
  template<> const bool is_lax<char>(const lax&);
  template<> const bool is_lax<int>(const lax&);
  template<> const bool is_lax<double>(const lax&);

  //template<typename A> const bool is_lax(const lax&)
  //{
  //  // no specialization exists for the type check
  //  BOOST_STATIC_ASSERT(false);
  //}

  std::ostream& operator<<(std::ostream&, const lax&);

  const bool operator==(const lax&, const lax&);
  const bool operator!=(const lax&, const lax&);

  const bool operator <(const lax&, const lax&);
  
	inline lax::lax(const std::shared_ptr<const values::value>& p)
		: _(p)
  {
  }
}
