#include "statistic-functor.hpp"

#include <limits>
#include <algorithm>
#include <iostream>
#include <boost/io/ios_state.hpp>
#include <iomanip>

dergunov::B6::StatisticFunctor::StatisticFunctor():
  max_(std::numeric_limits<int>::min()),
  min_(std::numeric_limits<int>::max()),
  countOfPositive_(0),
  countOfNegative_(0),
  countOfNumbers_(0),
  oddSum_(0),
  evenSum_(0),
  first_(0),
  last_(0)
{}

void dergunov::B6::StatisticFunctor::operator()(int value)
{
  max_ = std::max(max_, value);
  min_ = std::min(min_, value);
  if (value != 0) {
    value > 0 ? countOfPositive_++ : countOfNegative_++;
  }
  if (value % 2 != 0) {
    oddSum_ += value;
  } else {
    evenSum_ += value;
  }
  if (countOfNumbers_++ == 0) {
    first_ = value;
  }
  last_ = value;
}

std::ostream &dergunov::B6::operator<<(std::ostream &out, const dergunov::B6::StatisticFunctor &state)
{
  boost::io::ios_flags_saver ofs(out);
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  if (state.countOfNumbers_ == 0) {
    out << "No Data" << "\n";
    return out;
  }
  out.setf(std::ios_base::boolalpha);
  double mean = static_cast<double>(state.evenSum_ + state.oddSum_) / static_cast<double>(state.countOfNumbers_);
  bool firstLastEqual = state.first_ == state.last_;

  out << "Max: " << state.max_ << "\n"
      << "Min: " << state.min_ << "\n"
      << "Mean: " << std::setprecision(1) << std::fixed << mean << "\n"
      << "Positive: " << state.countOfPositive_ << "\n"
      << "Negative: " << state.countOfNegative_ << "\n"
      << "Odd Sum: " << state.oddSum_ << "\n"
      << "Even Sum: " << state.evenSum_ << "\n"
      << "First/Last Equal: " << (firstLastEqual ? "yes" : "no");
  return out;
}
