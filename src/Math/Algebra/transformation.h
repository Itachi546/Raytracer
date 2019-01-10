#ifndef ALGEBRA_TRANSFORMATION_H
#define ALGEBRA_TRANSFORMATION_H

#include <assert.h>
#include <math.h>
#include "operation.h"
namespace Math
{

    template <std::size_t n, typename T>
    matrix<n, n, T> scale(const vector<n, T>& scale)
    {
        matrix<n, n, T> mat;
		for (std::size_t i = 0; i < n; ++i) {
			mat[i][i] = scale[i];
		}
        return mat;
    }

    template <std::size_t n, typename T>
    matrix<n, n, T>& scale(matrix<n, n, T>& result, const vector<n, T>& scale)
    {

		for (std::size_t i = 0; i < n; ++i) {
			result[i][i] *= scale[i];
		}
        return result;
    }

    template <typename T>
    matrix<4, 4, T> scale(const vector<3, T>& scale)
    {
        matrix<4, 4, T> mat;
		for (std::size_t i = 0; i < 3; ++i) {
			mat[i][i] = scale[i];
		}
        return mat;
    }

    template <typename T>
    matrix<4, 4, T>& scale(matrix<4, 4, T>& result, vector<3, T>& scale)
    {
		for (std::size_t i = 0; i < 3; ++i) {
			result[i][i] *= scale[i];
		}
        return result;
    }

    template <typename T>
      matrix<4, 4, T> rotate( const T& angle, const vector<3, T>& axis)
    {
        matrix<4, 4, T> result;
	vec3 norm_axis = normalize(axis);
        const float c = cos(angle);
        const float s = sin(angle);
        const float t = 1.0f - c;

        result[0][0] = t*norm_axis.x*norm_axis.x + c;
        result[0][1] = t*norm_axis.x*norm_axis.y + s*norm_axis.z;
        result[0][2] = t*norm_axis.x*norm_axis.z - s*norm_axis.y;

        result[1][0] = t*norm_axis.x*norm_axis.y - s*norm_axis.z;
        result[1][1] = t*norm_axis.y*norm_axis.y + c;
        result[1][2] = t*norm_axis.y*norm_axis.z + s*norm_axis.x;

        result[2][0] = t*norm_axis.x*norm_axis.z + s*norm_axis.y;
        result[2][1] = t*norm_axis.y*norm_axis.z - s*norm_axis.x;
        result[2][2] = t*norm_axis.z*norm_axis.z + c;

        return result;
    }
   
    template <typename T>
      matrix<4, 4, T>& rotate(matrix<4, 4, T> &result,  const T& angle, const vector<3, T>& axis)
    {
      matrix<4, 4, T> rot = rotate(angle, axis);
      result = result * rot;
      return result;
    }



    template <typename T>
    matrix<4, 4, T> translate(const vector<3, T>& translation)
    {
        matrix<4, 4, T> mat;
        mat[3] = vector<4, T>(translation, 1.0);
        return mat;
    }

    template <typename T>
    matrix<4, 4, T>& translate(matrix<4, 4, T> &result, const vector<3, T>& translation)
    {
        matrix<4, 4, T> mat;
        mat[3] = vector<4, T>(translation, 1.0);

        result = result * mat;
        return result;
    }

    template <typename T>
    matrix<4, 4, T> lookAt(const vector<3, T>& position, const vector<3, T>& target, const vector<3, T>& worldUp)
    {
        matrix<4, 4, T> frame;
        matrix<4, 4, T> translate;

        vec3 forward = normalize(target - position);
        vec3 right   = normalize(cross(forward, worldUp));
        vec3 up      = cross(right, forward);

        frame[0].xyz = right;
        frame[1].xyz = up;

        frame[2].xyz = -forward; 

        frame = transpose(frame);

        translate[3].xyz = -position;

        return frame*translate;
    }


    template <typename T>
    matrix<4, 4, T> ortho(T left, T right, T top, T bottom, T near_plane, T far_plane)
    {
        matrix<4, 4, T> result;

        result[0][0] = 2.0f / (right - left);
        
        result[1][1] = 2.0f / (top - bottom);

        result[2][2] = -2.0f / (far_plane - near_plane);

        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        result[3][2] = -(far_plane + near_plane) / (far_plane - near_plane);
        result[3][3] = 1.0f;

        return result;
    }

    template <typename T>
    matrix<4, 4, T> perspective(T fov, T aspect, T near_plane, T far_plane)
    {
        matrix<4, 4, T> result;
	float d = 1.0f/ tan(fov/2.0f);
	float invDenom = 1.0f / (near_plane - far_plane);

	result[0][0] = d /aspect;
	result[1][1] = d;

	result[2][2] = (near_plane * far_plane) * invDenom;
	result[2][3] = -1.0f;

	result[3][2] = (2 * near_plane * far_plane) * invDenom;
	result[3][3] = 0.0f;
        return result;
    }
} 
#endif
