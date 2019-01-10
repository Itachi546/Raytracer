#ifndef ALGEBRA_OPERATION_H
#define ALGEBRA_OPERATION_H

#include "vec.h"
#include "mat.h"
#include <math.h>

namespace Math
{

    template <std::size_t n, typename T>
    inline T lengthSquared(const vector<n, T>& vec)
    {
        T result = {};
        for(std::size_t  i = 0; i < n; ++i)
            result += vec[i] * vec[i];
        return result;
    }

    template <std::size_t n, typename T>
    inline T length(const vector<n, T>& vec)
    {
        T result = {};
        for(std::size_t  i = 0; i < n; ++i)
            result += vec[i] * vec[i];
        return sqrt(result);
    }

    template <std::size_t n, typename T>
    inline float distance(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
        return length(lhs - rhs);
    }
    template <std::size_t n, typename T>
    inline float distanceSquared(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
        return lengthSquared(lhs - rhs);
    }

    template <std::size_t n, typename T>
    inline vector<n, T> normalize(const vector<n, T>& vec)
    {
        vector<n, T> result;
        T len = length(vec);
        for(std::size_t  i = 0; i < n; ++i)
            result[i] = vec[i] / len;
        return result;
    }

    template <std::size_t  n, typename T>
    inline T dot(const vector<n, T>& lhs, const vector<n, T>& rhs)
    {
        T result = {};
        for(std::size_t i = 0; i < n; ++i)
            result += lhs[i] * rhs[i];
        return result;
    }

    template<typename T>
    inline vector<3, T> cross(const vector<3, T>& lhs, const vector<3, T>& rhs)
    {
        vector<3, T> result;

        result.x = lhs.y*rhs.z - lhs.z*rhs.y;
        result.y = lhs.z*rhs.x - lhs.x*rhs.z;
        result.z = lhs.x*rhs.y - lhs.y*rhs.x;

        return result;
    }

    template<typename T>
      inline vector<3, T> reflect(const vector<3, T>& v, const vector<3, T>& normal){
      //2B * N = V + N
      //@Note V is assumed to be inward and calculated
      //Both are normalized vector(unit vector)
      return v - 2 * dot(v, normal) * normal;
    }

    template <unsigned int m, unsigned int n, typename T>
    inline matrix<m, n, T> transpose(const matrix<m, n, T>& mat)
    {
        matrix<n, m, T> result;
 
        for (std::size_t col = 0; col < m; ++col)
        {
            for (std::size_t row = 0; row < n; ++row)
            {
                result[col][row] = mat[row][col];
            }
        }
        return result;
    }

    template <std::size_t  m, std::size_t  n, typename T>
    inline matrix<m, n, T> inverse(const matrix<m, n, T>& mat)
    {
      matrix<m, n, T> result;
      assert(0);
      return result;
    }
}
#endif
