#include"rapl.h"

uint64_t read_uj(char*path){
	FILE *file=fopen(path,"r");
	if(!file){
		fprintf(stderr,"fopen failed to read %s: %s\n",path,strerror(errno));
		return 0;
	}
	unsigned long long v=0;
	if(fscanf(file,"%llu",&v)!=1){
		fprintf(stderr,"fscan failed to read %s\n",path);
		return 0;
	}
	fclose(file);
	return (uint64_t)v;
}

double time_s(){
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);
	return (double)ts.tv_sec+1e-9*(double)ts.tv_nsec;
}

uint64_t delta_wrap(uint64_t after, uint64_t before, uint64_t max_range){
	if(after>before)
		return (after-before);
	return ((max_range-before)+after);
}

char* core_energy_path(){
	char*path="/sys/class/powercap/intel-rapl:0:0/energy_uj";
	struct stat st;
	if(stat(path,&st)!=0){
		fprintf(stderr,"core_energy_path %s does not exist",path);
                return 0;
	}
	return path;
}

char* package_energy_path(){
        char*path="/sys/class/powercap/intel-rapl:0/energy_uj";
        struct stat st;
        if(stat(path,&st)!=0){
                fprintf(stderr,"package_energy_path %s does not exist",path);
                return 0;
        }
        return path;
}

char* core_max_energy_path(){
	char*path="/sys/class/powercap/intel-rapl:0:0/energy_uj";
        struct stat st;
        if(stat(path,&st)!=0){
                fprintf(stderr,"core_max_energy_path %s does not exist",path);
                return 0;
        }
        return path;

}
char* package_max_energy_path(){
        char*path="/sys/class/powercap/intel-rapl:0/energy_uj";
        struct stat st;
        if(stat(path,&st)!=0){
                fprintf(stderr,"package_max_energy_path %s does not exist",path);
                return 0;
        }
        return path;

}
