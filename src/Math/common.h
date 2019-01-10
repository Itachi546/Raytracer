#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include "Algebra/vec.h"

#include <algorithm>
#include <cmath>


namespace Math
{
  const float PI  = 3.14159265359f;
  const float TAU = 6.28318530717f;

  template <typename T>
    inline T lerp(const T& a, const T& b, const float t)
    {
      return (1.0f - t) * a + b * t;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> lerp(vector<n, T>& a, vector<n, T>& b, const float t)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = lerp(a[i], b[i], t);
      }
      return result;
    }

  template <typename T>
    inline T clamp(const T& val, const T& min, const T& max)
    {
      return std::max(min, std::min(val, max)); 
    }

  template <typename T>
    inline T clamp01(const T& val)
    {
      return clamp<T>(val, 0.0f, 1.0f);
    }

  template <std::size_t n, typename T>
    inline vector<n, T> clamp(const vector<n, T>& val, const T& min, const T& max)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = clamp(val[i], min, max);
      }
      return result;
    }

  template <std::size_t n, typename T>
    inline vector<n, T> clamp01(const vector<n, T>& val, const T& min, const T& max)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = clamp01(val[i], min, max);
      }
      return result;
    }


  template <typename T> 
    inline T range01(const T& x, const T& start, const T& end)
    {
      return clamp((x - start) / (end - start), 0.0f, 1.0f);
    }

  template <typename T>
    inline T smoothstep(const T& e0, const T& e1, const T& x)
    {
      T result;
      result = clamp01((x - e0) / (e1 - e0));
      result = result * result * (3.0f - 2.0f * result);
      return result;
    }

  template <typename T>
    inline T smootherstep(const T& e0, const T& e1, const T& x)
    {
      T result;
      result = clamp01((x - e0) / (e1 - e0));
      result = (result * result * result) * (result * (result * 6.0f - 15.0f) + 10.0f);
      return result;
    }

  template <std::size_t n, typename T>
    vector<n, T> abs(vector<n, T>& val)
    {
      vector<n, T> result;
      for (std::size_t i = 0; i < n; ++i) {
	result[i] = (T)std::abs(val[i]);
      }
      return result;
    }

  //Conversion function
  //Maybe need to move to seperate file

  inline float radian(float degrees)
  {
    return degrees / 180.0f * PI;
  }
  inline double radian(double degrees)
  {
    return degrees / 180.0 * PI;
  }

  inline float degree(float radians)
  {
    return radians / PI * 180.0f;
  }
  inline double degree(double radians)
  {
    return radians / PI * 180.0;
  }

}
#endif
