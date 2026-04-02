
```
      ___.        __                                          
  ____\_ |__     |__| ____  __ _________  ______ ____   ______
 /  _ \| __ \    |  |/ ___\|  |  \_  __ \/  ___// __ \ /  ___/
(  <_> ) \_\ \   |  \  \___|  |  /|  | \/\___ \\  ___/ \___ \ 
 \____/|___  /\__|  |\___  >____/ |__|  /____  >\___  >____  >
           \/\______|    \/                  \/     \/     \/ 
```

**objcurses** is a minimalistic 3D object viewer that runs in your terminal using `ncurses`. It renders `.obj` models in real time using ASCII characters and a simple rendering pipeline. The project was built from scratch in modern C++20 using up-to-date best practices and a clean modular design, as a personal exploration of low-level graphics programming - without relying on external graphic engines or frameworks.

<p align="center">
  <img src="resources/images/demo.gif" alt="TUI Demo Gif" width="600">
</p>

#Features

- Render `.obj` files directly in terminal
- Real-time camera and directional light control
- Basic color support from `.mtl` material files
- Start animation with consistent auto-rotation
- HUD overlay for additional stats
- Minimal dependencies: C/C++, `ncurses`, math

#Use Cases

<p align="center">
  <img src="resources/images/usage.gif" alt="One Use Case" width="800">
</p>

* Preview 3D files instantly without launching heavy editors
* Generate custom ASCII art for neofetch or terminal splash
* Style CLI tools or games with ASCII-based intros and visuals
* Animate coding workspace with rotating retro-style ASCII models
* Create stylish character-based GIFs from terminal-rendered scenes

#Usage

```bash
objcurses [OPTIONS] <file.obj>
```

## Options

```
-c, --color <theme>  Enable colors support, optional theme
{
    dark | light | transparent
}
-l, --light          Disable light rotation
-a, --animate <deg>  Start with animated object, optional speed [default: 30.0 deg/s]
-z, --zoom <x>       Provide initial zoom [default: 1.0 x]
    --flip           Flip faces winding order
    --invert-x       Flip geometry along X axis
    --invert-y       Flip geometry along Y axis
    --invert-z       Flip geometry along Z axis
-h, --help           Print help
-v, --version        Print version
```

Examples:

```bash
objcurses file.obj                # basic
objcurses -c file.obj             # enable colors
objcurses -c transparent file.obj # set transparent color theme
objcurses -c -a -z 1.5 file.obj   # start animation with zoom 1.5 x
objcurses -c -a 10 file.obj       # start animation with speed 10.0 deg/s
objcurses -c --invert-z file.obj  # flip z axis if blender model 
```

## Controls

Supports arrow keys, WASD, and Vim-style navigation:

```
←, h, a            Rotate left
→, l, d            Rotate right
↑, k, w            Rotate up
↓, j, s            Rotate down
+, i               Zoom in
-, o               Zoom out
Tab                Toggle HUD
q                  Quit
```

#Installation

Latest release available [here](https://github.com/admtrv/objcurses/releases). Replace `<version>` with the actual release version, e.g. `1.2.3`.

## Manual (build from source)

To manually compile and install `objcurses`, follow these steps:

### Install Dependencies

Make sure you have CMake and a C++ compiler installed:

```bash
sudo apt update
sudo apt install cmake g++ libncurses6 libtinfo6 -y
```

### Clone the Repository

```bash
git clone https://github.com/admtrv/objcurses
cd objcurses
```

### Compile the Program

```bash
mkdir cmake-build-release
cd cmake-build-release
cmake ..
make
```

### Install for Global Use (optional)

```bash
sudo make install
```

---

## From `.tar.gz`

To install `objcurses` from the binary archive:

```bash
tar -xzvf objcurses-<version>-linux.tar.gz
cd objcurses-<version>-linux
sudo mv objcurses /usr/local/bin/
sudo chmod +x /usr/local/bin/objcurses
```

---

## From `.deb`

For Debian-based distributions (Ubuntu, Mint, etc.), use:

```bash
sudo dpkg -i objcurses-<version>-linux.deb
```

To uninstall:

```bash
sudo dpkg -r objcurses
```

---

## Verify Installation

```bash
which objcurses
objcurses --help
```

You should now be able to use `objcurses` from anywhere in your terminal.
