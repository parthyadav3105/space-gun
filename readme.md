# SPACE-GUN
	This is a a simple remake of traditional space invaders game.

	The code is open source. The game is designed to be cross platform.

### Controls
		**LEFT arrow key** to move left
		**RIGHT arrow key** to move right
		**SPACE** to fire

### Binary file
	Binary executable for windows is stored in **bin** folder.
	The executable has been tested in windows 7,windows 10.

### Compiling source code
	The source code was wrote and tested in windows 7 in codeblocks ide using the default g++ compiler.
	You may not face any problem in compiling if you use the codeblock project file stored in "project code block" folder.
	
	If you are compiling on some other ide or directly in terminal then you would have to link the following static libraries stored in lib folder.
	"glew32s.lib"	"libglfw3dll.a"		"libglfw3.a"	"libSOIL.a"		"freetype.lib"	"libopengl32.a" "OpenAL32.lib"
	and give following linker options
	"-lmingw32" 
	
	If you are compiling on linux or mac then you will have to get libraries for that platform first.

	DLLs involved
	glfw3.dll freetype6.dll OpenAL32.dll zlib1.dll

### Libs and frameworks used
	opengl glfw soil freetype openal glm 

### Files not made by me
	audio file: "gunshot.wav","lasergun.wav"  
	font: "font.ttf" 
	images: "background.png" "ball.png" "ball1.png" "ball2.png" "bullet.png" "bullet2.png" "cursor.png" "drone1.png" "ship.png"

CREDITS:
	https://learnopengl.com/

### Extra info
	The game runs in full-screen mode and uses primary monitor.
	If sounds effects are not working then that means openAL is not installed on the system.
	


You can find me on twitter: [Asha_Seema_](https://twitter.com/Asha_Seema_)
