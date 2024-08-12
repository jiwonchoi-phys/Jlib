#ifndef __FILEIO_H__
#define __FILEIO_H__

namespace Jlib{
	void writeObs(const std::string& fname, const Observable& obs, std::ios_base::openmode mode = std::ios::out) {
		// Get data from input observable
		const auto& data = obs.get_obs();
		const auto& datamap = obs.get_obsMap();
		const auto& length = data[0].size();
		// Open file with defined mode
		std::ofstream output;
		output.open(fname.c_str(),mode);
		// Write header file if file was not existed
		//if ( output.peek() == std::ifstream::traits_type::eof() ){
		//	std::cout << "# ";
		//	for (auto const& x : m_obsMap) std::cout << x.first << " ";
		//	std::cout << "\n";
		//}
		for (int i=0;i<length;++i){
			for (auto const& x : datamap) output << data[x.second][i] << " ";
			output << "\n";
		}
		output.close();
	}
	//
	// template <class T>
	// void writeObs(const std::string& fname, const Observable<T>& obs1, const Observable<T>& obs2, std::ios_base::openmode mode = std::ios::out) {
	// 	if (obs1.get_length() != obs2.get_length()) throw std::invalid_argument("Two observables should have same length of vector.");
	// 	std::ofstream output;
	// 	output.open(fname.c_str(),mode);
	// 	const auto& data1 = obs1.get_obs();
	// 	const auto& data2 = obs2.get_obs();
	// 	const unsigned int length = obs1.get_length();
	// 	for (unsigned int i=0; i<length; ++i) output << data1[i] << " " << data2[i] << "\n";
	// 	output.close();
}

#endif
