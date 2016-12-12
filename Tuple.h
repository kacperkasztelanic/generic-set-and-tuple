#ifndef TUPLE_H_
#define TUPLE_H_

#include <sstream>

namespace zmpo
{
	template<typename K, typename V>
	class Tuple
	{
		private:
			K a;
			V b;

		public:
			Tuple(K a, V b) :
					a(a), b(b)
			{
			}

			virtual ~Tuple()
			{
			}

			K getA()
			{
				return a;
			}

			V getB()
			{
				return b;
			}

			void setA(K a)
			{
				this->a = a;
			}

			void setB(V b)
			{
				this->b = b;
			}

			std::string toString() const
			{
				std::stringstream ss;
				ss << '(' << a << ", " << b << ')';
				return ss.str();
			}

			friend std::ostream &operator<<(std::ostream &out, const Tuple &x)
			{
				out << x.toString();
				return out;
			}

			bool equals(const Tuple &other) const
			{
				return this->a == other.a && this->b == other.b;
			}

			bool operator==(const Tuple &other) const
			{
				return equals(other);
			}

			bool operator!=(const Tuple &other) const
			{
				return !equals(other);
			}
	};
}

#endif
