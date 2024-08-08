#ifndef __BASE_H__
#define __BASE_H__

#include <vector>
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <execution>


#define DEFAULT_OBS_LENGTH (100)
#define DEFAULT_SIZE_INCREMENT (100)

namespace Jlib{
	namespace Base{
		template <class T>
		int LowerBound(const std::vector<T> &list, const int length, const T target){
		  int start = 0;
		  int end = length;
		  int mid = 0;
		  while (start < end){
		    mid = (start + end)/2;
		    if (list[mid] > target) end = mid;
		    else start = mid + 1;
		  }
		  return start; 
		}
	}
}
#endif
