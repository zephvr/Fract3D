# Fract3D

A projet to render 3D fractal using the raymarching technique written in C++/Boost

## How to install

Install dependencies `boost` and `boost-libs`

### Archlinux
```
sudo pacman -S boost boost-libs
```

Then compile the project
```
make -j8
mkdir render
```

## How to use

Just execute the program
```
./Fract3D
```

## How to configure

Modify file `src/main.cpp` according to your desire. Then built it again.

## TODO

- [ ] JSON like config file
- [ ] Command-line option
- [ ] Implement more fractal figure
- [ ] Give exemple config file for direct result
