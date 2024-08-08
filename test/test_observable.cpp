#include "Jlib.h"
#include <random>
#include <chrono>
#include <omp.h>


int main(int argc, char **argv)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> normal(0.,1.);

  omp_set_num_threads(8);


		
	int N=atoi(argv[1]);
	int Nexec = 100;

	Jlib::Observable<double> exectime(Nexec);
	Jlib::Observable<double> result(Nexec);

	for (int exec=0;exec<Nexec;++exec){
		// Fill the data
		Jlib::Observable<double> obs1(N);
		for (int i=0;i<N;++i){
			obs1.append(std::abs(0.1*normal(gen)));
		}
		auto start = std::chrono::high_resolution_clock::now();
		double m = Jlib::Statistics<double>::second_moment(obs1,false);
    auto end = std::chrono::high_resolution_clock::now();
		result.append(m);
    std::chrono::duration<double> duration = end - start;
		//std::cout << duration.count() << "\n";
		exectime.append(duration.count());
	}

	std::cout << N << " " << Jlib::Statistics<double>::mean(exectime) << " " << Jlib::Statistics<double>::second_moment(exectime,false) << "\n";

	//obs2.print();
	
	return 0;
}
