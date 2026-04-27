# rapl-joule-meter
A lightweight C library for fine-grained energy measurement using the Linux RAPL energy_uj interface.



This library provides simple utilities to:

* Read energy consumption counters from the system (`energy_uj`)
* Measure elapsed time with high-resolution timers
* Handle counter wrap-around safely
* Locate RAPL energy files for CPU package and core domains

---

## API

### Energy Reading

```c
uint64_t read_uj(char *path);
```

Reads energy in **microjoules (µJ)** from a given sysfs path.

---

### Timing

```c
double time_s();
```

Returns current time in **seconds** using `CLOCK_MONOTONIC`.

---

### Counter Wrap Handling

```c
uint64_t delta_wrap(uint64_t after, uint64_t before, uint64_t max_range);
```

Computes correct energy difference, handling counter overflow.

---

### Sysfs Paths

```c
char* package_energy_path();
char* core_energy_path();
char* package_max_energy_path();
char* core_max_energy_path();
```

Return sysfs paths for:

* Package energy
* Core energy
* Maximum counter range (for wrap handling)

---

## Example Usage

```c
char *path = package_energy_path();
uint64_t before = read_uj(path);

/* workload */
do_work();

uint64_t after = read_uj(path);

uint64_t delta = after - before;
double energy_j = delta / 1e6;
```

---


## Build
You can simple run the bash script `configure` and pass the path where you want to install the libray and the header file:

```bash
Usage: ./configure [--prefix=INSTALLATION_PATH]
```
***Or***

```bash
cmake -S . -B build
cmake --build build
```
and then nstall:

```bash
cmake --install build
```

---

## Use in Other Projects

With CMake:

```cmake
find_package(Rapl REQUIRED)
target_link_libraries(app PRIVATE rapl::rapl)
```




