#include <iostream>
#include <cassert>


namespace jl
{
	int pgcd(int a, int b)
	{
		while (b != 0)
		{
			const int t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
	

	class Fraction
	{
	public:
		Fraction(int numerator = 0, int denominator = 1)
			: m_numerator(numerator), m_denominator(denominator)
		{
			assert(m_denominator != 0);
			reduce();
		}

		Fraction(const Fraction& other)
			: m_numerator(other.m_numerator), m_denominator(other.m_denominator)
		{}

		Fraction(Fraction&& other)
			: m_numerator(std::move(m_numerator)), m_denominator(std::move(m_denominator))
		{}

		~Fraction() = default;


		// ----- Casts -----
		operator int() const
		{
			assert(m_denominator == 1);	// No implicit rounding
			return m_numerator;
		}

		// Force decimal
		operator double() const
		{	
			return (double)m_numerator / (double)m_denominator;
		}


		// ----- Getters -----
		int getNumerator() const { return m_numerator; }
		int getDenominator() const { return m_denominator; }


	private:
		void reduce()
		{
			const int divider = pgcd(m_numerator, m_denominator);
			m_numerator /= divider;
			m_denominator /= divider;
		}

		// ----- Printing -----
		friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
		void print(std::ostream& out) const
		{
			if (m_denominator == 1)	// Print as integer?
				out << m_numerator;
			else
				out << m_numerator << '/' << m_denominator;
		}
	
	private:
		int m_numerator, m_denominator;
	};

	std::ostream& operator<<(std::ostream& out, const Fraction& f)
	{
		f.print(out);
		return out;
	}
}


int main()
{
	jl::Fraction f(60, 20);
	std::cout << f << std::endl;
	std::cout << (double)f << std::endl;
	jl::Fraction f2(305);
	std::cout << f2 << std::endl;
	return 0;
}