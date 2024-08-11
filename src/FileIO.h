#ifndef __FILEIO_H__
#define __FILEIO_H__

namespace Jlib{
	namespace FileIO{
		template <class T>
		void writeObs(const std::string& fname, const Observable<T>& obs, std::ios_base::openmode mode = std::ios::out) {
			std::ofstream output;
			output.open(fname.c_str(),mode);
			const auto& data = obs.get_obs();
			const unsigned int length = data.size();	
			for (unsigned int i=0; i<length; ++i) output << data[i] << "\n";
			output.close();
		}
}

#endif
