#ifndef B2_QUEUE_WITH_PRIORITY_HPP
#define B2_QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <memory>
#include <string>
#include <map>

namespace details
{

  enum class ElementPriority
  {
    HIGH,
    NORMAL,
    LOW
  };

  template<typename T>
  class QueueWithPriority
  {
  public:
    QueueWithPriority() =default;
    QueueWithPriority(QueueWithPriority const & copyQueueWithPriority) = default;
    QueueWithPriority(QueueWithPriority && moveQueueWithPriority) noexcept = default;
    ~QueueWithPriority() = default;

    QueueWithPriority & operator=(QueueWithPriority const & copyQueueWithPriority) = default;
    QueueWithPriority & operator=(QueueWithPriority && moveQueueWithPriority) noexcept = default;

    void push(T const & newElement, ElementPriority priority);
    void accelerate();
    bool empty() const;
    void pop();
    T top();

  private:
    std::map<ElementPriority, std::list<T>> queue_;
  };

  template<typename T>
  void QueueWithPriority<T>::push(T const & newElement, ElementPriority priority)
  {
    queue_[priority].push_front(newElement);
  }

  template<typename T>
  void QueueWithPriority<T>::accelerate()
  {
    queue_[ElementPriority::HIGH].splice(queue_[ElementPriority::HIGH].begin(), queue_[ElementPriority::LOW]);
  }

  template<typename T>
  bool QueueWithPriority<T>::empty() const
  {
    for (auto queueOnePriority = queue_.begin(); queueOnePriority != queue_.end();
         queueOnePriority++) {
      if (!queueOnePriority->second.empty()) {
        return false;
      }
    }
    return true;
  }

  template<typename T>
  void QueueWithPriority<T>::pop()
  {
    if (empty()) {
      return;
    }

    for (auto queueOnePriority = queue_.begin(); queueOnePriority != queue_.end();
         queueOnePriority++) {
      if (!queueOnePriority->second.empty()) {
        queueOnePriority->second.pop_back();
        return;
      }
    }
  }

  template<typename T>
  T QueueWithPriority<T>::top()
  {
    if (empty()) {
      throw std::runtime_error("Error, attempt get element from empty queue!");
    }

    for (auto queueOnePriority = queue_.begin(); queueOnePriority != queue_.end();
         queueOnePriority++) {
      if (!queueOnePriority->second.empty()) {
        return queueOnePriority->second.back();
      }
    }

    return nullptr;
  }


}
#endif
