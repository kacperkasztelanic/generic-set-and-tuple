#ifndef MYSET_H_
#define MYSET_H_

#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace zmpo
{
	template<typename T>
	class MySet
	{
		private:
			static const size_t DEFAULT_INITIAL_CAPACITY = 10;
			size_t m_capacity;
			size_t m_size;
			T** arr;

			bool checkOutOfBounds(unsigned int index) const
			{
				if (index < 0 || index >= m_capacity)
					throw std::out_of_range("Invalid index.");
				return true;
			}

			void ensureCapacity()
			{
				if (m_size >= m_capacity)
				{
					m_capacity *= 2;
					T** newArr = new T*[m_capacity];
					std::copy(arr, arr + m_size, newArr);
					delete arr;
					arr = newArr;
				}
			}

			int indexOf(T elem) const
			{
				int index = -1;
				for (unsigned int i = 0; i < m_size && index == -1; i++)
					if ((*arr[i]) == elem)
						index = i;
				return index;
			}

		public:
			MySet(size_t capacity = DEFAULT_INITIAL_CAPACITY) :
					m_capacity(capacity), m_size(0), arr(new T*[capacity])
			{
			}

			MySet(const MySet &obj) :
					m_capacity(obj.m_capacity), m_size(obj.m_size), arr(new T*[obj.m_capacity])
			{
				for (size_t i = 0; i < obj.m_size; i++)
					arr[i] = new T(*obj.arr[i]);
			}

			~MySet()
			{
				clear();
			}

			void clear()
			{
				for (unsigned int i = 0; i < m_size; i++)
					delete arr[i];
				m_size = 0;
			}

			bool add(T elem)
			{
				if (!contains(elem))
				{
					ensureCapacity();
					arr[m_size++] = new T(elem);
					return true;
				}
				return false;
			}

			bool add(int index, T elem)
			{
				checkOutOfBounds(index);
				if (!contains(elem))
				{
					ensureCapacity();
					arr[index] = new T(elem);
					m_size++;
					return true;
				}
				return false;
			}

			void addAll(const MySet &other)
			{
				for (unsigned int i = 0; i < other.length(); i++)
					this->add(*other.arr[i]);
			}

			bool set(int index, T elem)
			{
				checkOutOfBounds(index);
				if (!contains(elem))
				{
					delete arr[index];
					arr[index] = new T(elem);
					return true;
				}
				return false;
			}

			bool remove(T elem)
			{
				int index = indexOf(elem);
				if (index == -1)
					return false;
				return removeAt(index);
			}

			bool removeAt(int index)
			{
				checkOutOfBounds(index);
				delete arr[index];
				std::copy(arr + index + 1, arr + m_size, arr + index);
				m_size--;
				return true;
			}

			bool contains(T elem) const
			{
				return indexOf(elem) != -1;
			}

			T& get(int index) const
			{
				checkOutOfBounds(index);
				return *arr[index];
			}

			size_t length() const
			{
				return m_size;
			}

			size_t capacity() const
			{
				return m_capacity;
			}

			bool isEmpty() const
			{
				return m_size == 0;
			}

			std::string toString() const
			{
				std::stringstream ss;
				ss << '{';
				for (unsigned int i = 0; i < m_size; i++)
				{
					ss << (*arr[i]);
					if (i != m_size - 1)
						ss << ", ";
				}
				ss << '}';
				return ss.str();
			}

			friend std::ostream &operator<<(std::ostream &out, const MySet &x)
			{
				out << x.toString();
				return out;
			}

			MySet operator+(const MySet& other)
			{
				MySet result;
				for (size_t i = 0; i < m_size; i++)
					result.add(*arr[i]);
				for (size_t i = 0; i < other.length(); i++)
					result.add(*other.arr[i]);
				return result;
			}

			MySet& operator+=(const MySet& other)
			{
				addAll(other);
				return *this;
			}

			MySet operator+(T elem)
			{
				MySet result;
				for (size_t i = 0; i < m_size; i++)
					result.add(*arr[i]);
				result.add(elem);
				return result;
			}

			MySet& operator+=(T elem)
			{
				add(elem);
				return *this;
			}

			MySet operator-(const MySet& other)
			{
				MySet result;
				for (size_t i = 0; i < m_size; i++)
					result.add(*arr[i]);
				for (size_t i = 0; i < other.length(); i++)
					result.remove(*other.arr[i]);
				return result;
			}

			MySet& operator-=(const MySet& other)
			{
				for (size_t i = 0; i < other.length(); i++)
					remove(*other.arr[i]);
				return *this;
			}

			MySet operator-(T elem)
			{
				MySet result;
				for (size_t i = 0; i < m_size; i++)
					result.add(*arr[i]);
				result.remove(elem);
				return result;
			}

			MySet& operator-=(T elem)
			{
				remove(elem);
				return *this;
			}

			const MySet& operator=(const MySet &obj)
			{
				if (this != &obj)
				{
					this->clear();
					this->arr = new T*[obj.length()];
					m_capacity = obj.capacity();
					for (size_t i = 0; i < obj.length(); i++)
						add(*obj.arr[i]);
				}
				return *this;
			}

			bool equals(const MySet &other) const
			{
				if (length() != other.length())
					return false;
				for (size_t i = 0; i < m_size; i++)
					if (!contains(*other.arr[i]))
						return false;
				return true;
			}

			bool operator==(const MySet &other) const
			{
				return equals(other);
			}

			bool operator!=(const MySet &other) const
			{
				return !equals(other);
			}

			const T& operator[](const int index) const
			{
				return get(index);
			}

			void sort(bool (*compareFunction)(T*, T*))
			{
				std::sort(arr, arr + m_size, compareFunction);
			}
	};
}

#endif
