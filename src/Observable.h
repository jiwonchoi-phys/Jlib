#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include "Base.h"

namespace Jlib{

	template <class T>
	class Observable{
		protected:
			std::vector<T> m_obsList;
			int m_maxLength;
			unsigned int m_numElem;
		
		public:
			Observable();
			Observable(unsigned int maxLength);
			virtual ~Observable();
			inline void set_length(unsigned int maxLength);
			inline unsigned int get_length() const;
			inline void append(T val);
			virtual void extend(unsigned int length);
			inline T getElement(int idx) const;

			const std::vector<T>& get_obs() const;

			void print() const;


			// Operator overloading

  		friend Observable<T> operator+(const Observable<T>& A, const Observable<T>& B) {
				if (A.get_length() != B.get_length()) throw std::invalid_argument("Two observables should have same length of vector.");
				unsigned int newLength = A.get_length();
				Observable<T> result(newLength);
				for(unsigned int i = 0; i < newLength; ++i) result.append(A.m_obsList[i] + B.m_obsList[i]);
				return result;
  		}

  		friend Observable<T> operator*(const Observable<T>& A, const Observable<T>& B) {
				if (A.get_length() != B.get_length()) throw std::invalid_argument("Two observables should have same length of vector.");
				unsigned int newLength = A.get_length();
				Observable<T> result(newLength);
				for(unsigned int i = 0; i < newLength; ++i) result.append(A.m_obsList[i] * B.m_obsList[i]);
				return result;
  		}
	
	};

	template <class T>
	Observable<T>::Observable() : m_maxLength(DEFAULT_OBS_LENGTH), m_numElem(0) {
		m_obsList.reserve(m_maxLength);
	};

	template <class T>
	Observable<T>::Observable(unsigned int maxLength) : m_maxLength(maxLength), m_numElem(0){
		m_obsList.reserve(m_maxLength);
	};

	template <class T>
	Observable<T>::~Observable(){ std::vector<T>().swap(m_obsList); };

	template <class T>
	void Observable<T>::set_length(unsigned int maxLength) { m_maxLength = maxLength; };

	template <class T>
	unsigned int Observable<T>::get_length() const { return m_numElem; };


	template <class T>
	void Observable<T>::append(T val) {
		m_obsList.emplace_back(val);
		++m_numElem;
	};

	template <class T>
	void Observable<T>::extend(unsigned int length) {
		m_maxLength += length;
		m_obsList.reserve(m_maxLength);
	};


	template <class T>
	const std::vector<T>& Observable<T>::get_obs() const { return m_obsList; };

	template <class T>
	T Observable<T>::getElement(int idx) const { return m_obsList[idx]; };

	template <class T>
	void Observable<T>::print() const {
		for (unsigned int i=0;i<m_numElem;++i) std::cout << m_obsList[i] << "\n";
	};





  // Operator overloading for addition
	



}



#endif
