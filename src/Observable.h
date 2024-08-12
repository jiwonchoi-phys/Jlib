#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include "Base.h"

namespace Jlib{
	
	typedef std::vector< std::string > obsNames;

	class Observable{
		private:
			std::vector< std::vector<double> > m_obsList;
			std::map< std::string, int > m_obsMap;
			int m_maxLength;
			int m_numObs;
			
		
		public:
			Observable(obsNames obsName);
			Observable(obsNames obsName, int length);
			inline void append(std::string name, double val);
			void append(obsNames names, std::vector<double> vals);
			// Observable(unsigned int maxLength);
			// virtual ~Observable();
			// inline void set_length(unsigned int maxLength);
			// inline unsigned int get_length() const;
			// virtual void extend(unsigned int length);
			// inline T getElement(int idx) const;

			const std::map< std::string, int >& get_obsMap() const;
			const std::vector< std::vector<double> >& get_obs() const;
			const std::vector<double>& get_obs(int idx) const;
			const int get_numObs() const;
			const int get_numElem() const;
			std::string get_obsName(const int idx);

			void print() const;


			// Operator overloading

  		// friend Observable<T> operator+(const Observable<T>& A, const Observable<T>& B) {
			// 	if (A.get_length() != B.get_length()) throw std::invalid_argument("Two observables should have same length of vector.");
			// 	unsigned int newLength = A.get_length();
			// 	Observable<T> result(newLength);
			// 	for(unsigned int i = 0; i < newLength; ++i) result.append(A.m_obsList[i] + B.m_obsList[i]);
			// 	return result;
  		// }

  		// friend Observable<T> operator*(const Observable<T>& A, const Observable<T>& B) {
			// 	if (A.get_length() != B.get_length()) throw std::invalid_argument("Two observables should have same length of vector.");
			// 	unsigned int newLength = A.get_length();
			// 	Observable<T> result(newLength);
			// 	for(unsigned int i = 0; i < newLength; ++i) result.append(A.m_obsList[i] * B.m_obsList[i]);
			// 	return result;
  		// }
	
	};

	Observable::Observable(obsNames obsName) : m_maxLength(DEFAULT_OBS_LENGTH){
		// Assign the number of Observables
		m_numObs = obsName.size();
		m_obsList.resize(m_numObs);
		// Make a map for accessing a correct observable list
		for (int i=0;i<m_numObs;++i){
			m_obsList[i].reserve(m_maxLength);
			m_obsMap.insert( std::pair< std::string, int > (obsName[i],i) );
		}
	}

	Observable::Observable(obsNames obsName, int length) : m_maxLength(length){
		// Assign the number of Observables
		m_numObs = obsName.size();
		m_obsList.resize(m_numObs);
		// Make a map for accessing a correct observable list
		for (int i=0;i<m_numObs;++i){
			m_obsList[i].reserve(m_maxLength);
			m_obsMap.insert( std::pair< std::string, int > (obsName[i],i) );
		}
	}

	void Observable::append(std::string name, double val){
		// Find Observable by name
		const int idx = m_obsMap.at(name);
		// Append value
		m_obsList[idx].emplace_back(val);
	}

	void Observable::append(obsNames names, std::vector<double> vals){
		// Check if two input variables have same length
		if (names.size() != vals.size()) throw std::invalid_argument("Observable::append() -> Two input variables should have same number of component.");
		if (names.size() != m_numObs) throw std::invalid_argument("Observable::append() -> Input variables have different length with the number of observables.");
		for (int i=0;i<m_numObs;++i){
			// Find index corresponding to name
			const int idx = m_obsMap.at(names[i]);
			// Append value
			m_obsList[idx].emplace_back(vals[i]);
		}
	}
	// template <class T>
	// Observable<T>::Observable() : m_maxLength(DEFAULT_OBS_LENGTH), m_numElem(0) {
	// 	m_obsList.reserve(m_maxLength);
	// };

	// template <class T>
	// Observable<T>::Observable(unsigned int maxLength) : m_maxLength(maxLength), m_numElem(0){
	// 	m_obsList.reserve(m_maxLength);
	// };

	// template <class T>
	// Observable<T>::~Observable(){ std::vector<T>().swap(m_obsList); };

	// template <class T>
	// void Observable<T>::set_length(unsigned int maxLength) { m_maxLength = maxLength; };

	// template <class T>
	// unsigned int Observable<T>::get_length() const { return m_numElem; };


	// template <class T>
	// void Observable<T>::append(T val) {
	// 	m_obsList.emplace_back(val);
	// 	++m_numElem;
	// };

	// template <class T>
	// void Observable<T>::extend(unsigned int length) {
	// 	m_maxLength += length;
	// 	m_obsList.reserve(m_maxLength);
	// };

	const std::map< std::string, int >& Observable::get_obsMap() const {
		return m_obsMap;
	};

	// template <class T>
	const std::vector< std::vector<double> >& Observable::get_obs() const {
		return m_obsList;
	};

	const std::vector<double>& Observable::get_obs(int idx) const {
		return m_obsList[idx];
	};

	const int Observable::get_numObs() const { return m_numObs; };

	const int Observable::get_numElem() const { return m_obsList[0].size(); };

	// template <class T>
	// T Observable<T>::getElement(int idx) const { return m_obsList[idx]; };

	//std::string Observable::get_obsName(const int idx){
	//	return m_obsMap[idx]->key;
	//};

	void Observable::print() const {
		int numElem = m_obsList[0].size();
		for (auto const& x : m_obsMap) std::cout << x.first << " ";
		std::cout << "\n";
		for (int i=0;i<numElem;++i){
			for (auto const& x : m_obsMap) std::cout << m_obsList[x.second][i] << " ";
			std::cout << "\n";
		}
		
	};




}



#endif
