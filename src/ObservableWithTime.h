#ifndef __OBSERVABLE_WITH_TIME_H__
#define __OBSERVABLE_WITH_TIME_H__
#include "Observable.h"

namespace Jlib{

	template <class T>
	class ObservableWithTime : public Observable<T>{
		private:
			std::vector<double> m_timeList;
		
		public:
			ObservableWithTime();
			ObservableWithTime(unsigned int maxLength);
			virtual ~ObservableWithTime() final;
			void append(double time, T val);
			virtual void extend(unsigned int length);
			void print() const;
	};

	template <class T>
	ObservableWithTime<T>::ObservableWithTime(){
		m_timeList.reserve(this->m_maxLength);
		this->m_obsList.reserve(this->m_maxLength);
	};

	template <class T>
	ObservableWithTime<T>::ObservableWithTime(unsigned int maxLength){
		m_timeList.reserve(this->m_maxLength);
		this->m_obsList.reserve(this->m_maxLength);
	};

	template <class T>
	ObservableWithTime<T>::~ObservableWithTime(){
		std::vector<double>().swap(m_timeList);
		std::vector<T>().swap(this->m_obsList);
	};

	template <class T>
	void ObservableWithTime<T>::append(double time, T val){
		m_timeList.emplace_back(time);
		this->m_obsList.emplace_back(val);
		++(this->m_numElem);
	};

	template <class T>
	void ObservableWithTime<T>::extend(unsigned int length){
		this->m_maxLength += length;
		m_timeList.reserve(this->m_maxLength);
		this->m_obsList.reserve(this->m_maxLength);
	};

	template <class T>
	void ObservableWithTime<T>::print() const {
		for (unsigned int i=0;i<(this->m_numElem);++i)
			std::cout << this->m_timeList[i] << " " << this->m_obsList[i] << "\n";
	};

}

#endif
