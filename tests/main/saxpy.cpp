#include<stdlib.h>
#include<iostream>
extern "C" {
	#include<rapl.h>
}

#include<vector>

constexpr size_t N=1000000;
constexpr  float A=2.5f;

int main(void){
	char*pkg_path=package_energy_path();
	char*pkg_max_path=package_max_energy_path();
	char*core_path=core_energy_path();
	char*core_max_path=core_max_energy_path();
	
	if(!pkg_path||!pkg_max_path){
		std::cerr<<"Package RAPL not available\n";
		return EXIT_FAILURE;
	}
	std::vector<float> x(N,1.0f);
	std::vector<float> y(N,2.0f);
	
	uint64_t pkg_before=read_uj(pkg_path);
	uint64_t pkg_max=read_uj(pkg_max_path);
	uint64_t core_before=0,core_max=0;
	
	if (core_path && core_max_path) {
        	core_before=read_uj(core_path);
        	core_max=read_uj(core_max_path);
    	}
	
	double t0=time_s();
	
	for(int i=0;i<N;i++)
		y[i]=A*x[i]+y[i];
	
	double t1=time_s();

    	uint64_t pkg_after=read_uj(pkg_path);
	uint64_t core_after=0;
    	if(core_path&&core_max_path){
        	core_after=read_uj(core_path);
    	}

    	uint64_t pkg_delta=delta_wrap(pkg_after,pkg_before,pkg_max);
    	double pkg_energy=static_cast<double>(pkg_delta)/1e6;

    	double elapsed=t1-t0;	
	
	double checksum=0.0;
    	for(const auto&v:y) {
        	checksum += v;
    	}
	
	std::cout << "SAXPY test\n";
    	std::cout<< "N              : " <<N<<"\n";
    	std::cout<< "Elapsed time   : " <<elapsed<<" s\n";
    	std::cout<< "Package energy : " <<pkg_energy<<" J\n";
    	std::cout<< "Package power  : " <<pkg_energy/elapsed<<" W\n";
    	std::cout<< "Checksum       : " <<checksum<< "\n";

    	if(core_path && core_max_path){
        	uint64_t core_delta =delta_wrap(core_after, core_before, core_max);
        	double core_energy=static_cast<double>(core_delta)/1e6;

        	std::cout<<"Core energy    : "<< core_energy<<" J\n";
        	std::cout<<"Core power     : "<< core_energy/elapsed<<" W\n";
    	}

	
	return 0;
}
