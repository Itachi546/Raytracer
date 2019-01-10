#ifndef ALGEBRA_VEC_H
#define ALGEBRA_VEC_H

#include <initializer_list>
#include <assert.h>
#include <array>

//@Note need to update the const function specifier for most of the function
//@Note need to rewrite the perspective matrix

namespace Math
{
  template <std::size_t n, class T>
    struct vector
    {
    public:
      std::array<T, n> data;

      vector()
      {
      }

      vector(const T& v)
      {
	for (auto& el : data) {
	  el = v;
	}
      }

      vector(const std::initializer_list<T> args)
      {
	assert(args.size() < n);
	data = args;
      }


      T& operator[] (const std::size_t index)
      {
	assert(index >= 0 && index < n);
	return data.at(index);
      }

      const T& operator[] (const std::size_t index) const
      {
	assert(index >= 0 && index < n);
	return data.at(index);
      }

      vector<n, T> operator-() const;
    };

  template <typename T>
    struct vector<2, T>
    {
      union 
      {
	std::array<T, 2> data;

	struct 
	{
	  T x;
	  T y;
	};
	struct
	{
	  T u;
	  T v;
	};
      };

      
      vector()
        {
	  data = { };
        }
      
      vector(const T& v)
        {
	  data = { v, v };
        }
      
      vector(const std::initializer_list<T> args)
        {
	  assert(args.size() <= 2);
	  int index = 0;
	  for (auto begin = args.begin(); begin != args.end(); ++begin) {
	    data.at(index++) = *begin;
	  }
        }
      
      vector(const T& x, const T& y)
        {
	  data = { x, y };
        }


      T& operator[] (const std::size_t index)
        {
	  assert(index >= 0 && index < 2);
	  return data.at(index);
        }
      
      const T& operator[] (const std::size_t index) const
        {
	  assert(index >= 0 && index < 2);
	  return data.at(index);
        }

      vector<2, T> operator-() const;
    };

  template<typename T>
    struct vector<3, T>
    {
      union 
      {
	std::array<T, 3> data;
	// position
	struct
	{
	  T x;
	  T y;
	  T z;
	};
	// color
	struct
	{
	  T r;
	  T g;
	  T b;
	};
	struct
	{
	  vector<2, T> xy;
	};
      };


      static vector<3, T> UP;
      static vector<3, T> DOWN;
      static vector<3, T> LEFT;
      static vector<3, T> RIGHT;
      static vector<3, T> FORWARD;
      static vector<3, T> BACK;


      vector()
        {
	  data = {};
        }

      vector(const T& v)
        {
	  data = { v, v, v };
        }

      vector(const std::initializer_list<T> args)
        {
	  assert(args.size() <= 3);
	  int index = 0;
	  for (auto begin = args.begin(); begin != args.end(); ++begin) {
	    data.at(index++) = *begin;
	  }
        }

      vector(const T& x, const T& y, const T& z)
        {
	  data = { x, y, z };
        }

      vector(const vector<2, T>& vec, const T& z)
        {
	  data = { vec.x, vec.y, z };
        }

      vector(const T& x, const vector<2, T>& vec)
        {
	  data = { x, vec.x, vec.y };
        }
      vector(const vector<4, T>& vec)
	{
	  data = {vec.x, vec.y, vec.z};
	}
      T& operator[] (const std::size_t index)
        {
	  assert(index >= 0 && index < 3);
	  return data.at(index);
        }

      const T& operator[] (const std::size_t index) const
        {
	  assert(index >= 0 && index < 3);
	  return data.at(index);
        }

      vector<3, T> operator-() const;
    };


  template<typename T> vector<3, T> vector<3, T>::UP      = vector<3, T>( 0.0,  1.0,  0.0);
  template<typename T> vector<3, T> vector<3, T>::DOWN    = vector<3, T>( 0.0, -1.0,  0.0);
  template<typename T> vector<3, T> vector<3, T>::LEFT    = vector<3, T>(-1.0,  0.0,  0.0);
  template<typename T> vector<3, T> vector<3, T>::RIGHT   = vector<3, T>( 1.0,  0.0,  0.0);
  template<typename T> vector<3, T> vector<3, T>::FORWARD = vector<3, T>( 0.0,  0.0, -1.0);
  template<typename T> vector<3, T> vector<3, T>::BACK    = vector<3, T>( 0.0,  0.0,  1.0);

  template<typename T>
    struct vector<4, T>
    {
      union
      {
	std::array<T, 4> data;
	// position
	struct
	{
	  T x;
	  T y;
	  T z;
	  T w;
	};
	// color
	struct
	{
	  T r;
	  T g;
	  T b;
	  T a;
	};
	struct
	{
	  vector<2, T> xy;
	};
	struct
	{
	  vector<3, T> xyz;
	};
	struct
	{
	  vector<3, T> rgb;
	};
      };

      
      vector()
        {
	  data = { };
        }
      
      vector(const T& v)
        {
	  data = { v, v, v, v };
        }
      
      vector(const std::initializer_list<T> args)
        {
	  assert(args.size() <= 4);
	  int index = 0;
	  for (auto begin = args.begin(); begin != args.end(); ++begin) {
	    data.at(index++) = *begin;
	  }
        }
      
      vector(const T& x, const T& y, const T& z, const T& w)
        {
	  data = { x, y, z, w };
        }
      
      vector(const vector<2, T>& xy, const vector<2, T>& zw)
        {
	  data = { xy.x, xy.y, zw.z, zw.w };
        }
      
      vector(const vector<3, T>& xyz, const T& w)
        {
	  data = { xyz.x, xyz.y, xyz.z, w };
        }

      
      T& operator[] (const std::size_t index)
        {
	  assert(index >= 0 && index < 4);
	  return data.at(index);
        }     

      const T& operator[] (const std::size_t index) const 
        {
	  assert(index >= 0 && index < 4);
	  return data.at(index);
        }
      
        vector<4, T> operator-() const;
    };

  typedef vector<2, float>  vec2;
  typedef vector<3, float>  vec3;
  typedef vector<4, float>  vec4;
  typedef vector<2, int>    ivec2;
  typedef vector<3, int>    ivec3;
  typedef vector<4, int>    ivec4;
  typedef vector<2, double> dvec2;
  typedef vector<3, double> dvec3;
  typedef vector<4, double> dvec4;

  
  template <std::size_t n, typename T>
    inline vector<n, T> vector<n, T>::operator-() const
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = -data[i];
      }
      return result;
    }
  template <typename T>
    inline vector<2, T> vector<2, T>::operator-() const
    {
      return{ -x, -y };
    }
  template <typename T>
    inline vector<3, T> vector<3, T>::operator-() const 
    {
      return{ -x, -y, -z };
    }
  template <typename T>
    inline vector<4, T> vector<4, T>::operator-() const
    {
      return{ -x, -y, -z, -w };
    }


  template <std::size_t n, typename T>
    inline vector<n, T> operator+(const vector<n, T>& lhs, T scalar)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] + scalar;
      }
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator+(T scalar, const vector<n, T>& rhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i)
	result[i] = rhs[i] + scalar;
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator+(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i)
	result[i] = lhs[i] + rhs[i];
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator+=(vector<n, T>& lhs, const vector<n, T>& rhs)
    {
      for (std::size_t i = 0; i < n; ++i)
	lhs[i] = lhs[i] + rhs[i];
      return lhs;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator-(const vector<n, T>& lhs, T scalar)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] - scalar;
      }
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator-(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] - rhs[i];
      }
      return result;
    }


  template <std::size_t n, typename T>
    inline vector<n, T> operator*(const vector<n, T>& lhs, T scalar)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] * scalar;
      }
      return result;
    }

  template <std::size_t n, typename T>
    vector<n, T>& operator*=(vector<n, T>& lhs, T scalar)
    {
      for (std::size_t i = 0; i < n; ++i) {
	lhs[i] *= scalar;
      }
      return lhs;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator*(T scalar, const vector<n, T>& lhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] * scalar;
      }
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator*(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] * rhs[i];
      }
      return result;
    }


  template <std::size_t n, typename T>
    inline vector<n, T> operator/(const vector<n, T>& lhs, T scalar)
    {
      vector<n, T> result;
      for (unsigned int i = 0; i < n; ++i) {
	result[i] = lhs[i] / scalar;
      }
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> operator/(T scalar, const vector<n, T>& lhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] / scalar;
      }
      return result;
    }
  
  template <std::size_t n, typename T>
    inline vector<n, T> operator/(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lhs[i] / rhs[i];
      }
      return result;
    }
} 

#endif
