#ifndef __STATISTICS_H__
#define __STATISTICS_H__

#include "Observable.h"
#include "Base.h"

namespace Jlib{

	template <class T>
	class Statistics{
		public:
			static double mean(const Observable<T>& obs);
			static double second_moment(const Observable<T>& obs, bool raw = true);
			static double fourth_moment(const Observable<T>& obs, bool raw = true);
			static double binder_cumulant(const Observable<T>& obs);
	};

	template <class T>
	double Statistics<T>::mean(const Observable<T>& obs){
		const auto& data = obs.get_obs();
		//return std::accumulate(data.begin(), data.end(), 0.0)/data.size();
    return std::reduce(std::execution::par,data.begin(), data.end(), 0.0)/data.size();

	}

	template <class T>
	double Statistics<T>::second_moment(const Observable<T>& obs, bool raw){
		const auto& data = obs.get_obs();
    const double result_raw = std::reduce(data.begin(), data.end(), 0.0, 
      [](double accum, T value) { return accum + value * value; }
    )/data.size();

		if (raw) return result_raw; // Sample variance
		else{
			const double mean = Statistics<T>::mean(obs);
			return result_raw - mean*mean;
		}
	}

	template <class T>
	double Statistics<T>::fourth_moment(const Observable<T>& obs, bool raw){
		const auto& data = obs.get_obs();
    const double result_raw = std::reduce(data.begin(), data.end(), 0.0, 
      [](double accum, T value) { return accum + value*value*value*value; }
    )/data.size();

		if (raw) return result_raw; // Sample variance
		else{
			// Calculate raw second moment
			const double second_raw = Statistics<T>::second_moment(obs);
			return result_raw - 3.0*second_raw*second_raw;
		}
	}

	template <class T>
	double Statistics<T>::binder_cumulant(const Observable<T>& obs){
		const double second = Statistics<T>::second_moment(obs);
		const double fourth = Statistics<T>::fourth_moment(obs);
		return 1.0-fourth/(3.0*second*second);
	}

}
#endif
