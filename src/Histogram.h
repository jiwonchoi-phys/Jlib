#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__
#include "Observable.h"
#include "Base.h"

namespace Jlib{

	template <class T>
	class Histogram1d{
		private:
			std::vector<T> m_bin;
			std::vector<unsigned long long> m_occ;
			unsigned int m_numBin;
			T m_binMin;
			T m_binMax;
			T m_binInc;
		public:
			Histogram1d(T binMin, T binMax, T binInc);
			Histogram1d(T binMin, T binMax, T binInc, const Observable<T>& obs);
			~Histogram1d();

			inline void append(const T val);
			inline void append(const Observable<T>& obs);
			void print();
	};

	template <class T>
	Histogram1d<T>::Histogram1d(T binMin, T binMax, T binInc) : m_binMin(binMin), m_binMax(binMax), m_binInc(binInc) {
		// Number of bins
		m_numBin = (m_binMax - m_binMin)/m_binInc;
		// Initialize bin and occ
		m_bin.resize(m_numBin);
		m_occ.resize(m_numBin);
		for (unsigned int i=0;i<m_numBin;++i){
			m_bin[i] = m_binMin + i*m_binInc;
			m_occ[i] = 0;
		}
	};

	template <class T>
	Histogram1d<T>::Histogram1d(T binMin, T binMax, T binInc, const Observable<T>& obs) : m_binMin(binMin), m_binMax(binMax), m_binInc(binInc) {
		// Number of bins
		m_numBin = (m_binMax - m_binMin)/m_binInc;
		// Initialize bin and occ
		m_bin.resize(m_numBin);
		m_occ.resize(m_numBin);
		for (unsigned int i=0;i<m_numBin;++i){
			m_bin[i] = m_binMin + i*m_binInc;
			m_occ[i] = 0;
		}
		// Append data
		const auto& data = obs.get_obs();
		for (unsigned int i=0; i<data.size(); ++i) ++m_occ[Base::LowerBound(m_bin, m_numBin, data[i])];
	};


	template <class T>
	Histogram1d<T>::~Histogram1d() {
		std::vector<T>().swap(m_bin);
		std::vector<unsigned long long>().swap(m_occ);
	}

	template <class T>
	inline void Histogram1d<T>::append(const T val){ ++m_occ[Base::LowerBound(m_bin, m_numBin, val)]; }

	template <class T>
	inline void Histogram1d<T>::append(const Observable<T>& obs){
		const auto& data = obs.get_obs();
		for (unsigned int i=0; i<data.size(); ++i) ++m_occ[Base::LowerBound(m_bin, m_numBin, data[i])];
	}

	template <class T>
	void Histogram1d<T>::print(){
		for (unsigned int i=0;i<m_numBin;++i) std::cout << m_bin[i] << " " << m_occ[i] << "\n";
	}

}

#endif
