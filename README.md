# Adrift

## A text based puzzle game inspired by Zork.

Destined for Alpha Centauri, something unexpected wakes you from your cryopod.  
The success of the mission depends on your ability to fix the ship.

I wrote this during my first year as a CS student to gain familiarity with GitHub and C++

![adrift gif](./screenshots/adrift_gif.gif)

## Run the game:

Compile and build:

```bash
git clone https://github.com/mitchfen/Adrift.git
cd Adrift
g++ -o adrift ./src/main.cpp
./adrift
```

Pull the <10mb Docker image:

```bash
docker run -it --rm ghcr.io/mitchfen/adrift:latest
```

Or download the [Windows release](https://github.com/mitchfen/Adrift/releases/tag/v1.0).
