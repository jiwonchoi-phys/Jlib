#ifndef __STATISTICS_H__
#define __STATISTICS_H__

#include "Observable.h"
#include "Base.h"

namespace Jlib{
	namespace Statistics{
		template <class T>
		static double mean(const Observable<T>& obs);
		template <class T>
		static double second_moment(const Observable<T>& obs, bool raw = true);
		template <class T>
		static double fourth_moment(const Observable<T>& obs, bool raw = true);
		template <class T>
		static double binder_cumulant(const Observable<T>& obs);

		template <class T>
		double mean(const Observable<T>& obs){
			const auto& data = obs.get_obs();
			//return std::accumulate(data.begin(), data.end(), 0.0)/data.size();
	    return std::reduce(data.begin(), data.end(), 0.0)/data.size();
	
		}
	
		template <class T>
		double second_moment(const Observable<T>& obs, bool raw){
			const auto& data = obs.get_obs();
	    const double result_raw = std::transform_reduce(data.begin(), data.end(), 0.0, 
	      std::plus(), [](T value) { return value*value; }
	    )/data.size();
	
			if (raw) return result_raw; // Sample variance
			else{
				const double meanVal = mean(obs);
				return result_raw - meanVal*meanVal;
			}
		}
	
		template <class T>
		double fourth_moment(const Observable<T>& obs, bool raw){
			const auto& data = obs.get_obs();
	    const double result_raw = std::transform_reduce(data.begin(), data.end(), 0.0, 
	      std::plus(), [](T value) { return value*value*value*value; }
	    )/data.size();
	
			if (raw) return result_raw; // Sample variance
			else{
				// Calculate raw second moment
				const double second_raw = second_moment(obs);
				return result_raw - 3.0*second_raw*second_raw;
			}
		}
	
		template <class T>
		double binder_cumulant(const Observable<T>& obs){
			const double second = second_moment(obs);
			const double fourth = fourth_moment(obs);
			return 1.0-fourth/(3.0*second*second);
		}
	}
}
#endif
