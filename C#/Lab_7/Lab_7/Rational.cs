using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7
{
    public class Rational
    {
        private int numerator;
        private int denominator;

        public Rational(int numerator, int denominator)
        {
            if (numerator != 0)
            {
                this.numerator = numerator;
            }
            else
            {
                Console.WriteLine("Число равно нулю.");
            }           
            if (denominator != 0)
            {
                this.denominator = denominator;
            }
            else
            {
                throw new ArgumentException("Denominator can't be zero");
            }
        }

        public static implicit operator Rational(int x)
        {
            return new Rational(x, 1);
        }

        public static explicit operator int(Rational x)
        {
            return x.numerator / x.denominator;
        }

        public int Numerator
        {
            get
            {
                return numerator;
            }
            set
            {
                numerator = value;
            }
        }

        public int Denominator
        {
            get
            {
                return denominator;
            }
            set
            {
                denominator = value;
            }
        }
        
        public int getnumerator()
        {
            return numerator;
        }

        public int getdenominator()
        {
            return denominator;
        }

        public static Rational operator +(Rational r1, Rational r2)
        {
            int numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
            int denominator = r1.denominator * r2.denominator;
            return new Rational(numerator, denominator);
        }

        public static Rational operator -(Rational r1, Rational r2)
        {
            int numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
            int denominator = r1.denominator * r2.denominator;
            return new Rational(numerator, denominator);
        }

        public static Rational operator *(Rational r1, Rational r2)
        {
            int numerator = r1.numerator * r2.numerator;
            int denominator = r1.denominator * r2.denominator;
            return new Rational(numerator, denominator);
        }

        public static Rational operator ++(Rational r1)
        {
            return new Rational(r1.numerator + r1.denominator, r1.denominator);
        }

        public static Rational operator --(Rational r1)
        {
            return new Rational(r1.numerator - r1.denominator, r1.denominator);
        }

        

        public static Rational operator /(Rational r1, Rational r2)
        {
            int numerator = r1.numerator * r2.denominator;
            int denominator = r1.denominator * r2.numerator;
            return new Rational(numerator, denominator);
        }

        public static bool operator ==(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator == r2.numerator * r1.denominator;
        }

        public static bool operator !=(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator != r2.numerator * r1.denominator;
        }

        public static bool operator >(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator > r2.numerator * r1.denominator;
        }

        public static bool operator <(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator < r2.numerator * r1.denominator;
        }

        public static bool operator >=(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator >= r2.numerator * r1.denominator;
        }

        public static bool operator <=(Rational r1, Rational r2)
        {
            return r1.numerator * r2.denominator <= r2.numerator * r1.denominator;
        }
        

        public override string ToString()
        {
            return numerator + "/" + denominator;
        }

        //normalization
        public void Normalize()
        {
            int gcd = GCD(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;
        }

        static int GCD(int m, int h)
        {
            do
            {
                for (int i = m; i <= 1; i--)
                    if (m % i == 0 && h % i == 0)
                    {
                        int x = 0;
                        x = i;
                        return x;
                    }
            } while (true);
            return m;
        }


        public override bool Equals(object obj)
        {
            if (obj == null)
            {
                return false;
            }
            if (obj.GetType() != this.GetType())
            {
                return false;
            }
            Rational r = (Rational)obj;
            return this.numerator * r.denominator == r.numerator * this.denominator;
        }

        public override int GetHashCode()
        {
            return numerator * denominator;
        }
    }
}
