# Geodash-3D Level Editor

## About
This is a level editor for Geodash-3D, a 3D game inspired by the popular mobile game Geometry Dash that goes to the third dimension.

I created Geodash-3D to test my knowledge of OpenGL and this is a level editor I made so that making game levels was easier for me and anyone who wants to create their own custom levels.

## How to use the editor

### Controls
 - Save File - CTRL + E
 - Pause/Unpause - ESC
 - Move around - W,A,S,D
 - Change selected block - Scroll Wheel
 - Move up - Space
 - Move down - Left Shift
 - Destroy block - Left mouse
 - Place block - Right mouse
 - Enter view mode (cannot place blocks) - 1
 - Enter edit mode (can place blocks) - 2

### Import levels to the editor or Export levels to the game
If you want to import a level, go to the `saves` folder and copy and paste the level file inside. Then go to the `path-list.txt` file and add the name of your file to it. To export a level, copy the level you want to export from the `saves` folder in the editor directory and then paste it into the `res/levels` folder in the game directory. Once that is done, edit the `level-list.txt` file in the `res/levels` folder to include the name of the level.

## Compile the project

**DEPENDENCIES:** [glfw](https://github.com/glfw/glfw), [SOIL](https://github.com/littlstar/soil), [glad](https://glad.dav1d.de/), [glm](https://github.com/g-truc/glm)

To compile the project just run the following commands:

**Linux**:

```
cmake -S geodash3-editor -B geodash3-editor/build
cd geodash3-editor/build
make
```

**Windows**:

```
cmake -S geodash3-editor -B geodash3-editor/build
cd geodash3-editor/build
mingw32-make
```

I compiled the game using [mingw-w64](https://github.com/mingw-w64/mingw-w64) for Windows though you might be able to compile it using some other compiler if you do some configuring around though I haven't bothered to try that out.

**MacOS**:

I didn't really take MacOS into account when designing the game and I'm a bit too lazy to figure it out as I don't own a MacBook but it shouldn't be too hard to figure out so if you implement a way to compile it on Mac, then please make a pull request. 

After that, merely run the command `./gdash3-editor` to run the executable and use the editor.

## License
Source Code (includes shaders): GPLv2 or at your choice, any later version. (The code is a tangle of spaghetti but if you do decide to mod the game, I would love to try it out and see what additions/modifications were made)

Assets: Public Domain (CC0)
Use the art for whatever purpose you want to (my art isn't very good but you might find some use for it).

## Other
I don't intend to continue with this project as I've currently lost a decent bit of motivation so feel free to fork this and mod the game to whatever you want it to be. However, if you want to add some features (such as music, sound effects, art, or some other features) feel free to make a pull request.

## Credits
Programming: JLi69 AKA NotJL AKA Nullptr Error

Suggestions: Thornion, FUNDUDZ!
