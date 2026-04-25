#pragma once
#ifndef RAPL_H
#define RAPL_H
#define _GNU_SOURCE

#include<errno.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include<sys/stat.h>
#include <inttypes.h>
#include<string.h>


uint64_t read_uj(char*path);
uint64_t delta_wrap(uint64_t after, uint64_t before, uint64_t max_range);
char* package_energy_path();
char* core_energy_path();
char* core_max_energy_path();
char* package_max_energy_path();

#endif
